const assert = require('node:assert/strict');
const { execFileSync, spawnSync } = require('node:child_process');
const fs = require('node:fs');
const path = require('node:path');
const test = require('node:test');

const repoRoot = path.resolve(__dirname, '..');

function readRepoFile(...parts) {
  return fs.readFileSync(path.join(repoRoot, ...parts), 'utf8');
}

test('tracked JavaScript files parse successfully', () => {
  const files = execFileSync('git', ['ls-files', '-z', '*.js'], {
    cwd: repoRoot,
    encoding: 'utf8'
  }).split('\0').filter(Boolean);

  for (const file of files) {
    const result = spawnSync(process.execPath, ['--check', file], {
      cwd: repoRoot,
      encoding: 'utf8'
    });
    assert.equal(result.status, 0, `${file} failed to parse:\n${result.stderr}`);
  }
});

test('Model S configurator submits Model S checkout metadata', () => {
  const html = readRepoFile('hk2', 'order-model-s.html');
  const cta = html.match(/<button class="btn btn-red order-config-cta"[\s\S]*?<\/button>/)?.[0];

  assert.ok(cta, 'Model S configurator CTA should exist');
  assert.match(html, /<h1>Model S<\/h1>/);
  assert.match(html, /<strong>\$62,990<\/strong>/);
  assert.match(cta, /data-order-model="Model S"/);
  assert.match(cta, /data-order-trim="Standard Wheels"/);
  assert.match(cta, /data-order-price="\$62,990"/);
  assert.match(cta, /data-order-image="models\.jpg"/);
  assert.doesNotMatch(cta, /Model 3|\$38,990|mods\.png/);
});

test('checkout cart uses DOM text nodes for stored cart fields', () => {
  const script = readRepoFile('hk2', 'script.js');

  assert.doesNotMatch(script, /paymentCartItems\.innerHTML\s*=/);
  assert.match(script, /paymentCartItems\.replaceChildren/);
  assert.match(script, /model\.textContent = item\.model/);
  assert.match(script, /trim\.textContent = item\.trim/);
});

test('consultation success message does not interpolate submitted fields into HTML', () => {
  const script = readRepoFile('A', 'LMS ĐH-CĐ - Antigravity', 'script.js');

  assert.doesNotMatch(
    script,
    /formSuccessBlock\.innerHTML\s*=\s*`[\s\S]*\$\{(?:fullname|phone|email)\}/
  );
  assert.match(script, /data-success-fullname/);
  assert.match(script, /querySelector\('\[data-success-fullname\]'\)\.textContent = fullname/);
  assert.match(script, /querySelector\('\[data-success-phone\]'\)\.textContent = phone/);
  assert.match(script, /querySelector\('\[data-success-email\]'\)\.textContent = email/);
});

test('animal poll state is normalized and rendered without innerHTML', () => {
  const script = readRepoFile('html', 'script.js');

  assert.match(script, /function normalizePollCounts/);
  assert.match(script, /JSON\.parse\(localStorage\.getItem\('pollCounts'\)\)/);
  assert.doesNotMatch(script, /pollResult\.innerHTML/);
  assert.match(script, /pollResult\.replaceChildren/);
});
