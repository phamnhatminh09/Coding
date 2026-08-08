const assert = require('node:assert/strict');
const { execFileSync, spawnSync } = require('node:child_process');
const test = require('node:test');

function trackedJavaScriptFiles() {
  return execFileSync('git', ['ls-files', '-z', '*.js'], { encoding: 'utf8' })
    .split('\0')
    .filter(Boolean);
}

test('tracked JavaScript files parse successfully', () => {
  const failures = [];

  for (const file of trackedJavaScriptFiles()) {
    const result = spawnSync(process.execPath, ['--check', file], {
      encoding: 'utf8'
    });

    if (result.status !== 0) {
      failures.push(`${file}\n${result.stdout}${result.stderr}`);
    }
  }

  assert.deepEqual(failures, []);
});
