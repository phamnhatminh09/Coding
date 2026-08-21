const assert = require('node:assert/strict');
const { execFileSync } = require('node:child_process');
const { readFileSync } = require('node:fs');
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

test('consultation form success message does not interpolate submitted values into HTML', () => {
  const script = readFileSync('A/LMS \u0110H-C\u0110 - Antigravity/script.js', 'utf8');

  assert.doesNotMatch(
    script,
    /formSuccessBlock\.innerHTML\s*=\s*`[\s\S]*\$\{(?:fullname|phone|email|school)\}/,
    'submitted contact fields must not be rendered through innerHTML'
  );
  assert.match(script, /nameText\.textContent = fullname/);
  assert.match(script, /phoneText\.textContent = phone/);
  assert.match(script, /emailText\.textContent = email/);
});
