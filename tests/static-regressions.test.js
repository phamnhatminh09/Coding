const assert = require('node:assert/strict');
const { execFileSync } = require('node:child_process');
const test = require('node:test');

function gitTrackedJsFiles() {
  const output = execFileSync('git', ['ls-files', '-z', '*.js'], {
    cwd: process.cwd(),
    encoding: 'buffer',
  });

  return output
    .toString('utf8')
    .split('\0')
    .filter(Boolean);
}

test('tracked JavaScript files parse successfully', () => {
  const jsFiles = gitTrackedJsFiles();
  assert.ok(jsFiles.length > 0, 'expected at least one tracked JavaScript file');

  for (const file of jsFiles) {
    assert.doesNotThrow(
      () => execFileSync(process.execPath, ['--check', file], { cwd: process.cwd(), stdio: 'pipe' }),
      `${file} should parse successfully`
    );
  }
});
