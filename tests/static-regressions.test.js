const assert = require("node:assert/strict");
const { execFileSync } = require("node:child_process");
const fs = require("node:fs");
const path = require("node:path");
const test = require("node:test");

const repoRoot = path.resolve(__dirname, "..");

const read = (...parts) => fs.readFileSync(path.join(repoRoot, ...parts), "utf8");

test("tracked JavaScript files parse successfully", () => {
  const output = execFileSync("git", ["ls-files", "-z", "--", "*.js"], {
    cwd: repoRoot
  });
  const jsFiles = output.toString("utf8").split("\0").filter(Boolean);

  assert.ok(jsFiles.length > 0, "expected tracked JavaScript files");

  for (const file of jsFiles) {
    assert.doesNotThrow(
      () => execFileSync(process.execPath, ["--check", file], { cwd: repoRoot }),
      `${file} should pass node --check`
    );
  }
});

test("Model S configurator submits Model S checkout metadata", () => {
  const html = read("hk2", "order-model-s.html");

  assert.match(html, /<h1>Model S<\/h1>/);
  assert.match(html, /<strong>\$62,990<\/strong>/);
  assert.match(html, /data-order-model="Model S"/);
  assert.match(html, /data-order-trim="Standard Wheels"/);
  assert.match(html, /data-order-price="\$62,990"/);
  assert.match(html, /data-order-image="models\.jpg"/);
  assert.doesNotMatch(html, /data-order-model="Model 3"/);
});

test("payment cart renders persisted cart fields as text", () => {
  const script = read("hk2", "script.js");

  assert.match(script, /paymentCartItems\.replaceChildren\(\.\.\.cartRows\)/);
  assert.match(script, /model\.textContent = item\.model \|\| "Model"/);
  assert.match(script, /trim\.textContent = item\.trim \|\| "Base"/);
  assert.match(script, /image\.src = getSafeCartImage\(item\.image\)/);
  assert.doesNotMatch(script, /paymentCartItems\.innerHTML = cart\.map/);
  assert.doesNotMatch(script, /<h3>\$\{item\.model/);
});

test("consultation form success message does not interpolate submitted fields into HTML", () => {
  const script = read("A", "LMS ĐH-CĐ - Antigravity", "script.js");

  assert.doesNotMatch(script, /formSuccessBlock\.innerHTML\s*=/);
  assert.match(script, /fullNameText\.textContent = fullname/);
  assert.match(script, /phoneText\.textContent = phone/);
  assert.match(script, /emailText\.textContent = email/);
  assert.match(script, /formSuccessBlock\.append\(successIcon, successTitle, successMessage, resetButton\)/);
});
