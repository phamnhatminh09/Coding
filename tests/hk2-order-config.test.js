import assert from "node:assert/strict";
import { existsSync, readdirSync, readFileSync } from "node:fs";
import { dirname, join, resolve } from "node:path";
import { fileURLToPath } from "node:url";
import test from "node:test";

const repoRoot = resolve(dirname(fileURLToPath(import.meta.url)), "..");
const hk2Root = join(repoRoot, "hk2");

const read = (relativePath) => readFileSync(join(repoRoot, relativePath), "utf8");

test("order cart image references point at tracked hk2 assets", () => {
    const htmlFiles = readdirSync(hk2Root).filter((file) => file.endsWith(".html"));

    for (const htmlFile of htmlFiles) {
        const content = read(join("hk2", htmlFile));
        const imageRefs = content.matchAll(/data-order-image="([^"]+)"/g);

        for (const [, imageRef] of imageRefs) {
            assert.ok(
                existsSync(join(hk2Root, imageRef)),
                `${htmlFile} references missing cart image ${imageRef}`
            );
        }
    }
});

test("Model S configurator submits Model S cart metadata", () => {
    const modelSPage = read("hk2/order-model-s.html");

    assert.match(modelSPage, /data-order-model="Model S"/);
    assert.match(modelSPage, /data-order-price="\$62,990"/);
    assert.match(modelSPage, /data-order-image="models\.jpg"/);
});

test("Cybertruck trim tiles expose checkout metadata", () => {
    const cybertruckPage = read("hk2/order-cybertruck.html");

    assert.match(
        cybertruckPage,
        /data-config-trim="All-Wheel Drive"\s+data-config-price="\$79,990"/
    );
    assert.match(
        cybertruckPage,
        /data-config-trim="Cyberbeast Tri-Motor AWD"\s+data-config-price="\$99,990"/
    );
});

test("checkout script applies selected configurator tile metadata", () => {
    const script = read("hk2/script.js");

    assert.match(script, /activeConfigTile/);
    assert.match(script, /getAttribute\("data-config-trim"\)/);
    assert.match(script, /payload\.trim = selectedTrim/);
    assert.match(script, /getAttribute\("data-config-price"\)/);
    assert.match(script, /payload\.price = selectedPrice/);
});
