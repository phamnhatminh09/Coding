const { execFileSync, spawnSync } = require('node:child_process');
const { readFileSync } = require('node:fs');
const path = require('node:path');
const test = require('node:test');
const assert = require('node:assert/strict');

const repoRoot = path.resolve(__dirname, '..');

function gitFiles(pathspec) {
  return execFileSync('git', ['ls-files', '-z', pathspec], { cwd: repoRoot })
    .toString('utf8')
    .split('\0')
    .filter(Boolean);
}

test('tracked JavaScript files parse successfully', () => {
  const failures = [];

  for (const file of gitFiles('*.js')) {
    const result = spawnSync(process.execPath, ['--check', file], {
      cwd: repoRoot,
      encoding: 'utf8',
    });

    if (result.status !== 0) {
      failures.push(`${file}\n${result.stderr || result.stdout}`);
    }
  }

  assert.deepEqual(failures, []);
});

test('consultation success message does not interpolate submitted fields as HTML', () => {
  const script = readFileSync(
    path.join(repoRoot, 'A/LMS ĐH-CĐ - Antigravity/script.js'),
    'utf8',
  );

  assert.doesNotMatch(
    script,
    /formSuccessBlock\.innerHTML\s*=\s*`[\s\S]*\$\{(?:fullname|phone|email|school)\}/,
  );
  assert.match(script, /nameStrong\.textContent = fullname;/);
  assert.match(script, /phoneStrong\.textContent = phone;/);
  assert.match(script, /emailStrong\.textContent = email;/);
});
