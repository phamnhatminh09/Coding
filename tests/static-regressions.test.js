const assert = require('node:assert/strict');
const { mkdtempSync, readFileSync } = require('node:fs');
const { tmpdir } = require('node:os');
const path = require('node:path');
const { spawnSync } = require('node:child_process');
const test = require('node:test');

const repoRoot = path.resolve(__dirname, '..');

function readRepoFile(relativePath) {
  return readFileSync(path.join(repoRoot, relativePath), 'utf8');
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

  return result.stdout;
}

test('tracked page scripts parse successfully', () => {
  [
    'A/LMS AI/script.js',
    'A/LMS Lite - Antigravity/script.js',
    'A/LMS ĐH-CĐ - Antigravity/script.js',
    'C/LMS AI/script.js',
    'C/LMS Lite - Cursor/js/main.js',
    'C/LMS ĐH-CĐ - Cursor/js/main.js',
    'hk2/script.js',
    'html/script.js',
  ].forEach((scriptPath) => {
    run(process.execPath, ['--check', scriptPath]);
  });
});

test('Model S configurator submits Model S checkout data', () => {
  const html = readRepoFile('hk2/order-model-s.html');

  assert.match(html, /<h1>Model S<\/h1>/);
  assert.match(html, /<strong>\$62,990<\/strong>/);
  assert.match(html, /data-order-model="Model S"/);
  assert.match(html, /data-order-trim="Standard Wheels"/);
  assert.match(html, /data-order-price="\$62,990"/);
  assert.doesNotMatch(html, /data-order-model="Model 3"/);
});

test('user-controlled checkout and consultation fields are rendered as text', () => {
  const checkoutScript = readRepoFile('hk2/script.js');
  assert.doesNotMatch(checkoutScript, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
  assert.match(checkoutScript, /paymentCartItems\.replaceChildren\(fragment\)/);
  assert.match(checkoutScript, /title\.textContent = item\.model/);
  assert.match(checkoutScript, /trim\.textContent = item\.trim/);

  const consultationScript = readRepoFile('A/LMS ĐH-CĐ - Antigravity/script.js');
  assert.doesNotMatch(consultationScript, /formSuccessBlock\.innerHTML\s*=/);
  assert.match(consultationScript, /nameStrong\.textContent = fullname/);
  assert.match(consultationScript, /phoneStrong\.textContent = phone/);
  assert.match(consultationScript, /emailStrong\.textContent = email/);
});

test('ams_jump samples run without sanitizer failures', { skip: !hasCommand('g++') }, () => {
  const binary = compileCpp('C++/2025/ams_jump.cpp', 'ams_jump');

  assert.equal(
    normalize(runBinary(binary, readRepoFile('C++/2025/ams_jump_1.in'))),
    normalize(readRepoFile('C++/2025/ams_jump_1.ans')),
  );
  assert.equal(
    normalize(runBinary(binary, readRepoFile('C++/2025/ams_jump_2.in'))),
    normalize(readRepoFile('C++/2025/ams_jump_2.ans')),
  );
});

test('tongbang max-size sample completes without materializing the row', { skip: !hasCommand('g++') }, () => {
  const source = readRepoFile('C++/2025/tongbang.cpp');
  assert.doesNotMatch(source, /vector<int>\s+firstrow/);

  const binary = compileCpp('C++/2025/tongbang.cpp', 'tongbang');
  assert.equal(
    normalize(runBinary(binary, readRepoFile('C++/2025/tongbang_6.in'))),
    normalize(readRepoFile('C++/2025/tongbang_6.ans')),
  );
});

function hasCommand(command) {
  return spawnSync(command, ['--version'], { encoding: 'utf8' }).status === 0;
}

function compileCpp(relativePath, name) {
  const outputDir = mkdtempSync(path.join(tmpdir(), `${name}-`));
  const outputPath = path.join(outputDir, name);
  run('g++', [
    '-std=c++17',
    '-O1',
    '-g',
    '-Wall',
    '-Wextra',
    '-fsanitize=address,undefined',
    relativePath,
    '-o',
    outputPath,
  ]);
  return outputPath;
}

function runBinary(binary, input) {
  const result = spawnSync(binary, [], {
    input,
    encoding: 'utf8',
    timeout: 5000,
  });

  assert.equal(
    result.status,
    0,
    `${binary} failed\nstdout:\n${result.stdout}\nstderr:\n${result.stderr}`,
  );

  return result.stdout;
}

function normalize(value) {
  return value.trim().replace(/\s+/g, ' ');
}
