const { execFileSync, spawnSync } = require('node:child_process');
const { test } = require('node:test');
const assert = require('node:assert/strict');

function gitTrackedFiles(pattern) {
  const output = execFileSync('git', ['ls-files', '-z', pattern], {
    cwd: process.cwd(),
    encoding: 'buffer',
  });

  return output
    .toString('utf8')
    .split('\0')
    .filter(Boolean);
}

test('tracked JavaScript files parse successfully', () => {
  const failures = [];

  for (const file of gitTrackedFiles('*.js')) {
    const result = spawnSync(process.execPath, ['--check', file], {
      cwd: process.cwd(),
      encoding: 'utf8',
    });

    if (result.status !== 0) {
      failures.push(`\n${file}\n${result.stdout}${result.stderr}`);
    }
  }

  assert.equal(failures.length, 0, failures.join('\n'));
});
