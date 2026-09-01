const assert = require('node:assert/strict');
const { spawnSync } = require('node:child_process');
const { readFileSync } = require('node:fs');
const path = require('node:path');
const test = require('node:test');

const repoRoot = path.resolve(__dirname, '..');

function read(relativePath) {
  return readFileSync(path.join(repoRoot, relativePath), 'utf8');
}

function trackedJavaScriptFiles() {
  const result = spawnSync('git', ['ls-files', '-z', '--', '*.js'], {
    cwd: repoRoot,
    encoding: 'buffer',
  });

  assert.equal(result.status, 0, result.stderr.toString('utf8'));
  return result.stdout.toString('utf8').split('\0').filter(Boolean);
}

test('tracked JavaScript files parse successfully', () => {
  const failures = [];

  for (const file of trackedJavaScriptFiles()) {
    const result = spawnSync(process.execPath, ['--check', path.join(repoRoot, file)], {
      encoding: 'utf8',
    });

    if (result.status !== 0) {
      failures.push(`${file}\n${result.stderr || result.stdout}`);
    }
  }

  assert.deepEqual(failures, []);
});

test('LMS Lite nav close handler does not assign through optional chaining', () => {
  const script = read(path.join('C', 'LMS Lite - Cursor', 'js', 'main.js'));

  assert.doesNotMatch(script, /navToggle\?\.querySelector\('i'\)\.className\s*=/);
});

test('Model S configurator submits Model S order metadata', () => {
  const html = read(path.join('hk2', 'order-model-s.html'));
  const button = html.match(/<button class="btn btn-red order-config-cta"[\s\S]*?<\/button>/);

  assert.ok(button, 'Model S checkout button should exist');
  assert.match(button[0], /data-order-model="Model S"/);
  assert.match(button[0], /data-order-trim="Standard Wheels"/);
  assert.match(button[0], /data-order-price="\$62,990"/);
  assert.match(button[0], /data-order-image="models\.jpg"/);
  assert.doesNotMatch(button[0], /Model 3|\$38,990/);
  assert.match(html, /<strong>\$62,990<\/strong>/);
});

test('payment cart rows render stored cart fields as text', () => {
  const script = read(path.join('hk2', 'script.js'));

  assert.doesNotMatch(script, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
  assert.doesNotMatch(script, /\$\{item\.(?:image|model|trim)/);
  assert.match(script, /model\.textContent = item\.model \|\| "Model"/);
  assert.match(script, /trim\.textContent = item\.trim \|\| "Base"/);
  assert.match(script, /paymentCartItems\.replaceChildren\(fragment\)/);
});

test('college LMS success message renders submitted fields as text', () => {
  const script = read(path.join('A', 'LMS \u0110H-C\u0110 - Antigravity', 'script.js'));

  assert.doesNotMatch(script, /formSuccessBlock\.innerHTML\s*=\s*`[\s\S]*\$\{(?:fullname|phone|email)\}/);
  assert.match(script, /fullnameStrong\.textContent = fullname/);
  assert.match(script, /phoneStrong\.textContent = phone/);
  assert.match(script, /emailStrong\.textContent = email/);
  assert.match(script, /formSuccessBlock\.append\(successIcon, successTitle, message, resetButton\)/);
});
