const assert = require('node:assert/strict');
const { execFileSync, spawnSync } = require('node:child_process');
const { readFileSync } = require('node:fs');
const { join } = require('node:path');
const test = require('node:test');

const repoRoot = join(__dirname, '..');
const readRepoFile = (...segments) => readFileSync(join(repoRoot, ...segments), 'utf8');

test('tracked JavaScript files parse successfully', () => {
  const files = execFileSync('git', ['ls-files', '-z', '--', '*.js'], {
    cwd: repoRoot
  })
    .toString('utf8')
    .split('\0')
    .filter(Boolean);

  assert.ok(files.length > 0, 'expected tracked JavaScript files');

  for (const file of files) {
    const result = spawnSync(process.execPath, ['--check', file], {
      cwd: repoRoot,
      encoding: 'utf8'
    });

    assert.equal(
      result.status,
      0,
      `${file} failed node --check\n${result.stderr || result.stdout}`
    );
  }
});

test('LMS Lite mobile nav reset avoids optional chaining assignment', () => {
  const source = readRepoFile('C', 'LMS Lite - Cursor', 'js', 'main.js');

  assert.doesNotMatch(source, /navToggle\?\.querySelector\('i'\)\.className\s*=/);
  assert.match(source, /const icon = navToggle\?\.querySelector\('i'\);/);
});

test('consultation success message renders submitted fields as text', () => {
  const source = readRepoFile('A', 'LMS ĐH-CĐ - Antigravity', 'script.js');

  assert.doesNotMatch(source, /formSuccessBlock\.innerHTML/);
  assert.match(source, /formSuccessBlock\.replaceChildren\(\)/);
  assert.match(source, /strongName\.textContent = fullname/);
  assert.match(source, /strongPhone\.textContent = phone/);
  assert.match(source, /strongEmail\.textContent = email/);
});

test('Tesla payment summary does not render cart storage through HTML', () => {
  const source = readRepoFile('hk2', 'script.js');

  assert.doesNotMatch(source, /paymentCartItems\.innerHTML\s*=/);
  assert.match(source, /const safeCartImage = \(value\) =>/);
  assert.match(source, /paymentCartItems\.replaceChildren\(\)/);
});

test('Model S configurator submits Model S order metadata', () => {
  const source = readRepoFile('hk2', 'order-model-s.html');

  assert.match(source, /<h1>Model S<\/h1>/);
  assert.match(source, /<strong>\$62,990<\/strong>/);
  assert.match(source, /data-order-model="Model S"/);
  assert.match(source, /data-order-trim="Standard Wheels"/);
  assert.match(source, /data-order-price="\$62,990"/);
});

test('animal poll restores localStorage defensively and renders text nodes', () => {
  const source = readRepoFile('html', 'script.js');

  assert.match(source, /const normalizePollCounts = \(value\) =>/);
  assert.match(source, /try \{/);
  assert.doesNotMatch(source, /pollResult\.innerHTML/);
  assert.match(source, /pollResult\.replaceChildren\(\)/);
});

test('C++ crash and allocation regressions remain fixed', () => {
  const amsJumpActiveSource = readRepoFile('C++', '2025', 'ams_jump.cpp').split('/*')[0];
  const tongBangSource = readRepoFile('C++', '2025', 'tongbang.cpp');

  assert.doesNotMatch(amsJumpActiveSource, /h\[n\]\s*=/);
  assert.doesNotMatch(amsJumpActiveSource, /for\s*\(\s*int i = n;\s*i >= 0/);
  assert.match(amsJumpActiveSource, /vector<int> h\(n \+ 2\)/);
  assert.doesNotMatch(tongBangSource, /vector<int>\s+firstrow/);
  assert.match(tongBangSource, /ll half = n \/ 2/);
});
