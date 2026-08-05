const assert = require("node:assert/strict");
const { execFileSync } = require("node:child_process");
const fs = require("node:fs");
const path = require("node:path");
const test = require("node:test");

const repoRoot = path.resolve(__dirname, "..");

function trackedFiles(extension) {
    return execFileSync("git", ["ls-files", "-z"], { cwd: repoRoot })
        .toString("utf8")
        .split("\0")
        .filter((file) => file.endsWith(extension));
}

function readRepoFile(file) {
    return fs.readFileSync(path.join(repoRoot, file), "utf8");
}

function getAttr(markup, attr) {
    const match = markup.match(new RegExp(`${attr}="([^"]*)"`));
    return match ? match[1] : "";
}

test("tracked JavaScript files parse", () => {
    for (const file of trackedFiles(".js")) {
        assert.doesNotThrow(
            () => execFileSync(process.execPath, ["--check", path.join(repoRoot, file)], { stdio: "pipe" }),
            `${file} should pass node --check`
        );
    }
});

test("Model S configurator submits Model S cart metadata", () => {
    const file = "hk2/order-model-s.html";
    const html = readRepoFile(file);
    const heading = html.match(/<h1>([^<]+)<\/h1>/)?.[1];
    const visiblePrice = html.match(/<span>Vehicle price<\/span>\s*<strong>([^<]+)<\/strong>/)?.[1];
    const button = html.match(/<button[\s\S]*?order-config-cta[\s\S]*?>/)?.[0] || "";

    assert.equal(getAttr(button, "data-order-model"), heading);
    assert.equal(getAttr(button, "data-order-price"), visiblePrice);
    assert.notEqual(getAttr(button, "data-order-image"), "mods.png");
    assert.ok(fs.existsSync(path.join(repoRoot, "hk2", getAttr(button, "data-order-image"))));
});

test("consultation success message renders submitted fields as text", () => {
    const scriptFile = trackedFiles(".js").find(
        (file) => file.startsWith("A/LMS ") && file.includes(" - Antigravity/script.js") && !file.includes("Lite")
    );
    assert.ok(scriptFile, "expected LMS Antigravity script to be tracked");
    const script = readRepoFile(scriptFile);

    assert.doesNotMatch(script, /formSuccessBlock\.innerHTML\s*=[\s\S]*\$\{(?:fullname|phone|email)\}/);
    assert.match(script, /formSuccessBlock\.replaceChildren/);
});

test("payment cart renders cart fields through DOM text APIs", () => {
    const script = readRepoFile("hk2/script.js");

    assert.doesNotMatch(script, /paymentCartItems\.innerHTML\s*=\s*cart\.map/);
    assert.match(script, /paymentCartItems\.replaceChildren/);
    assert.match(script, /model\.textContent = item\.model/);
    assert.match(script, /trim\.textContent = item\.trim/);
});
