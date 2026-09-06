const assert = require('node:assert/strict');
const { execFileSync } = require('node:child_process');
const { mkdtempSync, readFileSync, rmSync } = require('node:fs');
const { tmpdir } = require('node:os');
const { join } = require('node:path');
const test = require('node:test');

function normalize(output) {
  return output.trim().replace(/\s+/g, ' ');
}

function compile(source, binary) {
  execFileSync('g++', [
    '-std=c++17',
    '-Wall',
    '-Wextra',
    '-fsanitize=address,undefined',
    '-g',
    source,
    '-o',
    binary,
  ]);
}

function runSample(binary, inputFile) {
  return execFileSync(binary, {
    input: readFileSync(inputFile),
    encoding: 'utf8',
    timeout: 5000,
  });
}

test('ams_jump bundled samples run without memory errors', () => {
  const dir = mkdtempSync(join(tmpdir(), 'ams-jump-'));
  try {
    const binary = join(dir, 'ams_jump');
    compile('C++/2025/ams_jump.cpp', binary);

    for (const id of [1, 2]) {
      assert.equal(
        normalize(runSample(binary, `C++/2025/ams_jump_${id}.in`)),
        normalize(readFileSync(`C++/2025/ams_jump_${id}.ans`, 'utf8'))
      );
    }
  } finally {
    rmSync(dir, { recursive: true, force: true });
  }
});

test('tongbang handles max-size bundled sample without materializing rows', () => {
  const dir = mkdtempSync(join(tmpdir(), 'tongbang-'));
  try {
    const binary = join(dir, 'tongbang');
    compile('C++/2025/tongbang.cpp', binary);

    assert.equal(
      normalize(runSample(binary, 'C++/2025/tongbang_6.in')),
      normalize(readFileSync('C++/2025/tongbang_6.ans', 'utf8'))
    );
  } finally {
    rmSync(dir, { recursive: true, force: true });
  }
});
