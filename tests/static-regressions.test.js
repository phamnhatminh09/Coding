const assert = require('node:assert/strict');
const fs = require('node:fs');
const os = require('node:os');
const path = require('node:path');
const { execFileSync, spawnSync } = require('node:child_process');
const test = require('node:test');

const repoRoot = path.resolve(__dirname, '..');

function readRepoFile(...segments) {
  return fs.readFileSync(path.join(repoRoot, ...segments), 'utf8');
}

function run(command, args, options = {}) {
  return execFileSync(command, args, {
    cwd: repoRoot,
    encoding: 'utf8',
    stdio: ['ignore', 'pipe', 'pipe'],
    ...options,
  });
}

function runWithInput(command, args, input, options = {}) {
  return execFileSync(command, args, {
    cwd: repoRoot,
    input,
    encoding: 'utf8',
    stdio: ['pipe', 'pipe', 'pipe'],
    ...options,
  });
}

test('tracked JavaScript files parse successfully', () => {
  const files = run('git', ['ls-files', '-z', '*.js'])
    .split('\0')
    .filter(Boolean);

  for (const file of files) {
    assert.doesNotThrow(() => {
      run('node', ['--check', file]);
    }, `${file} should pass node --check`);
  }
});

test('Model S checkout metadata matches the Model S product', () => {
  const html = readRepoFile('hk2', 'order-model-s.html');

  assert.match(html, /<h1>Model S<\/h1>/);
  assert.match(html, /data-order-model="Model S"/);
  assert.match(html, /data-order-trim="Standard Wheels"/);
  assert.match(html, /data-order-price="\$62,990"/);
  assert.match(html, /data-order-image="models\.jpg"/);
  assert.doesNotMatch(html, /data-order-model="Model 3"/);
});

test('submitted consultation fields are not interpolated into HTML', () => {
  const script = readRepoFile('A', 'LMS ĐH-CĐ - Antigravity', 'script.js');

  assert.doesNotMatch(script, /formSuccessBlock\.innerHTML/);
  assert.match(script, /strong\.textContent = fullname/);
  assert.match(script, /strong\.textContent = phone/);
  assert.match(script, /strong\.textContent = email/);
});

test('payment cart renders localStorage values as text nodes', () => {
  const script = readRepoFile('hk2', 'script.js');

  assert.doesNotMatch(script, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
  assert.doesNotMatch(script, /\$\{item\.(model|trim|image)/);
  assert.match(script, /model\.textContent = item\.model/);
  assert.match(script, /trim\.textContent = item\.trim/);
  assert.match(script, /image\.src = item\.image/);
});

const hasGpp = spawnSync('g++', ['--version'], { stdio: 'ignore' }).status === 0;

test('ams_jump bundled samples run without sanitizer failures', { skip: hasGpp ? false : 'g++ is not available' }, () => {
  const tmpDir = fs.mkdtempSync(path.join(os.tmpdir(), 'ams-jump-'));
  const binary = path.join(tmpDir, 'ams_jump');

  run('g++', ['-std=c++17', '-Wall', '-Wextra', '-fsanitize=address,undefined', '-O1', 'C++/2025/ams_jump.cpp', '-o', binary]);

  for (const sample of ['1', '2']) {
    const input = readRepoFile('C++', '2025', `ams_jump_${sample}.in`);
    const expected = readRepoFile('C++', '2025', `ams_jump_${sample}.ans`).trim();
    const actual = runWithInput(binary, [], input, { timeout: 5000 }).trim();
    assert.equal(actual, expected);
  }
});

test('tongbang bundled samples complete within the timeout', { skip: hasGpp ? false : 'g++ is not available' }, () => {
  const tmpDir = fs.mkdtempSync(path.join(os.tmpdir(), 'tongbang-'));
  const binary = path.join(tmpDir, 'tongbang');

  run('g++', ['-std=c++17', '-Wall', '-Wextra', '-O2', 'C++/2025/tongbang.cpp', '-o', binary]);

  for (const sample of ['1', '2', '3', '4', '5', '6']) {
    const input = readRepoFile('C++', '2025', `tongbang_${sample}.in`);
    const expected = readRepoFile('C++', '2025', `tongbang_${sample}.ans`).trim();
    const actual = runWithInput(binary, [], input, { timeout: 5000 }).trim();
    assert.equal(actual, expected);
  }
});
