const assert = require('node:assert/strict');
const { execFileSync, spawnSync } = require('node:child_process');
const fs = require('node:fs');
const path = require('node:path');
const test = require('node:test');

const repoRoot = path.resolve(__dirname, '..');

const readText = (...segments) => fs.readFileSync(path.join(repoRoot, ...segments), 'utf8');

test('tracked JavaScript files parse successfully', () => {
  const output = execFileSync('git', ['ls-files', '-z'], {
    cwd: repoRoot,
    encoding: 'buffer'
  });
  const jsFiles = output.toString('utf8').split('\0').filter((file) => file.endsWith('.js'));

  assert.ok(jsFiles.length > 0, 'expected tracked JavaScript files');

  const failures = [];
  for (const file of jsFiles) {
    const result = spawnSync(process.execPath, ['--check', file], {
      cwd: repoRoot,
      encoding: 'utf8'
    });

    if (result.status !== 0) {
      failures.push(`${file}\n${result.stderr || result.stdout}`);
    }
  }

  assert.deepEqual(failures, []);
});

test('Model S checkout submits Model S metadata', () => {
  const html = readText('hk2', 'order-model-s.html');

  assert.match(html, /<h1>Model S<\/h1>/);
  assert.match(html, /<strong>\$62,990<\/strong>/);
  assert.match(html, /data-order-model="Model S"/);
  assert.match(html, /data-order-trim="Standard Wheels"/);
  assert.match(html, /data-order-price="\$62,990"/);
  assert.match(html, /data-order-image="models\.jpg"/);
  assert.doesNotMatch(html, /data-order-model="Model 3"[\s\S]*data-order-price="\$38,990"/);
});

test('payment cart renders stored cart values with DOM text nodes', () => {
  const script = readText('hk2', 'script.js');

  assert.match(script, /paymentCartItems\.replaceChildren\(\)/);
  assert.match(script, /heading\.textContent = item\.model/);
  assert.match(script, /trim\.textContent = item\.trim/);
  assert.doesNotMatch(script, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
});

test('submitted LMS consultation values are not interpolated into HTML', () => {
  const script = readText('A', 'LMS ĐH-CĐ - Antigravity', 'script.js');

  assert.match(script, /formSuccessBlock\.replaceChildren\(\)/);
  assert.match(script, /strong\.textContent = fullname/);
  assert.match(script, /strong\.textContent = phone/);
  assert.match(script, /strong\.textContent = email/);
  assert.doesNotMatch(script, /formSuccessBlock\.innerHTML\s*=/);
});

test('animal poll storage is normalized and rendered without innerHTML', () => {
  const script = readText('html', 'script.js');

  assert.match(script, /function normalizePollCounts/);
  assert.match(script, /try \{/);
  assert.match(script, /localStorage\.removeItem\('pollCounts'\)/);
  assert.match(script, /pollResult\.replaceChildren\(/);
  assert.doesNotMatch(script, /pollResult\.innerHTML\s*=/);
});
