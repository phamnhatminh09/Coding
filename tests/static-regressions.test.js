const assert = require('node:assert/strict');
const { execFileSync, spawnSync } = require('node:child_process');
const fs = require('node:fs');
const os = require('node:os');
const path = require('node:path');
const test = require('node:test');

const repoRoot = path.resolve(__dirname, '..');

function read(relativePath) {
  return fs.readFileSync(path.join(repoRoot, relativePath), 'utf8');
}

function gitFiles(pattern) {
  const output = execFileSync('git', ['ls-files', '-z', pattern], {
    cwd: repoRoot,
    encoding: 'buffer',
  });

  return output
    .toString('utf8')
    .split('\0')
    .filter(Boolean);
}

function run(command, args, options = {}) {
  const result = spawnSync(command, args, {
    cwd: repoRoot,
    encoding: 'utf8',
    ...options,
  });

  assert.equal(
    result.status,
    0,
    `${command} ${args.join(' ')} failed\nstdout:\n${result.stdout}\nstderr:\n${result.stderr}`,
  );

  return result;
}

test('tracked JavaScript files parse', () => {
  for (const file of gitFiles('*.js')) {
    const result = spawnSync(process.execPath, ['--check', file], {
      cwd: repoRoot,
      encoding: 'utf8',
    });

    assert.equal(
      result.status,
      0,
      `${file} failed node --check\nstdout:\n${result.stdout}\nstderr:\n${result.stderr}`,
    );
  }
});

test('Model S configurator submits Model S checkout data', () => {
  const html = read('hk2/order-model-s.html');

  assert.match(html, /<h1>Model S<\/h1>/);
  assert.match(html, /Vehicle price[\s\S]*<strong>\$62,990<\/strong>/);
  assert.match(html, /data-order-model="Model S"/);
  assert.match(html, /data-order-trim="Standard Wheels"/);
  assert.match(html, /data-order-price="\$62,990"/);
  assert.doesNotMatch(html, /data-order-model="Model 3"/);
});

test('payment cart and consultation success render user data as text', () => {
  const paymentScript = read('hk2/script.js');
  const consultationScript = read('A/LMS ĐH-CĐ - Antigravity/script.js');
  const pollScript = read('html/script.js');

  assert.doesNotMatch(paymentScript, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
  assert.match(paymentScript, /paymentCartItems\.replaceChildren\(\)/);
  assert.match(paymentScript, /title\.textContent = item\.model/);
  assert.match(paymentScript, /trim\.textContent = item\.trim/);

  assert.doesNotMatch(consultationScript, /formSuccessBlock\.innerHTML\s*=/);
  assert.match(consultationScript, /textContent: fullname/);
  assert.match(consultationScript, /textContent: phone/);
  assert.match(consultationScript, /textContent: email/);

  assert.doesNotMatch(pollScript, /pollResult\.innerHTML\s*=/);
  assert.match(pollScript, /JSON\.parse\(localStorage\.getItem\('pollCounts'\)\)/);
  assert.match(pollScript, /catch \(error\)/);
});

test('ams_jump bundled samples do not crash and match expected answers', () => {
  const tmpDir = fs.mkdtempSync(path.join(os.tmpdir(), 'ams-jump-'));
  const binary = path.join(tmpDir, 'ams_jump');

  run('g++', [
    '-std=c++17',
    '-Wall',
    '-Wextra',
    '-fsanitize=address,undefined',
    '-g',
    'C++/2025/ams_jump.cpp',
    '-o',
    binary,
  ]);

  for (const sample of [1, 2]) {
    const input = fs.readFileSync(path.join(repoRoot, `C++/2025/ams_jump_${sample}.in`), 'utf8');
    const expected = fs.readFileSync(path.join(repoRoot, `C++/2025/ams_jump_${sample}.ans`), 'utf8').trim();
    const result = run(binary, [], { input });

    assert.equal(result.stdout.trim(), expected);
  }
});

test('tongbang max-size bundled sample completes without materializing the row', () => {
  const tmpDir = fs.mkdtempSync(path.join(os.tmpdir(), 'tongbang-'));
  const binary = path.join(tmpDir, 'tongbang');

  run('g++', [
    '-std=c++17',
    '-O2',
    '-Wall',
    '-Wextra',
    'C++/2025/tongbang.cpp',
    '-o',
    binary,
  ]);

  const input = fs.readFileSync(path.join(repoRoot, 'C++/2025/tongbang_6.in'), 'utf8');
  const expected = fs.readFileSync(path.join(repoRoot, 'C++/2025/tongbang_6.ans'), 'utf8').trim();
  const result = spawnSync(binary, [], {
    cwd: repoRoot,
    encoding: 'utf8',
    input,
    timeout: 2000,
  });

  assert.equal(result.signal, null, `tongbang timed out or was killed with ${result.signal}`);
  assert.equal(result.status, 0, result.stderr);
  assert.equal(result.stdout.trim(), expected);
});
