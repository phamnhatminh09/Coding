const fs = require("fs");
const path = require("path");
const assert = require("assert");

const html = fs.readFileSync(path.join(__dirname, "order-model-s.html"), "utf8");

const readAttribute = (name) => {
    const match = html.match(new RegExp(`${name}="([^"]+)"`));
    assert(match, `Missing ${name}`);
    return match[1];
};

assert.match(html, /<h1>\s*Model S\s*<\/h1>/);
assert.match(html, /<strong>\$74,990<\/strong>/);
assert.strictEqual(readAttribute("data-order-model"), "Model S");
assert.strictEqual(readAttribute("data-order-trim"), "Plaid All-Wheel Drive");
assert.strictEqual(readAttribute("data-order-price"), "$74,990");
assert.strictEqual(readAttribute("data-order-image"), "mods-white.png");
