const assert = require("assert");
const fs = require("fs");
const path = require("path");

const repoRoot = path.resolve(__dirname, "..");

const pages = [
    {
        file: "hk2/order-model-3.html",
        model: "Model 3",
        price: "$38,990"
    },
    {
        file: "hk2/order-model-s.html",
        model: "Model S",
        price: "$74,990"
    },
    {
        file: "hk2/order-model-x.html",
        model: "Model X",
        price: "$79,990"
    },
    {
        file: "hk2/order-model-y.html",
        model: "Model Y",
        price: "$52,490"
    },
    {
        file: "hk2/order-cybertruck.html",
        model: "Cybertruck",
        price: "$99,990"
    }
];

const getAttribute = (markup, attribute) => {
    const match = markup.match(new RegExp(`${attribute}="([^"]+)"`));
    assert(match, `Missing ${attribute}`);
    return match[1];
};

for (const page of pages) {
    const filePath = path.join(repoRoot, page.file);
    const markup = fs.readFileSync(filePath, "utf8");
    const headingMatch = markup.match(/<h1>([^<]+)<\/h1>/);
    const visiblePriceMatch = markup.match(/<span>(?:Vehicle price|Total price)<\/span>\s*<strong>([^<]+)<\/strong>/);

    assert(headingMatch, `${page.file} is missing a model heading`);
    assert.strictEqual(headingMatch[1], page.model, `${page.file} heading should match its model`);
    assert(visiblePriceMatch, `${page.file} is missing a visible order price`);
    assert.strictEqual(visiblePriceMatch[1], page.price, `${page.file} visible price should match expected price`);

    assert.strictEqual(
        getAttribute(markup, "data-order-model"),
        page.model,
        `${page.file} submits the wrong model to the cart`
    );
    assert.strictEqual(
        getAttribute(markup, "data-order-price"),
        page.price,
        `${page.file} submits a price that differs from the visible price`
    );
}
