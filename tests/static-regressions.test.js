const assert = require('node:assert/strict');
const { spawnSync } = require('node:child_process');
const fs = require('node:fs');
const os = require('node:os');
const path = require('node:path');
const test = require('node:test');

const repoRoot = path.resolve(__dirname, '..');

function readRepoFile(relativePath) {
  return fs.readFileSync(path.join(repoRoot, relativePath), 'utf8');
}

function hasCommand(command) {
  const result = spawnSync(command, ['--version'], { encoding: 'utf8' });
  return result.status === 0;
}

function compileCpp(relativePath, binaryName) {
  const tempDir = fs.mkdtempSync(path.join(os.tmpdir(), 'coding-regressions-'));
  const binaryPath = path.join(tempDir, binaryName);
  const result = spawnSync(
    'g++',
    ['-std=c++17', '-Wall', '-Wextra', '-fsanitize=address,undefined', '-g', relativePath, '-o', binaryPath],
    { cwd: repoRoot, encoding: 'utf8' }
  );

  assert.equal(result.status, 0, `${relativePath} failed to compile:\n${result.stderr}`);
  return binaryPath;
}

function runCppSamples(binaryPath, samplePrefix) {
  const sampleDir = path.join(repoRoot, 'C++/2025');
  const inputs = fs
    .readdirSync(sampleDir)
    .filter((file) => file.startsWith(`${samplePrefix}_`) && file.endsWith('.in'))
    .sort();

  assert.ok(inputs.length > 0, `expected samples for ${samplePrefix}`);

  for (const inputFile of inputs) {
    const expectedFile = inputFile.replace(/\.in$/, '.ans');
    const input = fs.readFileSync(path.join(sampleDir, inputFile), 'utf8');
    const expected = fs.readFileSync(path.join(sampleDir, expectedFile), 'utf8');
    const result = spawnSync(binaryPath, {
      input,
      encoding: 'utf8',
      timeout: 5000,
    });

    assert.equal(result.status, 0, `${samplePrefix} failed on ${inputFile}:\n${result.stderr}`);
    assert.equal(result.stdout, expected, `${samplePrefix} output mismatch on ${inputFile}`);
  }
}

test('tracked JavaScript files parse successfully', () => {
  const git = spawnSync('git', ['ls-files', '-z', '--', '*.js'], {
    cwd: repoRoot,
    encoding: 'utf8',
  });
  assert.equal(git.status, 0, git.stderr);

  const files = git.stdout.split('\0').filter(Boolean);
  assert.ok(files.length > 0, 'expected at least one JavaScript file');

  for (const file of files) {
    const check = spawnSync(process.execPath, ['--check', file], {
      cwd: repoRoot,
      encoding: 'utf8',
    });
    assert.equal(check.status, 0, `${file} failed node --check:\n${check.stderr}`);
  }
});

test('Model S configurator submits Model S cart metadata', () => {
  const html = readRepoFile('hk2/order-model-s.html');

  assert.match(html, /<h1>\s*Model S\s*<\/h1>/);
  assert.match(html, /<strong>\$62,990<\/strong>/);
  assert.match(html, /data-order-model="Model S"/);
  assert.match(html, /data-order-trim="Standard Wheels"/);
  assert.match(html, /data-order-price="\$62,990"/);
  assert.doesNotMatch(html, /data-order-model="Model 3"/);
});

test('payment cart renderer does not interpolate stored cart text as HTML', () => {
  const script = readRepoFile('hk2/script.js');

  assert.match(script, /paymentCartItems\.replaceChildren\(\)/);
  assert.match(script, /title\.textContent = String\(item\.model \|\| "Model"\)/);
  assert.match(script, /trim\.textContent = String\(item\.trim \|\| "Base"\)/);
  assert.doesNotMatch(script, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
  assert.doesNotMatch(script, /<h3>\$\{item\.model/);
  assert.doesNotMatch(script, /<p>\$\{item\.trim/);
});

test('consultation success message renders submitted fields as text', () => {
  const script = readRepoFile('A/LMS ĐH-CĐ - Antigravity/script.js');

  assert.match(script, /formSuccessBlock\.replaceChildren\(\)/);
  assert.match(script, /textContent: fullname/);
  assert.match(script, /textContent: phone/);
  assert.match(script, /textContent: email/);
  assert.doesNotMatch(script, /Cảm ơn <strong>\$\{fullname\}<\/strong>/);
});

test('ams_jump stays in bounds and matches bundled samples', { skip: !hasCommand('g++') && 'g++ is unavailable' }, () => {
  const binary = compileCpp('C++/2025/ams_jump.cpp', 'ams_jump');
  runCppSamples(binary, 'ams_jump');
});

test('tongbang handles max bundled sample without materializing first row', { skip: !hasCommand('g++') && 'g++ is unavailable' }, () => {
  const binary = compileCpp('C++/2025/tongbang.cpp', 'tongbang');
  runCppSamples(binary, 'tongbang');
});
