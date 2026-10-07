const assert = require("node:assert/strict");
const { execFileSync, spawnSync } = require("node:child_process");
const fs = require("node:fs");
const test = require("node:test");

const read = (path) => fs.readFileSync(path, "utf8");

test("tracked JavaScript files parse successfully", () => {
  const files = execFileSync("git", ["ls-files", "-z", "*.js"], { encoding: "buffer" })
    .toString("utf8")
    .split("\0")
    .filter(Boolean);

  assert.ok(files.length > 0, "expected at least one tracked JavaScript file");

  for (const file of files) {
    const result = spawnSync(process.execPath, ["--check", file], { encoding: "utf8" });
    assert.equal(
      result.status,
      0,
      `${file} failed syntax check:\n${result.stderr || result.stdout}`
    );
  }
});

test("Model S configurator submits Model S pricing metadata", () => {
  const html = read("hk2/order-model-s.html");

  assert.match(html, /<strong>\$62,990<\/strong>/);
  assert.match(html, /data-order-model="Model S"/);
  assert.match(html, /data-order-price="\$62,990"/);
  assert.doesNotMatch(html, /data-order-model="Model 3"/);
  assert.doesNotMatch(html, /data-order-price="\$38,990"/);
});

test("payment cart renders stored cart values without HTML interpolation", () => {
  const script = read("hk2/script.js");

  assert.doesNotMatch(script, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
  assert.doesNotMatch(script, /<img src="\$\{item\.image/);
  assert.match(script, /paymentCartItems\.replaceChildren/);
});

test("consultation success message treats submitted fields as text", () => {
  const script = read("A/LMS \u0110H-C\u0110 - Antigravity/script.js");

  assert.doesNotMatch(script, /formSuccessBlock\.innerHTML\s*=\s*`/);
  assert.match(script, /nameText\.textContent\s*=\s*fullname/);
  assert.match(script, /phoneText\.textContent\s*=\s*phone/);
  assert.match(script, /emailText\.textContent\s*=\s*email/);
});

test("animal poll tolerates bad storage and renders counts as text", () => {
  const script = read("html/script.js");

  assert.match(script, /try\s*\{/);
  assert.match(script, /localStorage\.removeItem\('pollCounts'\)/);
  assert.doesNotMatch(script, /pollResult\.innerHTML\s*=/);
  assert.match(script, /pollResult\.replaceChildren/);
});
