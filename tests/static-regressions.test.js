const assert = require('node:assert/strict');
const { execFileSync } = require('node:child_process');
const fs = require('node:fs');
const path = require('node:path');
const test = require('node:test');

const root = path.resolve(__dirname, '..');

function read(relativePath) {
  return fs.readFileSync(path.join(root, relativePath), 'utf8');
}

test('tracked JavaScript files parse successfully', () => {
  const files = execFileSync('git', ['ls-files', '-z'], { cwd: root })
    .toString('utf8')
    .split('\0')
    .filter((file) => file.endsWith('.js'));

  assert.ok(files.length > 0, 'expected tracked JavaScript files');
  for (const file of files) {
    execFileSync(process.execPath, ['--check', path.join(root, file)], {
      cwd: root,
      stdio: 'pipe',
    });
  }
});

test('Model S configurator submits Model S cart metadata', () => {
  const html = read('hk2/order-model-s.html');

  assert.match(html, /<h1>\s*Model S\s*<\/h1>/);
  assert.match(html, /<strong>\$62,990<\/strong>/);
  assert.match(html, /data-order-model="Model S"/);
  assert.match(html, /data-order-trim="Standard Wheels"/);
  assert.match(html, /data-order-price="\$62,990"/);
  assert.match(html, /data-order-image="models\.jpg"/);
  assert.doesNotMatch(html, /data-order-model="Model 3"[\s\S]*data-order-price="\$38,990"/);
});

test('payment cart renders saved cart fields as text, not HTML', () => {
  const script = read('hk2/script.js');

  assert.doesNotMatch(script, /paymentCartItems\.innerHTML\s*=\s*cart\.map/s);
  assert.match(script, /paymentCartItems\.replaceChildren\(\.\.\.cartRows\)/);
  assert.match(script, /model\.textContent\s*=\s*item\.model\s*\|\|\s*"Model"/);
  assert.match(script, /trim\.textContent\s*=\s*item\.trim\s*\|\|\s*"Base"/);
  assert.match(script, /unit\.textContent\s*=/);
  assert.match(script, /total\.textContent\s*=/);
});

test('consultation success message treats submitted fields as text', () => {
  const script = read('A/LMS ĐH-CĐ - Antigravity/script.js');

  assert.doesNotMatch(script, /formSuccessBlock\.innerHTML\s*=\s*`[\s\S]*\$\{(?:fullname|phone|email)\}/);
  assert.match(script, /nameValue\.textContent\s*=\s*fullname/);
  assert.match(script, /phoneValue\.textContent\s*=\s*phone/);
  assert.match(script, /emailValue\.textContent\s*=\s*email/);
  assert.match(script, /formSuccessBlock\.replaceChildren\(successIcon, successTitle, successMessage, resetButton\)/);
});
