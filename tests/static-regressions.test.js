const assert = require("node:assert/strict");
const { execFileSync } = require("node:child_process");
const { mkdtempSync, readFileSync, rmSync, writeFileSync } = require("node:fs");
const { tmpdir } = require("node:os");
const { join, resolve } = require("node:path");
const test = require("node:test");

const repoRoot = resolve(__dirname, "..");

function gitFiles(pattern) {
  return execFileSync("git", ["ls-files", "-z", pattern], { cwd: repoRoot })
    .toString("utf8")
    .split("\0")
    .filter(Boolean);
}

function checkJavaScriptSyntax(filePath, label = filePath) {
  try {
    execFileSync(process.execPath, ["--check", filePath], {
      cwd: repoRoot,
      stdio: "pipe",
    });
  } catch (error) {
    const output = [error.stdout, error.stderr]
      .filter(Boolean)
      .map((buffer) => buffer.toString())
      .join("");
    assert.fail(`${label} failed JavaScript syntax validation:\n${output}`);
  }
}

test("tracked JavaScript files parse", () => {
  for (const filePath of gitFiles("*.js")) {
    checkJavaScriptSyntax(filePath);
  }
});

test("inline HTML scripts parse", () => {
  const tempDir = mkdtempSync(join(tmpdir(), "static-inline-scripts-"));

  try {
    for (const filePath of gitFiles("*.html")) {
      const html = readFileSync(join(repoRoot, filePath), "utf8");
      const scripts = html.matchAll(/<script\b([^>]*)>([\s\S]*?)<\/script>/gi);
      let scriptIndex = 0;

      for (const [, rawAttributes, scriptBody] of scripts) {
        const attributes = rawAttributes || "";
        if (/\bsrc\s*=/i.test(attributes) || !scriptBody.trim()) {
          continue;
        }

        const typeMatch = attributes.match(/\btype\s*=\s*["']?([^"'\s>]+)/i);
        if (typeMatch && !["text/javascript", "application/javascript", "module"].includes(typeMatch[1])) {
          continue;
        }

        scriptIndex += 1;
        const tempFile = join(tempDir, `script-${scriptIndex}.js`);
        writeFileSync(tempFile, scriptBody);
        checkJavaScriptSyntax(tempFile, `${filePath} inline script ${scriptIndex}`);
      }
    }
  } finally {
    rmSync(tempDir, { force: true, recursive: true });
  }
});

test("Model S configurator submits Model S checkout metadata", () => {
  const html = readFileSync(join(repoRoot, "hk2/order-model-s.html"), "utf8");

  assert.match(html, /<h1>\s*Model S\s*<\/h1>/);
  assert.match(html, /<strong>\$62,990<\/strong>/);
  assert.match(html, /data-order-model="Model S"/);
  assert.match(html, /data-order-trim="Standard Wheels"/);
  assert.match(html, /data-order-price="\$62,990"/);
  assert.doesNotMatch(html, /data-order-model="Model 3"/);
});

test("payment cart rendering keeps stored cart fields out of HTML", () => {
  const script = readFileSync(join(repoRoot, "hk2/script.js"), "utf8");

  assert.match(script, /paymentCartItems\.replaceChildren\(\)/);
  assert.match(script, /model\.textContent = item\.model \|\| "Model"/);
  assert.match(script, /trim\.textContent = item\.trim \|\| "Base"/);
  assert.doesNotMatch(script, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
});
