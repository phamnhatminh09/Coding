document.addEventListener('DOMContentLoaded', () => {
  const header = document.getElementById('header');
  const navToggle = document.getElementById('nav-toggle');
  const navMenu = document.getElementById('nav-menu');
  const demoModal = document.getElementById('demo-modal');
  const modalClose = document.getElementById('modal-close');

  /* Header scroll */
  window.addEventListener('scroll', () => {
    header?.classList.toggle('is-scrolled', window.scrollY > 20);
  });

  /* Mobile nav */
  navToggle?.addEventListener('click', () => {
    navMenu?.classList.toggle('is-open');
    const icon = navToggle.querySelector('i');
    icon.className = navMenu?.classList.contains('is-open') ? 'bx bx-x' : 'bx bx-menu';
  });

  navMenu?.querySelectorAll('a').forEach((link) => {
    link.addEventListener('click', () => {
      navMenu?.classList.remove('is-open');
      navToggle?.querySelector('i').className = 'bx bx-menu';
    });
  });

  /* Active nav link */
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

  /* Reveal on scroll */
  const revealEls = document.querySelectorAll('.reveal');
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
  revealEls.forEach((el) => revealObserver.observe(el));

  /* Demo modal */
  const openModal = () => {
    demoModal.classList.add('is-open');
    document.body.style.overflow = 'hidden';
  };

  const closeModal = () => {
    demoModal.classList.remove('is-open');
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

  /* Feature segment tabs */
  const segmentBtns = document.querySelectorAll('.features__segment-btn');
  const panelAdmin = document.getElementById('panel-admin');
  const panelLearner = document.getElementById('panel-learner');

  segmentBtns.forEach((btn) => {
    btn.addEventListener('click', () => {
      const role = btn.dataset.role;
      segmentBtns.forEach((b) => b.classList.remove('is-active'));
      btn.classList.add('is-active');
      panelAdmin.classList.toggle('is-active', role === 'admin');
      panelLearner.classList.toggle('is-active', role === 'learner');
    });
  });

  /* Feature item click */
  function setupFeatureList(listId, previewId) {
    const list = document.getElementById(listId);
    const preview = document.getElementById(previewId);
    if (!list || !preview) return;

    const img = preview.querySelector('.features__preview-img');
    const title = preview.querySelector('.features__preview-title');

    list.querySelectorAll('.features__item').forEach((item) => {
      item.addEventListener('click', () => {
        list.querySelectorAll('.features__item').forEach((i) => i.classList.remove('is-active'));
        item.classList.add('is-active');
        img.src = item.dataset.img;
        img.alt = item.dataset.title;
        title.textContent = item.dataset.title;
      });
    });
  }

  setupFeatureList('admin-features-list', 'admin-preview');
  setupFeatureList('learner-features-list', 'learner-preview');

  /* Form success helper */
  function showFormSuccess(formCard, productName) {
    formCard.innerHTML = `
      <div class="form__success">
        <div class="form__success-icon">
          <i class="bx bx-check"></i>
        </div>
        <h3>Đăng ký thành công!</h3>
        <p>
          Cảm ơn bạn đã quan tâm đến ${productName}.<br>
          Chuyên gia của chúng tôi sẽ liên hệ với bạn trong vòng 24 giờ.
        </p>
        <div class="form__success-hotline">
          <i class="bx bx-phone"></i>
          Hotline hỗ trợ: 1800 xxxx (Miễn phí)
        </div>
      </div>
    `;
  }

  /* Main contact form */
  const contactForm = document.getElementById('contact-form');
  if (contactForm) {
    contactForm.addEventListener('submit', (e) => {
      e.preventDefault();
      const btn = document.getElementById('submit-form-btn');
      btn.disabled = true;
      btn.innerHTML = '<i class="bx bx-loader-alt bx-spin"></i> Đang gửi...';

      setTimeout(() => {
        showFormSuccess(document.getElementById('contact-form-card'), 'LMS Lite');
      }, 1800);
    });
  }

  /* Modal contact form */
  const modalForm = document.getElementById('modal-contact-form');
  if (modalForm) {
    modalForm.addEventListener('submit', (e) => {
      e.preventDefault();
      const btn = document.getElementById('modal-submit-btn');
      btn.disabled = true;
      btn.innerHTML = '<i class="bx bx-loader-alt bx-spin"></i> Đang gửi...';

      setTimeout(() => {
        showFormSuccess(document.getElementById('modal-form-card'), 'LMS Lite');
        setTimeout(closeModal, 2500);
      }, 1800);
    });
  }
});
