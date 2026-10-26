const assert = require('node:assert/strict');
const { execFileSync } = require('node:child_process');
const { readFileSync } = require('node:fs');
const path = require('node:path');
const test = require('node:test');

const repoRoot = path.resolve(__dirname, '..');

function readRepoFile(relativePath) {
  return readFileSync(path.join(repoRoot, relativePath), 'utf8');
}

test('tracked JavaScript files parse', () => {
  const files = execFileSync('git', ['ls-files', '-z', '--', '*.js'], {
    cwd: repoRoot
  }).toString('utf8').split('\0').filter(Boolean);

  assert.ok(files.length > 0, 'expected at least one tracked JavaScript file');

  for (const file of files) {
    execFileSync(process.execPath, ['--check', path.join(repoRoot, file)], {
      cwd: repoRoot,
      stdio: 'pipe'
    });
  }
});

test('Model S configurator submits Model S checkout metadata', () => {
  const html = readRepoFile('hk2/order-model-s.html');
  const buttonMatch = html.match(/<button[^>]*order-config-cta[\s\S]*?<\/button>/);

  assert.ok(buttonMatch, 'expected Model S checkout button');
  assert.match(html, /<strong>\$62,990<\/strong>/);
  assert.match(buttonMatch[0], /data-order-model="Model S"/);
  assert.match(buttonMatch[0], /data-order-price="\$62,990"/);
  assert.match(buttonMatch[0], /data-order-image="models\.jpg"/);
});

test('payment cart renders stored item fields as text', () => {
  const script = readRepoFile('hk2/script.js');

  assert.doesNotMatch(script, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
  assert.match(script, /paymentCartItems\.replaceChildren\(\)/);
  assert.match(script, /title\.textContent\s*=\s*item\.model/);
  assert.match(script, /trim\.textContent\s*=\s*item\.trim/);
});

test('consultation success message does not interpolate submitted fields as HTML', () => {
  const script = readRepoFile('A/LMS ĐH-CĐ - Antigravity/script.js');

  assert.doesNotMatch(script, /formSuccessBlock\.innerHTML\s*=\s*`/);
  assert.match(script, /nameNode\.textContent\s*=\s*fullname/);
  assert.match(script, /phoneNode\.textContent\s*=\s*phone/);
  assert.match(script, /emailNode\.textContent\s*=\s*email/);
});
