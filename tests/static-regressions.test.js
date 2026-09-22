const assert = require('node:assert/strict');
const { spawnSync } = require('node:child_process');
const fs = require('node:fs');
const os = require('node:os');
const path = require('node:path');
const test = require('node:test');

const repoRoot = path.resolve(__dirname, '..');

function readRepoFile(...parts) {
  return fs.readFileSync(path.join(repoRoot, ...parts), 'utf8');
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
    `${command} ${args.join(' ')} failed\nSTDOUT:\n${result.stdout}\nSTDERR:\n${result.stderr}`
  );

  return result.stdout;
}

function normalizedWords(text) {
  return text.trim().split(/\s+/).filter(Boolean);
}

test('tracked JavaScript files parse successfully', () => {
  const gitOutput = spawnSync('git', ['ls-files', '-z', '--', '*.js'], {
    cwd: repoRoot,
    encoding: 'buffer',
  });
  assert.equal(gitOutput.status, 0, gitOutput.stderr.toString('utf8'));

  const files = gitOutput.stdout.toString('utf8').split('\0').filter(Boolean);
  assert.ok(files.length > 0, 'expected tracked JavaScript files');

  for (const file of files) {
    run(process.execPath, ['--check', file]);
  }
});

test('static pages avoid known high-impact unsafe sinks', () => {
  const liteMain = readRepoFile('C', 'LMS Lite - Cursor', 'js', 'main.js');
  assert.doesNotMatch(liteMain, /navToggle\?\.[^\n;]+\.className\s*=/);

  const antigravityMain = readRepoFile('A', 'LMS ĐH-CĐ - Antigravity', 'script.js');
  assert.doesNotMatch(antigravityMain, /formSuccessBlock\.innerHTML\s*=\s*`/);
  assert.match(antigravityMain, /nameStrong\.textContent = fullname/);
  assert.match(antigravityMain, /phoneStrong\.textContent = phone/);
  assert.match(antigravityMain, /emailStrong\.textContent = email/);

  const teslaScript = readRepoFile('hk2', 'script.js');
  assert.match(teslaScript, /parsed\.filter\(\(item\) => item && typeof item === "object" && !Array\.isArray\(item\)\)/);
  assert.doesNotMatch(teslaScript, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
  assert.match(teslaScript, /paymentCartItems\.replaceChildren\(\)/);
  assert.match(teslaScript, /title\.textContent = item\.model/);
  assert.match(teslaScript, /trim\.textContent = item\.trim/);
});

test('Model S configurator submits Model S checkout metadata', () => {
  const modelSOrder = readRepoFile('hk2', 'order-model-s.html');
  assert.match(modelSOrder, /<h1>Model S<\/h1>/);
  assert.match(modelSOrder, /<strong>\$62,990<\/strong>/);
  assert.match(modelSOrder, /data-order-model="Model S"/);
  assert.match(modelSOrder, /data-order-trim="Standard Wheels"/);
  assert.match(modelSOrder, /data-order-price="\$62,990"/);
  assert.match(modelSOrder, /data-order-image="models\.jpg"/);
});

const hasGpp = spawnSync('g++', ['--version'], { encoding: 'utf8' }).status === 0;

test(
  'C++ samples run under sanitizers without crashes or max-size hangs',
  { skip: hasGpp ? false : 'g++ is not available' },
  () => {
    const buildDir = fs.mkdtempSync(path.join(os.tmpdir(), 'static-regressions-'));
    const asanEnv = {
      ...process.env,
      ASAN_OPTIONS: [process.env.ASAN_OPTIONS, 'detect_leaks=0'].filter(Boolean).join(':'),
    };

    const amsJumpExe = path.join(buildDir, 'ams_jump');
    run('g++', [
      '-std=c++17',
      '-Wall',
      '-Wextra',
      '-fsanitize=address,undefined',
      '-O1',
      '-g',
      path.join('C++', '2025', 'ams_jump.cpp'),
      '-o',
      amsJumpExe,
    ]);

    for (const sample of ['1', '2']) {
      const input = readRepoFile('C++', '2025', `ams_jump_${sample}.in`);
      const expected = normalizedWords(readRepoFile('C++', '2025', `ams_jump_${sample}.ans`));
      const result = spawnSync(amsJumpExe, [], {
        input,
        encoding: 'utf8',
        env: asanEnv,
        timeout: 5000,
      });
      assert.equal(result.status, 0, result.stderr);
      assert.deepEqual(normalizedWords(result.stdout), expected);
    }

    const tongBangExe = path.join(buildDir, 'tongbang');
    run('g++', [
      '-std=c++17',
      '-Wall',
      '-Wextra',
      '-fsanitize=address,undefined',
      '-O1',
      '-g',
      path.join('C++', '2025', 'tongbang.cpp'),
      '-o',
      tongBangExe,
    ]);

    const input = readRepoFile('C++', '2025', 'tongbang_6.in');
    const expected = normalizedWords(readRepoFile('C++', '2025', 'tongbang_6.ans'));
    const result = spawnSync(tongBangExe, [], {
      input,
      encoding: 'utf8',
      env: asanEnv,
      timeout: 5000,
    });
    assert.equal(result.status, 0, result.stderr);
    assert.deepEqual(normalizedWords(result.stdout), expected);
  }
);
