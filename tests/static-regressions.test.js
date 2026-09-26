const assert = require("node:assert/strict");
const { execFileSync, spawnSync } = require("node:child_process");
const fs = require("node:fs");
const os = require("node:os");
const path = require("node:path");
const test = require("node:test");

const root = path.resolve(__dirname, "..");

const read = (relativePath) => fs.readFileSync(path.join(root, relativePath), "utf8");
const normalizeOutput = (value) => value.trim().replace(/\s+/g, " ");

test("tracked JavaScript files parse", () => {
  const jsFiles = execFileSync("git", ["ls-files", "-z", "--", ":(glob)**/*.js"], {
    cwd: root,
  })
    .toString("utf8")
    .split("\0")
    .filter(Boolean);

  for (const relativePath of jsFiles) {
    execFileSync(process.execPath, ["--check", path.join(root, relativePath)], {
      cwd: root,
      stdio: "pipe",
    });
  }
});

test("consultation success message renders submitted fields as text", () => {
  const script = read("A/LMS ĐH-CĐ - Antigravity/script.js");

  assert.doesNotMatch(
    script,
    /formSuccessBlock\.innerHTML\s*=\s*`[\s\S]*\$\{(?:fullname|phone|email)\}/,
  );
  assert.match(script, /formSuccessBlock\.replaceChildren\(/);
});

test("payment cart renders stored cart fields without HTML interpolation", () => {
  const script = read("hk2/script.js");

  assert.doesNotMatch(script, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
  assert.doesNotMatch(script, /innerHTML\s*=\s*`[\s\S]*\$\{item\.(?:image|model|trim)/);
  assert.match(script, /paymentCartItems\.replaceChildren\(\)/);
  assert.match(script, /model\.textContent = item\.model/);
});

test("Model S configurator submits Model S checkout metadata", () => {
  const html = read("hk2/order-model-s.html");

  assert.match(html, /<h1>Model S<\/h1>/);
  assert.match(html, /data-order-model="Model S"/);
  assert.match(html, /data-order-trim="Standard Wheels"/);
  assert.match(html, /data-order-price="\$62,990"/);
  assert.match(html, /data-order-image="models\.jpg"/);
  assert.doesNotMatch(html, /data-order-model="Model 3"/);
});

function compileCpp(relativePath, tmpDir) {
  const output = path.join(tmpDir, path.basename(relativePath, ".cpp"));
  const result = spawnSync("g++", ["-std=c++17", "-O2", path.join(root, relativePath), "-o", output], {
    cwd: root,
    encoding: "utf8",
  });

  assert.equal(result.status, 0, result.stderr || result.stdout);
  return output;
}

function runCase(executable, inputPath, expectedPath) {
  const result = spawnSync(executable, {
    input: read(inputPath),
    encoding: "utf8",
    timeout: 3000,
    maxBuffer: 1024 * 1024,
  });

  assert.equal(result.status, 0, result.stderr || result.stdout);
  assert.equal(normalizeOutput(result.stdout), normalizeOutput(read(expectedPath)));
}

test("C++ sample regressions complete with expected output", () => {
  const tmpDir = fs.mkdtempSync(path.join(os.tmpdir(), "coding-regressions-"));

  try {
    const amsJump = compileCpp("C++/2025/ams_jump.cpp", tmpDir);
    runCase(amsJump, "C++/2025/ams_jump_1.in", "C++/2025/ams_jump_1.ans");
    runCase(amsJump, "C++/2025/ams_jump_2.in", "C++/2025/ams_jump_2.ans");

    const tongbang = compileCpp("C++/2025/tongbang.cpp", tmpDir);
    assert.doesNotMatch(read("C++/2025/tongbang.cpp"), /vector<int>\s+firstrow/);
    runCase(tongbang, "C++/2025/tongbang_6.in", "C++/2025/tongbang_6.ans");
  } finally {
    fs.rmSync(tmpDir, { recursive: true, force: true });
  }
});
