const assert = require('node:assert/strict');
const { spawnSync } = require('node:child_process');
const { mkdtempSync } = require('node:fs');
const { readFile } = require('node:fs/promises');
const { tmpdir } = require('node:os');
const path = require('node:path');
const test = require('node:test');

const repoRoot = path.resolve(__dirname, '..');

test('guessgame bundled sample does not spin on unexpected input', async () => {
  const workDir = mkdtempSync(path.join(tmpdir(), 'guessgame-'));
  const binary = path.join(workDir, 'guessgame');
  const source = path.join(repoRoot, 'C++/2025/guessgame.cpp');
  const sample = await readFile(path.join(repoRoot, 'C++/2025/guessgame_1.in'));

  const compile = spawnSync(
    'g++',
    ['-std=c++17', '-Wall', '-Wextra', '-fsanitize=address,undefined', source, '-o', binary],
    { encoding: 'utf8' },
  );

  assert.equal(compile.status, 0, compile.stderr);

  const run = spawnSync(binary, {
    input: sample,
    encoding: 'utf8',
    timeout: 1000,
    maxBuffer: 1024 * 1024,
  });

  assert.notEqual(run.error?.code, 'ETIMEDOUT', 'guessgame should not loop forever on its sample input');
  assert.equal(run.status, 0, run.stderr);
  assert.match(run.stdout, /^1000000000\n$/);
});
