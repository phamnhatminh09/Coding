# Tesla-style site: navigation, models, contact (`baicuoikitin`)

## Current state

- **[baicuoikitin/trangchu.html](c:/Coding/baicuoikitin/trangchu.html)** — Home layout with inline CSS/JS; hero uses Unsplash; product cards use Unsplash; header links are placeholders (`#`); `TESLA` is plain `<h1>` (not a link); “Schedule a drive” opens schedule.html in a new tab.
- **[baicuoikitin/schedule.html](c:/Coding/baicuoikitin/schedule.html)** — Demo drive flow; local assets (`modY.png`, `mod3.png`, `cybertruck.png`, `modS.png`, `modX.png`); no global site header.
- **Local images:** `modS.png`, `mod3.png`, `modX.png`, `modY.png`, `cybertruck.png`, `tesla.png`, `xebg.png`, etc.
- **[hk2/](c:/Coding/hk2)** — Reference: `styles.css`, `script.js`, model markup; Model 3 currently in `hk2/index.html`.

## Target information architecture

- Home: `index.html`
- Model pages: `model-s.html`, `model-3.html`, `model-x.html`, `model-y.html`, `cybertruck.html`
- `contact.html`, `schedule.html`

## Cross-model navigation (required)

On **every** model product page, the **center navigation** must include **all five** model links: Model S, Model 3, Model X, Model Y, Cybertruck — each pointing to its HTML file. From any model page, users can jump to **any other** model without returning to the home page. The **current** page gets the `active` nav style (underline/highlight). Logo still goes to `index.html`; Order still goes to `contact.html`.

This is the same header block reused on every model page (copy-paste or shared include pattern is fine for static HTML).

## Implementation steps

1. **index.html** — From trangchu: logo→index, nav anchors, local PNGs, View Details→model pages, ORDER→contact.html, schedule link.
2. **styles.css + script.js** — Merge hk2 + trangchu home sections; hero slider JS.
3. **Model pages** — Port from hk2; `model-3.html` from hk2 index; **shared nav with full cross-links** as above; Order→contact.html; logo→index.html.
4. **contact.html** — Form + optional JS validation.
5. **schedule.html** — Site header; logo→index.html.
6. **trangchu.html** — Redirect to `index.html` or keep as alias.

## Optional follow-up

- Shopping/checkout with JS totals (assignment “mua hàng và tính tiền”) — not in initial scope unless requested.
