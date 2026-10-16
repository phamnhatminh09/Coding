const assert = require("node:assert/strict");
const { execFileSync, spawnSync } = require("node:child_process");
const fs = require("node:fs");
const os = require("node:os");
const path = require("node:path");
const test = require("node:test");

const repoRoot = path.resolve(__dirname, "..");

const normalizeOutput = (value) => value.trim().replace(/\s+/g, " ");

test("tracked JavaScript files are syntactically valid", () => {
  const files = execFileSync("git", ["ls-files", "-z", "--", "*.js"], {
    cwd: repoRoot
  }).toString("utf8").split("\0").filter(Boolean);

  for (const file of files) {
    const result = spawnSync(process.execPath, ["--check", file], {
      cwd: repoRoot,
      encoding: "utf8"
    });
    assert.equal(
      result.status,
      0,
      `${file} failed node --check\n${result.stdout}\n${result.stderr}`
    );
  }
});

test("Model S checkout metadata matches the configured vehicle", () => {
  const modelS = fs.readFileSync(path.join(repoRoot, "hk2/order-model-s.html"), "utf8");

  assert.match(modelS, /<h1>Model S<\/h1>/);
  assert.match(modelS, /<strong>\$62,990<\/strong>/);
  assert.match(modelS, /data-order-model="Model S"/);
  assert.match(modelS, /data-order-trim="Standard Wheels"/);
  assert.match(modelS, /data-order-price="\$62,990"/);
  assert.doesNotMatch(modelS, /data-order-model="Model 3"/);
  assert.doesNotMatch(modelS, /data-order-price="\$38,990"/);
});

test("user and storage backed page content is rendered with text nodes", () => {
  const paymentScript = fs.readFileSync(path.join(repoRoot, "hk2/script.js"), "utf8");
  const consultationScript = fs.readFileSync(
    path.join(repoRoot, "A/LMS ĐH-CĐ - Antigravity/script.js"),
    "utf8"
  );
  const pollScript = fs.readFileSync(path.join(repoRoot, "html/script.js"), "utf8");

  assert.match(paymentScript, /paymentCartItems\.replaceChildren\(\)/);
  assert.doesNotMatch(paymentScript, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
  assert.match(consultationScript, /formSuccessBlock\.replaceChildren/);
  assert.doesNotMatch(consultationScript, /formSuccessBlock\.innerHTML\s*=/);
  assert.match(pollScript, /normalizePollCounts/);
  assert.match(pollScript, /localStorage\.removeItem\('pollCounts'\)/);
  assert.doesNotMatch(pollScript, /pollResult\.innerHTML\s*=/);
});

test("C++ sample programs avoid known crash and max-input hang regressions", (t) => {
  const compiler = spawnSync("g++", ["--version"], { encoding: "utf8" });
  if (compiler.error && compiler.error.code === "ENOENT") {
    t.skip("g++ is not available");
    return;
  }

  const tempDir = fs.mkdtempSync(path.join(os.tmpdir(), "coding-regressions-"));
  const compile = (source, outputName) => {
    const outputPath = path.join(tempDir, outputName);
    const result = spawnSync(
      "g++",
      ["-std=c++17", "-O2", "-Wall", "-Wextra", "-fsanitize=address,undefined", source, "-o", outputPath],
      { cwd: repoRoot, encoding: "utf8", timeout: 30000 }
    );
    assert.equal(result.status, 0, `${source} failed to compile\n${result.stdout}\n${result.stderr}`);
    return outputPath;
  };

  const runSample = (exe, inputFile, answerFile, timeout = 5000) => {
    const result = spawnSync(exe, {
      input: fs.readFileSync(path.join(repoRoot, inputFile), "utf8"),
      encoding: "utf8",
      env: { ...process.env, ASAN_OPTIONS: "detect_leaks=0" },
      timeout
    });
    assert.equal(
      result.status,
      0,
      `${inputFile} failed\nstdout:\n${result.stdout}\nstderr:\n${result.stderr}`
    );
    const expected = fs.readFileSync(path.join(repoRoot, answerFile), "utf8");
    assert.equal(normalizeOutput(result.stdout), normalizeOutput(expected), inputFile);
  };

  const amsJump = compile("C++/2025/ams_jump.cpp", "ams_jump");
  runSample(amsJump, "C++/2025/ams_jump_1.in", "C++/2025/ams_jump_1.ans");
  runSample(amsJump, "C++/2025/ams_jump_2.in", "C++/2025/ams_jump_2.ans");

  const tongbang = compile("C++/2025/tongbang.cpp", "tongbang");
  for (let index = 1; index <= 6; index += 1) {
    runSample(tongbang, `C++/2025/tongbang_${index}.in`, `C++/2025/tongbang_${index}.ans`);
  }
});
