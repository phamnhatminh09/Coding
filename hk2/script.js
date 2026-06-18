document.addEventListener("DOMContentLoaded", () => {
    const CART_KEY = "teslaOrderCart";
    const LEGACY_KEY = "teslaOrderSelection";
    const LANGUAGE_KEY = "teslaLanguage";
    const parsePrice = (value) => Number(String(value || "0").replace(/[^0-9.-]+/g, "")) || 0;
    const formatPrice = (num) => `$${Number(num || 0).toLocaleString("en-US")}`;
    const dictionary = {
        Home: { vi: "Trang chủ" },
        Products: { vi: "Sản phẩm" },
        Inventory: { vi: "Kho xe" },
        Contact: { vi: "Liên hệ" },
        Schedule: { vi: "Lịch hẹn" },
        ORDER: { vi: "ĐẶT XE" },
        "Experience the Future of Electric": { vi: "Trải nghiệm tương lai xe điện" },
        "Shop Now": { vi: "Mua ngay" },
        "Book a Test Drive": { vi: "Đặt lịch lái thử" },
        "The Lineup": { vi: "Dòng xe" },
        "Precision Engineered": { vi: "Thiết kế chính xác" },
        "View Details": { vi: "Xem chi tiết" },
        Autopilot: { vi: "Tự lái" },
        "Advanced safety features designed to assist you with driving.": { vi: "Các tính năng an toàn nâng cao hỗ trợ bạn khi lái xe." },
        Battery: { vi: "Pin" },
        "Fast Charge": { vi: "Sạc nhanh" },
        "Recharge up to 200 miles in only 15 minutes.": { vi: "Sạc thêm đến 200 dặm chỉ trong 15 phút." },
        Display: { vi: "Màn hình" },
        "Smart Screen": { vi: "Màn hình thông minh" },
        "A cinematic 17-inch touchscreen gives real-time control.": { vi: "Màn hình cảm ứng 17 inch cho khả năng điều khiển theo thời gian thực." },
        "Rigid Structure": { vi: "Khung vỏ cứng cáp" },
        "Designed from the ground up for maximum protection.": { vi: "Được thiết kế từ đầu để bảo vệ tối đa." },
        "Driving has never been this fun": { vi: "Lái xe chưa bao giờ thú vị đến vậy" },
        "Experience instant torque with a smooth and quiet ride.": { vi: "Trải nghiệm mô-men xoắn tức thì cùng cảm giác lái êm ái và yên tĩnh." },
        "Schedule A Drive": { vi: "Đặt lịch lái thử" },
        "Get In Touch": { vi: "Kết nối với chúng tôi" },
        "Questions about ordering, service, or ownership? Contact us directly.": { vi: "Có câu hỏi về đặt xe, dịch vụ hoặc sở hữu? Liên hệ trực tiếp với chúng tôi." },
        "Contact Tesla": { vi: "Liên hệ Tesla" },
        "Please fill in all required fields.": { vi: "Vui lòng điền đầy đủ các trường bắt buộc." },
        "All Cities": { vi: "Tất cả thành phố" },
        "No vehicles selected yet.": { vi: "Chưa có xe nào được chọn." },
        Unit: { vi: "Đơn giá" },
        "Please add at least one vehicle to cart.": { vi: "Vui lòng thêm ít nhất một xe vào giỏ hàng." },
        "Order completed": { vi: "Đặt hàng thành công" },
        "added to cart.": { vi: "đã được thêm vào giỏ hàng." },
        "Tesla | Home": { vi: "Tesla | Trang chủ" },
        "Tesla | Inventory": { vi: "Tesla | Kho xe" },
        "Tesla | Contact": { vi: "Tesla | Liên hệ" },
        "Tesla | Schedule Test Drive": { vi: "Tesla | Đặt lịch lái thử" },
        "Tesla | Payment": { vi: "Tesla | Thanh toán" },
        "Tesla | Model S": { vi: "Tesla | Model S" },
        "Tesla | Model 3": { vi: "Tesla | Model 3" },
        "Tesla | Model X": { vi: "Tesla | Model X" },
        "Tesla | Model Y": { vi: "Tesla | Model Y" },
        "Tesla | Cybertruck": { vi: "Tesla | Cybertruck" },
        "Tesla | Home Charger": { vi: "Tesla | Bộ sạc tại nhà" },
        "Tesla | Model S Configurator": { vi: "Tesla | Cấu hình Model S" },
        "Tesla | Model 3 Configurator": { vi: "Tesla | Cấu hình Model 3" },
        "Tesla | Model X Configurator": { vi: "Tesla | Cấu hình Model X" },
        "Tesla | Model Y Configurator": { vi: "Tesla | Cấu hình Model Y" },
        "Tesla | Cybertruck Configurator": { vi: "Tesla | Cấu hình Cybertruck" },
        "Schedule a Demo Drive | Tesla": { vi: "Đặt lịch lái thử | Tesla" },
        "Order Summary": { vi: "Tóm tắt đơn hàng" },
        "Selected vehicles": { vi: "Xe đã chọn" },
        "Total Due": { vi: "Tổng thanh toán" },
        "Continue shopping": { vi: "Tiếp tục mua sắm" },
        "Contact Information": { vi: "Thông tin liên hệ" },
        "Place Order": { vi: "Đặt hàng" },
        "First Name": { vi: "Tên" },
        "Last Name": { vi: "Họ" },
        "Email Address": { vi: "Địa chỉ email" },
        "Street Address": { vi: "Địa chỉ đường" },
        City: { vi: "Thành phố" },
        State: { vi: "Tỉnh/Thành" },
        "Card Number": { vi: "Số thẻ" },
        "Inventory Filters": { vi: "Bộ lọc kho xe" },
        Model: { vi: "Mẫu xe" },
        Trim: { vi: "Phiên bản" },
        "Standard Wheels": { vi: "Mâm tiêu chuẩn" },
        "Sport Wheels": { vi: "Mâm thể thao" },
        "Performance Wheels": { vi: "Mâm hiệu năng" },
        "Delivery City": { vi: "Thành phố giao xe" },
        Hanoi: { vi: "Hà Nội" },
        "Da Nang": { vi: "Đà Nẵng" },
        "Ho Chi Minh City": { vi: "TP. Hồ Chí Minh" },
        "Reset All Filters": { vi: "Đặt lại bộ lọc" },
        "New Inventory": { vi: "Kho xe mới" },
        "Available cars for immediate delivery near": { vi: "Các xe có thể giao ngay gần" },
        Vietnam: { vi: "Việt Nam" },
        "Sort by:": { vi: "Sắp xếp theo:" },
        "Price: Low to High": { vi: "Giá: thấp đến cao" },
        "Price: High to Low": { vi: "Giá: cao đến thấp" },
        "Checkout Cart": { vi: "Thanh toán giỏ hàng" },
        "Range (EPA)": { vi: "Tầm hoạt động (EPA)" },
        "Top speed": { vi: "Tốc độ tối đa" },
        Configure: { vi: "Tùy chỉnh" },
        "Add to cart": { vi: "Thêm vào giỏ" },
        "Include Home Charger (+$450)": { vi: "Thêm bộ sạc tại nhà (+$450)" },
        "Load More Vehicles": { vi: "Xem thêm xe" },
        "Select a topic": { vi: "Chọn chủ đề" },
        Service: { vi: "Dịch vụ" },
        "Roadside Assistance": { vi: "Hỗ trợ bên đường" },
        Message: { vi: "Tin nhắn" },
        "Send a Message": { vi: "Gửi tin nhắn" },
        "SUBMIT INQUIRY": { vi: "GỬI YÊU CẦU" },
        "Contact Tesla": { vi: "Liên hệ Tesla" },
        INQUIRY: { vi: "YÊU CẦU" },
        Sales: { vi: "Kinh doanh" },
        "Open 24 hours for online requests": { vi: "Mở cửa 24 giờ cho yêu cầu trực tuyến" },
        "Global roadside support 24/7": { vi: "Hỗ trợ bên đường toàn cầu 24/7" },
        "Inquiry submitted successfully. We will contact you soon.": { vi: "Gửi yêu cầu thành công. Chúng tôi sẽ liên hệ sớm." },
        "Charge at Home": { vi: "Sạc tại nhà" },
        "A convenient at-home charging solution that powers your EV overnight.": { vi: "Giải pháp sạc tại nhà tiện lợi, sạc xe điện qua đêm." },
        "Order now": { vi: "Đặt ngay" },
        "Smart Connectivity": { vi: "Kết nối thông minh" },
        "Versatile Design": { vi: "Thiết kế linh hoạt" },
        "Power Sharing": { vi: "Chia sẻ công suất" },
        "Technical Specifications": { vi: "Thông số kỹ thuật" },
        "Cable Length": { vi: "Chiều dài cáp" },
        "Max Power Output": { vi: "Công suất tối đa" },
        Compatibility: { vi: "Tương thích" },
        "Input Voltage": { vi: "Điện áp đầu vào" },
        "Your Charge, Anywhere.": { vi: "Quản lý sạc ở mọi nơi." },
        "Scheduled Charging": { vi: "Sạc theo lịch" },
        "Peak/Off-Peak Stats": { vi: "Thống kê giờ cao/thấp điểm" },
        "Seamless Installation": { vi: "Lắp đặt liền mạch" },
        "Find an installer": { vi: "Tìm đơn vị lắp đặt" },
        "Checkout now": { vi: "Thanh toán ngay" },
        "1. Select a Model": { vi: "1. Chọn mẫu xe" },
        "2. Select Location": { vi: "2. Chọn địa điểm" },
        "3. Select Time": { vi: "3. Chọn thời gian" },
        "4. Driver's Details": { vi: "4. Thông tin người lái" },
        "Midsize SUV": { vi: "SUV cỡ trung" },
        "Sports Sedan": { vi: "Sedan thể thao" },
        "Electric Pickup": { vi: "Bán tải điện" },
        "Luxury Sedan": { vi: "Sedan cao cấp" },
        "Luxury SUV": { vi: "SUV cao cấp" },
        "Submit Request": { vi: "Gửi yêu cầu" },
        Phone: { vi: "Điện thoại" },
        "Tesla Hanoi": { vi: "Tesla Hà Nội" },
        "Tesla Da Nang": { vi: "Tesla Đà Nẵng" },
        "Tesla HCM": { vi: "Tesla TP.HCM" },
        "Learn More": { vi: "Tìm hiểu thêm" },
        "Configure Now": { vi: "Tùy chỉnh ngay" },
        "Model S Specs": { vi: "Thông số Model S" },
        "Interior of the future": { vi: "Nội thất của tương lai" },
        "Cinematic Experience": { vi: "Trải nghiệm điện ảnh" },
        "Beyond Ludicrous": { vi: "Vượt xa Ludicrous" },
        Control: { vi: "Điều khiển" },
        "Yoke Steering": { vi: "Vô-lăng Yoke" },
        "EXPERIENCE THE FUTURE OF DRIVING": { vi: "TRẢI NGHIỆM TƯƠNG LAI LÁI XE" },
        "Demo Drive": { vi: "Lái thử" },
        Interior: { vi: "Nội thất" },
        "Minimalist Cabin": { vi: "Khoang lái tối giản" },
        Performance: { vi: "Hiệu năng" },
        Safety: { vi: "An toàn" },
        "Built for Safety": { vi: "Thiết kế vì an toàn" },
        Charging: { vi: "Sạc" },
        "Charge Anywhere": { vi: "Sạc ở mọi nơi" },
        Specifications: { vi: "Thông số kỹ thuật" },
        "Experience Model 3": { vi: "Trải nghiệm Model 3" },
        "Order now": { vi: "Đặt ngay" },
        "Schedule demo drive": { vi: "Đặt lịch lái thử" },
        "Engineered for Performance": { vi: "Thiết kế cho hiệu năng" },
        "Compare Model X": { vi: "So sánh Model X" },
        "The Largest Panoramic Windshield": { vi: "Kính chắn gió toàn cảnh lớn nhất" },
        Visibility: { vi: "Tầm nhìn" },
        Capability: { vi: "Khả năng" },
        Access: { vi: "Tiếp cận" },
        Connectivity: { vi: "Kết nối" },
        "Model X Specs": { vi: "Thông số Model X" },
        "DESIGN YOURS TODAY": { vi: "THIẾT KẾ XE CỦA BẠN NGAY HÔM NAY" },
        "Safety first": { vi: "An toàn là trên hết" },
        "Versatile Seating": { vi: "Ghế ngồi linh hoạt" },
        "All-Glass Roof": { vi: "Mái kính toàn phần" },
        "Model Y Specs": { vi: "Thông số Model Y" },
        Battery: { vi: "Pin" },
        Acceleration: { vi: "Tăng tốc" },
        Range: { vi: "Tầm hoạt động" },
        Drive: { vi: "Hệ dẫn động" },
        Seating: { vi: "Số chỗ" },
        Wheels: { vi: "Bánh xe" },
        Weight: { vi: "Khối lượng" },
        Cargo: { vi: "Khoang chứa đồ" },
        "Top Speed": { vi: "Tốc độ tối đa" },
        "Long Range": { vi: "Tầm xa" },
        "Up to 7 adults": { vi: "Tối đa 7 người lớn" },
        "Experience Model Y": { vi: "Trải nghiệm Model Y" },
        "SCHEDULE DEMO DRIVE": { vi: "ĐẶT LỊCH LÁI THỬ" },
        "ORDER NOW": { vi: "ĐẶT NGAY" },
        "Built for durability": { vi: "Được tạo ra để bền bỉ" },
        Exoskeleton: { vi: "Khung vỏ ngoài" },
        "Armor Glass": { vi: "Kính giáp" },
        "Ultra-strong": { vi: "Siêu bền" },
        "UTILITY REDEFINED": { vi: "TIỆN ÍCH ĐƯỢC ĐỊNH NGHĨA LẠI" },
        "Adaptive Air Suspension": { vi: "Hệ thống treo khí thích ứng" },
        "Versatile Power": { vi: "Nguồn điện linh hoạt" },
        Storage: { vi: "Lưu trữ" },
        "Hidden Gear": { vi: "Khoang đồ ẩn" },
        "PERFORMANCE SPECS": { vi: "THÔNG SỐ HIỆU NĂNG" }
    };
    const currentLanguage = {
        value: localStorage.getItem(LANGUAGE_KEY) === "vi" ? "vi" : "en"
    };
    const originalTitle = document.title;
    const getTranslation = (text, lang) => {
        const normalized = String(text || "").trim();
        if (!normalized || !dictionary[normalized]) {
            return text;
        }
        if (lang === "vi") {
            return dictionary[normalized].vi || normalized;
        }
        return normalized;
    };
    const translateDocument = (lang) => {
        document.querySelectorAll("*").forEach((el) => {
            if (!(el instanceof HTMLElement)) {
                return;
            }
            const tag = el.tagName.toLowerCase();
            if (tag === "script" || tag === "style" || tag === "noscript") {
                return;
            }
            if (el.hasAttribute("data-i18n-ignore")) {
                return;
            }
            const hasElementChild = Array.from(el.childNodes).some((n) => n.nodeType === Node.ELEMENT_NODE);
            if (hasElementChild) {
                return;
            }
            const textNode = Array.from(el.childNodes).find((n) => n.nodeType === Node.TEXT_NODE);
            if (!textNode) {
                return;
            }
            const currentText = (textNode.nodeValue || "").trim();
            if (!currentText) {
                return;
            }
            const original = el.getAttribute("data-i18n-original") || currentText;
            if (!el.hasAttribute("data-i18n-original")) {
                el.setAttribute("data-i18n-original", original);
            }
            const nextText = lang === "vi" ? getTranslation(original, "vi") : original;
            el.textContent = nextText;
        });
        document.querySelectorAll("input[placeholder], textarea[placeholder]").forEach((field) => {
            const placeholder = field.getAttribute("placeholder") || "";
            const original = field.getAttribute("data-i18n-placeholder") || placeholder;
            if (!field.hasAttribute("data-i18n-placeholder")) {
                field.setAttribute("data-i18n-placeholder", original);
            }
            const translated = lang === "vi" ? getTranslation(original, "vi") : original;
            field.setAttribute("placeholder", translated);
        });
        document.title = lang === "vi" ? getTranslation(originalTitle, "vi") : originalTitle;
        document.documentElement.lang = lang;
    };
    const applyLanguage = (lang) => {
        currentLanguage.value = lang === "vi" ? "vi" : "en";
        localStorage.setItem(LANGUAGE_KEY, currentLanguage.value);
        translateDocument(currentLanguage.value);
    };
    const injectLanguageToggle = () => {
        const header = document.querySelector("header");
        if (!header) {
            return;
        }
        const target = header.querySelector(".nav-right") || header;
        if (target.querySelector(".lang-toggle-btn")) {
            return;
        }
        const button = document.createElement("button");
        button.type = "button";
        button.className = "lang-toggle-btn";
        const refreshLabel = () => {
            button.textContent = currentLanguage.value === "vi" ? "EN" : "VI";
            button.title = currentLanguage.value === "vi" ? "Switch to English" : "Chuyển sang tiếng Việt";
        };
        refreshLabel();
        button.addEventListener("click", () => {
            const nextLanguage = currentLanguage.value === "vi" ? "en" : "vi";
            applyLanguage(nextLanguage);
            refreshLabel();
        });
        target.prepend(button);
    };
    const getCart = () => {
        try {
            const parsed = JSON.parse(localStorage.getItem(CART_KEY) || "[]");
            return Array.isArray(parsed) ? parsed : [];
        } catch (error) {
            return [];
        }
    };
    const setCart = (items) => {
        localStorage.setItem(CART_KEY, JSON.stringify(items));
    };
    const getSafeCartImage = (image) => {
        const candidate = String(image || "").trim();
        return /^[A-Za-z0-9_-]+\.(?:avif|jpe?g|png|webp)$/i.test(candidate) ? candidate : "mod3.png";
    };
    injectLanguageToggle();
    applyLanguage(currentLanguage.value);
    const header = document.querySelector("header");
    if (header) {
        window.addEventListener("scroll", () => {
            if (window.scrollY > 50) {
                header.style.background = "#0b0b0b";
                header.style.boxShadow = "0 2px 10px rgba(0,0,0,0.5)";
            } else {
                header.style.background = "rgba(8, 8, 8, 0.97)";
                header.style.boxShadow = "none";
            }
        });
    }

    const specToggle = document.querySelector(".model-y-specs-head .spec-toggle");
    if (specToggle) {
        const buttons = specToggle.querySelectorAll("button[data-variant]");
        const panels = document.querySelectorAll(".model-y-specs-panel[data-variant]");
        buttons.forEach((btn) => {
            btn.addEventListener("click", () => {
                const variant = btn.getAttribute("data-variant");
                buttons.forEach((b) => b.classList.toggle("active", b === btn));
                panels.forEach((panel) => {
                    panel.hidden = panel.getAttribute("data-variant") !== variant;
                });
            });
        });
    }

    const slides = document.querySelectorAll(".slide");
    if (slides.length > 1) {
        let index = 0;
        setInterval(() => {
            slides[index].classList.remove("active");
            index = (index + 1) % slides.length;
            slides[index].classList.add("active");
        }, 4000);
    }

    const contactForm = document.getElementById("contact-form");
    if (contactForm) {
        const successMessage = document.getElementById("contact-success");
        contactForm.addEventListener("submit", (event) => {
            event.preventDefault();
            const requiredFields = contactForm.querySelectorAll("[required]");
            let valid = true;

            requiredFields.forEach((field) => {
                if (!field.value.trim()) {
                    valid = false;
                }
            });

            if (!valid) {
                alert(getTranslation("Please fill in all required fields.", currentLanguage.value));
                return;
            }

            if (successMessage) {
                successMessage.style.display = "block";
            }
            contactForm.reset();
        });
    }

    const inventoryButtons = document.querySelectorAll("[data-order-model]");
    if (inventoryButtons.length) {
        inventoryButtons.forEach((button) => {
            button.addEventListener("click", () => {
                const payload = {
                    model: button.getAttribute("data-order-model") || "Model 3",
                    trim: button.getAttribute("data-order-trim") || "Base",
                    price: button.getAttribute("data-order-price") || "$38,990",
                    image: button.getAttribute("data-order-image") || "mod3.png",
                    quantity: 1
                };
                const parentScope = button.closest(".inventory-card, .order-config-panel");
                const homeChargerCheckbox = parentScope ? parentScope.querySelector("[data-home-charger]") : null;
                if (homeChargerCheckbox && homeChargerCheckbox.checked) {
                    const upgradedPrice = parsePrice(payload.price) + 450;
                    payload.price = formatPrice(upgradedPrice);
                    payload.trim = `${payload.trim} + Home Charger`;
                }
                const action = button.getAttribute("data-order-action") || "checkout";
                const cart = getCart();
                const existing = cart.find((item) =>
                    item.model === payload.model &&
                    item.trim === payload.trim &&
                    item.price === payload.price &&
                    item.image === payload.image
                );
                if (existing) {
                    existing.quantity = (Number(existing.quantity) || 1) + 1;
                } else {
                    cart.push(payload);
                }
                setCart(cart);
                if (action === "add") {
                    alert(`${payload.model} ${getTranslation("added to cart.", currentLanguage.value)}`);
                    return;
                }
                window.location.href = "payment.html";
            });
        });
    }

    const inventoryGrid = document.querySelector(".inventory-grid");
    if (inventoryGrid) {
        const modelFilters = document.querySelectorAll(".inventory-model-filter");
        const trimFilters = document.querySelectorAll(".filter-pill[data-trim]");
        const cityFilters = document.querySelectorAll(".city-pill[data-city]");
        const cityLabel = document.getElementById("inventory-city-label");
        const sortSelect = document.getElementById("inventory-sort");
        const resetButton = document.getElementById("inventory-reset");
        const loadMoreButton = document.getElementById("inventory-load-more");
        let hasFilterInteraction = false;
        const pageSize = 6;
        let visibleCount = pageSize;

        const applyInventoryState = () => {
            const activeModels = Array.from(modelFilters)
                .filter((filter) => filter.checked)
                .map((filter) => filter.value);
            const activeTrimButton = Array.from(trimFilters).find((btn) => btn.classList.contains("active"));
            const activeTrim = activeTrimButton ? activeTrimButton.getAttribute("data-trim") : "";
            const activeCityButton = Array.from(cityFilters).find((btn) => btn.classList.contains("active"));
            const activeCity = activeCityButton ? activeCityButton.getAttribute("data-city") : "";
            if (cityLabel && activeCity) {
                cityLabel.textContent = activeCity;
            } else if (cityLabel) {
                cityLabel.textContent = getTranslation("All Cities", currentLanguage.value);
            }
            const cards = Array.from(inventoryGrid.querySelectorAll(".inventory-card"));

            cards.forEach((card) => {
                if (!hasFilterInteraction || (!activeModels.length && !activeTrim)) {
                    const cardCity = card.getAttribute("data-city") || "";
                    card.style.display = !activeCity || cardCity === activeCity ? "" : "none";
                    return;
                }
                const model = card.getAttribute("data-model") || "";
                const trim = card.getAttribute("data-trim") || "";
                const cardCity = card.getAttribute("data-city") || "";
                const modelMatch = !activeModels.length || activeModels.includes(model);
                const trimMatch = !activeTrim || trim === activeTrim;
                const cityMatch = !activeCity || cardCity === activeCity;
                card.style.display = modelMatch && trimMatch && cityMatch ? "" : "none";
            });

            const sortedVisible = cards
                .filter((card) => card.style.display !== "none")
                .sort((a, b) => {
                    const priceA = Number(a.getAttribute("data-price")) || 0;
                    const priceB = Number(b.getAttribute("data-price")) || 0;
                    if (sortSelect && sortSelect.value === "price-desc") {
                        return priceB - priceA;
                    }
                    return priceA - priceB;
                });

            sortedVisible.forEach((card) => inventoryGrid.appendChild(card));

            sortedVisible.forEach((card, index) => {
                card.style.display = index < visibleCount ? "" : "none";
            });

            if (loadMoreButton) {
                loadMoreButton.style.display = sortedVisible.length > visibleCount ? "" : "none";
            }
        };

        modelFilters.forEach((filter) => {
            filter.addEventListener("change", () => {
                hasFilterInteraction = true;
                visibleCount = pageSize;
                applyInventoryState();
            });
        });
        if (sortSelect) {
            sortSelect.addEventListener("change", () => {
                visibleCount = pageSize;
                applyInventoryState();
            });
        }
        trimFilters.forEach((button) => {
            button.addEventListener("click", () => {
                hasFilterInteraction = true;
                const wasActive = button.classList.contains("active");
                trimFilters.forEach((btn) => btn.classList.remove("active"));
                if (!wasActive) {
                    button.classList.add("active");
                }
                visibleCount = pageSize;
                applyInventoryState();
            });
        });
        cityFilters.forEach((button) => {
            button.addEventListener("click", () => {
                hasFilterInteraction = true;
                cityFilters.forEach((btn) => btn.classList.toggle("active", btn === button));
                visibleCount = pageSize;
                applyInventoryState();
            });
        });
        if (resetButton) {
            resetButton.addEventListener("click", () => {
                modelFilters.forEach((filter) => {
                    filter.checked = false;
                });
                trimFilters.forEach((btn) => btn.classList.remove("active"));
                const defaultCity = cityFilters[0];
                cityFilters.forEach((btn) => btn.classList.toggle("active", btn === defaultCity));
                visibleCount = pageSize;
                applyInventoryState();
            });
        }
        if (loadMoreButton) {
            loadMoreButton.addEventListener("click", () => {
                visibleCount += pageSize;
                applyInventoryState();
            });
        }
        applyInventoryState();
    }

    const paintChips = document.querySelectorAll(".config-chip");
    if (paintChips.length) {
        const getPaintFilter = (paintName) => {
            const paint = (paintName || "").toLowerCase();
            const filterMap = {
                white: "brightness(1.08) saturate(0.85)",
                "satin-white": "brightness(1.08) saturate(0.9)",
                black: "brightness(0.58) saturate(0.7)",
                "satin-black": "brightness(0.52) saturate(0.65)",
                blue: "hue-rotate(160deg) saturate(1.35) brightness(0.92)",
                red: "hue-rotate(0deg) saturate(1.25) brightness(0.98)",
                silver: "saturate(0.45) brightness(1.02)",
                grey: "saturate(0.4) brightness(0.95)",
                stainless: "saturate(0.25) brightness(1.02) contrast(1.05)"
            };
            return filterMap[paint] || "none";
        };

        const applySelectedPaint = (chipRow) => {
            if (!chipRow) {
                return;
            }
            const activeChip = chipRow.querySelector(".config-chip.active");
            const paint = activeChip ? activeChip.getAttribute("data-paint") : "";
            const layout = chipRow.closest(".order-config-layout");
            const visualImage = layout ? layout.querySelector(".order-config-visual img") : null;
        };

        paintChips.forEach((chip) => {
            chip.addEventListener("click", () => {
                const chipRow = chip.closest(".config-chip-row");
                if (!chipRow) {
                    return;
                }
                const siblings = chipRow.querySelectorAll(".config-chip");
                siblings.forEach((item) => item.classList.toggle("active", item === chip));
                applySelectedPaint(chipRow);
            });
        });

        document.querySelectorAll(".config-chip-row").forEach((chipRow) => {
            applySelectedPaint(chipRow);
        });
    }

    const wheelTiles = document.querySelectorAll(".config-tiles .config-tile");
    if (wheelTiles.length) {
        wheelTiles.forEach((tile) => {
            tile.addEventListener("click", () => {
                const group = tile.closest(".config-tiles");
                if (!group) {
                    return;
                }
                const siblings = group.querySelectorAll(".config-tile");
                siblings.forEach((item) => item.classList.toggle("active", item === tile));
            });
        });
    }

    const paymentCartItems = document.getElementById("payment-cart-items");
    if (paymentCartItems) {
        let cart = getCart();
        if (!cart.length) {
            const storedSelection = localStorage.getItem(LEGACY_KEY);
            if (storedSelection) {
                try {
                    const legacy = JSON.parse(storedSelection);
                    cart = [{ ...legacy, quantity: Number(legacy.quantity) || 1 }];
                    setCart(cart);
                    localStorage.removeItem(LEGACY_KEY);
                } catch (error) {
                    localStorage.removeItem(LEGACY_KEY);
                }
            }
        }

        const paymentTotal = document.getElementById("payment-total");
        const paymentSubtotal = document.getElementById("payment-subtotal");
        const paymentDiscountLine = document.getElementById("payment-discount-line");
        const paymentDiscountAmount = document.getElementById("payment-discount-amount");
        const paymentDiscountSelect = document.getElementById("payment-discount-select");

        const getCartSubtotal = () =>
            cart.reduce((sum, item) => {
                const qty = Math.max(1, Number(item.quantity) || 1);
                return sum + parsePrice(item.price) * qty;
            }, 0);

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

        const renderPaymentCart = () => {
            if (!cart.length) {
                const emptyMessage = document.createElement("p");
                emptyMessage.className = "payment-empty";
                emptyMessage.textContent = getTranslation("No vehicles selected yet.", currentLanguage.value);
                paymentCartItems.replaceChildren(emptyMessage);
            } else {
                const fragment = document.createDocumentFragment();
                cart.forEach((item, index) => {
                    const qty = Math.max(1, Number(item.quantity) || 1);
                    const unitPrice = parsePrice(item.price);
                    const lineTotal = unitPrice * qty;
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
                    unit.textContent = `${getTranslation("Unit", currentLanguage.value)}: ${formatPrice(unitPrice)}`;
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
            setCart(cart);
        };

        if (paymentDiscountSelect) {
            paymentDiscountSelect.addEventListener("change", () => renderPaymentCart());
        }

        renderPaymentCart();

        paymentCartItems.addEventListener("click", (event) => {
            const target = event.target;
            if (!(target instanceof HTMLElement)) {
                return;
            }
            const button = target.closest(".qty-btn");
            if (!button) {
                return;
            }
            const idx = Number(button.getAttribute("data-cart-idx"));
            const action = button.getAttribute("data-qty-action");
            if (!Number.isInteger(idx) || idx < 0 || idx >= cart.length) {
                return;
            }

            const currentQty = Math.max(1, Number(cart[idx].quantity) || 1);
            if (action === "inc") {
                cart[idx].quantity = currentQty + 1;
            } else if (action === "dec") {
                if (currentQty <= 1) {
                    cart.splice(idx, 1);
                } else {
                    cart[idx].quantity = currentQty - 1;
                }
            }
            renderPaymentCart();
        });

        const orderForm = document.getElementById("order-form");
        if (orderForm) {
            orderForm.addEventListener("submit", (event) => {
                event.preventDefault();
                if (!cart.length) {
                    alert(getTranslation("Please add at least one vehicle to cart.", currentLanguage.value));
                    return;
                }
                alert(getTranslation("Order completed", currentLanguage.value));
                localStorage.removeItem(CART_KEY);
                localStorage.removeItem(LEGACY_KEY);
                window.location.href = "index.html";
            });
        }
    }
});
