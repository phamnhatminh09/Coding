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
  const files = execFileSync('git', ['ls-files', '-z', '*.js'], {
    cwd: repoRoot,
  })
    .toString('utf8')
    .split('\0')
    .filter(Boolean);

  assert.ok(files.length > 0, 'expected tracked JavaScript files');

  for (const file of files) {
    assert.doesNotThrow(
      () => execFileSync('node', ['--check', file], { cwd: repoRoot }),
      `${file} should parse`
    );
  }
});

test('Model S configurator submits Model S cart metadata', () => {
  const html = read('hk2/order-model-s.html');
  const cta = html.match(/<button class="btn btn-red order-config-cta"[\s\S]*?<\/button>/);

  assert.ok(cta, 'expected a checkout CTA button');
  assert.match(html, /<h1>Model S<\/h1>/);
  assert.match(html, /<strong>\$62,990<\/strong>/);
  assert.match(cta[0], /data-order-model="Model S"/);
  assert.match(cta[0], /data-order-trim="Standard Wheels"/);
  assert.match(cta[0], /data-order-price="\$62,990"/);
  assert.match(cta[0], /data-order-image="models\.jpg"/);
  assert.doesNotMatch(cta[0], /Model 3|\$38,990/);
});

test('submitted consultation values are not interpolated into innerHTML', () => {
  const script = read('A/LMS ĐH-CĐ - Antigravity/script.js');

  assert.doesNotMatch(script, /innerHTML\s*=\s*`[\s\S]*\$\{fullname\}[\s\S]*`/);
  assert.doesNotMatch(script, /innerHTML\s*=\s*`[\s\S]*\$\{phone\}[\s\S]*`/);
  assert.doesNotMatch(script, /innerHTML\s*=\s*`[\s\S]*\$\{email\}[\s\S]*`/);
  assert.match(script, /#success-fullname'\)\.textContent\s*=\s*fullname/);
  assert.match(script, /#success-phone'\)\.textContent\s*=\s*phone/);
  assert.match(script, /#success-email'\)\.textContent\s*=\s*email/);
});

test('payment cart rows render stored cart fields through text nodes', () => {
  const script = read('hk2/script.js');

  assert.doesNotMatch(script, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
  assert.doesNotMatch(script, /<h3>\$\{item\.model/);
  assert.doesNotMatch(script, /<p>\$\{item\.trim/);
  assert.match(script, /model\.textContent\s*=\s*item\.model/);
  assert.match(script, /trim\.textContent\s*=\s*item\.trim/);
  assert.match(script, /paymentCartItems\.replaceChildren\(\)/);
});
