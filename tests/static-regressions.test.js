const assert = require('node:assert/strict');
const { execFileSync } = require('node:child_process');
const { readFileSync } = require('node:fs');
const test = require('node:test');

const listTrackedFiles = () =>
  execFileSync('git', ['ls-files', '-z'], { encoding: 'utf8' })
    .split('\0')
    .filter(Boolean);

test('tracked JavaScript files parse successfully', () => {
  const jsFiles = listTrackedFiles().filter((file) => file.endsWith('.js'));

  assert.ok(jsFiles.length > 0, 'expected tracked JavaScript files');

  for (const file of jsFiles) {
    assert.doesNotThrow(
      () => execFileSync(process.execPath, ['--check', file], { stdio: 'pipe' }),
      `${file} should parse`
    );
  }
});

test('LMS Lite mobile nav close handler avoids invalid optional-chain assignment', () => {
  const source = readFileSync('C/LMS Lite - Cursor/js/main.js', 'utf8');

  assert.doesNotMatch(source, /navToggle\?\.querySelector\('i'\)\.className\s*=/);
  assert.match(source, /const icon = navToggle\?\.querySelector\('i'\);/);
});

test('Model S configurator stores Model S checkout details', () => {
  const source = readFileSync('hk2/order-model-s.html', 'utf8');

  assert.match(source, /<h1>Model S<\/h1>/);
  assert.match(source, /<strong>\$62,990<\/strong>/);
  assert.match(source, /data-order-model="Model S"/);
  assert.match(source, /data-order-trim="Standard Wheels"/);
  assert.match(source, /data-order-price="\$62,990"/);
  assert.match(source, /data-order-image="models\.jpg"/);
  assert.doesNotMatch(source, /data-order-model="Model 3"/);
});

test('payment cart renderer does not parse stored cart fields as HTML', () => {
  const source = readFileSync('hk2/script.js', 'utf8');

  assert.doesNotMatch(source, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
  assert.match(source, /paymentCartItems\.replaceChildren\(\)/);
  assert.match(source, /modelName\.textContent = item\.model \|\| "Model"/);
  assert.match(source, /trim\.textContent = item\.trim \|\| "Base"/);
});

test('LMS consultation success message renders submitted contact fields as text', () => {
  const source = readFileSync('A/LMS ĐH-CĐ - Antigravity/script.js', 'utf8');

  assert.doesNotMatch(source, /formSuccessBlock\.innerHTML\s*=/);
  assert.match(source, /formSuccessBlock\.replaceChildren\(\)/);
  assert.match(source, /textContent: fullname/);
  assert.match(source, /textContent: phone/);
  assert.match(source, /textContent: email/);
});
