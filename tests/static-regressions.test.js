const assert = require('node:assert/strict');
const { execFileSync, spawnSync } = require('node:child_process');
const fs = require('node:fs');
const path = require('node:path');
const test = require('node:test');

const repoRoot = path.resolve(__dirname, '..');

function trackedFiles(pattern) {
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
  const jsFiles = trackedFiles('*.js');

  assert.notEqual(jsFiles.length, 0, 'expected at least one tracked JavaScript file');

  for (const file of jsFiles) {
    const result = spawnSync(process.execPath, ['--check', file], {
      cwd: repoRoot,
      encoding: 'utf8',
    });

    assert.equal(
      result.status,
      0,
      `${file} failed node --check\n${result.stderr || result.stdout}`
    );
  }
});

test('consultation success message does not inject submitted values as HTML', () => {
  const scriptPath = path.join(repoRoot, 'A/LMS ĐH-CĐ - Antigravity/script.js');
  const source = fs.readFileSync(scriptPath, 'utf8');

  assert.doesNotMatch(
    source,
    /formSuccessBlock\.innerHTML\s*=\s*`[\s\S]*\$\{\s*(?:fullname|phone|email)\s*\}/,
    'submitted contact fields must not be interpolated into formSuccessBlock.innerHTML'
  );

  assert.match(source, /formSuccessBlock\.replaceChildren\(/);
  assert.match(source, /createStrongText\(fullname\)/);
  assert.match(source, /createStrongText\(phone\)/);
  assert.match(source, /createStrongText\(email\)/);
});
