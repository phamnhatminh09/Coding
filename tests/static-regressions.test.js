const assert = require('node:assert/strict');
const { spawnSync } = require('node:child_process');
const fs = require('node:fs');
const path = require('node:path');
const test = require('node:test');

const repoRoot = path.resolve(__dirname, '..');

function readRepoFile(...segments) {
  return fs.readFileSync(path.join(repoRoot, ...segments), 'utf8');
}

test('tracked JavaScript files parse successfully', () => {
  const gitResult = spawnSync('git', ['ls-files', '-z', '*.js'], {
    cwd: repoRoot,
    encoding: 'utf8',
  });
  assert.equal(gitResult.status, 0, gitResult.stderr);

  const files = gitResult.stdout.split('\0').filter(Boolean);
  assert.ok(files.length > 0, 'expected tracked JavaScript files');

  for (const file of files) {
    const check = spawnSync(process.execPath, ['--check', file], {
      cwd: repoRoot,
      encoding: 'utf8',
    });
    assert.equal(check.status, 0, `${file} failed syntax check:\n${check.stderr}`);
  }
});

test('Model S configurator submits Model S checkout metadata', () => {
  const html = readRepoFile('hk2', 'order-model-s.html');

  assert.match(html, /<h1>\s*Model S\s*<\/h1>/);
  assert.match(html, /<strong>\$62,990<\/strong>/);
  assert.match(html, /data-order-model="Model S"/);
  assert.match(html, /data-order-trim="Standard Wheels"/);
  assert.match(html, /data-order-price="\$62,990"/);
  assert.match(html, /data-order-image="mods-white\.png"/);
  assert.doesNotMatch(html, /data-order-model="Model 3"/);
});

test('payment cart renders stored cart metadata as text', () => {
  const script = readRepoFile('hk2', 'script.js');

  assert.doesNotMatch(script, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
  assert.match(script, /title\.textContent\s*=\s*item\.model/);
  assert.match(script, /trim\.textContent\s*=\s*item\.trim/);
  assert.match(script, /paymentCartItems\.replaceChildren\(fragment\)/);
});

test('consultation success message does not interpolate submitted fields as HTML', () => {
  const script = fs.readFileSync(
    path.join(repoRoot, 'A', 'LMS \u0110H-C\u0110 - Antigravity', 'script.js'),
    'utf8'
  );

  assert.doesNotMatch(script, /formSuccessBlock\.innerHTML\s*=/);
  assert.match(script, /textContent:\s*fullname/);
  assert.match(script, /textContent:\s*phone/);
  assert.match(script, /textContent:\s*email/);
});
