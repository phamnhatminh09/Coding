const assert = require("node:assert/strict");
const { execFileSync, spawnSync } = require("node:child_process");
const fs = require("node:fs");
const os = require("node:os");
const path = require("node:path");
const test = require("node:test");

const ROOT = path.resolve(__dirname, "..");

const read = (relativePath) => fs.readFileSync(path.join(ROOT, relativePath), "utf8");

test("critical browser scripts remain parseable", () => {
  [
    "C/LMS Lite - Cursor/js/main.js",
    "hk2/script.js",
    "html/script.js",
    "A/LMS ĐH-CĐ - Antigravity/script.js"
  ].forEach((scriptPath) => {
    execFileSync(process.execPath, ["--check", path.join(ROOT, scriptPath)], {
      cwd: ROOT,
      stdio: "pipe"
    });
  });
});

test("payment cart and form success render untrusted values as text", () => {
  const teslaScript = read("hk2/script.js");
  assert.doesNotMatch(teslaScript, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
  assert.match(teslaScript, /paymentCartItems\.replaceChildren\(fragment\)/);
  assert.match(teslaScript, /title\.textContent\s*=\s*item\.model/);
  assert.match(teslaScript, /trim\.textContent\s*=\s*item\.trim/);

  const lmsScript = read("A/LMS ĐH-CĐ - Antigravity/script.js");
  assert.doesNotMatch(lmsScript, /formSuccessBlock\.innerHTML\s*=/);
  assert.match(lmsScript, /nameStrong\.textContent\s*=\s*fullname/);
  assert.match(lmsScript, /phoneStrong\.textContent\s*=\s*phone/);
  assert.match(lmsScript, /emailStrong\.textContent\s*=\s*email/);
});

test("animal poll tolerates corrupted localStorage and avoids HTML injection", () => {
  const animalScript = read("html/script.js");
  assert.match(animalScript, /try\s*\{\s*[\s\S]*JSON\.parse\(storedPollCounts\)/);
  assert.match(animalScript, /localStorage\.removeItem\('pollCounts'\)/);
  assert.doesNotMatch(animalScript, /pollResult\.innerHTML\s*=/);
  assert.match(animalScript, /pollResult\.replaceChildren\(/);
});

test("Model S configurator submits Model S checkout metadata", () => {
  const modelSOrder = read("hk2/order-model-s.html");
  assert.match(modelSOrder, /<strong>\$62,990<\/strong>/);
  assert.match(modelSOrder, /data-order-model="Model S"/);
  assert.match(modelSOrder, /data-order-trim="Standard Wheels"/);
  assert.match(modelSOrder, /data-order-price="\$62,990"/);
  assert.match(modelSOrder, /data-order-image="models\.jpg"/);
  assert.doesNotMatch(modelSOrder, /data-order-model="Model 3"/);
});

const compileAndRunSample = (sourcePath, inputPath, expectedPath) => {
  const tmpDir = fs.mkdtempSync(path.join(os.tmpdir(), "critical-regression-"));
  const executable = path.join(tmpDir, "program");
  try {
    execFileSync(
      "g++",
      [
        "-std=c++17",
        "-O2",
        "-Wall",
        "-Wextra",
        "-fsanitize=address,undefined",
        path.join(ROOT, sourcePath),
        "-o",
        executable
      ],
      { cwd: ROOT, stdio: "pipe" }
    );

    const result = spawnSync(executable, {
      input: read(inputPath),
      encoding: "utf8",
      timeout: 5000,
      maxBuffer: 1024 * 1024
    });

    assert.equal(result.error, undefined, result.error && result.error.message);
    assert.equal(result.status, 0, result.stderr);
    assert.equal(
      result.stdout.trim().replace(/\s+/g, " "),
      read(expectedPath).trim().replace(/\s+/g, " ")
    );
  } finally {
    fs.rmSync(tmpDir, { recursive: true, force: true });
  }
};

test("ams_jump samples do not crash and match expected answers", () => {
  compileAndRunSample("C++/2025/ams_jump.cpp", "C++/2025/ams_jump_1.in", "C++/2025/ams_jump_1.ans");
  compileAndRunSample("C++/2025/ams_jump.cpp", "C++/2025/ams_jump_2.in", "C++/2025/ams_jump_2.ans");
});

test("tongbang max-constraint sample finishes and matches expected answer", () => {
  compileAndRunSample("C++/2025/tongbang.cpp", "C++/2025/tongbang_6.in", "C++/2025/tongbang_6.ans");
});
