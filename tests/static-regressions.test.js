const assert = require('node:assert/strict');
const { execFileSync } = require('node:child_process');
const fs = require('node:fs');
const path = require('node:path');
const test = require('node:test');

const repoRoot = path.resolve(__dirname, '..');

function readRepoFile(...segments) {
  return fs.readFileSync(path.join(repoRoot, ...segments), 'utf8');
}

test('tracked JavaScript files parse successfully', () => {
  const trackedJs = execFileSync('git', ['ls-files', '-z', '*.js'], {
    cwd: repoRoot,
    encoding: 'buffer'
  })
    .toString('utf8')
    .split('\0')
    .filter(Boolean);

  assert.ok(trackedJs.length > 0, 'expected at least one tracked JavaScript file');

  for (const file of trackedJs) {
    execFileSync(process.execPath, ['--check', path.join(repoRoot, file)], {
      cwd: repoRoot,
      stdio: 'pipe'
    });
  }
});

test('Model S configurator submits Model S checkout metadata', () => {
  const html = readRepoFile('hk2', 'order-model-s.html');

  assert.match(html, /<h1>\s*Model S\s*<\/h1>/);
  assert.match(html, /data-order-model="Model S"/);
  assert.match(html, /data-order-trim="Standard Wheels"/);
  assert.match(html, /data-order-price="\$62,990"/);
  assert.match(html, /data-order-image="models\.jpg"/);
  assert.doesNotMatch(html, /data-order-model="Model 3"/);
});

test('payment cart rendering does not interpolate stored cart values as HTML', () => {
  const script = readRepoFile('hk2', 'script.js');

  assert.doesNotMatch(script, /paymentCartItems\.innerHTML\s*=/);
});

test('consultation success message does not interpolate submitted fields as HTML', () => {
  const script = readRepoFile('A', 'LMS ĐH-CĐ - Antigravity', 'script.js');

  assert.doesNotMatch(script, /formSuccessBlock\.innerHTML\s*=/);
  assert.match(script, /textContent:\s*fullname/);
  assert.match(script, /textContent:\s*phone/);
  assert.match(script, /textContent:\s*email/);
});
