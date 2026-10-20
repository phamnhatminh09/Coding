const assert = require('node:assert/strict');
const { execFileSync, spawnSync } = require('node:child_process');
const fs = require('node:fs');
const path = require('node:path');
const test = require('node:test');

const repoRoot = path.resolve(__dirname, '..');

const read = (...segments) => fs.readFileSync(path.join(repoRoot, ...segments), 'utf8');

test('tracked JavaScript files parse successfully', () => {
  const output = execFileSync('git', ['ls-files', '-z', '*.js'], {
    cwd: repoRoot,
    encoding: 'buffer'
  });
  const files = output.toString('utf8').split('\0').filter(Boolean);

  for (const file of files) {
    const result = spawnSync(process.execPath, ['--check', file], {
      cwd: repoRoot,
      encoding: 'utf8'
    });
    assert.equal(result.status, 0, `${file} failed syntax check:\n${result.stderr}`);
  }
});

test('Model S configurator submits Model S checkout metadata', () => {
  const html = read('hk2', 'order-model-s.html');

  assert.match(html, /data-order-model="Model S"/);
  assert.match(html, /data-order-trim="Standard Wheels"/);
  assert.match(html, /data-order-price="\$62,990"/);
  assert.match(html, /data-order-image="models\.jpg"/);
  assert.doesNotMatch(html, /data-order-model="Model 3"[\s\S]*data-order-image="mods\.png"/);
});

test('payment cart renders stored cart fields with DOM text APIs', () => {
  const script = read('hk2', 'script.js');
  const renderPaymentCart = script.slice(
    script.indexOf('const renderPaymentCart = () => {'),
    script.indexOf('const subtotal = getCartSubtotal();')
  );

  assert.match(renderPaymentCart, /document\.createElement\("article"\)/);
  assert.match(renderPaymentCart, /title\.textContent = item\.model/);
  assert.match(renderPaymentCart, /trim\.textContent = item\.trim/);
  assert.doesNotMatch(renderPaymentCart, /innerHTML\s*=\s*cart\.map/);
  assert.doesNotMatch(renderPaymentCart, /\$\{item\.(?:model|trim|image)/);
});

test('consultation success message escapes submitted fields before HTML rendering', () => {
  const script = read('A', 'LMS ĐH-CĐ - Antigravity', 'script.js');

  assert.match(script, /const escapeHTML = /);
  assert.match(script, /\$\{escapeHTML\(fullname\)\}/);
  assert.match(script, /\$\{escapeHTML\(phone\)\}/);
  assert.match(script, /\$\{escapeHTML\(email\)\}/);
  assert.doesNotMatch(script, /\$\{fullname\}/);
  assert.doesNotMatch(script, /\$\{phone\}/);
  assert.doesNotMatch(script, /\$\{email\}/);
});

test('animal poll state is normalized and rendered without HTML injection sinks', () => {
  const script = read('html', 'script.js');

  assert.match(script, /normalizePollCounts/);
  assert.match(script, /try \{/);
  assert.match(script, /localStorage\.removeItem\('pollCounts'\)/);
  assert.match(script, /pollResult\.replaceChildren/);
  assert.doesNotMatch(script, /pollResult\.innerHTML\s*=/);
});
