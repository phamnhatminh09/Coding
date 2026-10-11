const assert = require('node:assert/strict');
const { execFileSync } = require('node:child_process');
const { readFileSync } = require('node:fs');
const test = require('node:test');

const repoRoot = process.cwd();

function trackedFiles(pattern) {
  const output = execFileSync('git', ['ls-files', '-z', pattern], {
    cwd: repoRoot,
  });

  return output
    .toString('utf8')
    .split('\0')
    .filter(Boolean);
}

test('tracked JavaScript files parse successfully', () => {
  for (const file of trackedFiles('*.js')) {
    assert.doesNotThrow(
      () => execFileSync('node', ['--check', file], { cwd: repoRoot, stdio: 'pipe' }),
      `${file} should parse`
    );
  }
});

test('Model S configurator submits Model S checkout metadata', () => {
  const html = readFileSync('hk2/order-model-s.html', 'utf8');

  assert.match(html, /<h1>\s*Model S\s*<\/h1>/);
  assert.match(html, /Vehicle price[\s\S]*?<strong>\$62,990<\/strong>/);
  assert.match(html, /data-order-model="Model S"/);
  assert.match(html, /data-order-trim="Standard Wheels"/);
  assert.match(html, /data-order-price="\$62,990"/);
  assert.match(html, /data-order-image="models\.jpg"/);
});

test('payment cart renders stored cart values as text, not HTML', () => {
  const script = readFileSync('hk2/script.js', 'utf8');

  assert.match(script, /paymentCartItems\.replaceChildren\(\)/);
  assert.doesNotMatch(script, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
  assert.doesNotMatch(script, /\$\{item\.(?:image|model|trim|price)/);
});

test('consultation success message does not interpolate submitted fields into HTML', () => {
  const script = readFileSync('A/LMS ĐH-CĐ - Antigravity/script.js', 'utf8');

  assert.doesNotMatch(script, /formSuccessBlock\.innerHTML/);
  assert.doesNotMatch(script, /\$\{(?:fullname|phone|email)\}/);
  assert.match(script, /textContent: fullname/);
  assert.match(script, /textContent: phone/);
  assert.match(script, /textContent: email/);
});
