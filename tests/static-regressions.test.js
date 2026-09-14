const { execFileSync } = require('node:child_process');
const { readFileSync } = require('node:fs');
const test = require('node:test');
const assert = require('node:assert/strict');

const read = (path) => readFileSync(path, 'utf8');

test('tracked JavaScript files parse successfully', () => {
  const files = execFileSync('git', ['ls-files', '-z', '*.js'])
    .toString('utf8')
    .split('\0')
    .filter(Boolean);

  assert.ok(files.length > 0, 'expected tracked JavaScript files');
  for (const file of files) {
    execFileSync(process.execPath, ['--check', file], { stdio: 'pipe' });
  }
});

test('LMS Lite mobile menu reset does not assign through optional chaining', () => {
  const source = read('C/LMS Lite - Cursor/js/main.js');

  assert.doesNotMatch(source, /\?\.\s*querySelector\([^)]*\)\.className\s*=/);
  assert.match(source, /const icon = navToggle\?\.querySelector\('i'\);/);
});

test('Model S configurator submits Model S cart metadata', () => {
  const html = read('hk2/order-model-s.html');

  assert.match(html, /<h1>Model S<\/h1>/);
  assert.match(html, /data-order-model="Model S"/);
  assert.match(html, /data-order-trim="Standard Wheels"/);
  assert.match(html, /data-order-price="\$62,990"/);
  assert.match(html, /data-order-image="models\.jpg"/);
  assert.doesNotMatch(html, /data-order-model="Model 3"/);
});

test('payment cart renderer does not parse stored cart fields as HTML', () => {
  const source = read('hk2/script.js');

  assert.doesNotMatch(source, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
  assert.match(source, /paymentCartItems\.replaceChildren\(\);/);
  assert.match(source, /model\.textContent = item\.model \|\| "Model";/);
  assert.match(source, /trim\.textContent = item\.trim \|\| "Base";/);
});

test('consultation success message renders submitted fields as text', () => {
  const source = read('A/LMS ĐH-CĐ - Antigravity/script.js');

  assert.doesNotMatch(source, /formSuccessBlock\.innerHTML\s*=/);
  assert.match(source, /fullnameText\.textContent = fullname;/);
  assert.match(source, /phoneText\.textContent = phone;/);
  assert.match(source, /emailText\.textContent = email;/);
});
