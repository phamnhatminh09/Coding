const assert = require("node:assert/strict");
const { execFileSync, spawnSync } = require("node:child_process");
const { readFileSync } = require("node:fs");
const path = require("node:path");
const test = require("node:test");

const repoRoot = path.resolve(__dirname, "..");

function readRepoFile(relativePath) {
  return readFileSync(path.join(repoRoot, relativePath), "utf8");
}

function trackedJavaScriptFiles() {
  const output = execFileSync("git", ["ls-files", "-z", "--", "*.js"], {
    cwd: repoRoot,
  });

  return output
    .toString("utf8")
    .split("\0")
    .filter(Boolean);
}

test("tracked JavaScript files parse", () => {
  for (const file of trackedJavaScriptFiles()) {
    const result = spawnSync(process.execPath, ["--check", file], {
      cwd: repoRoot,
      encoding: "utf8",
    });

    assert.equal(
      result.status,
      0,
      `${file} failed syntax check:\n${result.stderr || result.stdout}`,
    );
  }
});

test("Model S configurator submits Model S checkout metadata", () => {
  const html = readRepoFile("hk2/order-model-s.html");

  assert.match(html, /<h1>Model S<\/h1>/);
  assert.match(html, /<strong>\$62,990<\/strong>/);
  assert.match(html, /data-order-model="Model S"/);
  assert.match(html, /data-order-trim="Standard Wheels"/);
  assert.match(html, /data-order-price="\$62,990"/);
  assert.doesNotMatch(html, /data-order-model="Model 3"/);
  assert.doesNotMatch(html, /data-order-price="\$38,990"/);
});

test("payment cart renders persisted cart fields as text", () => {
  const script = readRepoFile("hk2/script.js");

  assert.doesNotMatch(script, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
  assert.doesNotMatch(script, /<h3>\$\{item\.model/);
  assert.doesNotMatch(script, /<p>\$\{item\.trim/);
  assert.match(script, /model\.textContent = item\.model \|\| "Model"/);
  assert.match(script, /trim\.textContent = item\.trim \|\| "Base"/);
});

test("consultation success message treats submitted fields as text", () => {
  const script = readRepoFile("A/LMS ĐH-CĐ - Antigravity/script.js");

  assert.doesNotMatch(
    script,
    /formSuccessBlock\.innerHTML\s*=\s*`[\s\S]*\$\{(?:fullname|phone|email)\}/,
  );
  assert.match(script, /nameText\.textContent = fullname/);
  assert.match(script, /phoneText\.textContent = phone/);
  assert.match(script, /emailText\.textContent = email/);
});
