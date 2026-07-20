const assert = require('node:assert/strict');
const { spawnSync } = require('node:child_process');
const test = require('node:test');

function run(command, args) {
  return spawnSync(command, args, {
    cwd: process.cwd(),
    encoding: 'utf8',
    stdio: ['ignore', 'pipe', 'pipe'],
  });
}

test('tracked JavaScript files parse successfully', () => {
  const listed = run('git', ['ls-files', '-z', '--', '*.js']);
  assert.equal(listed.status, 0, listed.stderr);

  const files = listed.stdout.split('\0').filter(Boolean);
  assert.ok(files.length > 0, 'expected at least one tracked JavaScript file');

  const failures = [];
  for (const file of files) {
    const checked = run(process.execPath, ['--check', file]);
    if (checked.status !== 0) {
      failures.push(`${file}\n${checked.stdout}${checked.stderr}`);
    }
  }

  assert.deepEqual(failures, [], failures.join('\n'));
});
