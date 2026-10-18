const assert = require('node:assert/strict');
const { spawnSync } = require('node:child_process');
const fs = require('node:fs');
const os = require('node:os');
const path = require('node:path');
const test = require('node:test');

const repoRoot = path.resolve(__dirname, '..');

function read(relativePath) {
  return fs.readFileSync(path.join(repoRoot, relativePath), 'utf8');
}

function run(command, args, options = {}) {
  const result = spawnSync(command, args, {
    cwd: repoRoot,
    encoding: 'utf8',
    timeout: 10000,
    ...options,
  });

  assert.equal(
    result.status,
    0,
    `${command} ${args.join(' ')} failed\nstdout:\n${result.stdout}\nstderr:\n${result.stderr}`,
  );

  return result;
}

function normalizeOutput(value) {
  return value.trim().replace(/\s+/g, ' ');
}

test('tracked live JavaScript files parse successfully', () => {
  [
    'A/LMS AI/script.js',
    'A/LMS Lite - Antigravity/script.js',
    'A/LMS ĐH-CĐ - Antigravity/script.js',
    'C/LMS AI/script.js',
    'C/LMS Lite - Cursor/js/main.js',
    'C/LMS ĐH-CĐ - Cursor/js/main.js',
    'hk2/script.js',
    'html/script.js',
  ].forEach((relativePath) => {
    run(process.execPath, ['--check', path.join(repoRoot, relativePath)]);
  });
});

test('LMS Lite mobile nav reset does not use invalid optional-chain assignment', () => {
  const source = read('C/LMS Lite - Cursor/js/main.js');

  assert.doesNotMatch(source, /navToggle\?\.querySelector\('i'\)\.className\s*=/);
  assert.match(source, /const icon = navToggle\?\.querySelector\('i'\);/);
});

test('Model S configurator submits Model S cart metadata', () => {
  const source = read('hk2/order-model-s.html');

  assert.match(source, /<strong>\$62,990<\/strong>/);
  assert.match(source, /data-order-model="Model S"/);
  assert.match(source, /data-order-trim="Standard Wheels"/);
  assert.match(source, /data-order-price="\$62,990"/);
  assert.match(source, /data-order-image="models\.jpg"/);
  assert.doesNotMatch(source, /data-order-model="Model 3"/);
});

test('payment cart renders stored cart data through DOM text nodes', () => {
  const source = read('hk2/script.js');

  assert.doesNotMatch(source, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
  assert.doesNotMatch(source, /\$\{item\.(model|trim|image)[^}]*\}/);
  assert.match(source, /paymentCartItems\.replaceChildren\(\)/);
  assert.match(source, /title\.textContent = item\.model \|\| "Model"/);
});

test('submitted LMS consultation fields are not interpolated into HTML', () => {
  const source = read('A/LMS ĐH-CĐ - Antigravity/script.js');

  assert.doesNotMatch(source, /formSuccessBlock\.innerHTML\s*=/);
  assert.doesNotMatch(source, /\$\{fullname\}|\$\{phone\}|\$\{email\}/);
  assert.match(source, /nameValue\.textContent = fullname/);
  assert.match(source, /formSuccessBlock\.replaceChildren/);
});

test('animal poll storage is normalized before rendering with text nodes', () => {
  const source = read('html/script.js');

  assert.doesNotMatch(source, /pollResult\.innerHTML\s*=/);
  assert.match(source, /try \{/);
  assert.match(source, /normalizePollCounts/);
  assert.match(source, /pollResult\.replaceChildren/);
});

test('ams_jump bundled samples complete without sanitizer failures', () => {
  const tmpDir = fs.mkdtempSync(path.join(os.tmpdir(), 'coding-audit-'));
  const binaryPath = path.join(tmpDir, 'ams_jump');

  run('g++', [
    '-std=c++17',
    '-Wall',
    '-Wextra',
    '-fsanitize=address,undefined',
    '-g',
    'C++/2025/ams_jump.cpp',
    '-o',
    binaryPath,
  ]);

  ['1', '2'].forEach((sample) => {
    const input = read(`C++/2025/ams_jump_${sample}.in`);
    const expected = normalizeOutput(read(`C++/2025/ams_jump_${sample}.ans`));
    const result = run(binaryPath, [], { input });
    assert.equal(normalizeOutput(result.stdout), expected);
  });
});

test('tongbang max sample uses the closed form instead of materializing the row', () => {
  const tmpDir = fs.mkdtempSync(path.join(os.tmpdir(), 'coding-audit-'));
  const binaryPath = path.join(tmpDir, 'tongbang');

  run('g++', ['-std=c++17', '-Wall', '-Wextra', '-O2', 'C++/2025/tongbang.cpp', '-o', binaryPath]);

  const result = run(binaryPath, [], {
    input: read('C++/2025/tongbang_6.in'),
    timeout: 3000,
  });

  assert.equal(normalizeOutput(result.stdout), normalizeOutput(read('C++/2025/tongbang_6.ans')));
});
