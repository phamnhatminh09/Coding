const assert = require('node:assert/strict');
const { execFileSync } = require('node:child_process');
const test = require('node:test');

function trackedJavaScriptFiles() {
  const output = execFileSync('git', ['ls-files', '-z', '--', '*.js']);
  return output
    .toString('utf8')
    .split('\0')
    .filter(Boolean);
}

test('tracked JavaScript files parse successfully', () => {
  const failures = [];

  for (const file of trackedJavaScriptFiles()) {
    try {
      execFileSync(process.execPath, ['--check', file], { stdio: 'pipe' });
    } catch (error) {
      failures.push(`${file}\n${error.stdout || ''}${error.stderr || ''}`);
    }
  }

  assert.deepEqual(failures, []);
});
