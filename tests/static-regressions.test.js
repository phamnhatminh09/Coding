const assert = require('node:assert/strict');
const { execFileSync } = require('node:child_process');
const fs = require('node:fs');
const path = require('node:path');
const test = require('node:test');

const repoRoot = path.resolve(__dirname, '..');

function read(relativePath) {
  return fs.readFileSync(path.join(repoRoot, relativePath), 'utf8');
}

test('tracked JavaScript files parse successfully', () => {
  const output = execFileSync('git', ['ls-files', '-z', '*.js'], {
    cwd: repoRoot
  });
  const files = output.toString('utf8').split('\0').filter(Boolean);

  for (const file of files) {
    assert.doesNotThrow(
      () => execFileSync(process.execPath, ['--check', file], { cwd: repoRoot }),
      `${file} should pass node --check`
    );
  }
});

test('Model S configurator stores Model S checkout metadata', () => {
  const html = read('hk2/order-model-s.html');

  assert.match(html, /<h1>Model S<\/h1>/);
  assert.match(html, /<strong>\$62,990<\/strong>/);
  assert.match(html, /data-order-model="Model S"/);
  assert.match(html, /data-order-trim="Standard Wheels"/);
  assert.match(html, /data-order-price="\$62,990"/);
  assert.match(html, /data-order-image="models\.jpg"/);
  assert.doesNotMatch(html, /data-order-model="Model 3"/);
});

test('payment cart renders stored cart data without HTML interpolation', () => {
  const script = read('hk2/script.js');

  assert.match(script, /createPaymentCartItem/);
  assert.match(script, /paymentCartItems\.replaceChildren\(\)/);
  assert.match(script, /modelName\.textContent = item\.model/);
  assert.match(script, /trimName\.textContent = item\.trim/);
  assert.doesNotMatch(script, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
  assert.doesNotMatch(script, /\$\{item\.(?:model|trim|image)\s*\|\|/);
});

test('consultation success message renders submitted fields as text', () => {
  const script = read('A/LMS ĐH-CĐ - Antigravity/script.js');

  assert.match(script, /formSuccessBlock\.replaceChildren/);
  assert.match(script, /strong\.textContent = value/);
  assert.doesNotMatch(script, /formSuccessBlock\.innerHTML\s*=/);
  assert.doesNotMatch(script, /<strong>\$\{(?:fullname|phone|email)\}<\/strong>/);
});

test('animal poll storage is normalized and rendered without HTML interpolation', () => {
  const script = read('html/script.js');

  assert.match(script, /function normalizePollCounts/);
  assert.match(script, /localStorage\.removeItem\('pollCounts'\)/);
  assert.match(script, /pollResult\.replaceChildren\(fragment\)/);
  assert.doesNotMatch(script, /pollResult\.innerHTML\s*=/);
});
