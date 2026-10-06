const assert = require("node:assert/strict");
const { spawnSync } = require("node:child_process");
const { readFileSync } = require("node:fs");
const path = require("node:path");
const test = require("node:test");

const repoRoot = path.resolve(__dirname, "..");

function repoPath(...parts) {
  return path.join(repoRoot, ...parts);
}

function readRepoFile(...parts) {
  return readFileSync(repoPath(...parts), "utf8");
}

test("tracked JavaScript files parse", () => {
  const listResult = spawnSync("git", ["ls-files", "-z", "--", "*.js"], {
    cwd: repoRoot,
    encoding: "buffer",
  });

  assert.equal(listResult.status, 0, listResult.stderr.toString("utf8"));

  const jsFiles = listResult.stdout.toString("utf8").split("\0").filter(Boolean);
  assert.ok(jsFiles.length > 0, "expected tracked JavaScript files");

  for (const file of jsFiles) {
    const checkResult = spawnSync(process.execPath, ["--check", file], {
      cwd: repoRoot,
      encoding: "utf8",
    });

    assert.equal(
      checkResult.status,
      0,
      `${file} failed to parse:\n${checkResult.stderr || checkResult.stdout}`
    );
  }
});

test("Model S configurator submits Model S order details", () => {
  const html = readRepoFile("hk2", "order-model-s.html");

  assert.match(html, /<h1>Model S<\/h1>/);
  assert.match(html, /<strong>\$62,990<\/strong>/);
  assert.match(html, /data-order-model="Model S"/);
  assert.match(html, /data-order-trim="Standard Wheels"/);
  assert.match(html, /data-order-price="\$62,990"/);
  assert.match(html, /data-order-image="models\.jpg"/);
  assert.doesNotMatch(html, /data-order-model="Model 3"/);
});

test("payment cart renders stored item data without HTML interpolation", () => {
  const script = readRepoFile("hk2", "script.js");

  assert.doesNotMatch(script, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
  assert.match(script, /paymentCartItems\.replaceChildren\(\)/);
  assert.match(script, /titleEl\.textContent = item\.model/);
  assert.match(script, /trimEl\.textContent = item\.trim/);
});

test("consultation success message treats submitted fields as text", () => {
  const script = readRepoFile("A", "LMS \u0110H-C\u0110 - Antigravity", "script.js");

  assert.doesNotMatch(script, /formSuccessBlock\.innerHTML\s*=\s*`/);
  assert.match(script, /nameValue\.textContent = fullname/);
  assert.match(script, /phoneValue\.textContent = phone/);
  assert.match(script, /emailValue\.textContent = email/);
});
