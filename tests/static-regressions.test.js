const assert = require('node:assert/strict');
const { execFileSync, spawnSync } = require('node:child_process');
const { readFileSync } = require('node:fs');
const test = require('node:test');

test('tracked JavaScript files parse successfully', () => {
  const files = execFileSync('git', ['ls-files', '-z', '*.js'])
    .toString('utf8')
    .split('\0')
    .filter(Boolean);

  assert.ok(files.length > 0, 'expected at least one tracked JavaScript file');

  for (const file of files) {
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

test('Antigravity university form success does not inject raw submitted fields', () => {
  const script = readFileSync('A/LMS ĐH-CĐ - Antigravity/script.js', 'utf8');
  const successTemplate = script.match(/formSuccessBlock\.innerHTML\s*=\s*`([\s\S]*?)`;/);

  assert.ok(successTemplate, 'expected success message template');
  assert.match(script, /const escapeHtml = /);
  assert.doesNotMatch(successTemplate[1], /\$\{(?:fullname|phone|email)\}/);
  assert.match(successTemplate[1], /\$\{safeFullname\}/);
  assert.match(successTemplate[1], /\$\{safePhone\}/);
  assert.match(successTemplate[1], /\$\{safeEmail\}/);
});
