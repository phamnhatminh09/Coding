const assert = require('node:assert/strict');
const { execFileSync } = require('node:child_process');
const { mkdtempSync, readFileSync, rmSync, writeFileSync } = require('node:fs');
const { readFile } = require('node:fs/promises');
const { tmpdir } = require('node:os');
const path = require('node:path');
const test = require('node:test');

const repoRoot = path.resolve(__dirname, '..');

async function readRepoFile(relativePath) {
  return readFile(path.join(repoRoot, relativePath), 'utf8');
}

test('tracked JavaScript files parse successfully', () => {
  const files = execFileSync('git', ['ls-files', '-z', '*.js'], {
    cwd: repoRoot
  }).toString('utf8').split('\0').filter(Boolean);

  for (const file of files) {
    assert.doesNotThrow(() => {
      execFileSync(process.execPath, ['--check', file], {
        cwd: repoRoot,
        stdio: 'pipe'
      });
    }, `${file} should parse`);
  }
});

test('inline scripts in tracked HTML files parse successfully', () => {
  const files = execFileSync('git', ['ls-files', '-z', '*.html'], {
    cwd: repoRoot
  }).toString('utf8').split('\0').filter(Boolean);
  const tempDir = mkdtempSync(path.join(tmpdir(), 'inline-scripts-'));

  try {
    for (const file of files) {
      const html = readFileSync(path.join(repoRoot, file), 'utf8');
      const scripts = html.matchAll(/<script(?![^>]*\bsrc=)[^>]*>([\s\S]*?)<\/script>/gi);
      let index = 0;
      for (const match of scripts) {
        const source = match[1].trim();
        if (!source) continue;
        const tempFile = path.join(tempDir, `${index++}.js`);
        writeFileSync(tempFile, source);
        assert.doesNotThrow(() => {
          execFileSync(process.execPath, ['--check', tempFile], {
            cwd: repoRoot,
            stdio: 'pipe'
          });
        }, `${file} inline script ${index} should parse`);
      }
    }
  } finally {
    rmSync(tempDir, { recursive: true, force: true });
  }
});

test('Model S configurator submits Model S order metadata', async () => {
  const html = await readRepoFile('hk2/order-model-s.html');

  assert.match(html, /<h1>Model S<\/h1>/);
  assert.match(html, /<strong>\$62,990<\/strong>/);
  assert.match(html, /data-order-model="Model S"/);
  assert.match(html, /data-order-trim="Standard Wheels"/);
  assert.match(html, /data-order-price="\$62,990"/);
  assert.match(html, /data-order-image="models\.jpg"/);
  assert.doesNotMatch(html, /data-order-model="Model 3"/);
  assert.doesNotMatch(html, /data-order-price="\$38,990"/);
});

test('payment cart renders stored cart fields as text, not HTML', async () => {
  const script = await readRepoFile('hk2/script.js');
  const renderPaymentCart = script.slice(
    script.indexOf('const renderPaymentCart = () => {'),
    script.indexOf('const subtotal = getCartSubtotal();')
  );

  assert.match(renderPaymentCart, /document\.createElement\("article"\)/);
  assert.match(renderPaymentCart, /title\.textContent = item\.model/);
  assert.match(renderPaymentCart, /trim\.textContent = item\.trim/);
  assert.doesNotMatch(renderPaymentCart, /innerHTML\s*=/);
  assert.doesNotMatch(renderPaymentCart, /\$\{item\.(?:model|trim|image|price)\}/);
});

test('submitted LMS consultation fields are not interpolated into HTML', async () => {
  const script = await readRepoFile('A/LMS ĐH-CĐ - Antigravity/script.js');
  const successBlock = script.slice(
    script.indexOf("formSuccessBlock.style.display = 'flex';"),
    script.indexOf('consultForm.reset();')
  );

  assert.match(successBlock, /formSuccessBlock\.replaceChildren/);
  assert.match(successBlock, /nameText\.textContent = fullname/);
  assert.match(successBlock, /phoneText\.textContent = phone/);
  assert.match(successBlock, /emailText\.textContent = email/);
  assert.doesNotMatch(successBlock, /formSuccessBlock\.innerHTML\s*=/);
  assert.doesNotMatch(successBlock, /\$\{(?:fullname|phone|email)\}/);
});

test('animal poll state is normalized and rendered without HTML injection', async () => {
  const script = await readRepoFile('html/script.js');
  const updatePollResult = script.slice(
    script.indexOf('function updatePollResult()'),
    script.indexOf('// Hiệu ứng cuộn mượt')
  );

  assert.match(script, /function normalizePollCounts/);
  assert.match(script, /try\s*{\s*pollCounts = normalizePollCounts/s);
  assert.doesNotMatch(script, /pollCounts = JSON\.parse\(localStorage\.getItem\('pollCounts'\)\);/);
  assert.doesNotMatch(updatePollResult, /innerHTML\s*=/);
  assert.match(updatePollResult, /labelNode\.textContent = label/);
  assert.match(updatePollResult, /totalNode\.textContent/);
});
