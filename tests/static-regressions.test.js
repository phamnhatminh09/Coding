const { spawnSync } = require('node:child_process');
const { readFileSync } = require('node:fs');
const test = require('node:test');
const assert = require('node:assert/strict');

function gitTrackedFiles(pattern) {
  const result = spawnSync('git', ['ls-files', '-z', '--', pattern], {
    encoding: 'buffer',
  });

  assert.equal(
    result.status,
    0,
    `git ls-files failed: ${result.stderr.toString('utf8')}`
  );

  return result.stdout
    .toString('utf8')
    .split('\0')
    .filter(Boolean);
}

test('tracked JavaScript files parse successfully', () => {
  const failures = [];

  for (const file of gitTrackedFiles('*.js')) {
    const result = spawnSync(process.execPath, ['--check', file], {
      encoding: 'utf8',
    });

    if (result.status !== 0) {
      failures.push(`${file}\n${result.stderr || result.stdout}`);
    }
  }

  assert.deepEqual(failures, []);
});

function getAttribute(markup, name) {
  const match = markup.match(new RegExp(`\\s${name}="([^"]*)"`));
  assert.ok(match, `Missing ${name} in ${markup}`);
  return match[1];
}

test('Model S configurator submits Model S cart metadata', () => {
  const html = readFileSync('hk2/order-model-s.html', 'utf8');
  const buttonMatch = html.match(
    /<button class="btn btn-red order-config-cta"[\s\S]*?<\/button>/
  );

  assert.ok(buttonMatch, 'Missing Model S checkout button');
  assert.match(html, /<h1>Model S<\/h1>/);
  assert.match(html, /<strong>\$62,990<\/strong>/);

  const button = buttonMatch[0];
  assert.equal(getAttribute(button, 'data-order-model'), 'Model S');
  assert.equal(getAttribute(button, 'data-order-trim'), 'Standard Wheels');
  assert.equal(getAttribute(button, 'data-order-price'), '$62,990');
  assert.equal(getAttribute(button, 'data-order-image'), 'models.jpg');
});
