const assert = require('node:assert/strict');
const { execFileSync, spawnSync } = require('node:child_process');
const { readFileSync } = require('node:fs');
const test = require('node:test');

function gitFiles(pattern) {
  const output = execFileSync('git', ['ls-files', '-z', pattern]);
  return output.toString('utf8').split('\0').filter(Boolean);
}

function attributesForFirstTag(html, selectorClass) {
  const classPattern = new RegExp(`<[^>]*class=["'][^"']*\\b${selectorClass}\\b[^"']*["'][^>]*>`, 'i');
  const tag = html.match(classPattern)?.[0];
  assert.ok(tag, `Expected to find an element with class ${selectorClass}`);

  const attrs = {};
  for (const match of tag.matchAll(/([\w-]+)=["']([^"']*)["']/g)) {
    attrs[match[1]] = match[2];
  }
  return attrs;
}

test('tracked JavaScript files parse successfully', () => {
  for (const file of gitFiles('*.js')) {
    const result = spawnSync(process.execPath, ['--check', file], {
      encoding: 'utf8'
    });

    assert.equal(
      result.status,
      0,
      `${file} failed to parse:\n${result.stderr || result.stdout}`
    );
  }
});

test('Model S configurator stores Model S checkout metadata', () => {
  const html = readFileSync('hk2/order-model-s.html', 'utf8');
  const attrs = attributesForFirstTag(html, 'order-config-cta');

  assert.equal(attrs['data-order-model'], 'Model S');
  assert.equal(attrs['data-order-trim'], 'Standard Wheels');
  assert.equal(attrs['data-order-price'], '$62,990');
  assert.equal(attrs['data-order-image'], 'models.jpg');
  assert.match(html, /<h1>\s*Model S\s*<\/h1>/);
  assert.match(html, /<strong>\$62,990<\/strong>/);
});
