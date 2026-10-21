const assert = require('node:assert/strict');
const { spawnSync } = require('node:child_process');
const fs = require('node:fs');
const os = require('node:os');
const path = require('node:path');
const test = require('node:test');

const repoRoot = path.resolve(__dirname, '..');

function read(relPath) {
  return fs.readFileSync(path.join(repoRoot, relPath), 'utf8');
}

test('tracked JavaScript files parse successfully', () => {
  const ls = spawnSync('git', ['ls-files', '-z', '*.js'], {
    cwd: repoRoot,
    encoding: 'buffer'
  });
  assert.equal(ls.status, 0, ls.stderr.toString('utf8'));

  const files = ls.stdout.toString('utf8').split('\0').filter(Boolean);
  assert.ok(files.length > 0, 'expected at least one tracked JS file');

  for (const file of files) {
    const checked = spawnSync(process.execPath, ['--check', path.join(repoRoot, file)], {
      encoding: 'utf8'
    });
    assert.equal(
      checked.status,
      0,
      `${file} failed to parse:\n${checked.stderr || checked.stdout}`
    );
  }
});

test('tracked inline scripts parse successfully', () => {
  const ls = spawnSync('git', ['ls-files', '-z', '*.html'], {
    cwd: repoRoot,
    encoding: 'buffer'
  });
  assert.equal(ls.status, 0, ls.stderr.toString('utf8'));

  const tmpDir = fs.mkdtempSync(path.join(os.tmpdir(), 'inline-scripts-'));
  const files = ls.stdout.toString('utf8').split('\0').filter(Boolean);
  const scriptPattern = /<script\b([^>]*)>([\s\S]*?)<\/script>/gi;
  let checkedCount = 0;

  for (const file of files) {
    const html = read(file);
    let match;
    let index = 0;
    while ((match = scriptPattern.exec(html)) !== null) {
      const [, attrs, script] = match;
      if (/\bsrc\s*=/.test(attrs)) continue;

      const typeMatch = attrs.match(/\btype\s*=\s*["']?([^"'\s>]+)/i);
      if (typeMatch && !/^(module|text\/javascript|application\/javascript)$/i.test(typeMatch[1])) {
        continue;
      }

      const tempScript = path.join(tmpDir, `${file.replace(/[^a-z0-9_-]/gi, '_')}-${index}.js`);
      fs.writeFileSync(tempScript, script);
      const checked = spawnSync(process.execPath, ['--check', tempScript], { encoding: 'utf8' });
      assert.equal(
        checked.status,
        0,
        `${file} inline script ${index} failed to parse:\n${checked.stderr || checked.stdout}`
      );
      checkedCount += 1;
      index += 1;
    }
  }

  assert.ok(checkedCount > 0, 'expected at least one inline script to be checked');
});

test('Model S configurator submits the visible Model S order', () => {
  const html = read('hk2/order-model-s.html');

  assert.match(html, /<h1>\s*Model S\s*<\/h1>/);
  assert.match(html, /<strong>\$62,990<\/strong>/);
  assert.match(html, /data-order-model="Model S"/);
  assert.match(html, /data-order-trim="Standard Wheels"/);
  assert.match(html, /data-order-price="\$62,990"/);
  assert.match(html, /data-order-image="models\.jpg"/);
  assert.doesNotMatch(html, /data-order-model="Model 3"/);
});

test('payment cart renders stored vehicle data as text, not markup', () => {
  const js = read('hk2/script.js');
  const renderStart = js.indexOf('const renderPaymentCart = () => {');
  const renderEnd = js.indexOf('const subtotal = getCartSubtotal();', renderStart);
  assert.notEqual(renderStart, -1, 'renderPaymentCart should exist');
  assert.notEqual(renderEnd, -1, 'subtotal calculation should remain inside renderPaymentCart');

  const renderBody = js.slice(renderStart, renderEnd);
  assert.doesNotMatch(renderBody, /paymentCartItems\.innerHTML/);
  assert.match(renderBody, /title\.textContent = item\.model/);
  assert.match(renderBody, /trim\.textContent = item\.trim/);
  assert.match(renderBody, /image\.alt = item\.model/);
});

test('consultation success message does not interpolate submitted fields into HTML', () => {
  const js = read('A/LMS ĐH-CĐ - Antigravity/script.js');
  assert.doesNotMatch(js, /formSuccessBlock\.innerHTML\s*=\s*`[\s\S]*\$\{(?:fullname|phone|email)\}/);
  assert.match(js, /data-success-field="fullname"/);
  assert.match(js, /textContent = fullname/);
  assert.match(js, /textContent = phone/);
  assert.match(js, /textContent = email/);
});

test('animal poll tolerates poisoned storage and renders counts without HTML injection', () => {
  const js = read('html/script.js');
  assert.match(js, /try\s*{[\s\S]*JSON\.parse\(localStorage\.getItem\('pollCounts'\)\)/);
  assert.match(js, /normalizePollCounts/);
  assert.doesNotMatch(js, /pollResult\.innerHTML/);
  assert.match(js, /pollResult\.replaceChildren\(\)/);
  assert.match(js, /strong\.textContent/);
});
