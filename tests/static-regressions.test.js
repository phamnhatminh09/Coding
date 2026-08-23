const assert = require("node:assert/strict");
const fs = require("node:fs");
const path = require("node:path");
const { spawnSync } = require("node:child_process");
const test = require("node:test");

const repoRoot = path.resolve(__dirname, "..");

const readFile = (relativePath) =>
    fs.readFileSync(path.join(repoRoot, relativePath), "utf8");

test("tracked JavaScript files parse", () => {
    const gitResult = spawnSync("git", ["ls-files", "-z", "*.js"], {
        cwd: repoRoot,
        encoding: "buffer"
    });

    assert.equal(gitResult.status, 0, gitResult.stderr.toString());

    const files = gitResult.stdout
        .toString("utf8")
        .split("\0")
        .filter(Boolean);

    const failures = [];
    for (const file of files) {
        const checkResult = spawnSync(process.execPath, ["--check", file], {
            cwd: repoRoot,
            encoding: "utf8"
        });
        if (checkResult.status !== 0) {
            failures.push(`${file}\n${checkResult.stderr || checkResult.stdout}`);
        }
    }

    assert.deepEqual(failures, []);
});

test("consultation success message does not interpolate submitted fields into HTML", () => {
    const script = readFile("A/LMS ĐH-CĐ - Antigravity/script.js");

    assert.doesNotMatch(
        script,
        /formSuccessBlock\.innerHTML\s*=\s*`[\s\S]*\$\{(?:fullname|phone|email)\}/
    );
});

test("payment cart does not render localStorage-backed cart items with innerHTML", () => {
    const script = readFile("hk2/script.js");

    assert.doesNotMatch(script, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
    assert.match(script, /paymentCartItems\.replaceChildren\(\)/);
});

test("Model S configurator submits Model S checkout metadata", () => {
    const html = readFile("hk2/order-model-s.html");

    assert.match(html, /<h1>Model S<\/h1>/);
    assert.match(html, /<strong>\$62,990<\/strong>/);
    assert.match(html, /data-order-model="Model S"/);
    assert.match(html, /data-order-trim="Standard Wheels"/);
    assert.match(html, /data-order-price="\$62,990"/);
    assert.match(html, /data-order-image="models\.jpg"/);
});
