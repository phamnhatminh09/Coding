const assert = require('node:assert/strict');
const { execFileSync } = require('node:child_process');
const fs = require('node:fs');
const path = require('node:path');
const test = require('node:test');

const repoRoot = path.resolve(__dirname, '..');

function read(relativePath) {
  return fs.readFileSync(path.join(repoRoot, relativePath), 'utf8');
}

function getTrackedFiles(pattern) {
  const output = execFileSync('git', ['ls-files', '-z', pattern], {
    cwd: repoRoot,
    encoding: 'buffer',
  });

  return output
    .toString('utf8')
    .split('\0')
    .filter(Boolean);
}

test('tracked JavaScript files parse successfully', () => {
  for (const file of getTrackedFiles('*.js')) {
    assert.doesNotThrow(() => {
      execFileSync(process.execPath, ['--check', file], {
        cwd: repoRoot,
        stdio: 'pipe',
      });
    }, `${file} should parse`);
  }
});

test('Model S configurator submits Model S order metadata', () => {
  const html = read('hk2/order-model-s.html');

  assert.match(html, /<h1>\s*Model S\s*<\/h1>/);
  assert.match(html, /<strong>\$62,990<\/strong>/);
  assert.match(html, /data-order-model="Model S"/);
  assert.match(html, /data-order-trim="Standard Wheels"/);
  assert.match(html, /data-order-price="\$62,990"/);
});

test('payment cart does not interpolate stored cart fields into HTML', () => {
  const script = read('hk2/script.js');

  assert.doesNotMatch(script, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
  assert.doesNotMatch(script, /<img\s+src="\$\{item\.image/);
  assert.doesNotMatch(script, /<h3>\$\{item\.model/);
  assert.match(script, /paymentCartItems\.replaceChildren\(\)/);
});

test('consultation success message renders submitted contact data as text', () => {
  const script = read('A/LMS ĐH-CĐ - Antigravity/script.js');

  assert.doesNotMatch(
    script,
    /formSuccessBlock\.innerHTML\s*=\s*`[\s\S]*\$\{(?:fullname|phone|email)\}/
  );
  assert.match(script, /nameText\.textContent = fullname/);
  assert.match(script, /phoneText\.textContent = phone/);
  assert.match(script, /emailText\.textContent = email/);
});
