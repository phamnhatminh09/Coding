const assert = require("node:assert/strict");
const { execFileSync } = require("node:child_process");
const fs = require("node:fs");
const path = require("node:path");
const test = require("node:test");

const repoRoot = path.resolve(__dirname, "..");

const read = (relativePath) => fs.readFileSync(path.join(repoRoot, relativePath), "utf8");

test("tracked JavaScript files parse successfully", () => {
  const files = execFileSync("git", ["ls-files", "-z", "*.js"], {
    cwd: repoRoot,
    encoding: "utf8",
  })
    .split("\0")
    .filter(Boolean);

  for (const file of files) {
    execFileSync(process.execPath, ["--check", file], { cwd: repoRoot });
  }
});

test("payment cart renders persisted order data without HTML interpolation", () => {
  const script = read("hk2/script.js");

  assert.match(script, /paymentCartItems\.replaceChildren\(\)/);
  assert.doesNotMatch(script, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
  assert.doesNotMatch(script, /\$\{item\.(?:image|model|trim|price)\b/);
});

test("Model S configurator submits Model S checkout metadata", () => {
  const html = read("hk2/order-model-s.html");

  assert.match(html, /<h1>Model S<\/h1>/);
  assert.match(html, /<strong>\$62,990<\/strong>/);
  assert.match(html, /data-order-model="Model S"/);
  assert.match(html, /data-order-trim="Standard Wheels"/);
  assert.match(html, /data-order-price="\$62,990"/);
  assert.match(html, /data-order-image="models\.jpg"/);
  assert.doesNotMatch(html, /data-order-model="Model 3"/);
});

test("submitted consultation fields are inserted as text, not parsed as HTML", () => {
  const script = read("A/LMS ĐH-CĐ - Antigravity/script.js");

  assert.match(script, /formSuccessBlock\.replaceChildren\(/);
  assert.doesNotMatch(script, /formSuccessBlock\.innerHTML\s*=/);
  assert.match(script, /nameText\.textContent = fullname/);
  assert.match(script, /phoneText\.textContent = phone/);
  assert.match(script, /emailText\.textContent = email/);
});
