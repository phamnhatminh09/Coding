const assert = require('node:assert/strict');
const { spawnSync } = require('node:child_process');
const fs = require('node:fs');
const os = require('node:os');
const path = require('node:path');
const test = require('node:test');

function gitFiles(pathspec) {
  const result = spawnSync('git', ['ls-files', '-z', '--', pathspec], {
    cwd: path.resolve(__dirname, '..'),
    encoding: 'utf8',
  });

  assert.equal(result.status, 0, result.stderr);
  return result.stdout.split('\0').filter(Boolean);
}

function nodeCheck(filePath) {
  const result = spawnSync(process.execPath, ['--check', filePath], {
    cwd: path.resolve(__dirname, '..'),
    encoding: 'utf8',
  });

  assert.equal(result.status, 0, result.stderr || result.stdout);
}

test('tracked JavaScript files parse successfully', () => {
  const jsFiles = gitFiles('*.js');
  assert.ok(jsFiles.length > 0, 'expected at least one tracked JavaScript file');

  for (const file of jsFiles) {
    nodeCheck(file);
  }
});

test('inline HTML scripts parse successfully', () => {
  const htmlFiles = gitFiles('*.html');
  const scriptPattern = /<script\b([^>]*)>([\s\S]*?)<\/script>/gi;
  const typePattern = /\btype\s*=\s*["']?([^"'\s>]+)/i;
  let checkedScripts = 0;

  for (const file of htmlFiles) {
    const html = fs.readFileSync(path.resolve(__dirname, '..', file), 'utf8');
    let match;

    while ((match = scriptPattern.exec(html)) !== null) {
      const attrs = match[1] || '';
      if (/\bsrc\s*=/.test(attrs)) continue;

      const type = attrs.match(typePattern)?.[1]?.toLowerCase();
      if (type && !['module', 'text/javascript', 'application/javascript'].includes(type)) {
        continue;
      }

      const code = match[2].trim();
      if (!code) continue;

      const tempDir = fs.mkdtempSync(path.join(os.tmpdir(), 'static-regression-'));
      const tempFile = path.join(tempDir, `${path.basename(file)}.${checkedScripts}.js`);
      try {
        fs.writeFileSync(tempFile, code);
        nodeCheck(tempFile);
      } finally {
        fs.rmSync(tempDir, { recursive: true, force: true });
      }
      checkedScripts += 1;
    }
  }
});
