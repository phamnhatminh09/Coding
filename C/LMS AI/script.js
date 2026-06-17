/* =============================================
   OES LMS AI — Main JavaScript
   ============================================= */

(function () {
  'use strict';

  /* ===== HEADER SCROLL ===== */
  const header = document.getElementById('header');
  const handleHeaderScroll = () => {
    if (!header) return;
    if (window.scrollY > 60) {
      header.classList.add('scrolled');
    } else {
      header.classList.remove('scrolled');
    }
  };
  window.addEventListener('scroll', handleHeaderScroll, { passive: true });

  /* ===== MOBILE MENU ===== */
  const navToggle = document.getElementById('nav-toggle');
  const navMenu = document.getElementById('nav-menu');
  let menuOverlay;

  if (navToggle && navMenu) {
    // Create overlay
    menuOverlay = document.createElement('div');
    menuOverlay.style.cssText = `
      position: fixed; inset: 0; background: rgba(0,0,0,0.5);
      z-index: 99; display: none; backdrop-filter: blur(4px);
    `;
    document.body.appendChild(menuOverlay);

    const toggleMenu = () => {
      navMenu.classList.toggle('open');
      const isOpen = navMenu.classList.contains('open');
      menuOverlay.style.display = isOpen ? 'block' : 'none';
      navToggle.innerHTML = isOpen
        ? "<i class='bx bx-x'></i>"
        : "<i class='bx bx-menu'></i>";
      document.body.style.overflow = isOpen ? 'hidden' : '';
    };

    navToggle.addEventListener('click', toggleMenu);
    menuOverlay.addEventListener('click', toggleMenu);

    // Close on nav link click
    navMenu.querySelectorAll('.nav__link').forEach(link => {
      link.addEventListener('click', () => {
        if (navMenu.classList.contains('open')) toggleMenu();
      });
    });
  }

  /* ===== PARTICLES ===== */
  const particlesContainer = document.getElementById('particles');
  if (particlesContainer) {
    const count = 20;
    for (let i = 0; i < count; i++) {
      const p = document.createElement('div');
      const size = Math.random() * 60 + 10;
      p.classList.add('hero__particle');
      p.style.cssText = `
        width: ${size}px;
        height: ${size}px;
        left: ${Math.random() * 100}%;
        top: ${Math.random() * 100}%;
        animation-duration: ${Math.random() * 20 + 15}s;
        animation-delay: ${Math.random() * -20}s;
        opacity: ${Math.random() * 0.06 + 0.02};
        filter: blur(${Math.random() * 2}px);
      `;
      particlesContainer.appendChild(p);
    }
  }

  /* ===== ANIMATED COUNTER ===== */
  const animateCounter = (el, target, duration = 2000) => {
    const start = performance.now();
    const isLarge = target >= 10000;
    const easeOut = t => 1 - Math.pow(1 - t, 3);

    const step = (timestamp) => {
      const progress = Math.min((timestamp - start) / duration, 1);
      const value = Math.floor(easeOut(progress) * target);
      if (isLarge) {
        el.textContent = (value >= 1000)
          ? (value / 1000).toFixed(0) + ',000'
          : value.toLocaleString();
      } else {
        el.textContent = value.toLocaleString();
      }
      if (progress < 1) requestAnimationFrame(step);
      else el.textContent = isLarge
        ? target.toLocaleString().replace(/\B(?=(\d{3})+(?!\d))/g, ',')
        : target;
    };
    requestAnimationFrame(step);
  };

  /* ===== INTERSECTION OBSERVER ===== */
  const observers = [];

  // Reveal animations
  const revealObserver = new IntersectionObserver((entries) => {
    entries.forEach(entry => {
      if (entry.isIntersecting) {
        entry.target.classList.add('visible');
        revealObserver.unobserve(entry.target);
      }
    });
  }, { threshold: 0.1, rootMargin: '0px 0px -50px 0px' });

  document.querySelectorAll('.reveal, .reveal-left, .reveal-right').forEach(el => {
    revealObserver.observe(el);
  });
  observers.push(revealObserver);

  // Counter observer
  let countersStarted = false;
  const counterObserver = new IntersectionObserver((entries) => {
    entries.forEach(entry => {
      if (entry.isIntersecting && !countersStarted) {
        countersStarted = true;
        document.querySelectorAll('.hero__stat-number').forEach(el => {
          const target = parseInt(el.dataset.target, 10);
          animateCounter(el, target);
        });
        counterObserver.disconnect();
      }
    });
  }, { threshold: 0.5 });

  const heroStats = document.querySelector('.hero__stats');
  if (heroStats) counterObserver.observe(heroStats);
  observers.push(counterObserver);

  // Add reveal classes to sections dynamically
  const addRevealToChildren = (selector, childClass, animClass) => {
    const parent = document.querySelector(selector);
    if (!parent) return;
    const children = parent.querySelectorAll(childClass);
    children.forEach((child, i) => {
      child.classList.add(animClass);
      child.style.transitionDelay = `${i * 0.1}s`;
      revealObserver.observe(child);
    });
  };

  addRevealToChildren('.benefits__grid', '.benefits__card', 'reveal');
  addRevealToChildren('.features__ai-grid', '.features__ai-card', 'reveal');
  addRevealToChildren('.contact__features', '.contact__feature', 'reveal');
  addRevealToChildren('.clients__industries', '.clients__industry-tag', 'reveal');

  document.querySelectorAll('.section__header').forEach(el => {
    el.classList.add('reveal');
    revealObserver.observe(el);
  });

  document.querySelectorAll('.intro__feature-card').forEach((el, i) => {
    el.classList.add('reveal-right');
    el.style.transitionDelay = `${i * 0.1}s`;
    revealObserver.observe(el);
  });

  /* ===== FEATURE TABS ===== */
  const tabs = document.querySelectorAll('.features__tab');
  const panels = document.querySelectorAll('.features__panel');

  tabs.forEach(tab => {
    tab.addEventListener('click', () => {
      const targetId = tab.dataset.tab;

      tabs.forEach(t => t.classList.remove('active'));
      panels.forEach(p => p.classList.remove('active'));

      tab.classList.add('active');
      const targetPanel = document.getElementById(`panel-${targetId}`);
      if (targetPanel) targetPanel.classList.add('active');

      // Reset to first feature item in the activated panel
      const firstItem = targetPanel?.querySelector('.features__item');
      if (firstItem) {
        targetPanel.querySelectorAll('.features__item').forEach(i => i.classList.remove('active'));
        targetPanel.querySelectorAll('.features__detail-panel').forEach(p => p.classList.remove('active'));
        firstItem.classList.add('active');
        const featureIdx = firstItem.dataset.feature;
        const panelId = `detail-${targetId}-${featureIdx}`;
        const detailPanel = document.getElementById(panelId);
        if (detailPanel) detailPanel.classList.add('active');
      }
    });
  });

  /* ===== FEATURE ITEMS ===== */
  document.querySelectorAll('.features__panel').forEach(panel => {
    const tabId = panel.id.replace('panel-', '');
    const items = panel.querySelectorAll('.features__item');

    items.forEach(item => {
      item.addEventListener('click', () => {
        items.forEach(i => i.classList.remove('active'));
        item.classList.add('active');

        const featureIdx = item.dataset.feature;
        const allPanels = panel.querySelectorAll('.features__detail-panel');
        allPanels.forEach(p => p.classList.remove('active'));

        const targetDetailPanel = document.getElementById(`detail-${tabId}-${featureIdx}`);
        if (targetDetailPanel) targetDetailPanel.classList.add('active');
      });
    });
  });

  /* ===== VIDEO SECTION ===== */
  const chapters = document.querySelectorAll('.video-section__chapter');
  chapters.forEach(chapter => {
    chapter.addEventListener('click', () => {
      chapters.forEach(c => c.classList.remove('active'));
      chapter.classList.add('active');
    });
  });

  const playBtn = document.getElementById('video-play-btn');
  if (playBtn) {
    playBtn.addEventListener('click', () => {
      // Simulate video start
      const overlay = playBtn.closest('.video-section__thumbnail').querySelector('.video-section__overlay');
      playBtn.innerHTML = "<i class='bx bx-pause'></i>";
      if (overlay) {
        overlay.style.opacity = '0.3';
      }
      // Add playing animation to play button
      playBtn.style.transform = 'translate(-50%, -50%) scale(0.9)';
      setTimeout(() => {
        playBtn.style.transform = 'translate(-50%, -50%) scale(1)';
      }, 200);
    });
  }

  /* ===== SHOWCASE THUMBNAILS ===== */
  const thumbnails = document.querySelectorAll('.showcase__thumbnail');
  const showcaseUrl = document.querySelector('.showcase__url-bar span');
  const showcaseWelcome = document.querySelector('.showcase__welcome');
  const showcaseSidenavItems = document.querySelectorAll('.showcase__sidenav-item');
  const showcaseViews = [
    { url: 'welearning.oes.vn/dashboard', welcome: 'Xin chào, Minh Anh! 👋 Hôm nay là 11/06/2026', sidenav: 0 },
    { url: 'welearning.oes.vn/analytics', welcome: 'Báo cáo học tập — Tháng 6/2026', sidenav: 4 },
    { url: 'welearning.oes.vn/gau-ai', welcome: 'G@U AI — Trợ lý học tập thông minh', sidenav: 5 },
    { url: 'welearning.oes.vn/exam', welcome: 'Bài thi trực tuyến — Quản lý chất lượng', sidenav: 3 },
  ];

  thumbnails.forEach((thumb, index) => {
    thumb.addEventListener('click', () => {
      thumbnails.forEach(t => t.classList.remove('active'));
      thumb.classList.add('active');

      const view = showcaseViews[index];
      if (!view) return;

      if (showcaseUrl) showcaseUrl.textContent = view.url;
      if (showcaseWelcome) showcaseWelcome.textContent = view.welcome;
      showcaseSidenavItems.forEach((item, i) => {
        item.classList.toggle('active', i === view.sidenav);
      });
    });
  });

  /* ===== CONTACT FORM ===== */
  const form = document.getElementById('contact-form');
  if (form) {
    form.addEventListener('submit', (e) => {
      e.preventDefault();

      const btn = document.getElementById('submit-form-btn');
      btn.disabled = true;
      btn.innerHTML = "<i class='bx bx-loader-alt bx-spin'></i> Đang gửi...";

      // Simulate form submission
      setTimeout(() => {
        const formCard = document.querySelector('.contact__form-card');
        formCard.innerHTML = `
          <div class="form__success">
            <div class="form__success-icon">
              <i class='bx bx-check'></i>
            </div>
            <h3 style="color: var(--title-color); margin-bottom: 8px;">Đăng ký thành công!</h3>
            <p style="color: var(--text-color-light); font-size: 0.875rem; margin-bottom: 24px;">
              Cảm ơn bạn đã quan tâm đến OES WeLearning AI.<br>
              Chuyên gia của chúng tôi sẽ liên hệ với bạn trong vòng 24 giờ.
            </p>
            <div style="
              display: flex; align-items: center; justify-content: center; gap: 8px;
              background: rgba(0,146,108,0.08); border: 1px solid rgba(0,146,108,0.2);
              border-radius: 12px; padding: 16px 24px;
              font-size: 0.875rem; color: var(--first-color); font-weight: 600;
            ">
              <i class='bx bx-phone'></i>
              Hotline hỗ trợ: 1800 xxxx (Miễn phí)
            </div>
          </div>
        `;
      }, 1800);
    });
  }

  /* ===== SMOOTH ACTIVE NAV LINK ===== */
  const sections = document.querySelectorAll('section[id]');
  const navLinks = document.querySelectorAll('.nav__link:not(.nav__link--cta)');

  const activeLinkObserver = new IntersectionObserver((entries) => {
    entries.forEach(entry => {
      if (entry.isIntersecting) {
        const id = entry.target.id;
        navLinks.forEach(link => {
          link.classList.remove('active-link');
          if (link.getAttribute('href') === `#${id}`) {
            link.classList.add('active-link');
          }
        });
      }
    });
  }, { rootMargin: '-40% 0px -40% 0px' });

  sections.forEach(section => activeLinkObserver.observe(section));
  observers.push(activeLinkObserver);

  /* ===== BACK TO TOP ===== */
  const backToTop = document.getElementById('back-to-top');
  if (backToTop) {
    window.addEventListener('scroll', () => {
      if (window.scrollY > 400) {
        backToTop.classList.add('visible');
      } else {
        backToTop.classList.remove('visible');
      }
    }, { passive: true });

    backToTop.addEventListener('click', () => {
      window.scrollTo({ top: 0, behavior: 'smooth' });
    });
  }

  /* ===== PROGRESS BARS ANIMATION ===== */
  const progressObserver = new IntersectionObserver((entries) => {
    entries.forEach(entry => {
      if (entry.isIntersecting) {
        const bars = entry.target.querySelectorAll('.dash__progress-fill, .showcase__course-progress-bar > div');
        bars.forEach(bar => {
          const targetWidth = bar.style.width;
          bar.style.width = '0%';
          setTimeout(() => {
            bar.style.transition = 'width 1.2s cubic-bezier(0.4, 0, 0.2, 1)';
            bar.style.width = targetWidth;
          }, 200);
        });
        progressObserver.unobserve(entry.target);
      }
    });
  }, { threshold: 0.3 });

  document.querySelectorAll('.intro__mockup, .showcase__main-screen').forEach(el => {
    progressObserver.observe(el);
  });
  observers.push(progressObserver);

  /* ===== HOVER TILT EFFECT ON CARDS ===== */
  document.querySelectorAll('.benefits__card').forEach(card => {
    card.addEventListener('mousemove', (e) => {
      const rect = card.getBoundingClientRect();
      const x = (e.clientX - rect.left) / rect.width - 0.5;
      const y = (e.clientY - rect.top) / rect.height - 0.5;
      card.style.transform = `translateY(-6px) rotateX(${-y * 6}deg) rotateY(${x * 6}deg)`;
    });

    card.addEventListener('mouseleave', () => {
      card.style.transform = '';
      card.style.transition = 'transform 0.5s ease';
    });
  });

  /* ===== TYPING ANIMATION ON HERO ===== */
  // subtle pulse effect on hero badge
  const heroBadge = document.querySelector('.hero__badge');
  if (heroBadge) {
    setInterval(() => {
      heroBadge.style.boxShadow = '0 0 0 6px rgba(147,190,94,0.1)';
      setTimeout(() => {
        heroBadge.style.boxShadow = '';
      }, 600);
    }, 3000);
  }

  /* ===== WHY ITEMS STAGGER ===== */
  const whyItemObserver = new IntersectionObserver((entries) => {
    entries.forEach(entry => {
      if (entry.isIntersecting) {
        const items = entry.target.querySelectorAll('.why__item');
        items.forEach((item, i) => {
          setTimeout(() => {
            item.style.opacity = '1';
            item.style.transform = 'translateX(0)';
          }, i * 80);
        });
        whyItemObserver.unobserve(entry.target);
      }
    });
  }, { threshold: 0.1 });

  document.querySelectorAll('.why__column').forEach(col => {
    const items = col.querySelectorAll('.why__item');
    items.forEach(item => {
      item.style.opacity = '0';
      item.style.transform = col.classList.contains('why__column--old')
        ? 'translateX(-20px)'
        : 'translateX(20px)';
      item.style.transition = 'opacity 0.4s ease, transform 0.4s ease';
    });
    whyItemObserver.observe(col);
  });
  observers.push(whyItemObserver);

  /* ===== INTRO FEATURE CARDS STAGGER ===== */
  const introObserver = new IntersectionObserver((entries) => {
    entries.forEach(entry => {
      if (entry.isIntersecting) {
        const cards = entry.target.querySelectorAll('.intro__feature-card');
        cards.forEach((card, i) => {
          setTimeout(() => {
            card.style.opacity = '1';
            card.style.transform = 'translateX(0)';
          }, i * 100);
        });
        introObserver.unobserve(entry.target);
      }
    });
  }, { threshold: 0.1 });

  const introInfo = document.querySelector('.intro__info');
  if (introInfo) {
    const cards = introInfo.querySelectorAll('.intro__feature-card');
    cards.forEach(card => {
      card.style.opacity = '0';
      card.style.transform = 'translateX(30px)';
      card.style.transition = 'opacity 0.5s ease, transform 0.5s ease';
    });
    introObserver.observe(introInfo);
  }
  observers.push(introObserver);

  /* ===== NUMBER FORMAT HELPER ===== */
  function formatNumber(num) {
    if (num >= 100000) return (num / 1000).toFixed(0) + ',000';
    return num.toLocaleString('vi-VN');
  }

  /* ===== INIT ===== */
  // Force initial hero counter if already in view
  const firstStatEl = document.querySelector('.hero__stat-number');
  if (firstStatEl) {
    const rect = heroStats?.getBoundingClientRect();
    if (rect && rect.top < window.innerHeight) {
      countersStarted = true;
      document.querySelectorAll('.hero__stat-number').forEach(el => {
        animateCounter(el, parseInt(el.dataset.target, 10));
      });
    }
  }

  console.log('%c OES WeLearning AI ', 'background: #00926c; color: #fff; padding: 4px 12px; border-radius: 4px; font-weight: bold;');
  console.log('%c Design System 2.0 — Powered by OES Marketing\'s Media Lab ', 'color: #93be5e;');

})();
