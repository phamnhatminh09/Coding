const assert = require('node:assert/strict');
const { spawnSync } = require('node:child_process');
const fs = require('node:fs');
const path = require('node:path');
const test = require('node:test');

const root = path.resolve(__dirname, '..');

function readRepoFile(...segments) {
  return fs.readFileSync(path.join(root, ...segments), 'utf8');
}

test('tracked JavaScript files parse successfully', () => {
  const filesResult = spawnSync('git', ['ls-files', '-z', '*.js'], {
    cwd: root,
    encoding: 'buffer',
  });
  assert.equal(filesResult.status, 0, filesResult.stderr.toString());

  const files = filesResult.stdout
    .toString('utf8')
    .split('\0')
    .filter(Boolean);

  const failures = files.flatMap((file) => {
    const result = spawnSync(process.execPath, ['--check', file], {
      cwd: root,
      encoding: 'utf8',
    });
    return result.status === 0 ? [] : [`${file}\n${result.stderr || result.stdout}`];
  });

  assert.deepEqual(failures, []);
});

test('Model S configurator persists Model S checkout metadata', () => {
  const html = readRepoFile('hk2', 'order-model-s.html');
  const cta = html.match(/<button\b[^>]*\border-config-cta\b[^>]*>/s);
  assert.ok(cta, 'Model S checkout button should exist');

  const attr = (name) => {
    const match = cta[0].match(new RegExp(`${name}="([^"]*)"`));
    return match && match[1];
  };

  assert.equal(attr('data-order-model'), 'Model S');
  assert.equal(attr('data-order-trim'), 'Standard Wheels');
  assert.equal(attr('data-order-price'), '$62,990');
  assert.equal(attr('data-order-image'), 'models.jpg');
  assert.match(html, /<strong>\$62,990<\/strong>/);
  assert.match(html, /Est\. \$944\/mo/);
});

test('payment cart renders stored cart fields as text', () => {
  const script = readRepoFile('hk2', 'script.js');

  assert.doesNotMatch(script, /paymentCartItems\.innerHTML\s*=\s*cart\.map/s);
  assert.doesNotMatch(script, /\$\{item\.(?:image|model|trim)/);
  assert.match(script, /paymentCartItems\.replaceChildren\(\)/);
  assert.match(script, /title\.textContent = item\.model/);
  assert.match(script, /trim\.textContent = item\.trim/);
});

test('consultation success message does not interpolate submitted fields into HTML', () => {
  const script = readRepoFile('A', 'LMS ĐH-CĐ - Antigravity', 'script.js');

  assert.doesNotMatch(script, /formSuccessBlock\.innerHTML\s*=\s*`[\s\S]*\$\{(?:fullname|phone|email)\}/);
  assert.match(script, /formSuccessBlock\.replaceChildren\(\)/);
  assert.match(script, /textContent: fullname/);
  assert.match(script, /textContent: phone/);
  assert.match(script, /textContent: email/);
});
