const assert = require('node:assert/strict');
const { execFileSync } = require('node:child_process');
const { readFileSync } = require('node:fs');
const path = require('node:path');
const test = require('node:test');

const repoRoot = path.resolve(__dirname, '..');

function gitLsFiles(pattern) {
  const output = execFileSync('git', ['ls-files', '-z', '--', pattern], {
    cwd: repoRoot,
    encoding: 'buffer',
  });

  return output
    .toString('utf8')
    .split('\0')
    .filter(Boolean);
}

test('tracked JavaScript files parse successfully', () => {
  for (const file of gitLsFiles('*.js')) {
    assert.doesNotThrow(
      () => {
        execFileSync(process.execPath, ['--check', file], {
          cwd: repoRoot,
          stdio: 'pipe',
        });
      },
      `${file} should pass node --check`
    );
  }
});

test('university consultation success message renders submitted fields as text', () => {
  const source = readFileSync(
    path.join(repoRoot, 'A/LMS ĐH-CĐ - Antigravity/script.js'),
    'utf8'
  );

  assert.doesNotMatch(source, /formSuccessBlock\.innerHTML\s*=/);
  assert.match(source, /nameText\.textContent\s*=\s*fullname/);
  assert.match(source, /phoneText\.textContent\s*=\s*phone/);
  assert.match(source, /emailText\.textContent\s*=\s*email/);
});
