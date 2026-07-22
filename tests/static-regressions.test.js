const assert = require('node:assert/strict');
const { execFileSync } = require('node:child_process');
const { readFileSync } = require('node:fs');
const { test } = require('node:test');

function gitFiles(pattern) {
  return execFileSync('git', ['ls-files', '-z', '--', pattern])
    .toString('utf8')
    .split('\0')
    .filter(Boolean);
}

test('tracked JavaScript parses successfully', () => {
  for (const file of gitFiles('*.js')) {
    assert.doesNotThrow(() => execFileSync(process.execPath, ['--check', file]), file);
  }
});

test('JavaScript does not assign through optional chaining', () => {
  for (const file of gitFiles('*.js')) {
    const source = readFileSync(file, 'utf8');
    assert.doesNotMatch(source, /\?\.[^;\n]*=/, file);
  }
});

test('payment cart renders stored item fields without HTML interpolation', () => {
  const source = readFileSync('hk2/script.js', 'utf8');
  assert.doesNotMatch(source, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
  assert.match(source, /paymentCartItems\.replaceChildren\(\)/);
});

test('consultation success message does not inject submitted fields as HTML', () => {
  const source = readFileSync('A/LMS ĐH-CĐ - Antigravity/script.js', 'utf8');
  assert.doesNotMatch(source, /formSuccessBlock\.innerHTML\s*=/);
  assert.match(source, /formSuccessBlock\.replaceChildren/);
});
