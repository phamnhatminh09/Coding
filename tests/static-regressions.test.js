const test = require('node:test');
const assert = require('node:assert/strict');
const { execFileSync } = require('node:child_process');
const fs = require('node:fs');
const path = require('node:path');

const repoRoot = path.resolve(__dirname, '..');

function readRepoFile(relativePath) {
  return fs.readFileSync(path.join(repoRoot, relativePath), 'utf8');
}

function trackedFiles(pathspec) {
  const output = execFileSync('git', ['ls-files', '-z', '--', pathspec], { cwd: repoRoot });
  return output.toString('utf8').split('\0').filter(Boolean);
}

function requireMatch(value, pattern, message) {
  const match = value.match(pattern);
  assert.ok(match, message);
  return match[0];
}

test('tracked JavaScript files parse successfully', () => {
  for (const file of trackedFiles('*.js')) {
    assert.doesNotThrow(
      () => execFileSync(process.execPath, ['--check', path.join(repoRoot, file)], { cwd: repoRoot, stdio: 'pipe' }),
      file
    );
  }
});

test('university LMS success message renders submitted fields as text', () => {
  const script = readRepoFile('A/LMS ĐH-CĐ - Antigravity/script.js');

  assert.doesNotMatch(script, /formSuccessBlock\.innerHTML\s*=/);
  assert.match(script, /nameStrong\.textContent\s*=\s*fullname/);
  assert.match(script, /phoneStrong\.textContent\s*=\s*phone/);
  assert.match(script, /emailStrong\.textContent\s*=\s*email/);
  assert.match(script, /formSuccessBlock\.replaceChildren\(/);
});

test('Model S configurator submits Model S checkout metadata', () => {
  const html = readRepoFile('hk2/order-model-s.html');
  const priceBlock = requireMatch(
    html,
    /<div class="order-config-price">[\s\S]*?<label class="order-home-charger">/,
    'Model S price block not found'
  );
  const ctaButton = requireMatch(
    html,
    /<button class="btn btn-red order-config-cta"[\s\S]*?<\/button>/,
    'Model S checkout button not found'
  );

  assert.match(priceBlock, /<strong>\$62,990<\/strong>/);
  assert.match(ctaButton, /data-order-model="Model S"/);
  assert.match(ctaButton, /data-order-trim="Standard Wheels"/);
  assert.match(ctaButton, /data-order-price="\$62,990"/);
  assert.match(ctaButton, /data-order-image="models\.jpg"/);
  assert.doesNotMatch(ctaButton, /data-order-model="Model 3"/);
});
