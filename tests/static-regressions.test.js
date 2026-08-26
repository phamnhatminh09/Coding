const assert = require('node:assert/strict');
const { execFileSync } = require('node:child_process');
const fs = require('node:fs');
const path = require('node:path');
const test = require('node:test');

const repoRoot = path.resolve(__dirname, '..');

function readRepoFile(...parts) {
  return fs.readFileSync(path.join(repoRoot, ...parts), 'utf8');
}

test('tracked JavaScript files parse successfully', () => {
  const jsFiles = execFileSync('git', ['ls-files', '-z', '*.js'], {
    cwd: repoRoot
  })
    .toString('utf8')
    .split('\0')
    .filter(Boolean);

  assert.ok(jsFiles.length > 0, 'expected tracked JavaScript files');

  const failures = [];
  for (const file of jsFiles) {
    try {
      execFileSync('node', ['--check', file], {
        cwd: repoRoot,
        stdio: 'pipe'
      });
    } catch (error) {
      failures.push(`${file}\n${error.stdout || ''}${error.stderr || ''}`);
    }
  }

  assert.deepEqual(failures, []);
});

test('LMS Lite mobile nav reset avoids optional-chain assignment', () => {
  const script = readRepoFile('C', 'LMS Lite - Cursor', 'js', 'main.js');

  assert.doesNotMatch(
    script,
    /navToggle\?\.\s*querySelector\(['"]i['"]\)\.className\s*=/,
    'optional chaining cannot appear on the left side of an assignment'
  );
});

test('Antigravity university form renders submitted fields as text', () => {
  const script = readRepoFile('A', 'LMS \u0110H-C\u0110 - Antigravity', 'script.js');

  assert.doesNotMatch(
    script,
    /formSuccessBlock\.innerHTML\s*=\s*`[\s\S]*\$\{(?:fullname|phone|email)\}/,
    'submitted contact fields must not be interpolated into innerHTML'
  );
  assert.match(script, /nameStrong\.textContent\s*=\s*fullname/);
  assert.match(script, /phoneStrong\.textContent\s*=\s*phone/);
  assert.match(script, /emailStrong\.textContent\s*=\s*email/);
});
