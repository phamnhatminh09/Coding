const { execFileSync } = require('node:child_process');
const { test } = require('node:test');

function trackedJavaScriptFiles() {
  const output = execFileSync('git', ['ls-files', '-z', '*.js'], {
    encoding: 'utf8',
  });

  return output.split('\0').filter(Boolean);
}

test('tracked JavaScript files parse successfully', () => {
  for (const file of trackedJavaScriptFiles()) {
    execFileSync(process.execPath, ['--check', file], {
      encoding: 'utf8',
      stdio: 'pipe',
    });
  }
});
