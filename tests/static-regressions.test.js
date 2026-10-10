const assert = require('node:assert/strict');
const { execFileSync } = require('node:child_process');
const fs = require('node:fs');
const path = require('node:path');
const test = require('node:test');

const repoRoot = path.resolve(__dirname, '..');

function readRepoFile(relativePath) {
  return fs.readFileSync(path.join(repoRoot, relativePath), 'utf8');
}

test('tracked JavaScript files parse successfully', () => {
  const files = execFileSync('git', ['ls-files', '-z', '*.js'], {
    cwd: repoRoot,
    encoding: 'utf8',
  }).split('\0').filter(Boolean);

  for (const file of files) {
    execFileSync(process.execPath, ['--check', file], { cwd: repoRoot });
  }
});

test('consultation success message renders submitted fields as text nodes', () => {
  const script = readRepoFile('A/LMS ĐH-CĐ - Antigravity/script.js');

  assert.doesNotMatch(script, /formSuccessBlock\.innerHTML\s*=\s*`/);
  assert.match(script, /safeName\.textContent\s*=\s*fullname/);
  assert.match(script, /safePhone\.textContent\s*=\s*phone/);
  assert.match(script, /safeEmail\.textContent\s*=\s*email/);
});

test('payment cart rows do not interpolate stored cart fields into HTML', () => {
  const script = readRepoFile('hk2/script.js');

  assert.doesNotMatch(script, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
  assert.match(script, /title\.textContent\s*=\s*item\.model/);
  assert.match(script, /trim\.textContent\s*=\s*item\.trim/);
  assert.match(script, /image\.alt\s*=\s*item\.model/);
});

test('Model S configurator sends Model S checkout metadata', () => {
  const html = readRepoFile('hk2/order-model-s.html');

  assert.match(html, /<h1>Model S<\/h1>/);
  assert.match(html, /data-order-model="Model S"/);
  assert.match(html, /data-order-trim="Standard Wheels"/);
  assert.match(html, /data-order-price="\$62,990"/);
  assert.match(html, /data-order-image="models\.jpg"/);
  assert.doesNotMatch(html, /data-order-model="Model 3"/);
});
