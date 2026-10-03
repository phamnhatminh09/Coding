const { execFileSync } = require('node:child_process');
const test = require('node:test');

function gitFiles(pattern) {
  const output = execFileSync('git', ['ls-files', '-z', pattern]);
  return output
    .toString('utf8')
    .split('\0')
    .filter(Boolean);
}

test('tracked JavaScript files parse successfully', () => {
  for (const file of gitFiles('*.js')) {
    execFileSync('node', ['--check', file], { stdio: 'pipe' });
  }
});
