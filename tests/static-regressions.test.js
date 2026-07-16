const assert = require("assert");
const fs = require("fs");
const path = require("path");

const root = path.resolve(__dirname, "..");
const read = (relativePath) => fs.readFileSync(path.join(root, relativePath), "utf8");

const getAttr = (html, attr) => {
  const match = html.match(new RegExp(`${attr}="([^"]+)"`));
  return match ? match[1] : "";
};

const lmsLite = read("C/LMS Lite - Cursor/js/main.js");
assert(
  !lmsLite.includes("navToggle?.querySelector('i').className"),
  "LMS Lite must not assign through optional chaining, which is a parse error"
);

const modelS = read("hk2/order-model-s.html");
assert.strictEqual(getAttr(modelS, "data-order-model"), "Model S");
assert.strictEqual(getAttr(modelS, "data-order-price"), "$62,990");
assert(
  modelS.includes("<strong>$62,990</strong>"),
  "Model S visible price must match submitted order price"
);

[
  "hk2/order-model-3.html",
  "hk2/order-model-s.html",
  "hk2/order-model-y.html",
  "hk2/order-model-x.html",
  "hk2/order-cybertruck.html"
].forEach((relativePath) => {
  const html = read(relativePath);
  const paidTiles = html.matchAll(/<article class="config-tile[^"]*"([^>]*)>[\s\S]*?<span>\$[\d,]+<\/span>/g);
  for (const [, attributes] of paidTiles) {
    assert(
      attributes.includes("data-order-price") || attributes.includes("data-order-price-delta"),
      `${relativePath} has a priced configurator tile without order metadata`
    );
  }
});

const hk2Script = read("hk2/script.js");
assert(
  hk2Script.includes("applyConfiguratorSelections(payload, parentScope)"),
  "Order buttons must apply active configurator selections before writing the cart"
);
assert(
  !/paymentCartItems\.innerHTML\s*=\s*cart\.map/.test(hk2Script),
  "Payment cart rows must not be rendered by interpolating stored cart values into innerHTML"
);
assert(
  hk2Script.includes("title.textContent = item.model"),
  "Payment cart model names should be written as text"
);

const lmsDhCd = read("A/LMS ĐH-CĐ - Antigravity/script.js");
assert(
  lmsDhCd.includes("escapeHtml(fullname)") &&
    lmsDhCd.includes("escapeHtml(phone)") &&
    lmsDhCd.includes("escapeHtml(email)"),
  "Consultation success message must escape user-provided fields"
);
