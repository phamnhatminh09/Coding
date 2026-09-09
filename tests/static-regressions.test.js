const assert = require('node:assert/strict');
const { spawnSync } = require('node:child_process');
const fs = require('node:fs');
const path = require('node:path');
const test = require('node:test');

const root = path.resolve(__dirname, '..');

function read(relPath) {
  return fs.readFileSync(path.join(root, relPath), 'utf8');
}

test('tracked static JavaScript files parse successfully', () => {
  const files = [
    'A/LMS ĐH-CĐ - Antigravity/script.js',
    'C/LMS Lite - Cursor/js/main.js',
    'C/LMS ĐH-CĐ - Cursor/js/main.js',
    'hk2/script.js',
  ];

  for (const file of files) {
    const result = spawnSync(process.execPath, ['--check', path.join(root, file)], {
      encoding: 'utf8',
    });

    assert.equal(
      result.status,
      0,
      `${file} failed syntax check:\n${result.stderr || result.stdout}`
    );
  }
});

test('Model S configurator submits Model S checkout details', () => {
  const html = read('hk2/order-model-s.html');
  const cta = html.match(/<button class="btn btn-red order-config-cta"[\s\S]*?<\/button>/);

  assert.ok(cta, 'Model S checkout button should exist');
  assert.match(html, /<h1>Model S<\/h1>/);
  assert.match(html, /<strong>\$62,990<\/strong>/);
  assert.match(cta[0], /data-order-model="Model S"/);
  assert.match(cta[0], /data-order-price="\$62,990"/);
  assert.doesNotMatch(cta[0], /data-order-model="Model 3"/);
  assert.doesNotMatch(cta[0], /data-order-price="\$38,990"/);
});

test('payment cart renders localStorage-backed fields as text', () => {
  const script = read('hk2/script.js');

  assert.doesNotMatch(script, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
  assert.doesNotMatch(script, /\$\{item\.(?:image|model|trim)\b/);
  assert.match(script, /paymentCartItems\.replaceChildren\(\)/);
  assert.match(script, /image\.src = getSafeCartImage\(cartItem\.image\)/);
  assert.match(script, /title\.textContent = cartItem\.model \|\| "Model"/);
  assert.match(script, /trim\.textContent = cartItem\.trim \|\| "Base"/);
});

test('consultation success message does not interpolate submitted fields into HTML', () => {
  const script = read('A/LMS ĐH-CĐ - Antigravity/script.js');

  assert.doesNotMatch(script, /\$\{fullname\}|\$\{phone\}|\$\{email\}/);
  assert.match(script, /nameText\.textContent = fullname/);
  assert.match(script, /phoneText\.textContent = phone/);
  assert.match(script, /emailText\.textContent = email/);
  assert.match(script, /formSuccessBlock\.replaceChildren\(\)/);
});
