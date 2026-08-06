const { execFileSync } = require('node:child_process');
const { readFileSync } = require('node:fs');
const { test } = require('node:test');

function trackedFiles(pattern) {
  const output = execFileSync('git', ['ls-files', '-z', pattern], {
    encoding: 'utf8',
  });

  return output.split('\0').filter(Boolean);
}

test('tracked JavaScript files parse successfully', () => {
  for (const file of trackedFiles('*.js')) {
    execFileSync(process.execPath, ['--check', file], {
      stdio: 'pipe',
    });
  }
});

test('payment cart does not render stored cart fields as HTML', () => {
  const source = readFileSync('hk2/script.js', 'utf8');

  assertNoPattern(
    source,
    /paymentCartItems\.innerHTML\s*=\s*cart\.map/s,
    'payment cart rows must be built with DOM APIs/textContent'
  );
});

test('consultation success message does not interpolate submitted fields into HTML', () => {
  const source = readFileSync('A/LMS ĐH-CĐ - Antigravity/script.js', 'utf8');

  assertNoPattern(
    source,
    /formSuccessBlock\.innerHTML\s*=\s*`[\s\S]*\$\{(?:fullname|phone|email)\}/,
    'submitted contact fields must be assigned via textContent'
  );
});

function assertNoPattern(source, pattern, message) {
  if (pattern.test(source)) {
    throw new Error(message);
  }
}
