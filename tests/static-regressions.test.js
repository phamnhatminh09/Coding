const assert = require('node:assert/strict');
const { execFileSync } = require('node:child_process');
const path = require('node:path');
const test = require('node:test');

const repoRoot = path.resolve(__dirname, '..');

function trackedFiles(glob) {
  const output = execFileSync('git', ['ls-files', '-z', '--', glob], {
    cwd: repoRoot,
    encoding: 'buffer',
  });

  return output.toString('utf8').split('\0').filter(Boolean);
}

test('tracked JavaScript files parse successfully', () => {
  const files = trackedFiles('*.js');

  assert.notEqual(files.length, 0, 'expected at least one tracked JavaScript file');

  for (const file of files) {
    execFileSync(process.execPath, ['--check', path.join(repoRoot, file)], {
      cwd: repoRoot,
      stdio: 'pipe',
    });
  }
});
