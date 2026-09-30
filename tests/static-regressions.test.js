const assert = require('node:assert/strict');
const { execFileSync } = require('node:child_process');
const { mkdtempSync, readFileSync } = require('node:fs');
const { tmpdir } = require('node:os');
const path = require('node:path');
const test = require('node:test');

const repoRoot = path.resolve(__dirname, '..');

function read(relativePath) {
  return readFileSync(path.join(repoRoot, relativePath), 'utf8');
}

function gitFiles(pattern) {
  const output = execFileSync('git', ['ls-files', '-z', pattern], {
    cwd: repoRoot,
  });
  return output.toString('utf8').split('\0').filter(Boolean);
}

function normalizeOutput(value) {
  return String(value).trim().replace(/\s+/g, ' ');
}

test('tracked JavaScript files parse successfully', () => {
  for (const file of gitFiles('*.js')) {
    assert.doesNotThrow(
      () => execFileSync('node', ['--check', file], { cwd: repoRoot, stdio: 'pipe' }),
      `${file} should pass node --check`,
    );
  }
});

test('payment cart renders stored cart fields without HTML interpolation', () => {
  const source = read('hk2/script.js');

  assert.doesNotMatch(source, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
  assert.doesNotMatch(source, /\$\{item\.(?:image|model|trim)/);
});

test('Model S configurator submits Model S checkout metadata', () => {
  const source = read('hk2/order-model-s.html');

  assert.match(source, /<h1>Model S<\/h1>/);
  assert.match(source, /<strong>\$62,990<\/strong>/);
  assert.match(source, /data-order-model="Model S"/);
  assert.match(source, /data-order-trim="Standard Wheels"/);
  assert.match(source, /data-order-price="\$62,990"/);
  assert.match(source, /data-order-image="models\.jpg"/);
});

test('consultation form success message does not interpolate submitted fields as HTML', () => {
  const source = read('A/LMS ĐH-CĐ - Antigravity/script.js');

  assert.doesNotMatch(source, /formSuccessBlock\.innerHTML\s*=/);
  assert.doesNotMatch(source, /\$\{(?:fullname|phone|email)\}/);
});

test('ams_jump matches bundled samples without sanitizer failures', () => {
  const buildDir = mkdtempSync(path.join(tmpdir(), 'ams-jump-'));
  const binary = path.join(buildDir, 'ams_jump');
  execFileSync('g++', [
    '-std=c++17',
    '-Wall',
    '-Wextra',
    '-fsanitize=address,undefined',
    '-g',
    path.join(repoRoot, 'C++/2025/ams_jump.cpp'),
    '-o',
    binary,
  ]);

  for (const input of gitFiles('C++/2025/ams_jump_*.in')) {
    const expected = read(input.replace(/\.in$/, '.ans'));
    const actual = execFileSync(binary, {
      input: read(input),
      timeout: 2000,
      env: { ...process.env, ASAN_OPTIONS: 'detect_leaks=0' },
    });
    assert.equal(normalizeOutput(actual), normalizeOutput(expected), input);
  }
});

test('tongbang matches bundled samples including max-size input promptly', () => {
  const buildDir = mkdtempSync(path.join(tmpdir(), 'tongbang-'));
  const binary = path.join(buildDir, 'tongbang');
  execFileSync('g++', [
    '-std=c++17',
    '-Wall',
    '-Wextra',
    '-O2',
    path.join(repoRoot, 'C++/2025/tongbang.cpp'),
    '-o',
    binary,
  ]);

  for (const input of gitFiles('C++/2025/tongbang_*.in')) {
    const expected = read(input.replace(/\.in$/, '.ans'));
    const actual = execFileSync(binary, {
      input: read(input),
      timeout: 2000,
    });
    assert.equal(normalizeOutput(actual), normalizeOutput(expected), input);
  }
});
