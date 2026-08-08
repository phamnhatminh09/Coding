const assert = require('node:assert/strict');
const { execFileSync, spawnSync } = require('node:child_process');
const { readFileSync } = require('node:fs');
const test = require('node:test');

function trackedJavaScriptFiles() {
  return execFileSync('git', ['ls-files', '-z', '*.js'], { encoding: 'utf8' })
    .split('\0')
    .filter(Boolean);
}

test('tracked JavaScript files parse successfully', () => {
  const failures = [];

  for (const file of trackedJavaScriptFiles()) {
    const result = spawnSync(process.execPath, ['--check', file], {
      encoding: 'utf8'
    });

    if (result.status !== 0) {
      failures.push(`${file}\n${result.stdout}${result.stderr}`);
    }
  }

  assert.deepEqual(failures, []);
});

test('Model S configurator submits Model S checkout metadata', () => {
  const html = readFileSync('hk2/order-model-s.html', 'utf8');

  assert.match(html, /<h1>Model S<\/h1>/);
  assert.match(html, /<strong>\$62,990<\/strong>/);
  assert.match(html, /data-order-model="Model S"/);
  assert.match(html, /data-order-trim="Standard Wheels"/);
  assert.match(html, /data-order-price="\$62,990"/);
  assert.match(html, /data-order-image="models\.jpg"/);
});

test('consultation success message renders submitted values as text', () => {
  const script = readFileSync('A/LMS ĐH-CĐ - Antigravity/script.js', 'utf8');

  assert.doesNotMatch(script, /formSuccessBlock\.innerHTML/);
  assert.match(script, /formSuccessBlock\.replaceChildren/);
  assert.match(script, /textContent: fullname/);
  assert.match(script, /textContent: phone/);
  assert.match(script, /textContent: email/);
});
