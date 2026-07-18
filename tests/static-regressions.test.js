const assert = require('node:assert/strict');
const { spawnSync } = require('node:child_process');
const fs = require('node:fs');
const os = require('node:os');
const path = require('node:path');
const test = require('node:test');

const repoRoot = path.resolve(__dirname, '..');

function run(command, args, options = {}) {
  return spawnSync(command, args, {
    cwd: repoRoot,
    encoding: 'utf8',
    ...options,
  });
}

test('recent LMS JavaScript files parse successfully', () => {
  const files = [
    path.join('C', 'LMS Lite - Cursor', 'js', 'main.js'),
    path.join('A', 'LMS \u0110H-C\u0110 - Antigravity', 'script.js'),
  ];

  for (const file of files) {
    const result = run(process.execPath, ['--check', file]);
    assert.equal(result.status, 0, `${file} failed syntax check:\n${result.stderr}`);
  }
});

test('consultation form does not interpolate raw submitted fields into innerHTML', () => {
  const script = fs.readFileSync(
    path.join(repoRoot, 'A', 'LMS \u0110H-C\u0110 - Antigravity', 'script.js'),
    'utf8',
  );

  assert.match(script, /const escapeHtml = \(value\)/);
  assert.doesNotMatch(script, /<strong>\$\{fullname\}<\/strong>/);
  assert.doesNotMatch(script, /<strong>\$\{phone\}<\/strong>/);
  assert.doesNotMatch(script, /<strong>\$\{email\}<\/strong>/);
  assert.match(script, /<strong>\$\{escapedFullname\}<\/strong>/);
  assert.match(script, /<strong>\$\{escapedPhone\}<\/strong>/);
  assert.match(script, /<strong>\$\{escapedEmail\}<\/strong>/);
});

test('ams_jump samples run without sanitizer failures', () => {
  const binary = path.join(os.tmpdir(), `ams_jump_${process.pid}`);
  const compile = run('g++', [
    '-std=c++17',
    '-Wall',
    '-Wextra',
    '-fsanitize=address,undefined',
    '-g',
    path.join('C++', '2025', 'ams_jump.cpp'),
    '-o',
    binary,
  ]);
  assert.equal(compile.status, 0, compile.stderr);

  const samples = [
    ['ams_jump_1.in', 'ams_jump_1.ans'],
    ['ams_jump_2.in', 'ams_jump_2.ans'],
  ];

  for (const [inputFile, expectedFile] of samples) {
    const input = fs.readFileSync(path.join(repoRoot, 'C++', '2025', inputFile), 'utf8');
    const expected = fs.readFileSync(path.join(repoRoot, 'C++', '2025', expectedFile), 'utf8').trim();
    const result = run(binary, [], { input });

    assert.equal(result.status, 0, `${inputFile} crashed:\n${result.stderr}`);
    assert.equal(result.stdout.trim(), expected, `${inputFile} output mismatch`);
  }

  fs.rmSync(binary, { force: true });
});
