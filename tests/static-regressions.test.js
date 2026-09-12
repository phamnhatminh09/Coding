const assert = require('node:assert/strict');
const { execFileSync, spawnSync } = require('node:child_process');
const { readFileSync } = require('node:fs');
const test = require('node:test');

function read(path) {
  return readFileSync(path, 'utf8');
}

test('tracked JavaScript files parse successfully', () => {
  const files = execFileSync('git', ['ls-files', '-z', '--', '*.js'], {
    encoding: 'utf8'
  }).split('\0').filter(Boolean);

  assert.ok(files.length > 0, 'expected tracked JavaScript files');

  const failures = [];
  for (const file of files) {
    const result = spawnSync(process.execPath, ['--check', file], {
      encoding: 'utf8'
    });
    if (result.status !== 0) {
      failures.push(`${file}\n${result.stderr || result.stdout}`);
    }
  }

  assert.deepEqual(failures, []);
});

test('Model S configurator submits Model S checkout metadata', () => {
  const html = read('hk2/order-model-s.html');

  assert.match(html, /<h1>Model S<\/h1>/);
  assert.match(html, /<strong>\$62,990<\/strong>/);
  assert.match(html, /data-order-model="Model S"/);
  assert.match(html, /data-order-trim="Standard Wheels"/);
  assert.match(html, /data-order-price="\$62,990"/);
  assert.doesNotMatch(html, /data-order-model="Model 3"/);
});

test('payment cart renders stored item fields as text', () => {
  const script = read('hk2/script.js');

  assert.match(script, /paymentCartItems\.replaceChildren\(\)/);
  assert.match(script, /title\.textContent = item\.model \|\| "Model"/);
  assert.match(script, /trim\.textContent = item\.trim \|\| "Base"/);
  assert.doesNotMatch(script, /paymentCartItems\.innerHTML = cart\.map/);
  assert.doesNotMatch(script, /\$\{item\.(?:model|trim|image)/);
});

test('consultation success message treats submitted contact fields as text', () => {
  const script = read('A/LMS ĐH-CĐ - Antigravity/script.js');

  assert.match(script, /nameValue\.textContent = fullname/);
  assert.match(script, /phoneValue\.textContent = phone/);
  assert.match(script, /emailValue\.textContent = email/);
  assert.doesNotMatch(script, /formSuccessBlock\.innerHTML = `[\s\S]*\$\{(?:fullname|phone|email)\}/);
});
