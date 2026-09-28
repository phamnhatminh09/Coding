const assert = require('node:assert/strict');
const { spawnSync } = require('node:child_process');
const fs = require('node:fs');
const os = require('node:os');
const path = require('node:path');
const test = require('node:test');

const repoRoot = path.resolve(__dirname, '..');

const readRepoFile = (relativePath) =>
  fs.readFileSync(path.join(repoRoot, relativePath), 'utf8');

const normalizeOutput = (value) => value.trim().replace(/\s+/g, ' ');

test('tracked JavaScript files parse successfully', () => {
  const jsFiles = [
    'html/script.js',
    'hk2/script.js',
    'hk2/1.js',
    'C/LMS AI/script.js',
    'C/LMS ĐH-CĐ - Cursor/js/main.js',
    'C/LMS Lite - Cursor/js/main.js',
    'A/LMS Lite - Antigravity/script.js',
    'A/LMS AI/script.js',
    'A/LMS ĐH-CĐ - Antigravity/script.js',
  ];

  for (const jsFile of jsFiles) {
    const result = spawnSync(process.execPath, ['--check', jsFile], {
      cwd: repoRoot,
      encoding: 'utf8',
    });

    assert.equal(
      result.status,
      0,
      `${jsFile} failed syntax check:\n${result.stderr || result.stdout}`
    );
  }
});

test('Model S configurator submits Model S cart metadata', () => {
  const source = readRepoFile('hk2/order-model-s.html');

  assert.match(source, /<h1>Model S<\/h1>/);
  assert.match(source, /<strong>\$62,990<\/strong>/);
  assert.match(source, /data-order-model="Model S"/);
  assert.match(source, /data-order-trim="Standard Wheels"/);
  assert.match(source, /data-order-price="\$62,990"/);
  assert.match(source, /data-order-image="models\.jpg"/);
  assert.doesNotMatch(source, /data-order-model="Model 3"/);
});

test('payment cart does not interpolate stored cart fields as HTML', () => {
  const source = readRepoFile('hk2/script.js');

  assert.match(source, /paymentCartItems\.replaceChildren\(\)/);
  assert.doesNotMatch(source, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
  assert.doesNotMatch(source, /\$\{\s*item\.(?:image|model|trim)/);
});

test('consultation success message renders submitted fields as text nodes', () => {
  const source = readRepoFile('A/LMS ĐH-CĐ - Antigravity/script.js');

  assert.match(source, /formSuccessBlock\.replaceChildren/);
  assert.doesNotMatch(
    source,
    /formSuccessBlock\.innerHTML\s*=\s*`[\s\S]*\$\{\s*(?:fullname|phone|email)\s*\}/
  );
});

const compileCpp = (relativePath, extraFlags = []) => {
  const tempDir = fs.mkdtempSync(path.join(os.tmpdir(), 'coding-regression-'));
  const binary = path.join(tempDir, path.basename(relativePath, '.cpp'));
  const result = spawnSync(
    'g++',
    ['-std=c++17', '-Wall', '-Wextra', ...extraFlags, relativePath, '-o', binary],
    { cwd: repoRoot, encoding: 'utf8', timeout: 15000 }
  );

  assert.equal(
    result.status,
    0,
    `${relativePath} failed to compile:\n${result.stderr || result.stdout}`
  );

  return binary;
};

const runBinary = (binary, input, timeout = 5000) => {
  const result = spawnSync(binary, {
    input,
    encoding: 'utf8',
    timeout,
  });

  assert.equal(
    result.status,
    0,
    `${path.basename(binary)} failed:\n${result.stderr || result.stdout}`
  );

  return result.stdout;
};

test('ams_jump handles bundled samples without out-of-bounds crashes', () => {
  const binary = compileCpp('C++/2025/ams_jump.cpp', ['-fsanitize=address,undefined']);

  for (const sample of [1, 2]) {
    const input = readRepoFile(`C++/2025/ams_jump_${sample}.in`);
    const expected = readRepoFile(`C++/2025/ams_jump_${sample}.ans`);
    assert.equal(normalizeOutput(runBinary(binary, input)), normalizeOutput(expected));
  }
});

test('tongbang handles bundled max-size sample without materializing n values', () => {
  const binary = compileCpp('C++/2025/tongbang.cpp');
  const input = readRepoFile('C++/2025/tongbang_6.in');
  const expected = readRepoFile('C++/2025/tongbang_6.ans');

  assert.equal(normalizeOutput(runBinary(binary, input, 2000)), normalizeOutput(expected));
});
