const assert = require('node:assert/strict');
const { spawnSync } = require('node:child_process');
const { readFileSync } = require('node:fs');
const path = require('node:path');
const test = require('node:test');

const repoRoot = path.resolve(__dirname, '..');

function read(relativePath) {
  return readFileSync(path.join(repoRoot, relativePath), 'utf8');
}

test('tracked JavaScript files parse successfully', () => {
  const git = spawnSync('git', ['ls-files', '-z', '*.js'], {
    cwd: repoRoot,
    encoding: 'utf8',
  });
  assert.equal(git.status, 0, git.stderr);

  const files = git.stdout.split('\0').filter(Boolean);
  assert.ok(files.length > 0, 'expected tracked JavaScript files');

  for (const file of files) {
    const check = spawnSync(process.execPath, ['--check', file], {
      cwd: repoRoot,
      encoding: 'utf8',
    });
    assert.equal(check.status, 0, `${file}\n${check.stderr}`);
  }
});

test('LMS Lite mobile menu does not use optional chaining as an assignment target', () => {
  const source = read('C/LMS Lite - Cursor/js/main.js');
  assert.doesNotMatch(source, /navToggle\?\.querySelector\('i'\)\.className\s*=/);
});

test('Model S configurator submits Model S checkout data', () => {
  const html = read('hk2/order-model-s.html');
  assert.match(html, /<h1>Model S<\/h1>/);
  assert.match(html, /<strong>\$62,990<\/strong>/);
  assert.match(html, /data-order-model="Model S"/);
  assert.match(html, /data-order-trim="Standard Wheels"/);
  assert.match(html, /data-order-price="\$62,990"/);
  assert.match(html, /data-order-image="models\.jpg"/);
  assert.doesNotMatch(html, /data-order-model="Model 3"/);
});

test('payment cart renders stored cart fields through DOM text APIs', () => {
  const source = read('hk2/script.js');
  assert.doesNotMatch(source, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
  assert.match(source, /paymentCartItems\.replaceChildren\(\.\.\.cart\.map\(createPaymentCartItem\)\)/);
  assert.match(source, /title\.textContent = item\.model/);
  assert.match(source, /trim\.textContent = item\.trim/);
});

test('consultation success message does not interpolate submitted fields into HTML', () => {
  const source = read('A/LMS ĐH-CĐ - Antigravity/script.js');
  assert.doesNotMatch(source, /formSuccessBlock\.innerHTML/);
  assert.match(source, /textContent: fullname/);
  assert.match(source, /textContent: phone/);
  assert.match(source, /textContent: email/);
});

test('animal poll storage is normalized and rendered without innerHTML', () => {
  const source = read('html/script.js');
  assert.match(source, /try\s*\{/);
  assert.match(source, /normalizePollCounts/);
  assert.doesNotMatch(source, /pollResult\.innerHTML/);
  assert.match(source, /pollResult\.replaceChildren/);
});
