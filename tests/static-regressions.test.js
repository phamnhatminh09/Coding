const assert = require('node:assert/strict');
const { execFileSync } = require('node:child_process');
const fs = require('node:fs');
const path = require('node:path');
const test = require('node:test');

const root = path.resolve(__dirname, '..');

function read(relativePath) {
  return fs.readFileSync(path.join(root, relativePath), 'utf8');
}

test('tracked JavaScript files parse successfully', () => {
  const files = execFileSync('git', ['ls-files', '-z', '*.js'], {
    cwd: root,
    encoding: 'utf8',
  })
    .split('\0')
    .filter(Boolean);

  assert.ok(files.length > 0, 'expected JavaScript files to be tracked');

  for (const file of files) {
    execFileSync(process.execPath, ['--check', path.join(root, file)], {
      cwd: root,
      stdio: 'pipe',
    });
  }
});

test('LMS Lite nav close handler avoids optional-chain assignment', () => {
  const script = read('C/LMS Lite - Cursor/js/main.js');

  assert.doesNotMatch(script, /navToggle\?\.querySelector\('i'\)\.className\s*=/);
  assert.match(script, /const icon = navToggle\?\.querySelector\('i'\);/);
  assert.match(script, /if \(icon\) icon\.className = 'bx bx-menu';/);
});

test('payment cart renders stored cart fields without HTML interpolation', () => {
  const script = read('hk2/script.js');

  assert.match(script, /paymentCartItems\.replaceChildren\(\);/);
  assert.doesNotMatch(script, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
  assert.doesNotMatch(script, /\$\{item\.(?:image|model|trim)/);
  assert.match(script, /model\.textContent = item\.model \|\| "Model";/);
  assert.match(script, /trim\.textContent = item\.trim \|\| "Base";/);
});

test('consultation success message inserts submitted fields as text', () => {
  const script = read('A/LMS ĐH-CĐ - Antigravity/script.js');

  assert.doesNotMatch(script, /formSuccessBlock\.innerHTML\s*=/);
  assert.match(script, /nameText\.textContent = fullname;/);
  assert.match(script, /phoneText\.textContent = phone;/);
  assert.match(script, /emailText\.textContent = email;/);
  assert.match(script, /resetButton\.addEventListener\('click', \(\) => location\.reload\(\)\);/);
});

test('Model S configurator submits Model S cart metadata', () => {
  const html = read('hk2/order-model-s.html');

  assert.match(html, /<strong>\$62,990<\/strong>/);
  assert.match(html, /data-order-model="Model S"/);
  assert.match(html, /data-order-trim="Standard Wheels"/);
  assert.match(html, /data-order-price="\$62,990"/);
  assert.match(html, /data-order-image="models\.jpg"/);
  assert.doesNotMatch(html, /data-order-model="Model 3"/);
});
