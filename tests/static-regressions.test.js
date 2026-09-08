const assert = require('node:assert/strict');
const fs = require('node:fs');
const { spawnSync } = require('node:child_process');
const test = require('node:test');

function read(path) {
  return fs.readFileSync(path, 'utf8');
}

function gitFiles(pattern) {
  const result = spawnSync('git', ['ls-files', '-z', '--', pattern], {
    encoding: 'buffer'
  });
  assert.equal(result.status, 0, result.stderr.toString());
  return result.stdout
    .toString('utf8')
    .split('\0')
    .filter(Boolean);
}

test('tracked JavaScript files parse successfully', () => {
  const failures = [];
  for (const path of gitFiles('*.js')) {
    const result = spawnSync(process.execPath, ['--check', path], {
      encoding: 'utf8'
    });
    if (result.status !== 0) {
      failures.push(`${path}\n${result.stderr || result.stdout}`);
    }
  }

  assert.deepEqual(failures, []);
});

test('Model S configurator submits Model S checkout details', () => {
  const html = read('hk2/order-model-s.html');

  assert.match(html, /<h1>Model S<\/h1>/);
  assert.match(html, /<strong>\$62,990<\/strong>/);
  assert.match(html, /data-order-model="Model S"/);
  assert.match(html, /data-order-trim="Standard Wheels"/);
  assert.match(html, /data-order-price="\$62,990"/);
  assert.match(html, /data-order-image="models\.jpg"/);
  assert.doesNotMatch(html, /data-order-model="Model 3"/);
});

test('payment cart renders stored cart fields as text, not HTML', () => {
  const source = read('hk2/script.js');

  assert.doesNotMatch(source, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
  assert.match(source, /modelName\.textContent\s*=\s*item\.model\s*\|\|\s*"Model"/);
  assert.match(source, /trimName\.textContent\s*=\s*item\.trim\s*\|\|\s*"Base"/);
});

test('consultation success message renders submitted fields as text', () => {
  const source = read('A/LMS \u0110H-C\u0110 - Antigravity/script.js');

  assert.doesNotMatch(
    source,
    /formSuccessBlock\.innerHTML\s*=\s*`[\s\S]*\$\{(?:fullname|phone|email)\}/
  );
  assert.match(source, /fullnameText\.textContent\s*=\s*fullname/);
  assert.match(source, /phoneText\.textContent\s*=\s*phone/);
  assert.match(source, /emailText\.textContent\s*=\s*email/);
});
