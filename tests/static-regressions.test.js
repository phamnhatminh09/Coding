const assert = require('node:assert/strict');
const { execFileSync } = require('node:child_process');
const fs = require('node:fs');
const os = require('node:os');
const path = require('node:path');
const test = require('node:test');

const repoRoot = path.resolve(__dirname, '..');

const read = (...segments) => fs.readFileSync(path.join(repoRoot, ...segments), 'utf8');

test('tracked JavaScript files parse successfully', () => {
  const files = execFileSync('git', ['ls-files', '-z', '*.js'], { cwd: repoRoot })
    .toString('utf8')
    .split('\0')
    .filter(Boolean);

  for (const file of files) {
    execFileSync(process.execPath, ['--check', path.join(repoRoot, file)], {
      cwd: repoRoot,
      stdio: 'pipe',
    });
  }
});

test('inline scripts in changed HTML parse successfully', () => {
  const files = [
    'hk2/order-model-s.html',
    'test.html',
    'A/LMS AI/LMS AI.html',
    'C/LMS AI/LMS AI.html',
  ];
  const tempDir = fs.mkdtempSync(path.join(os.tmpdir(), 'static-inline-scripts-'));

  try {
    for (const file of files) {
      const html = read(...file.split('/'));
      const scripts = [...html.matchAll(/<script(?![^>]*\bsrc=)[^>]*>([\s\S]*?)<\/script>/gi)];

      scripts.forEach((match, index) => {
        const scriptPath = path.join(tempDir, `${file.replace(/[^\w.-]+/g, '_')}-${index}.js`);
        fs.writeFileSync(scriptPath, match[1]);
        execFileSync(process.execPath, ['--check', scriptPath], { stdio: 'pipe' });
      });
    }
  } finally {
    fs.rmSync(tempDir, { recursive: true, force: true });
  }
});

test('Model S configurator stores Model S cart metadata', () => {
  const html = read('hk2', 'order-model-s.html');

  assert.match(html, /<h1>Model S<\/h1>/);
  assert.match(html, /<strong>\$62,990<\/strong>/);
  assert.match(html, /data-order-model="Model S"/);
  assert.match(html, /data-order-trim="Standard Wheels"/);
  assert.match(html, /data-order-price="\$62,990"/);
  assert.match(html, /data-order-image="models\.jpg"/);
  assert.doesNotMatch(html, /data-order-model="Model 3"/);
});

test('submitted and stored values are rendered as text', () => {
  const consultationScript = read('A', 'LMS ĐH-CĐ - Antigravity', 'script.js');
  assert.doesNotMatch(
    consultationScript,
    /formSuccessBlock\.innerHTML\s*=\s*`[\s\S]*\$\{(?:fullname|phone|email)\}/,
  );
  assert.match(consultationScript, /formSuccessBlock\.replaceChildren\(\)/);
  assert.match(consultationScript, /fullnameText\.textContent = fullname/);
  assert.match(consultationScript, /phoneText\.textContent = phone/);
  assert.match(consultationScript, /emailText\.textContent = email/);

  const checkoutScript = read('hk2', 'script.js');
  assert.doesNotMatch(checkoutScript, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
  assert.match(checkoutScript, /paymentCartItems\.replaceChildren\(\)/);
  assert.match(checkoutScript, /title\.textContent = item\.model/);
  assert.match(checkoutScript, /trim\.textContent = item\.trim/);

  const animalScript = read('html', 'script.js');
  assert.doesNotMatch(animalScript, /pollResult\.innerHTML/);
  assert.match(animalScript, /JSON\.parse\(storedPollCounts\)/);
  assert.match(animalScript, /localStorage\.removeItem\('pollCounts'\)/);
});

test('ams_jump bundled samples run without sanitizer failures', () => {
  const tempDir = fs.mkdtempSync(path.join(os.tmpdir(), 'ams-jump-'));
  const binary = path.join(tempDir, 'ams_jump');

  try {
    execFileSync(
      'g++',
      [
        '-std=c++17',
        '-Wall',
        '-Wextra',
        '-fsanitize=address,undefined',
        path.join(repoRoot, 'C++', '2025', 'ams_jump.cpp'),
        '-o',
        binary,
      ],
      { cwd: repoRoot, stdio: 'pipe' },
    );

    for (const index of [1, 2]) {
      const input = fs.readFileSync(path.join(repoRoot, 'C++', '2025', `ams_jump_${index}.in`));
      const expected = fs.readFileSync(path.join(repoRoot, 'C++', '2025', `ams_jump_${index}.ans`), 'utf8').trim();
      const actual = execFileSync(binary, { input, timeout: 5000 }).toString('utf8').trim();
      assert.equal(actual, expected);
    }
  } finally {
    fs.rmSync(tempDir, { recursive: true, force: true });
  }
});

test('tongbang handles max-size bundled sample without materializing rows', () => {
  const tempDir = fs.mkdtempSync(path.join(os.tmpdir(), 'tongbang-'));
  const binary = path.join(tempDir, 'tongbang');

  try {
    execFileSync(
      'g++',
      ['-std=c++17', '-Wall', '-Wextra', '-O2', path.join(repoRoot, 'C++', '2025', 'tongbang.cpp'), '-o', binary],
      { cwd: repoRoot, stdio: 'pipe' },
    );

    for (const index of [1, 2, 3, 4, 5, 6]) {
      const input = fs.readFileSync(path.join(repoRoot, 'C++', '2025', `tongbang_${index}.in`));
      const expected = fs.readFileSync(path.join(repoRoot, 'C++', '2025', `tongbang_${index}.ans`), 'utf8').trim();
      const actual = execFileSync(binary, { input, timeout: 5000 }).toString('utf8').trim();
      assert.equal(actual, expected);
    }
  } finally {
    fs.rmSync(tempDir, { recursive: true, force: true });
  }
});
