const assert = require('node:assert/strict');
const { execFileSync } = require('node:child_process');
const { mkdtempSync, readFileSync, rmSync } = require('node:fs');
const { tmpdir } = require('node:os');
const path = require('node:path');
const test = require('node:test');

const repoRoot = path.resolve(__dirname, '..');

test('mincd handles all bundled samples without reading past the input array', () => {
  const workdir = mkdtempSync(path.join(tmpdir(), 'mincd-'));
  const binary = path.join(workdir, 'mincd');

  try {
    execFileSync(
      'g++',
      [
        '-std=c++17',
        '-Wall',
        '-Wextra',
        '-fsanitize=address,undefined',
        path.join(repoRoot, 'C++/2025/mincd.cpp'),
        '-o',
        binary,
      ],
      { stdio: 'pipe' },
    );

    const cases = [
      { input: 'mincd_1.in', expected: '-1' },
      { input: 'mincd_2.in', expected: '2' },
    ];

    for (const { input, expected } of cases) {
      const output = execFileSync(binary, {
        cwd: path.join(repoRoot, 'C++/2025'),
        input: readFileSync(path.join(repoRoot, 'C++/2025', input)),
        encoding: 'utf8',
        stdio: ['pipe', 'pipe', 'pipe'],
      });

      assert.equal(output.trim(), expected);
    }
  } finally {
    rmSync(workdir, { recursive: true, force: true });
  }
});
