const { spawnSync } = require('node:child_process');
const test = require('node:test');
const assert = require('node:assert/strict');

function gitTrackedFiles(pattern) {
  const result = spawnSync('git', ['ls-files', '-z', '--', pattern], {
    encoding: 'buffer',
  });

  assert.equal(
    result.status,
    0,
    `git ls-files failed: ${result.stderr.toString('utf8')}`
  );

  return result.stdout
    .toString('utf8')
    .split('\0')
    .filter(Boolean);
}

test('tracked JavaScript files parse successfully', () => {
  const failures = [];

  for (const file of gitTrackedFiles('*.js')) {
    const result = spawnSync(process.execPath, ['--check', file], {
      encoding: 'utf8',
    });

    if (result.status !== 0) {
      failures.push(`${file}\n${result.stderr || result.stdout}`);
    }
  }

  assert.deepEqual(failures, []);
});
