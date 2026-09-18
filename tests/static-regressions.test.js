const assert = require('node:assert/strict');
const { execFileSync } = require('node:child_process');
const fs = require('node:fs');
const os = require('node:os');
const path = require('node:path');
const test = require('node:test');

const root = path.resolve(__dirname, '..');

function readRepoFile(relativePath) {
  return fs.readFileSync(path.join(root, relativePath), 'utf8');
}

function getAttribute(tag, name) {
  const match = tag.match(new RegExp(`${name}="([^"]*)"`));
  return match ? match[1] : null;
}

function runCppSample(source, input, expected) {
  const tmpDir = fs.mkdtempSync(path.join(os.tmpdir(), 'coding-regression-'));
  const binary = path.join(tmpDir, path.basename(source, '.cpp'));

  try {
    execFileSync(
      'g++',
      ['-std=c++17', '-Wall', '-Wextra', '-fsanitize=address,undefined', '-O1', source, '-o', binary],
      { cwd: root, stdio: 'pipe', timeout: 30000 }
    );

    const actual = execFileSync(binary, {
      cwd: root,
      input: readRepoFile(input),
      timeout: 5000
    }).toString('utf8');

    assert.equal(actual.trim(), readRepoFile(expected).trim());
  } finally {
    fs.rmSync(tmpDir, { recursive: true, force: true });
  }
}

test('tracked JavaScript files parse successfully', () => {
  const trackedFiles = execFileSync('git', ['ls-files', '-z'], { cwd: root })
    .toString('utf8')
    .split('\0')
    .filter((file) => file.endsWith('.js'));

  assert.ok(trackedFiles.length > 0, 'expected tracked JavaScript files');

  for (const file of trackedFiles) {
    assert.doesNotThrow(
      () => execFileSync(process.execPath, ['--check', file], { cwd: root, stdio: 'pipe' }),
      `${file} should parse successfully`
    );
  }
});

test('Model S configurator submits Model S cart metadata', () => {
  const html = readRepoFile('hk2/order-model-s.html');
  const cta = html.match(/<button\b[^>]*\border-config-cta\b[^>]*>/s);

  assert.ok(cta, 'expected Model S checkout button');
  assert.equal(getAttribute(cta[0], 'data-order-model'), 'Model S');
  assert.equal(getAttribute(cta[0], 'data-order-trim'), 'Standard Wheels');
  assert.equal(getAttribute(cta[0], 'data-order-price'), '$62,990');
  assert.equal(getAttribute(cta[0], 'data-order-image'), 'models.jpg');
  assert.match(html, /Vehicle price[\s\S]*\$62,990/);
});

test('payment cart escapes stored item fields before rendering HTML', () => {
  const script = readRepoFile('hk2/script.js');

  assert.match(script, /const escapeHTML = /);
  assert.doesNotMatch(script, /\$\{item\.(?:image|model|trim)/);
});

test('consultation success message renders submitted fields as text', () => {
  const script = readRepoFile('A/LMS ĐH-CĐ - Antigravity/script.js');

  assert.doesNotMatch(script, /formSuccessBlock\.innerHTML\s*=\s*`[\s\S]*\$\{(?:fullname|phone|email)\}/);
  assert.match(script, /fullnameText\.textContent = fullname/);
  assert.match(script, /phoneText\.textContent = phone/);
  assert.match(script, /emailText\.textContent = email/);
});

test('ams_jump sample does not crash or write out of bounds', () => {
  runCppSample('C++/2025/ams_jump.cpp', 'C++/2025/ams_jump_1.in', 'C++/2025/ams_jump_1.ans');
});

test('tongbang max-size sample finishes without materializing the first row', () => {
  runCppSample('C++/2025/tongbang.cpp', 'C++/2025/tongbang_6.in', 'C++/2025/tongbang_6.ans');
});
