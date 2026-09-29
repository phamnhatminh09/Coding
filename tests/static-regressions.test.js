const assert = require('node:assert/strict');
const { execFileSync } = require('node:child_process');
const { readFileSync } = require('node:fs');
const test = require('node:test');

function trackedFiles(pattern) {
  return execFileSync('git', ['ls-files', '-z', pattern], { encoding: 'utf8' })
    .split('\0')
    .filter(Boolean);
}

function read(path) {
  return readFileSync(path, 'utf8');
}

test('tracked JavaScript files parse successfully', () => {
  for (const file of trackedFiles('*.js')) {
    execFileSync(process.execPath, ['--check', file], { stdio: 'pipe' });
  }
});

test('Model S configurator submits Model S checkout metadata', () => {
  const html = read('hk2/order-model-s.html');

  assert.match(html, /<h1>\s*Model S\s*<\/h1>/);
  assert.match(html, /data-order-model="Model S"/);
  assert.match(html, /data-order-price="\$62,990"/);
  assert.doesNotMatch(html, /data-order-model="Model 3"/);
  assert.doesNotMatch(html, /data-order-price="\$38,990"/);
});

test('payment cart does not interpolate stored cart fields as HTML', () => {
  const script = read('hk2/script.js');

  assert.doesNotMatch(script, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
  assert.doesNotMatch(script, /\$\{\s*(?:item|cartItem)\.(?:model|trim|image)\b/);
});

test('consultation success message renders submitted fields as text', () => {
  const script = read('A/LMS ĐH-CĐ - Antigravity/script.js');

  assert.doesNotMatch(script, /formSuccessBlock\.innerHTML/);
  assert.match(script, /fullnameText\.textContent\s*=\s*fullname/);
  assert.match(script, /phoneText\.textContent\s*=\s*phone/);
  assert.match(script, /emailText\.textContent\s*=\s*email/);
});
