document.addEventListener('DOMContentLoaded', () => {
  const header = document.getElementById('header');
  const navToggle = document.getElementById('nav-toggle');
  const navMenu = document.getElementById('nav-menu');
  const demoModal = document.getElementById('demo-modal');
  const modalClose = document.getElementById('modal-close');

  window.addEventListener('scroll', () => {
    header?.classList.toggle('is-scrolled', window.scrollY > 20);
  });

  navToggle?.addEventListener('click', () => {
    if (!navMenu) return;
    navMenu.classList.toggle('is-open');
    const icon = navToggle.querySelector('i');
    icon.className = navMenu.classList.contains('is-open') ? 'bx bx-x' : 'bx bx-menu';
  });

  navMenu?.querySelectorAll('a').forEach((link) => {
    link.addEventListener('click', () => {
      navMenu.classList.remove('is-open');
      navToggle.querySelector('i').className = 'bx bx-menu';
    });
  });

  const sections = document.querySelectorAll('section[id]');
  const navLinks = document.querySelectorAll('.header__link');

  const observerNav = new IntersectionObserver(
    (entries) => {
      entries.forEach((entry) => {
        if (entry.isIntersecting) {
          const id = entry.target.getAttribute('id');
          navLinks.forEach((link) => {
            link.classList.toggle('is-active', link.getAttribute('href') === `#${id}`);
          });
        }
      });
    },
    { rootMargin: '-40% 0px -55% 0px' }
  );

  sections.forEach((section) => observerNav.observe(section));

  document.querySelectorAll('.reveal').forEach((el) => {
    const revealObserver = new IntersectionObserver(
      (entries) => {
        entries.forEach((entry) => {
          if (entry.isIntersecting) {
            entry.target.classList.add('is-visible');
            revealObserver.unobserve(entry.target);
          }
        });
      },
      { threshold: 0.12 }
    );
    revealObserver.observe(el);
  });

  const openModal = () => {
    demoModal?.classList.add('is-open');
    document.body.style.overflow = 'hidden';
  };

  const closeModal = () => {
    demoModal?.classList.remove('is-open');
    document.body.style.overflow = '';
  };

  document.getElementById('btn-demo-hero')?.addEventListener('click', openModal);
  document.getElementById('btn-demo-header')?.addEventListener('click', openModal);
  modalClose?.addEventListener('click', closeModal);
  demoModal?.addEventListener('click', (e) => {
    if (e.target === demoModal) closeModal();
  });
  document.addEventListener('keydown', (e) => {
    if (e.key === 'Escape') closeModal();
  });

  const segmentBtns = document.querySelectorAll('.features__segment-btn');
  const panelStudent = document.getElementById('panel-student');
  const panelAdmin = document.getElementById('panel-admin');

  segmentBtns.forEach((btn) => {
    btn.addEventListener('click', () => {
      const role = btn.dataset.role;
      segmentBtns.forEach((b) => b.classList.remove('is-active'));
      btn.classList.add('is-active');
      panelStudent?.classList.toggle('is-active', role === 'student');
      panelAdmin?.classList.toggle('is-active', role === 'admin');
    });
  });

  function renderBullets(container, bulletsJson) {
    if (!container) return;
    container.innerHTML = '';
    try {
      const bullets = JSON.parse(bulletsJson || '[]');
      bullets.forEach((text) => {
        const li = document.createElement('li');
        li.textContent = text;
        container.appendChild(li);
      });
    } catch {
      container.innerHTML = '';
    }
  }

  function setupFeatureList(listId, previewId) {
    const list = document.getElementById(listId);
    const preview = document.getElementById(previewId);
    if (!list || !preview) return;

    const img = preview.querySelector('.features__preview-img');
    const title = preview.querySelector('.features__preview-title');
    const desc = preview.querySelector('.features__preview-desc');
    const bullets = preview.querySelector('.feature-bullets');
    const ctaWrap = preview.querySelector('.features__preview-cta');

    const updatePreview = (item) => {
      list.querySelectorAll('.features__item').forEach((i) => i.classList.remove('is-active'));
      item.classList.add('is-active');
      img.src = item.dataset.img;
      img.alt = item.dataset.title;
      title.textContent = item.dataset.title;
      desc.textContent = item.dataset.desc;
      renderBullets(bullets, item.dataset.bullets);
      if (ctaWrap) {
        ctaWrap.style.display = item.dataset.cta === 'true' ? 'block' : 'none';
      }
    };

    list.querySelectorAll('.features__item').forEach((item) => {
      item.addEventListener('click', () => updatePreview(item));
    });

    const active = list.querySelector('.features__item.is-active');
    if (active) updatePreview(active);
  }

  setupFeatureList('student-features-list', 'student-preview');
  setupFeatureList('admin-features-list', 'admin-preview');

  function animateCounter(el, target, suffix = '') {
    const duration = 2000;
    const start = performance.now();
    const isPercent = suffix === '%';

    const step = (now) => {
      const progress = Math.min((now - start) / duration, 1);
      const eased = 1 - Math.pow(1 - progress, 3);
      const value = Math.floor(target * eased);
      el.textContent = isPercent ? value : value.toLocaleString('vi-VN');
      if (progress < 1) requestAnimationFrame(step);
      else el.textContent = isPercent ? target : target.toLocaleString('vi-VN');
    };

    requestAnimationFrame(step);
  }

  const statsObserver = new IntersectionObserver(
    (entries) => {
      entries.forEach((entry) => {
        if (entry.isIntersecting) {
          entry.target.querySelectorAll('[data-counter]').forEach((el) => {
            const target = parseInt(el.dataset.counter, 10);
            const suffix = el.dataset.suffix || '';
            animateCounter(el, target, suffix);
          });
          statsObserver.unobserve(entry.target);
        }
      });
    },
    { threshold: 0.3 }
  );

  const statsSection = document.getElementById('gioi-thieu');
  if (statsSection) statsObserver.observe(statsSection);

  function showFormSuccess(formCard, productName) {
    formCard.innerHTML = `
      <div class="form__success">
        <div class="form__success-icon"><i class="bx bx-check"></i></div>
        <h3>Đăng ký thành công!</h3>
        <p>Cảm ơn bạn đã quan tâm đến ${productName}.<br>Chuyên gia của chúng tôi sẽ liên hệ với bạn trong vòng 24 giờ.</p>
        <div class="form__success-hotline"><i class="bx bx-phone"></i> Hotline hỗ trợ: 1800 xxxx (Miễn phí)</div>
      </div>
    `;
  }

  const contactForm = document.getElementById('contact-form');
  contactForm?.addEventListener('submit', (e) => {
    e.preventDefault();
    const btn = document.getElementById('submit-form-btn');
    btn.disabled = true;
    btn.innerHTML = '<i class="bx bx-loader-alt bx-spin"></i> Đang gửi...';
    setTimeout(() => {
      showFormSuccess(document.getElementById('contact-form-card'), 'LMS cho trường Đại học - Cao đẳng');
    }, 1800);
  });

  const modalForm = document.getElementById('modal-contact-form');
  modalForm?.addEventListener('submit', (e) => {
    e.preventDefault();
    const btn = document.getElementById('modal-submit-btn');
    btn.disabled = true;
    btn.innerHTML = '<i class="bx bx-loader-alt bx-spin"></i> Đang gửi...';
    setTimeout(() => {
      showFormSuccess(document.getElementById('modal-form-card'), 'LMS cho trường Đại học - Cao đẳng');
      setTimeout(closeModal, 2500);
    }, 1800);
  });
});
