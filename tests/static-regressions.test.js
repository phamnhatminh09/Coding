const assert = require('node:assert/strict');
const { execFileSync } = require('node:child_process');
const fs = require('node:fs');
const os = require('node:os');
const path = require('node:path');
const test = require('node:test');

const repoRoot = path.resolve(__dirname, '..');

function read(relPath) {
  return fs.readFileSync(path.join(repoRoot, relPath), 'utf8');
}

test('tracked JavaScript files parse successfully', () => {
  const files = execFileSync('git', ['ls-files', '-z', '--', '*.js'], {
    cwd: repoRoot,
  })
    .toString('utf8')
    .split('\0')
    .filter(Boolean);

  for (const file of files) {
    execFileSync(process.execPath, ['--check', file], {
      cwd: repoRoot,
      stdio: 'pipe',
    });
  }
});

test('Model S configurator stores Model S checkout data', () => {
  const html = read('hk2/order-model-s.html');
  assert.match(html, /<h1>Model S<\/h1>/);
  assert.match(html, /<strong>\$62,990<\/strong>/);
  assert.match(html, /data-order-model="Model S"/);
  assert.match(html, /data-order-trim="Standard Wheels"/);
  assert.match(html, /data-order-price="\$62,990"/);
  assert.match(html, /data-order-image="models\.jpg"/);
  assert.doesNotMatch(html, /data-order-model="Model 3"/);
});

test('stored cart and poll data are not rendered as HTML', () => {
  const teslaScript = read('hk2/script.js');
  assert.doesNotMatch(teslaScript, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
  assert.match(teslaScript, /paymentCartItems\.replaceChildren\(\)/);
  assert.match(teslaScript, /title\.textContent = String\(item\.model \|\| "Model"\)/);
  assert.match(teslaScript, /trim\.textContent = String\(item\.trim \|\| "Base"\)/);

  const pollScript = read('html/script.js');
  assert.doesNotMatch(pollScript, /pollResult\.innerHTML\s*=/);
  assert.match(pollScript, /normalizePollCounts/);
  assert.match(pollScript, /pollResult\.replaceChildren\(\)/);
});

test('consultation form echoes submitted fields with text nodes', () => {
  const script = read('A/LMS ĐH-CĐ - Antigravity/script.js');
  assert.doesNotMatch(script, /formSuccessBlock\.innerHTML\s*=/);
  assert.match(script, /strong\.textContent = text/);
});

test('C++ samples avoid the ams_jump crash and tongbang max-input hang', () => {
  const tmpDir = fs.mkdtempSync(path.join(os.tmpdir(), 'coding-regressions-'));
  const amsBin = path.join(tmpDir, 'ams_jump');
  const tongbangBin = path.join(tmpDir, 'tongbang');

  execFileSync('g++', [
    '-std=c++17',
    '-Wall',
    '-Wextra',
    '-fsanitize=address,undefined',
    'C++/2025/ams_jump.cpp',
    '-o',
    amsBin,
  ], { cwd: repoRoot, stdio: 'pipe' });

  execFileSync('g++', [
    '-std=c++17',
    '-Wall',
    '-Wextra',
    'C++/2025/tongbang.cpp',
    '-o',
    tongbangBin,
  ], { cwd: repoRoot, stdio: 'pipe' });

  for (const sample of ['1', '2']) {
    const actual = execFileSync(amsBin, {
      input: read(`C++/2025/ams_jump_${sample}.in`),
      encoding: 'utf8',
      timeout: 2000,
    }).trim();
    const expected = read(`C++/2025/ams_jump_${sample}.ans`).trim();
    assert.equal(actual, expected);
  }

  for (const sample of ['1', '2', '3', '4', '5', '6']) {
    const actual = execFileSync(tongbangBin, {
      input: read(`C++/2025/tongbang_${sample}.in`),
      encoding: 'utf8',
      timeout: 2000,
    }).trim();
    const expected = read(`C++/2025/tongbang_${sample}.ans`).trim();
    assert.equal(actual, expected);
  }
});
