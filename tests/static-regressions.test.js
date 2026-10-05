const assert = require("node:assert/strict");
const { execFileSync } = require("node:child_process");
const { readFileSync } = require("node:fs");
const path = require("node:path");
const test = require("node:test");

const root = path.resolve(__dirname, "..");
const DH_CD = "\u0110H-C\u0110";

const readRepoFile = (...parts) => readFileSync(path.join(root, ...parts), "utf8");

test("tracked JavaScript files parse", () => {
  const files = execFileSync("git", ["ls-files", "-z", "*.js"], { cwd: root })
    .toString("utf8")
    .split("\0")
    .filter(Boolean);

  for (const file of files) {
    execFileSync(process.execPath, ["--check", path.join(root, file)], { stdio: "pipe" });
  }
});

test("LMS Lite mobile nav close handler does not use optional-chain assignment", () => {
  const script = readRepoFile("C", "LMS Lite - Cursor", "js", "main.js");

  assert.equal(script.includes("navToggle?.querySelector('i').className ="), false);
  assert.match(script, /const icon = navToggle\?\.querySelector\('i'\);/);
});

test("consultation form success message does not interpolate submitted fields as HTML", () => {
  const script = readRepoFile("A", `LMS ${DH_CD} - Antigravity`, "script.js");

  assert.doesNotMatch(script, /formSuccessBlock\.innerHTML\s*=/);
  assert.match(script, /textContent: fullname/);
  assert.match(script, /textContent: phone/);
  assert.match(script, /textContent: email/);
});

test("payment cart renders localStorage data with DOM text nodes", () => {
  const script = readRepoFile("hk2", "script.js");

  assert.doesNotMatch(script, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
  assert.match(script, /paymentCartItems\.replaceChildren\(\.\.\.cart\.map\(renderCartItem\)\)/);
  assert.match(script, /title\.textContent = item\.model \|\| "Model";/);
  assert.match(script, /trim\.textContent = item\.trim \|\| "Base";/);
});

test("Model S configurator submits Model S metadata", () => {
  const html = readRepoFile("hk2", "order-model-s.html");

  assert.match(html, /data-order-model="Model S"/);
  assert.match(html, /data-order-trim="Standard Wheels"/);
  assert.match(html, /data-order-price="\$62,990"/);
  assert.doesNotMatch(html, /data-order-model="Model 3"[\s\S]{0,160}data-order-price="\$38,990"/);
});
