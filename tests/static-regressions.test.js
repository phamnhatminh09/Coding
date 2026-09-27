const assert = require('node:assert/strict');
const { spawnSync } = require('node:child_process');
const fs = require('node:fs');
const path = require('node:path');
const test = require('node:test');

const repoRoot = path.resolve(__dirname, '..');
const read = (...segments) => fs.readFileSync(path.join(repoRoot, ...segments), 'utf8');

test('tracked static JavaScript entrypoints parse', () => {
  const scripts = [
    ['A', 'LMS AI', 'script.js'],
    ['A', 'LMS Lite - Antigravity', 'script.js'],
    ['A', 'LMS ĐH-CĐ - Antigravity', 'script.js'],
    ['C', 'LMS AI', 'script.js'],
    ['C', 'LMS Lite - Cursor', 'js', 'main.js'],
    ['C', 'LMS ĐH-CĐ - Cursor', 'js', 'main.js'],
    ['hk2', 'script.js'],
    ['html', 'script.js']
  ];

  for (const script of scripts) {
    const scriptPath = path.join(repoRoot, ...script);
    const result = spawnSync(process.execPath, ['--check', scriptPath], { encoding: 'utf8' });
    assert.equal(result.status, 0, `${script.join('/')} should parse:\n${result.stderr}`);
  }
});

test('Model S configurator submits Model S cart metadata', () => {
  const html = read('hk2', 'order-model-s.html');

  assert.match(html, /<h1>Model S<\/h1>/);
  assert.match(html, /<strong>\$62,990<\/strong>/);
  assert.match(html, /data-order-model="Model S"/);
  assert.match(html, /data-order-trim="Standard Wheels"/);
  assert.match(html, /data-order-price="\$62,990"/);
  assert.match(html, /data-order-image="mods-white\.png"/);
  assert.doesNotMatch(html, /data-order-model="Model 3"/);
  assert.doesNotMatch(html, /data-order-price="\$38,990"/);
});

test('payment cart renders stored cart fields without HTML interpolation', () => {
  const script = read('hk2', 'script.js');

  assert.match(script, /paymentCartItems\.replaceChildren\(\)/);
  assert.match(script, /model\.textContent = item\.model \|\| "Model"/);
  assert.match(script, /trim\.textContent = item\.trim \|\| "Base"/);
  assert.doesNotMatch(script, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
  assert.doesNotMatch(script, /<h3>\$\{item\.model/);
});

test('consultation success message treats submitted fields as text', () => {
  const script = read('A', 'LMS ĐH-CĐ - Antigravity', 'script.js');

  assert.match(script, /formSuccessBlock\.replaceChildren\(\)/);
  assert.match(script, /nameText\.textContent = fullname/);
  assert.match(script, /phoneText\.textContent = phone/);
  assert.match(script, /emailText\.textContent = email/);
  assert.doesNotMatch(script, /formSuccessBlock\.innerHTML/);
  assert.doesNotMatch(script, /\$\{fullname\}|\$\{phone\}|\$\{email\}/);
});
