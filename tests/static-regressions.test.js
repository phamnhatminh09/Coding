const { execFileSync, spawnSync } = require('node:child_process');
const fs = require('node:fs');
const path = require('node:path');
const { test } = require('node:test');
const assert = require('node:assert/strict');

const repoRoot = path.resolve(__dirname, '..');

function readRepoFile(...segments) {
  return fs.readFileSync(path.join(repoRoot, ...segments), 'utf8');
}

function gitFiles(pathspec) {
  return execFileSync('git', ['ls-files', '-z', pathspec], { cwd: repoRoot })
    .toString('utf8')
    .split('\0')
    .filter(Boolean);
}

test('tracked JavaScript files parse', () => {
  const jsFiles = gitFiles('*.js');
  assert.ok(jsFiles.length > 0, 'expected at least one tracked JavaScript file');

  for (const file of jsFiles) {
    const result = spawnSync(process.execPath, ['--check', file], {
      cwd: repoRoot,
      encoding: 'utf8'
    });

    assert.equal(result.status, 0, `${file} failed syntax check:\n${result.stderr}`);
  }
});

test('Model S configurator submits Model S checkout metadata', () => {
  const html = readRepoFile('hk2', 'order-model-s.html');
  const cta = html.match(/<button class="btn btn-red order-config-cta"[\s\S]*?<\/button>/);

  assert.ok(cta, 'expected a Model S checkout button');
  assert.match(html, /<h1>\s*Model S\s*<\/h1>/);
  assert.match(html, /<strong>\$62,990<\/strong>/);
  assert.match(cta[0], /data-order-model="Model S"/);
  assert.match(cta[0], /data-order-trim="Standard Wheels"/);
  assert.match(cta[0], /data-order-price="\$62,990"/);
  assert.match(cta[0], /data-order-image="models\.jpg"/);
  assert.doesNotMatch(cta[0], /data-order-model="Model 3"|data-order-price="\$38,990"/);
});

test('payment cart renders stored cart fields as text nodes', () => {
  const script = readRepoFile('hk2', 'script.js');

  assert.match(script, /paymentCartItems\.replaceChildren\(\)/);
  assert.match(script, /\.filter\(\(item\) => item && typeof item === "object"\)/);
  assert.match(script, /title\.textContent = item\.model \|\| "Model"/);
  assert.match(script, /trim\.textContent = item\.trim \|\| "Base"/);
  assert.doesNotMatch(script, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
  assert.doesNotMatch(script, /<h3>\$\{item\.model|<p>\$\{item\.trim|alt="\$\{item\.model/);
});

test('LMS consultation success message does not interpolate submitted fields as HTML', () => {
  const script = readRepoFile('A', 'LMS \u0110H-C\u0110 - Antigravity', 'script.js');

  assert.doesNotMatch(script, /formSuccessBlock\.innerHTML\s*=/);
  assert.match(script, /nameStrong\.textContent = fullname/);
  assert.match(script, /phoneStrong\.textContent = phone/);
  assert.match(script, /emailStrong\.textContent = email/);
});
