import assert from 'node:assert/strict';
import { spawnSync } from 'node:child_process';
import { readFileSync } from 'node:fs';
import path from 'node:path';
import { test } from 'node:test';
import { fileURLToPath } from 'node:url';

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), '..');
const readRepoFile = (...parts) => readFileSync(path.join(repoRoot, ...parts), 'utf8');

test('tracked JavaScript files parse successfully', () => {
  const trackedFiles = spawnSync('git', ['ls-files', '-z', '--', '*.js'], {
    cwd: repoRoot,
    encoding: 'utf8'
  });

  assert.equal(trackedFiles.status, 0, trackedFiles.stderr);

  const jsFiles = trackedFiles.stdout.split('\0').filter(Boolean);
  assert.ok(jsFiles.length > 0, 'expected at least one tracked JavaScript file');

  for (const file of jsFiles) {
    const result = spawnSync(process.execPath, ['--check', file], {
      cwd: repoRoot,
      encoding: 'utf8'
    });
    assert.equal(result.status, 0, `${file} failed syntax check:\n${result.stderr}`);
  }
});

test('Model S configurator submits Model S order data', () => {
  const html = readRepoFile('hk2', 'order-model-s.html');
  const button = html.match(/<button class="btn btn-red order-config-cta"[\s\S]*?<\/button>/)?.[0];

  assert.ok(button, 'expected a Model S checkout button');
  assert.match(button, /data-order-model="Model S"/);
  assert.match(button, /data-order-trim="Standard Wheels"/);
  assert.match(button, /data-order-price="\$62,990"/);
  assert.match(button, /data-order-image="models\.jpg"/);
  assert.doesNotMatch(button, /Model 3|\$38,990|mods\.png/);
});

test('payment cart renders stored cart values as text nodes', () => {
  const script = readRepoFile('hk2', 'script.js');

  assert.match(script, /paymentCartItems\.replaceChildren\(\)/);
  assert.match(script, /title\.textContent = item\.model/);
  assert.match(script, /trim\.textContent = item\.trim/);
  assert.doesNotMatch(script, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
});

test('consultation form success message does not interpolate submitted fields into HTML', () => {
  const script = readRepoFile('A', 'LMS ĐH-CĐ - Antigravity', 'script.js');

  assert.match(script, /formSuccessBlock\.replaceChildren\(\)/);
  assert.match(script, /nameText\.textContent = fullname/);
  assert.match(script, /phoneText\.textContent = phone/);
  assert.match(script, /emailText\.textContent = email/);
  assert.doesNotMatch(script, /formSuccessBlock\.innerHTML/);
});

test('animal poll storage is normalized before rendering', () => {
  const script = readRepoFile('html', 'script.js');

  assert.match(script, /normalizePollCounts/);
  assert.match(script, /JSON\.parse\(storedPollCounts\)/);
  assert.match(script, /localStorage\.removeItem\('pollCounts'\)/);
  assert.match(script, /pollResult\.replaceChildren\(\)/);
  assert.doesNotMatch(script, /pollResult\.innerHTML/);
});
