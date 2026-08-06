const { execFileSync } = require('node:child_process');
const { test } = require('node:test');

function trackedFiles(pattern) {
  const output = execFileSync('git', ['ls-files', '-z', pattern], {
    encoding: 'utf8',
  });

  return output.split('\0').filter(Boolean);
}

test('tracked JavaScript files parse successfully', () => {
  for (const file of trackedFiles('*.js')) {
    execFileSync(process.execPath, ['--check', file], {
      stdio: 'pipe',
    });
  }
});
