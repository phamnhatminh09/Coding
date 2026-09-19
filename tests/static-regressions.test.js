const assert = require('node:assert/strict');
const { execFileSync } = require('node:child_process');
const fs = require('node:fs');
const path = require('node:path');
const test = require('node:test');

const repoRoot = path.resolve(__dirname, '..');

function read(relativePath) {
  return fs.readFileSync(path.join(repoRoot, relativePath), 'utf8');
}

function getAttribute(markup, name) {
  const match = markup.match(new RegExp(`${name}="([^"]*)"`));
  assert.ok(match, `Expected ${name} attribute`);
  return match[1];
}

test('tracked JavaScript files parse successfully', () => {
  const output = execFileSync('git', ['ls-files', '-z'], { cwd: repoRoot });
  const jsFiles = output
    .toString('utf8')
    .split('\0')
    .filter((file) => file.endsWith('.js'));

  assert.ok(jsFiles.length > 0, 'Expected at least one JavaScript file');

  for (const file of jsFiles) {
    execFileSync(process.execPath, ['--check', file], { cwd: repoRoot, stdio: 'pipe' });
  }
});

test('Model S configurator submits Model S cart metadata', () => {
  const source = read('hk2/order-model-s.html');
  const button = source.match(/<button class="btn btn-red order-config-cta"[\s\S]*?<\/button>/);

  assert.ok(button, 'Expected Model S checkout button');
  assert.match(source, /<h1>Model S<\/h1>/);
  assert.match(source, /Vehicle price[\s\S]*<strong>\$62,990<\/strong>/);
  assert.equal(getAttribute(button[0], 'data-order-model'), 'Model S');
  assert.equal(getAttribute(button[0], 'data-order-trim'), 'Standard Wheels');
  assert.equal(getAttribute(button[0], 'data-order-price'), '$62,990');
  assert.equal(getAttribute(button[0], 'data-order-image'), 'models.jpg');
});

test('payment cart renderer does not interpolate stored cart HTML', () => {
  const source = read('hk2/script.js');

  assert.doesNotMatch(source, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
  assert.doesNotMatch(source, /\$\{item\.(?:image|model|trim)/);
  assert.match(source, /paymentCartItems\.replaceChildren\(\)/);
  assert.match(source, /title\.textContent = item\.model \|\| "Model"/);
});

test('consultation success message renders submitted fields as text', () => {
  const source = read('A/LMS ĐH-CĐ - Antigravity/script.js');

  assert.doesNotMatch(source, /formSuccessBlock\.innerHTML\s*=`[\s\S]*\$\{(?:fullname|phone|email)\}/);
  assert.match(source, /nameText\.textContent = fullname/);
  assert.match(source, /phoneText\.textContent = phone/);
  assert.match(source, /emailText\.textContent = email/);
});

test('animal poll storage is normalized and rendered without HTML interpolation', () => {
  const source = read('html/script.js');

  assert.match(source, /function normalizePollCounts/);
  assert.match(source, /try \{[\s\S]*JSON\.parse\(localStorage\.getItem\('pollCounts'\)\)/);
  assert.match(source, /localStorage\.removeItem\('pollCounts'\)/);
  assert.doesNotMatch(source, /pollResult\.innerHTML/);
  assert.match(source, /pollResult\.replaceChildren\(/);
});
