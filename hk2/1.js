// Chờ DOM parse xong rồi mới chạy toàn bộ logic (tránh query element chưa tồn tại).
document.addEventListener("DOMContentLoaded", () => {
    // Khóa lưu localStorage: CART_KEY là định dạng hiện tại, LEGACY_KEY dùng để tương thích dữ liệu cũ.
    const CART_KEY = "teslaOrderCart"; // Tên key lưu giỏ hàng dạng JSON.
    const LEGACY_KEY = "teslaOrderSelection"; // Tên key cũ khi chỉ lưu một lựa chọn đơn.
    const parsePrice = (value) => Number(String(value || "0").replace(/[^0-9.-]+/g, "")) || 0; // Bỏ ký tự không phải số rồi parse sang Number.
    const formatPrice = (num) => `$${Number(num || 0).toLocaleString("en-US")}`; // Định dạng tiền USD có dấu phẩy ngăn cách nghìn.
    // Luôn trả về mảng hợp lệ kể cả khi localStorage thiếu dữ liệu hoặc bị lỗi JSON.
    const getCart = () => {
        try { // Thử đọc và parse JSON.
            const parsed = JSON.parse(localStorage.getItem(CART_KEY) || "[]"); // Lấy chuỗi JSON hoặc mặc định "[]".
            return Array.isArray(parsed) ? parsed : []; // Chỉ chấp nhận mảng, không thì trả mảng rỗng.
        } catch (error) { // JSON hỏng hoặc lỗi parse.
            return []; // Trả mảng rỗng an toàn.
        }
    };
    const setCart = (items) => {
        localStorage.setItem(CART_KEY, JSON.stringify(items)); // Ghi lại toàn bộ giỏ hàng vào localStorage.
    };
    const getSafeCartImage = (image) => {
        const candidate = String(image || "").trim(); // Chỉ cho phép tên file ảnh nội bộ, không nhận HTML/URL tùy ý.
        return /^[A-Za-z0-9_-]+\.(?:avif|jpe?g|png|webp)$/i.test(candidate) ? candidate : "mod3.png";
    };
    const header = document.querySelector("header"); // Tham chiếu phần header cố định trên cùng.
    if (header) { // Chỉ gắn listener nếu có header trên trang.
        window.addEventListener("scroll", () => { // Mỗi lần cuộn trang.
            if (window.scrollY > 50) { // Đã cuộn xuống đủ xa.
                header.style.background = "#0b0b0b"; // Nền header đậm hơn.
                header.style.boxShadow = "0 2px 10px rgba(0,0,0,0.5)"; // Thêm bóng tách khỏi nội dung.
            } else { // Gần đầu trang.
                header.style.background = "rgba(8, 8, 8, 0.97)"; // Nền gần trong suốt như ban đầu.
                header.style.boxShadow = "none"; // Bỏ bóng.
            }
        });
    }

    // Bộ chuyển phiên bản ở trang Model Y: đổi tab active và hiện đúng khối thông số tương ứng.
    const specToggle = document.querySelector(".model-y-specs-head .spec-toggle"); // Vùng chứa nút chọn phiên bản xe.
    if (specToggle) { // Trang có bộ toggle mới xử lý.
        const buttons = specToggle.querySelectorAll("button[data-variant]"); // Các nút có data-variant.
        const panels = document.querySelectorAll(".model-y-specs-panel[data-variant]"); // Các panel thông số tương ứng.
        buttons.forEach((btn) => { // Gắn sự kiện cho từng nút.
            btn.addEventListener("click", () => { // Khi bấm một phiên bản.
                const variant = btn.getAttribute("data-variant"); // Đọc mã phiên bản (ví dụ Long Range).
                buttons.forEach((b) => b.classList.toggle("active", b === btn)); // Chỉ nút được bấm có class active.
                panels.forEach((panel) => {
                    panel.hidden = panel.getAttribute("data-variant") !== variant; // Ẩn panel không khớp, hiện panel khớp.
                });
            });
        });
    }

    const slides = document.querySelectorAll(".slide"); // Tất cả ảnh slide trong hero.
    if (slides.length > 1) { // Cần ít nhất 2 slide mới tự động chuyển.
        let index = 0; // Chỉ số slide đang hiển thị.
        setInterval(() => { // Lặp mỗi 4 giây.
            slides[index].classList.remove("active"); // Tắt slide hiện tại.
            index = (index + 1) % slides.length; // Chuyển sang slide kế (vòng lại từ đầu).
            slides[index].classList.add("active"); // Bật slide mới.
        }, 4000); // Chu kỳ 4000 ms.
    }

    const contactForm = document.getElementById("contact-form"); // Form liên hệ trên contact.html.
    if (contactForm) { // Chỉ chạy khi trang có form này.
        const successMessage = document.getElementById("contact-success"); // Thông báo gửi thành công (ẩn mặc định).
        contactForm.addEventListener("submit", (event) => {
            event.preventDefault(); // Không gửi form theo cách mặc định (tránh reload).
            const requiredFields = contactForm.querySelectorAll("[required]"); // Tất cả ô bắt buộc.
            let valid = true; // Cờ hợp lệ tổng.

            requiredFields.forEach((field) => {
                if (!field.value.trim()) { // Ô trống sau khi trim.
                    valid = false; // Đánh dấu không hợp lệ.
                }
            });

            if (!valid) {
                alert("Please fill in all required fields."); // Thông báo thiếu trường.
                return; // Dừng, không reset form.
            }

            if (successMessage) {
                successMessage.style.display = "block"; // Hiện dòng xác nhận gửi thành công.
            }
            contactForm.reset(); // Xóa nội dung form sau khi xử lý.
        });
    }

    // Handler dùng chung cho nút "thêm giỏ / thanh toán" ở trang inventory và trang order.
    const inventoryButtons = document.querySelectorAll("[data-order-model]"); // Mọi nút có thuộc tính đặt hàng theo model.
    if (inventoryButtons.length) { // Có ít nhất một nút.
        inventoryButtons.forEach((button) => {
            button.addEventListener("click", () => {
                const payload = {
                    model: button.getAttribute("data-order-model") || "Model 3", // Tên xe từ data attribute.
                    trim: button.getAttribute("data-order-trim") || "Base", // Phiên bản/trim.
                    price: button.getAttribute("data-order-price") || "$38,990", // Giá hiển thị dạng chuỗi.
                    image: button.getAttribute("data-order-image") || "mod3.png", // Ảnh đại diện trong giỏ.
                    quantity: 1 // Số lượng mặc định khi thêm mới.
                };
                const parentScope = button.closest(".inventory-card, .order-config-panel"); // Phạm vi thẻ cha gần nhất.
                const homeChargerCheckbox = parentScope ? parentScope.querySelector("[data-home-charger]") : null; // Checkbox bộ sạc tại nhà nếu có.
                if (homeChargerCheckbox && homeChargerCheckbox.checked) { // Người dùng chọn thêm Home Charger.
                    const upgradedPrice = parsePrice(payload.price) + 450; // Cộng thêm 450 USD vào giá số.
                    payload.price = formatPrice(upgradedPrice); // Ghi lại giá đã định dạng.
                    payload.trim = `${payload.trim} + Home Charger`; // Ghi chú trong trim để phân biệt cấu hình.
                }
                const action = button.getAttribute("data-order-action") || "checkout"; // "add" chỉ thêm giỏ, mặc định chuyển thanh toán.
                const cart = getCart(); // Đọc giỏ hiện tại.
                // Gộp cấu hình giống nhau thành một dòng, chỉ tăng số lượng thay vì tạo item trùng.
                const existing = cart.find((item) =>
                    item.model === payload.model &&
                    item.trim === payload.trim &&
                    item.price === payload.price &&
                    item.image === payload.image
                );
                if (existing) {
                    existing.quantity = (Number(existing.quantity) || 1) + 1; // Tăng số lượng dòng đã có.
                } else {
                    cart.push(payload); // Thêm dòng mới vào mảng giỏ.
                }
                setCart(cart); // Lưu giỏ đã cập nhật.
                if (action === "add") {
                    alert(`${payload.model} added to cart.`); // Chỉ báo đã thêm, không chuyển trang.
                    return;
                }
                window.location.href = "payment.html"; // Chuyển sang trang thanh toán.
            });
        });
    }

    const inventoryGrid = document.querySelector(".inventory-grid"); // Lưới thẻ xe trên inventory.
    if (inventoryGrid) {
        const modelFilters = document.querySelectorAll(".inventory-model-filter"); // Checkbox lọc theo dòng xe.
        const trimFilters = document.querySelectorAll(".filter-pill[data-trim]"); // Nút lọc trim.
        const cityFilters = document.querySelectorAll(".city-pill[data-city]"); // Nút chọn thành phố.
        const cityLabel = document.getElementById("inventory-city-label"); // Nhãn hiển thị tên thành phố đang chọn.
        const sortSelect = document.getElementById("inventory-sort"); // Dropdown sắp xếp theo giá.
        const resetButton = document.getElementById("inventory-reset"); // Nút reset bộ lọc.
        const loadMoreButton = document.getElementById("inventory-load-more"); // Nút tải thêm thẻ.
        let hasFilterInteraction = false; // Chưa đụng lọc model/trim thì chỉ lọc theo city (logic đặc biệt).
        const pageSize = 6; // Số thẻ hiển thị mỗi "trang" trước khi bấm load more.
        let visibleCount = pageSize; // Số thẻ đang được phép hiện sau sort/lọc.

        // Áp dụng toàn bộ trạng thái lọc, sắp xếp và phân trang ("load more") trong một lần xử lý.
        const applyInventoryState = () => {
            const activeModels = Array.from(modelFilters)
                .filter((filter) => filter.checked) // Chỉ checkbox đang bật.
                .map((filter) => filter.value); // Lấy giá trị model.
            const activeTrimButton = Array.from(trimFilters).find((btn) => btn.classList.contains("active")); // Nút trim đang active (nếu có).
            const activeTrim = activeTrimButton ? activeTrimButton.getAttribute("data-trim") : ""; // Chuỗi trim hoặc rỗng.
            const activeCityButton = Array.from(cityFilters).find((btn) => btn.classList.contains("active")); // Nút thành phố active.
            const activeCity = activeCityButton ? activeCityButton.getAttribute("data-city") : ""; // Mã thành phố hoặc rỗng.
            if (cityLabel && activeCity) {
                cityLabel.textContent = activeCity; // Hiện tên thành phố trên nhãn.
            } else if (cityLabel) {
                cityLabel.textContent = "All Cities"; // Không chọn cụ thể thì hiện tất cả.
            }
            const cards = Array.from(inventoryGrid.querySelectorAll(".inventory-card")); // Danh sách thẻ xe hiện có trong lưới.

            cards.forEach((card) => {
                if (!hasFilterInteraction || (!activeModels.length && !activeTrim)) { // Chưa lọc model/trim hoặc chưa tương tác bộ lọc đó.
                    const cardCity = card.getAttribute("data-city") || ""; // Thuộc tính city trên thẻ.
                    card.style.display = !activeCity || cardCity === activeCity ? "" : "none"; // Chỉ ẩn theo city.
                    return; // Bỏ qua so khớp model/trim ở nhánh này.
                }
                const model = card.getAttribute("data-model") || ""; // Model của thẻ.
                const trim = card.getAttribute("data-trim") || ""; // Trim của thẻ.
                const cardCity = card.getAttribute("data-city") || ""; // City của thẻ.
                const modelMatch = !activeModels.length || activeModels.includes(model); // Không chọn model nào = không lọc theo model.
                const trimMatch = !activeTrim || trim === activeTrim; // Không chọn trim = không lọc theo trim.
                const cityMatch = !activeCity || cardCity === activeCity; // City khớp hoặc không lọc city.
                card.style.display = modelMatch && trimMatch && cityMatch ? "" : "none"; // Ẩn nếu bất kỳ điều kiện nào fail.
            });

            const sortedVisible = cards
                .filter((card) => card.style.display !== "none") // Chỉ thẻ đang visible sau bước lọc.
                .sort((a, b) => {
                    const priceA = Number(a.getAttribute("data-price")) || 0; // Giá số trên thẻ A.
                    const priceB = Number(b.getAttribute("data-price")) || 0; // Giá số trên thẻ B.
                    if (sortSelect && sortSelect.value === "price-desc") {
                        return priceB - priceA; // Giảm dần.
                    }
                    return priceA - priceB; // Tăng dần (mặc định).
                });

            // Gắn lại phần tử theo thứ tự đã sort để thứ tự DOM khớp với tiêu chí giá.
            sortedVisible.forEach((card) => inventoryGrid.appendChild(card));

            sortedVisible.forEach((card, index) => {
                card.style.display = index < visibleCount ? "" : "none"; // Chỉ hiện visibleCount thẻ đầu trong danh sách đã sort.
            });

            if (loadMoreButton) {
                loadMoreButton.style.display = sortedVisible.length > visibleCount ? "" : "none"; // Ẩn nút nếu đã hiện hết.
            }
        };

        modelFilters.forEach((filter) => {
            filter.addEventListener("change", () => {
                hasFilterInteraction = true; // Đã dùng bộ lọc model.
                visibleCount = pageSize; // Reset về số thẻ ban đầu khi đổi lọc.
                applyInventoryState(); // Cập nhật lưới.
            });
        });
        if (sortSelect) {
            sortSelect.addEventListener("change", () => {
                visibleCount = pageSize; // Đổi sort thì reset phân trang.
                applyInventoryState();
            });
        }
        trimFilters.forEach((button) => {
            button.addEventListener("click", () => {
                hasFilterInteraction = true; // Đã dùng lọc trim.
                const wasActive = button.classList.contains("active"); // Trước khi bấm, nút này đã active chưa.
                trimFilters.forEach((btn) => btn.classList.remove("active")); // Bỏ active tất cả.
                if (!wasActive) {
                    button.classList.add("active"); // Bật lại nếu trước đó không active (toggle: bấm lần 2 = bỏ chọn).
                }
                visibleCount = pageSize;
                applyInventoryState();
            });
        });
        cityFilters.forEach((button) => {
            button.addEventListener("click", () => {
                hasFilterInteraction = true;
                cityFilters.forEach((btn) => btn.classList.toggle("active", btn === button)); // Chỉ một city active.
                visibleCount = pageSize;
                applyInventoryState();
            });
        });
        if (resetButton) {
            resetButton.addEventListener("click", () => {
                modelFilters.forEach((filter) => {
                    filter.checked = false; // Bỏ chọn tất cả model.
                });
                trimFilters.forEach((btn) => btn.classList.remove("active")); // Bỏ chọn trim.
                const defaultCity = cityFilters[0]; // Thành phố mặc định = nút đầu tiên.
                cityFilters.forEach((btn) => btn.classList.toggle("active", btn === defaultCity)); // Chỉ city đầu active.
                visibleCount = pageSize;
                applyInventoryState();
            });
        }
        if (loadMoreButton) {
            loadMoreButton.addEventListener("click", () => {
                visibleCount += pageSize; // Tăng số thẻ được phép hiện.
                applyInventoryState();
            });
        }
        applyInventoryState(); // Trạng thái ban đầu khi load trang.
    }

    // Bộ chọn màu sơn hiển thị trên các trang cấu hình xe.
    const paintChips = document.querySelectorAll(".config-chip"); // Các nút tròn chọn màu.
    if (paintChips.length) {
        // Ánh xạ tên màu -> CSS filter để một ảnh gốc có thể giả lập nhiều màu sơn.
        const getPaintFilter = (paintName) => {
            const paint = (paintName || "").toLowerCase(); // Chuẩn hóa tên màu chữ thường.
            const filterMap = {
                white: "brightness(1.08) saturate(0.85)", // Trắng.
                "satin-white": "brightness(1.08) saturate(0.9)", // Trắng satin.
                black: "brightness(0.58) saturate(0.7)", // Đen.
                "satin-black": "brightness(0.52) saturate(0.65)", // Đen satin.
                blue: "hue-rotate(160deg) saturate(1.35) brightness(0.92)", // Xanh.
                red: "hue-rotate(0deg) saturate(1.25) brightness(0.98)", // Đỏ.
                silver: "saturate(0.45) brightness(1.02)", // Bạc.
                grey: "saturate(0.4) brightness(0.95)", // Xám.
                stainless: "saturate(0.25) brightness(1.02) contrast(1.05)" // Thép không gỉ (Cybertruck).
            };
            return filterMap[paint] || "none"; // Không khớp thì không áp filter.
        };

        const applySelectedPaint = (chipRow) => {
            if (!chipRow) {
                return; // Không có hàng chip thì thoát.
            }
            const activeChip = chipRow.querySelector(".config-chip.active"); // Chip đang được chọn.
            const paint = activeChip ? activeChip.getAttribute("data-paint") : ""; // Giá trị data-paint.
            const layout = chipRow.closest(".order-config-layout"); // Layout cha cấu hình.
            const visualImage = layout ? layout.querySelector(".order-config-visual img") : null; // Ảnh xe lớn (có thể gán filter sau này).
        };

        paintChips.forEach((chip) => {
            chip.addEventListener("click", () => {
                const chipRow = chip.closest(".config-chip-row"); // Hàng chứa các chip màu.
                if (!chipRow) {
                    return;
                }
                const siblings = chipRow.querySelectorAll(".config-chip"); // Tất cả chip cùng hàng.
                siblings.forEach((item) => item.classList.toggle("active", item === chip)); // Chỉ chip được bấm có active.
                applySelectedPaint(chipRow); // Cập nhật trạng thái theo chip chọn.
            });
        });

        document.querySelectorAll(".config-chip-row").forEach((chipRow) => {
            applySelectedPaint(chipRow); // Khởi tạo đúng trạng thái khi load (chip .active có sẵn trong HTML).
        });
    }

    const wheelTiles = document.querySelectorAll(".config-tiles .config-tile"); // Ô chọn mâm/lốp trong configurator.
    if (wheelTiles.length) {
        wheelTiles.forEach((tile) => {
            tile.addEventListener("click", () => {
                const group = tile.closest(".config-tiles"); // Nhóm mâm hiện tại.
                if (!group) {
                    return;
                }
                const siblings = group.querySelectorAll(".config-tile"); // Các ô cùng nhóm.
                siblings.forEach((item) => item.classList.toggle("active", item === tile)); // Chỉ một ô active trong nhóm.
            });
        });
    }

    // Khối render giỏ hàng ở trang thanh toán + điều khiển tăng/giảm số lượng.
    const paymentCartItems = document.getElementById("payment-cart-items"); // Container danh sách dòng giỏ.
    if (paymentCartItems) {
        let cart = getCart(); // Biến giỏ có thể thay đổi khi +/- hoặc migration.
        // Migration 1 lần: chuyển dữ liệu cũ (1 item) sang định dạng giỏ hàng dạng mảng.
        if (!cart.length) {
            const storedSelection = localStorage.getItem(LEGACY_KEY); // Chuỗi JSON phiên bản cũ.
            if (storedSelection) {
                try {
                    const legacy = JSON.parse(storedSelection); // Parse object cũ.
                    cart = [{ ...legacy, quantity: Number(legacy.quantity) || 1 }]; // Gói thành mảng một phần tử.
                    setCart(cart); // Ghi định dạng mới.
                    localStorage.removeItem(LEGACY_KEY); // Xóa key cũ để không migrate lại.
                } catch (error) {
                    localStorage.removeItem(LEGACY_KEY); // Dữ liệu hỏng thì xóa key cũ.
                }
            }
        }

        const paymentTotal = document.getElementById("payment-total"); // Phần tử hiển thị tổng tiền.
        const paymentSubtotal = document.getElementById("payment-subtotal"); // Tổng trước giảm giá.
        const paymentDiscountLine = document.getElementById("payment-discount-line"); // Dòng hiển thị số tiền được giảm.
        const paymentDiscountAmount = document.getElementById("payment-discount-amount"); // Số tiền giảm (đã định dạng).
        const paymentDiscountSelect = document.getElementById("payment-discount-select"); // Chọn mã / loại giảm giá.

        // Tính tổng giá trị giỏ (số) trước khi áp dụng giảm giá.
        const getCartSubtotal = () =>
            cart.reduce((sum, item) => {
                const qty = Math.max(1, Number(item.quantity) || 1);
                return sum + parsePrice(item.price) * qty;
            }, 0);

        // Áp dụng mã đã chọn trong select: SAVE10 = 10%, EV500 = trừ tối đa $500 (không vượt subtotal).
        const getDiscountAmount = (code, subtotal) => {
            if (!subtotal || !code) {
                return 0;
            }
            if (code === "SAVE10") {
                return Math.round(subtotal * 0.1 * 100) / 100;
            }
            if (code === "EV500") {
                return Math.min(500, subtotal);
            }
            return 0;
        };

        // Render lại UI giỏ hàng và tính lại tổng tiền mỗi khi số lượng/item thay đổi.
        const renderPaymentCart = () => {
            if (!cart.length) {
                const emptyMessage = document.createElement("p");
                emptyMessage.className = "payment-empty";
                emptyMessage.textContent = "No vehicles selected yet."; // Giỏ trống.
                paymentCartItems.replaceChildren(emptyMessage);
            } else {
                const fragment = document.createDocumentFragment();
                cart.forEach((item, index) => {
                    const qty = Math.max(1, Number(item.quantity) || 1); // Số lượng tối thiểu 1.
                    const unitPrice = parsePrice(item.price); // Giá một chiếc (số).
                    const lineTotal = unitPrice * qty; // Thành tiền dòng.
                    const model = String(item.model || "Model");
                    const article = document.createElement("article");
                    article.className = "payment-cart-item";

                    const image = document.createElement("img");
                    image.src = getSafeCartImage(item.image);
                    image.alt = model;
                    article.appendChild(image);

                    const details = document.createElement("div");
                    const heading = document.createElement("h3");
                    heading.textContent = model;
                    const trim = document.createElement("p");
                    trim.textContent = String(item.trim || "Base");

                    const qtyRow = document.createElement("div");
                    qtyRow.className = "payment-qty-row";
                    const decButton = document.createElement("button");
                    decButton.type = "button";
                    decButton.className = "qty-btn";
                    decButton.dataset.cartIdx = String(index);
                    decButton.dataset.qtyAction = "dec";
                    decButton.textContent = "-";
                    const qtyValue = document.createElement("span");
                    qtyValue.className = "qty-value";
                    qtyValue.textContent = String(qty);
                    const incButton = document.createElement("button");
                    incButton.type = "button";
                    incButton.className = "qty-btn";
                    incButton.dataset.cartIdx = String(index);
                    incButton.dataset.qtyAction = "inc";
                    incButton.textContent = "+";
                    qtyRow.append(decButton, qtyValue, incButton);

                    const unit = document.createElement("small");
                    unit.textContent = `Unit: ${formatPrice(unitPrice)}`;
                    const total = document.createElement("strong");
                    total.textContent = formatPrice(lineTotal);

                    details.append(heading, trim, qtyRow, unit, total);
                    article.appendChild(details);
                    fragment.appendChild(article);
                });
                paymentCartItems.replaceChildren(fragment);
            }

            const subtotal = getCartSubtotal();
            const discountCode = paymentDiscountSelect ? paymentDiscountSelect.value : "";
            const discount = getDiscountAmount(discountCode, subtotal);
            const totalDue = Math.max(0, subtotal - discount);

            if (paymentSubtotal) {
                paymentSubtotal.textContent = formatPrice(subtotal);
            }
            if (paymentDiscountLine && paymentDiscountAmount) {
                if (discount > 0) {
                    paymentDiscountLine.hidden = false;
                    paymentDiscountAmount.textContent = `-${formatPrice(discount)}`;
                } else {
                    paymentDiscountLine.hidden = true;
                    paymentDiscountAmount.textContent = "-$0";
                }
            }

            if (paymentTotal) {
                paymentTotal.textContent = formatPrice(totalDue);
            }
            setCart(cart); // Đồng bộ lại localStorage sau mỗi lần render.
        };

        if (paymentDiscountSelect) {
            paymentDiscountSelect.addEventListener("change", () => renderPaymentCart());
        }

        renderPaymentCart(); // Hiển thị lần đầu khi vào trang payment.

        // Dùng event delegation cho nút +/- vì danh sách item được render lại động.
        paymentCartItems.addEventListener("click", (event) => {
            const target = event.target; // Phần tử DOM thực sự được bấm.
            if (!(target instanceof HTMLElement)) {
                return; // Không phải element (ví dụ text node) thì bỏ qua.
            }
            const button = target.closest(".qty-btn"); // Tìm nút qty gần nhất (có thể bấm vào chữ trong nút).
            if (!button) {
                return; // Click không phải vùng nút số lượng.
            }
            const idx = Number(button.getAttribute("data-cart-idx")); // Chỉ số dòng trong mảng cart.
            const action = button.getAttribute("data-qty-action"); // "inc" hoặc "dec".
            if (!Number.isInteger(idx) || idx < 0 || idx >= cart.length) {
                return; // Chỉ số không hợp lệ.
            }

            const currentQty = Math.max(1, Number(cart[idx].quantity) || 1); // Số lượng hiện tại của dòng.
            if (action === "inc") {
                cart[idx].quantity = currentQty + 1; // Tăng một.
            } else if (action === "dec") {
                if (currentQty <= 1) {
                    cart.splice(idx, 1); // Hết về 0 thì xóa dòng khỏi giỏ.
                } else {
                    cart[idx].quantity = currentQty - 1; // Giảm một.
                }
            }
            renderPaymentCart(); // Vẽ lại sau khi đổi cart.
        });

        const orderForm = document.getElementById("order-form"); // Form đặt hàng cuối trang payment.
        if (orderForm) {
            orderForm.addEventListener("submit", (event) => {
                event.preventDefault(); // Không submit HTTP thật.
                if (!cart.length) {
                    alert("Please add at least one vehicle to cart."); // Bắt buộc có xe trong giỏ.
                    return;
                }
                alert("Order completed"); // Thông báo demo hoàn tất đơn.
                localStorage.removeItem(CART_KEY); // Xóa giỏ sau khi "đặt".
                localStorage.removeItem(LEGACY_KEY); // Dọn luôn key cũ nếu còn.
                window.location.href = "index.html"; // Quay về trang chủ.
            });
        }
    }
});
