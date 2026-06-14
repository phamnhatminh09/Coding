const fs = require("fs");
const path = require("path");

const repoRoot = path.resolve(__dirname, "..");
const hk2Root = path.join(repoRoot, "hk2");
const orderPages = [
    "order-model-3.html",
    "order-model-s.html",
    "order-model-x.html",
    "order-model-y.html",
    "order-cybertruck.html"
];

const getMatch = (html, pattern, description, file) => {
    const match = html.match(pattern);
    if (!match) {
        throw new Error(`${file}: missing ${description}`);
    }
    return match[1].trim();
};

const getButtonAttribute = (buttonHtml, attribute, file) =>
    getMatch(buttonHtml, new RegExp(`${attribute}="([^"]+)"`), attribute, file);

for (const file of orderPages) {
    const filePath = path.join(hk2Root, file);
    const html = fs.readFileSync(filePath, "utf8");

    const heading = getMatch(html, /<h1>\s*([^<]+?)\s*<\/h1>/, "page heading", file);
    const priceBlock = getMatch(
        html,
        /<div class="order-config-price">([\s\S]*?)<\/div>\s*<\/div>/,
        "visible price block",
        file
    );
    const visiblePrice = getMatch(priceBlock, /<strong>\s*([^<]+?)\s*<\/strong>/, "visible price", file);
    const checkoutButton = getMatch(
        html,
        /(<button[^>]*class="[^"]*\border-config-cta\b[^"]*"[\s\S]*?>)/,
        "checkout button",
        file
    );

    const checkoutModel = getButtonAttribute(checkoutButton, "data-order-model", file);
    const checkoutPrice = getButtonAttribute(checkoutButton, "data-order-price", file);

    if (checkoutModel !== heading) {
        throw new Error(`${file}: checkout model "${checkoutModel}" does not match heading "${heading}"`);
    }

    if (checkoutPrice !== visiblePrice) {
        throw new Error(`${file}: checkout price "${checkoutPrice}" does not match visible price "${visiblePrice}"`);
    }
}
