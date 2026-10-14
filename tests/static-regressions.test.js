const assert = require('node:assert/strict');
const { execFileSync } = require('node:child_process');
const fs = require('node:fs');
const os = require('node:os');
const path = require('node:path');
const test = require('node:test');

const repoRoot = path.resolve(__dirname, '..');

function readRepoFile(...segments) {
  return fs.readFileSync(path.join(repoRoot, ...segments), 'utf8');
}

function compileCpp(sourcePath, outputPath) {
  execFileSync(
    'g++',
    ['-std=c++17', '-Wall', '-Wextra', '-fsanitize=address,undefined', '-g', sourcePath, '-o', outputPath],
    { cwd: repoRoot, stdio: 'pipe' }
  );
}

function normalizeOutput(value) {
  return value.toString('utf8').trim().replace(/\s+/g, ' ');
}

test('tracked JavaScript files parse successfully', () => {
  const files = execFileSync('git', ['ls-files', '-z', '*.js'], { cwd: repoRoot })
    .toString('utf8')
    .split('\0')
    .filter(Boolean);

  for (const file of files) {
    execFileSync(process.execPath, ['--check', path.join(repoRoot, file)], {
      cwd: repoRoot,
      stdio: 'pipe'
    });
  }
});

test('new LMS Lite navigation script avoids optional-chain assignment', () => {
  const source = readRepoFile('C', 'LMS Lite - Cursor', 'js', 'main.js');

  assert.doesNotMatch(source, /navToggle\?\.querySelector\('i'\)\.className\s*=/);
  assert.match(source, /const icon = navToggle\?\.querySelector\('i'\);/);
});

test('Model S configurator submits Model S checkout data', () => {
  const source = readRepoFile('hk2', 'order-model-s.html');

  assert.match(source, /<h1>Model S<\/h1>/);
  assert.match(source, /<strong>\$62,990<\/strong>/);
  assert.match(source, /data-order-model="Model S"/);
  assert.match(source, /data-order-trim="Standard Wheels"/);
  assert.match(source, /data-order-price="\$62,990"/);
  assert.match(source, /data-order-image="models\.jpg"/);
  assert.doesNotMatch(source, /data-order-model="Model 3"/);
});

test('payment cart renders stored cart data as DOM text nodes', () => {
  const source = readRepoFile('hk2', 'script.js');

  assert.doesNotMatch(source, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
  assert.match(source, /paymentCartItems\.replaceChildren\(\)/);
  assert.match(source, /getSafeCartImage/);
  assert.match(source, /title\.textContent = String\(item\.model \|\| "Model"\)/);
  assert.match(source, /trim\.textContent = String\(item\.trim \|\| "Base"\)/);
});

test('consultation success does not interpolate submitted fields into HTML', () => {
  const source = readRepoFile('A', 'LMS ĐH-CĐ - Antigravity', 'script.js');

  assert.doesNotMatch(source, /formSuccessBlock\.innerHTML\s*=/);
  assert.doesNotMatch(source, /Cảm ơn <strong>\$\{fullname\}<\/strong>/);
  assert.match(source, /formSuccessBlock\.replaceChildren\(\)/);
  assert.match(source, /textContent: fullname/);
});

test('animal poll tolerates malformed storage and renders counts as text', () => {
  const source = readRepoFile('html', 'script.js');

  assert.doesNotMatch(source, /pollResult\.innerHTML\s*=/);
  assert.match(source, /JSON\.parse\(localStorage\.getItem\('pollCounts'\)\)/);
  assert.match(source, /localStorage\.removeItem\('pollCounts'\)/);
  assert.match(source, /pollResult\.replaceChildren\(resultFragment\)/);
});

test('inline HTML scripts parse successfully', () => {
  const htmlFiles = execFileSync('git', ['ls-files', '-z', '*.html'], { cwd: repoRoot })
    .toString('utf8')
    .split('\0')
    .filter(Boolean);

  for (const file of htmlFiles) {
    const source = readRepoFile(file);
    const scripts = [...source.matchAll(/<script\b(?![^>]*\bsrc=)[^>]*>([\s\S]*?)<\/script>/gi)];

    scripts.forEach(([, script], index) => {
      const tempFile = path.join(os.tmpdir(), `inline-script-${process.pid}-${index}.js`);
      fs.writeFileSync(tempFile, script, 'utf8');
      try {
        execFileSync(process.execPath, ['--check', tempFile], { cwd: repoRoot, stdio: 'pipe' });
      } finally {
        fs.rmSync(tempFile, { force: true });
      }
    });
  }
});

test('ams_jump bundled samples run without sanitizer failures', () => {
  const tempDir = fs.mkdtempSync(path.join(os.tmpdir(), 'ams-jump-'));
  const binary = path.join(tempDir, 'ams_jump');

  try {
    compileCpp(path.join(repoRoot, 'C++', '2025', 'ams_jump.cpp'), binary);

    for (const caseId of [1, 2]) {
      const inputPath = path.join(repoRoot, 'C++', '2025', `ams_jump_${caseId}.in`);
      const expectedPath = path.join(repoRoot, 'C++', '2025', `ams_jump_${caseId}.ans`);
      const output = execFileSync(binary, { input: fs.readFileSync(inputPath), stdio: 'pipe' });
      assert.equal(normalizeOutput(output), normalizeOutput(fs.readFileSync(expectedPath)));
    }
  } finally {
    fs.rmSync(tempDir, { recursive: true, force: true });
  }
});

test('tongbang bundled samples avoid max-input materialization', () => {
  const tempDir = fs.mkdtempSync(path.join(os.tmpdir(), 'tongbang-'));
  const binary = path.join(tempDir, 'tongbang');

  try {
    compileCpp(path.join(repoRoot, 'C++', '2025', 'tongbang.cpp'), binary);

    for (const caseId of [1, 2, 3, 4, 5, 6]) {
      const inputPath = path.join(repoRoot, 'C++', '2025', `tongbang_${caseId}.in`);
      const expectedPath = path.join(repoRoot, 'C++', '2025', `tongbang_${caseId}.ans`);
      const output = execFileSync(binary, { input: fs.readFileSync(inputPath), stdio: 'pipe' });
      assert.equal(normalizeOutput(output), normalizeOutput(fs.readFileSync(expectedPath)));
    }
  } finally {
    fs.rmSync(tempDir, { recursive: true, force: true });
  }
});
