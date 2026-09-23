const assert = require('node:assert/strict');
const fs = require('node:fs');
const os = require('node:os');
const path = require('node:path');
const { execFileSync } = require('node:child_process');
const test = require('node:test');

const root = path.resolve(__dirname, '..');

function read(relativePath) {
  return fs.readFileSync(path.join(root, relativePath), 'utf8');
}

function walk(directory, predicate, results = []) {
  for (const entry of fs.readdirSync(directory, { withFileTypes: true })) {
    if (entry.name === '.git' || entry.name === 'node_modules') continue;
    const fullPath = path.join(directory, entry.name);
    if (entry.isDirectory()) {
      walk(fullPath, predicate, results);
    } else if (predicate(fullPath)) {
      results.push(fullPath);
    }
  }
  return results;
}

test('tracked JavaScript and inline HTML scripts parse successfully', () => {
  for (const jsFile of walk(root, (file) => file.endsWith('.js'))) {
    execFileSync('node', ['--check', jsFile], { stdio: 'pipe' });
  }

  for (const htmlFile of walk(root, (file) => file.endsWith('.html'))) {
    const html = fs.readFileSync(htmlFile, 'utf8');
    const inlineScripts = html.matchAll(/<script(?![^>]*\bsrc=)[^>]*>([\s\S]*?)<\/script>/gi);
    let index = 0;
    for (const match of inlineScripts) {
      const script = match[1].trim();
      if (!script) continue;
      const tempFile = path.join(os.tmpdir(), `inline-script-${process.pid}-${index++}.js`);
      fs.writeFileSync(tempFile, script);
      try {
        execFileSync('node', ['--check', tempFile], { stdio: 'pipe' });
      } finally {
        fs.rmSync(tempFile, { force: true });
      }
    }
  }
});

test('LMS Lite navigation does not use invalid optional-chain assignment', () => {
  const script = read(path.join('C', 'LMS Lite - Cursor', 'js', 'main.js'));
  assert.doesNotMatch(script, /navToggle\?\.querySelector\('i'\)\.className\s*=/);
});

test('consultation success message renders submitted fields as text', () => {
  const script = read(path.join('A', 'LMS \u0110H-C\u0110 - Antigravity', 'script.js'));
  assert.doesNotMatch(script, /formSuccessBlock\.innerHTML\s*=\s*`[\s\S]*\$\{(?:fullname|phone|email)/);
  assert.match(script, /fullnameText\.textContent = fullname/);
  assert.match(script, /phoneText\.textContent = phone/);
  assert.match(script, /emailText\.textContent = email/);
});

test('Tesla payment cart does not render localStorage item fields as HTML', () => {
  const script = read(path.join('hk2', 'script.js'));
  assert.doesNotMatch(script, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
  assert.match(script, /paymentCartItems\.replaceChildren\(\)/);
  assert.match(script, /model\.textContent = item\.model \|\| "Model"/);
  assert.match(script, /trim\.textContent = item\.trim \|\| "Base"/);
});

test('Model S configurator submits Model S metadata to checkout', () => {
  const html = read(path.join('hk2', 'order-model-s.html'));
  assert.match(html, /<strong>\$62,990<\/strong>/);
  assert.match(html, /data-order-model="Model S"/);
  assert.match(html, /data-order-trim="Standard Wheels"/);
  assert.match(html, /data-order-price="\$62,990"/);
});

test('animal poll survives malformed storage and avoids HTML rendering', () => {
  const script = read(path.join('html', 'script.js'));
  assert.match(script, /try\s*\{/);
  assert.match(script, /localStorage\.removeItem\('pollCounts'\)/);
  assert.match(script, /normalizeCount/);
  assert.doesNotMatch(script, /pollResult\.innerHTML\s*=/);
  assert.match(script, /pollResult\.replaceChildren\(/);
});
