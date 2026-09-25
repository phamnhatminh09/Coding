const assert = require('node:assert/strict');
const { mkdtempSync, readFileSync, rmSync } = require('node:fs');
const os = require('node:os');
const path = require('node:path');
const { spawnSync } = require('node:child_process');
const test = require('node:test');

const repoRoot = path.resolve(__dirname, '..');

function run(command, args, options = {}) {
  const result = spawnSync(command, args, {
    cwd: repoRoot,
    encoding: 'utf8',
    ...options,
  });

  assert.equal(
    result.status,
    0,
    `${command} ${args.join(' ')} failed\nSTDOUT:\n${result.stdout}\nSTDERR:\n${result.stderr}`,
  );
  return result;
}

test('tracked JavaScript entry points parse', () => {
  const files = [
    'A/LMS AI/script.js',
    'A/LMS Lite - Antigravity/script.js',
    'A/LMS \u0110H-C\u0110 - Antigravity/script.js',
    'C/LMS AI/script.js',
    'C/LMS Lite - Cursor/js/main.js',
    'C/LMS \u0110H-C\u0110 - Cursor/js/main.js',
    'hk2/script.js',
  ];

  for (const file of files) {
    run(process.execPath, ['--check', file]);
  }
});

test('Model S configurator submits Model S cart metadata', () => {
  const html = readFileSync(path.join(repoRoot, 'hk2/order-model-s.html'), 'utf8');

  assert.match(html, /<h1>Model S<\/h1>/);
  assert.match(html, /<strong>\$62,990<\/strong>/);
  assert.match(html, /data-order-model="Model S"/);
  assert.match(html, /data-order-trim="Standard Wheels"/);
  assert.match(html, /data-order-price="\$62,990"/);
  assert.match(html, /data-order-image="models\.jpg"/);
  assert.doesNotMatch(html, /data-order-model="Model 3"/);
});

test('stored cart fields are rendered as DOM text, not HTML', () => {
  const js = readFileSync(path.join(repoRoot, 'hk2/script.js'), 'utf8');

  assert.match(js, /const safeCartImage = /);
  assert.match(js, /paymentCartItems\.replaceChildren\(\)/);
  assert.match(js, /title\.textContent = item\.model \|\| "Model"/);
  assert.match(js, /trim\.textContent = item\.trim \|\| "Base"/);
  assert.doesNotMatch(js, /paymentCartItems\.innerHTML = cart\.map/);
  assert.doesNotMatch(js, /<h3>\$\{item\.model/);
});

test('consultation success output escapes submitted fields', () => {
  const js = readFileSync(path.join(repoRoot, 'A/LMS \u0110H-C\u0110 - Antigravity/script.js'), 'utf8');

  assert.match(js, /const escapeHTML = /);
  assert.match(js, /const safeFullname = escapeHTML\(fullname\)/);
  assert.match(js, /const safePhone = escapeHTML\(phone\)/);
  assert.match(js, /const safeEmail = escapeHTML\(email\)/);
  assert.doesNotMatch(js, /<strong>\$\{fullname\}<\/strong>/);
  assert.doesNotMatch(js, /<strong>\$\{phone\}<\/strong>/);
  assert.doesNotMatch(js, /<strong>\$\{email\}<\/strong>/);
});

test('C++ samples pass under sanitizers', () => {
  const tmp = mkdtempSync(path.join(os.tmpdir(), 'static-regressions-'));
  try {
    const programs = [
      {
        name: 'ams_jump',
        source: 'C++/2025/ams_jump.cpp',
        samples: ['1', '2'],
      },
      {
        name: 'tongbang',
        source: 'C++/2025/tongbang.cpp',
        samples: ['1', '2', '3', '4', '5', '6'],
      },
    ];

    for (const program of programs) {
      const binary = path.join(tmp, program.name);
      run('g++', [
        '-std=c++17',
        '-Wall',
        '-Wextra',
        '-fsanitize=address,undefined',
        '-g',
        program.source,
        '-o',
        binary,
      ]);

      for (const sample of program.samples) {
        const inputPath = path.join(repoRoot, `C++/2025/${program.name}_${sample}.in`);
        const expectedPath = path.join(repoRoot, `C++/2025/${program.name}_${sample}.ans`);
        const result = run(binary, [], {
          input: readFileSync(inputPath, 'utf8'),
        });
        assert.equal(result.stdout, readFileSync(expectedPath, 'utf8'));
      }
    }
  } finally {
    rmSync(tmp, { recursive: true, force: true });
  }
});
