const assert = require('node:assert/strict');
const { execFileSync, spawnSync } = require('node:child_process');
const { readFileSync } = require('node:fs');
const path = require('node:path');
const test = require('node:test');

const repoRoot = path.resolve(__dirname, '..');

function readRepoFile(relativePath) {
  return readFileSync(path.join(repoRoot, relativePath), 'utf8');
}

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
  const failures = trackedFiles('*.js')
    .map((file) => {
      const result = spawnSync(process.execPath, ['--check', path.join(repoRoot, file)], {
        cwd: repoRoot,
        encoding: 'utf8',
      });

      return result.status === 0 ? null : `${file}\n${result.stderr || result.stdout}`;
    })
    .filter(Boolean);

  assert.deepEqual(failures, []);
});

test('Model S configurator submits Model S cart metadata', () => {
  const html = readRepoFile('hk2/order-model-s.html');

  assert.match(html, /<h1>Model S<\/h1>/);
  assert.match(html, /<strong>\$62,990<\/strong>/);
  assert.match(html, /data-order-model="Model S"/);
  assert.match(html, /data-order-trim="Standard Wheels"/);
  assert.match(html, /data-order-price="\$62,990"/);
  assert.match(html, /data-order-image="models\.jpg"/);
  assert.doesNotMatch(html, /data-order-model="Model 3"/);
});

test('payment cart renders stored cart values through DOM text APIs', () => {
  const script = readRepoFile('hk2/script.js');

  assert.match(script, /paymentCartItems\.replaceChildren\(\)/);
  assert.match(script, /title\.textContent = item\.model/);
  assert.match(script, /trim\.textContent = item\.trim/);
  assert.doesNotMatch(script, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
});

test('consultation form does not interpolate submitted fields into innerHTML', () => {
  const script = trackedFiles('*.js')
    .map((file) => readRepoFile(file))
    .find((content) => content.includes('formSuccessBlock'));

  assert.ok(script, 'expected consultation form script to be tracked');
  assert.match(script, /formSuccessBlock\.replaceChildren\(\)/);
  assert.match(script, /name\.textContent = fullname/);
  assert.match(script, /phoneText\.textContent = phone/);
  assert.match(script, /emailText\.textContent = email/);
  assert.doesNotMatch(script, /formSuccessBlock\.innerHTML/);
  assert.doesNotMatch(script, /\$\{fullname\}|\$\{phone\}|\$\{email\}/);
});
