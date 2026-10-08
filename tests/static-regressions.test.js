const assert = require('node:assert/strict');
const { execFileSync } = require('node:child_process');
const { mkdtempSync, readFileSync, rmSync } = require('node:fs');
const { tmpdir } = require('node:os');
const path = require('node:path');
const test = require('node:test');

const repoRoot = path.resolve(__dirname, '..');

function gitFiles(pattern) {
  return execFileSync('git', ['ls-files', '-z', pattern], { cwd: repoRoot })
    .toString('utf8')
    .split('\0')
    .filter(Boolean);
}

function readRepoFile(filePath) {
  return readFileSync(path.join(repoRoot, filePath), 'utf8');
}

function compileCpp(sourcePath, outputPath) {
  execFileSync(
    'g++',
    [
      '-std=c++17',
      '-Wall',
      '-Wextra',
      '-fsanitize=address,undefined',
      path.join(repoRoot, sourcePath),
      '-o',
      outputPath,
    ],
    { cwd: repoRoot, stdio: 'pipe', timeout: 30_000 },
  );
}

function normalizeOutput(output) {
  return output.trim().replace(/\s+/g, ' ');
}

test('tracked JavaScript files parse', () => {
  for (const file of gitFiles('*.js')) {
    assert.doesNotThrow(
      () => execFileSync(process.execPath, ['--check', path.join(repoRoot, file)], { stdio: 'pipe' }),
      `${file} should parse`,
    );
  }
});

test('Model S configurator submits Model S checkout data', () => {
  const html = readRepoFile('hk2/order-model-s.html');

  assert.match(html, /<h1>Model S<\/h1>/);
  assert.match(html, /<strong>\$62,990<\/strong>/);
  assert.match(html, /data-order-model="Model S"/);
  assert.match(html, /data-order-trim="Standard Wheels"/);
  assert.match(html, /data-order-price="\$62,990"/);
  assert.match(html, /data-order-image="models\.jpg"/);
  assert.doesNotMatch(html, /data-order-model="Model 3"/);
});

test('consultation success message does not interpolate user input into HTML', () => {
  const script = readRepoFile('A/LMS ĐH-CĐ - Antigravity/script.js');

  assert.doesNotMatch(
    script,
    /formSuccessBlock\.innerHTML\s*=\s*`[\s\S]*\$\{(?:fullname|phone|email)\}/,
  );
  assert.match(script, /formSuccessBlock\.append\(successIcon, successTitle, successMessage, resetButton\)/);
});

test('payment cart renders stored cart fields as DOM text', () => {
  const script = readRepoFile('hk2/script.js');
  const renderStart = script.indexOf('const renderPaymentCart = () => {');
  const renderEnd = script.indexOf('const subtotal = getCartSubtotal();', renderStart);
  const renderPaymentCart = script.slice(renderStart, renderEnd);

  assert.ok(renderStart > -1 && renderEnd > renderStart, 'renderPaymentCart block should be found');
  assert.doesNotMatch(renderPaymentCart, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
  assert.match(renderPaymentCart, /document\.createElement\("article"\)/);
  assert.match(renderPaymentCart, /model\.textContent = item\.model \|\| "Model"/);
  assert.match(renderPaymentCart, /trim\.textContent = item\.trim \|\| "Base"/);
  assert.match(script, /const getSafeImageSrc = \(value\) =>/);
});

test('ams_jump samples run without sanitizer failures', () => {
  const buildDir = mkdtempSync(path.join(tmpdir(), 'ams-jump-'));
  const binary = path.join(buildDir, 'ams_jump');

  try {
    compileCpp('C++/2025/ams_jump.cpp', binary);

    for (const inputPath of gitFiles('C++/2025/ams_jump_*.in')) {
      const answerPath = inputPath.replace(/\.in$/, '.ans');
      const actual = execFileSync(binary, {
        input: readRepoFile(inputPath),
        encoding: 'utf8',
        timeout: 5_000,
      });
      assert.equal(normalizeOutput(actual), normalizeOutput(readRepoFile(answerPath)), inputPath);
    }
  } finally {
    rmSync(buildDir, { recursive: true, force: true });
  }
});

test('tongbang bundled samples, including max constraints, finish quickly', () => {
  const buildDir = mkdtempSync(path.join(tmpdir(), 'tongbang-'));
  const binary = path.join(buildDir, 'tongbang');

  try {
    compileCpp('C++/2025/tongbang.cpp', binary);

    for (const inputPath of gitFiles('C++/2025/tongbang_*.in')) {
      const answerPath = inputPath.replace(/\.in$/, '.ans');
      const actual = execFileSync(binary, {
        input: readRepoFile(inputPath),
        encoding: 'utf8',
        timeout: 5_000,
      });
      assert.equal(normalizeOutput(actual), normalizeOutput(readRepoFile(answerPath)), inputPath);
    }
  } finally {
    rmSync(buildDir, { recursive: true, force: true });
  }
});
