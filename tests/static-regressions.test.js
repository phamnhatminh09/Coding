const assert = require('node:assert/strict');
const { execFileSync } = require('node:child_process');
const { readFileSync } = require('node:fs');
const test = require('node:test');

function gitTrackedFiles(pattern) {
  const output = execFileSync('git', ['ls-files', '-z', pattern], {
    encoding: 'buffer',
  });

  return output
    .toString('utf8')
    .split('\0')
    .filter(Boolean);
}

test('tracked JavaScript files parse successfully', () => {
  for (const file of gitTrackedFiles('*.js')) {
    assert.doesNotThrow(() => {
      execFileSync(process.execPath, ['--check', file], { stdio: 'pipe' });
    }, `${file} should parse`);
  }
});

test('Model S configurator submits Model S checkout metadata', () => {
  const html = readFileSync('hk2/order-model-s.html', 'utf8');
  const buttonMatch = html.match(
    /<button[^>]*class="[^"]*\border-config-cta\b[^"]*"[^>]*>[\s\S]*?<\/button>/
  );

  assert.ok(buttonMatch, 'Model S checkout button should exist');

  const button = buttonMatch[0];
  assert.match(button, /data-order-model="Model S"/);
  assert.match(button, /data-order-trim="Standard Wheels"/);
  assert.match(button, /data-order-price="\$62,990"/);
  assert.match(button, /data-order-image="models\.jpg"/);
  assert.doesNotMatch(button, /data-order-model="Model 3"/);
});
