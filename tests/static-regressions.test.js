const assert = require("node:assert/strict");
const { readFileSync } = require("node:fs");
const { spawnSync } = require("node:child_process");
const test = require("node:test");

const readText = (path) => readFileSync(path, "utf8");

test("tracked JavaScript files parse successfully", () => {
  const listed = spawnSync("git", ["ls-files", "-z", "--", "*.js"], {
    cwd: process.cwd(),
    encoding: "buffer"
  });

  assert.equal(listed.status, 0, listed.stderr.toString("utf8"));

  const files = listed.stdout
    .toString("utf8")
    .split("\0")
    .filter(Boolean);

  assert.ok(files.length > 0, "expected at least one tracked JavaScript file");

  for (const file of files) {
    const checked = spawnSync(process.execPath, ["--check", file], {
      cwd: process.cwd(),
      encoding: "utf8"
    });

    assert.equal(checked.status, 0, `${file} failed syntax check:\n${checked.stderr}`);
  }
});

test("Model S configurator stores Model S checkout metadata", () => {
  const html = readText("hk2/order-model-s.html");

  assert.match(html, /<h1>Model S<\/h1>/);
  assert.match(html, /<strong>\$62,990<\/strong>/);
  assert.match(html, /data-order-model="Model S"/);
  assert.match(html, /data-order-trim="Standard Wheels"/);
  assert.match(html, /data-order-price="\$62,990"/);
  assert.match(html, /data-order-image="models\.jpg"/);
  assert.doesNotMatch(html, /data-order-model="Model 3"[\s\S]*data-order-image="mods\.png"/);
});

test("payment cart renders stored cart fields as text, not markup", () => {
  const script = readText("hk2/script.js");

  assert.doesNotMatch(script, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
  assert.doesNotMatch(script, /\$\{item\.(?:model|trim|image|price)/);
  assert.match(script, /model\.textContent\s*=\s*item\.model/);
  assert.match(script, /trim\.textContent\s*=\s*item\.trim/);
});

test("LMS consultation success message does not interpolate submitted fields into HTML", () => {
  const script = readText("A/LMS ĐH-CĐ - Antigravity/script.js");

  assert.doesNotMatch(script, /formSuccessBlock\.innerHTML\s*=/);
  assert.doesNotMatch(script, /\$\{(?:fullname|phone|email)\}/);
  assert.match(script, /appendStrong\(fullname\)/);
  assert.match(script, /appendStrong\(phone\)/);
  assert.match(script, /appendStrong\(email\)/);
});
