const assert = require('node:assert/strict');
const { execFileSync, spawnSync } = require('node:child_process');
const fs = require('node:fs');
const path = require('node:path');
const test = require('node:test');

const repoRoot = path.resolve(__dirname, '..');

const read = (relativePath) => fs.readFileSync(path.join(repoRoot, relativePath), 'utf8');

test('tracked JavaScript files parse successfully', () => {
  const files = execFileSync('git', ['ls-files', '-z', '*.js'], {
    cwd: repoRoot
  }).toString('utf8').split('\0').filter(Boolean);

  const failures = [];
  for (const file of files) {
    const result = spawnSync(process.execPath, ['--check', file], {
      cwd: repoRoot,
      encoding: 'utf8'
    });

    if (result.status !== 0) {
      failures.push(`${file}\n${result.stderr}`);
    }
  }

  assert.deepEqual(failures, []);
});

test('LMS Lite mobile menu does not assign through optional chaining', () => {
  const script = read('C/LMS Lite - Cursor/js/main.js');

  assert.doesNotMatch(script, /navToggle\?\.querySelector\('i'\)\.className\s*=/);
});

test('Model S configurator sends Model S checkout metadata', () => {
  const html = read('hk2/order-model-s.html');

  assert.match(html, /<h1>Model S<\/h1>/);
  assert.match(html, /<strong>\$62,990<\/strong>/);
  assert.match(html, /data-order-model="Model S"/);
  assert.match(html, /data-order-trim="Standard Wheels"/);
  assert.match(html, /data-order-price="\$62,990"/);
  assert.match(html, /data-order-image="models\.jpg"/);
  assert.doesNotMatch(html, /data-order-model="Model 3"/);
  assert.doesNotMatch(html, /data-order-price="\$38,990"/);
});

test('payment cart renders stored cart fields as DOM text', () => {
  const script = read('hk2/script.js');
  const renderStart = script.indexOf('const renderPaymentCart = () => {');
  const renderEnd = script.indexOf('const subtotal = getCartSubtotal();', renderStart);
  const renderBlock = script.slice(renderStart, renderEnd);

  assert.ok(renderStart >= 0 && renderEnd > renderStart);
  assert.match(renderBlock, /paymentCartItems\.replaceChildren\(\)/);
  assert.doesNotMatch(renderBlock, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
  assert.match(renderBlock, /title\.textContent = item\.model \|\| "Model"/);
  assert.match(renderBlock, /trim\.textContent = item\.trim \|\| "Base"/);
});

test('consultation success message renders submitted fields as text', () => {
  const script = read('A/LMS ĐH-CĐ - Antigravity/script.js');

  assert.doesNotMatch(script, /formSuccessBlock\.innerHTML\s*=/);
  assert.match(script, /appendStrongValue\(fullname\)/);
  assert.match(script, /appendStrongValue\(phone\)/);
  assert.match(script, /appendStrongValue\(email\)/);
});
