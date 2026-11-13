const assert = require('node:assert/strict');
const { execFileSync } = require('node:child_process');
const { mkdtempSync, readFileSync, rmSync } = require('node:fs');
const { tmpdir } = require('node:os');
const path = require('node:path');
const test = require('node:test');

const repoRoot = path.resolve(__dirname, '..');
const sourcePath = path.join(repoRoot, 'C++/2025/homework.cpp');

test('homework handles task type ids above the consecutive limit', () => {
  const workdir = mkdtempSync(path.join(tmpdir(), 'homework-'));
  const binary = path.join(workdir, 'homework');

  try {
    execFileSync(
      'g++',
      [
        '-std=c++17',
        '-Wall',
        '-Wextra',
        '-fsanitize=address,undefined',
        sourcePath,
        '-o',
        binary,
      ],
      { stdio: 'pipe' },
    );

    const output = execFileSync(binary, {
      input: '1 2 1\n2\n5 7\n11 13\n',
      encoding: 'utf8',
      stdio: ['pipe', 'pipe', 'pipe'],
    });
    assert.equal(output.trim(), '7');
  } finally {
    rmSync(workdir, { recursive: true, force: true });
  }
});

test('homework still matches the bundled sample', () => {
  const workdir = mkdtempSync(path.join(tmpdir(), 'homework-'));
  const binary = path.join(workdir, 'homework');

  try {
    execFileSync(
      'g++',
      [
        '-std=c++17',
        '-Wall',
        '-Wextra',
        '-fsanitize=address,undefined',
        sourcePath,
        '-o',
        binary,
      ],
      { stdio: 'pipe' },
    );

    const output = execFileSync(binary, {
      input: readFileSync(path.join(repoRoot, 'C++/2025/homework_1.in')),
      encoding: 'utf8',
      stdio: ['pipe', 'pipe', 'pipe'],
    });
    assert.equal(output.trim(), readFileSync(path.join(repoRoot, 'C++/2025/homework_1.ans'), 'utf8').trim());
  } finally {
    rmSync(workdir, { recursive: true, force: true });
  }
});
