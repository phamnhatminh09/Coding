const { execFileSync, spawnSync } = require('node:child_process');
const { readFileSync } = require('node:fs');
const test = require('node:test');
const assert = require('node:assert/strict');

function trackedFiles(pattern) {
  const output = execFileSync('git', ['ls-files', '-z', pattern]);
  return output
    .toString('utf8')
    .split('\0')
    .filter(Boolean);
}

test('tracked JavaScript files parse successfully', () => {
  const jsFiles = trackedFiles('*.js');
  assert.ok(jsFiles.length > 0, 'expected at least one tracked JavaScript file');

  const failures = [];
  for (const file of jsFiles) {
    const result = spawnSync(process.execPath, ['--check', file], {
      encoding: 'utf8'
    });

    if (result.status !== 0) {
      failures.push(`--- ${file}\n${result.stdout}${result.stderr}`);
    }
  }

  assert.deepEqual(failures, []);
});

test('Model S configurator submits Model S checkout metadata', () => {
  const html = readFileSync('hk2/order-model-s.html', 'utf8');

  assert.match(html, /<h1>Model S<\/h1>/);
  assert.match(html, /data-order-model="Model S"/);
  assert.match(html, /data-order-trim="Standard Wheels"/);
  assert.match(html, /data-order-price="\$62,990"/);
  assert.match(html, /data-order-image="models\.jpg"/);
});
