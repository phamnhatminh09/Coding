document.addEventListener('DOMContentLoaded', () => {

  /* ==================== 1. SCROLL HEADER EFFECT ==================== */
  const navbar = document.querySelector('.navbar');
  window.addEventListener('scroll', () => {
    if (window.scrollY > 20) {
      navbar.classList.add('scrolled');
    } else {
      navbar.classList.remove('scrolled');
    }
  });

  /* ==================== 2. MOBILE MENU HAMBURGER ==================== */
  const hamburger = document.querySelector('.hamburger');
  const navMenuWrapper = document.querySelector('.nav-menu-wrapper');
  const navMenu = document.querySelector('.nav-menu');

  if (hamburger && navMenu) {
    hamburger.addEventListener('click', () => {
      hamburger.classList.toggle('active');
      navMenu.classList.toggle('active');
      
      // Toggle bar class for Hamburger morphing into X
      const bars = hamburger.querySelectorAll('.bar');
      if (hamburger.classList.contains('active')) {
        bars[0].style.transform = 'translateY(8px) rotate(45deg)';
        bars[1].style.opacity = '0';
        bars[2].style.transform = 'translateY(-8px) rotate(-45deg)';
      } else {
        bars[0].style.transform = 'none';
        bars[1].style.opacity = '1';
        bars[2].style.transform = 'none';
      }
    });

    // Close menu when clicking a link
    document.querySelectorAll('.nav-link').forEach(link => {
      link.addEventListener('click', () => {
        hamburger.classList.remove('active');
        navMenu.classList.remove('active');
        const bars = hamburger.querySelectorAll('.bar');
        bars[0].style.transform = 'none';
        bars[1].style.opacity = '1';
        bars[2].style.transform = 'none';
      });
    });
  }

  /* ==================== 3. STATS COUNT UP ANIMATION ==================== */
  const stats = document.querySelectorAll('.hero-stat-number');
  
  const countUp = (element) => {
    const target = parseInt(element.getAttribute('data-target'), 10);
    const count = parseInt(element.innerText, 10);
    const speed = target / 50;
    
    if (count < target) {
      element.innerText = Math.ceil(count + speed);
      setTimeout(() => countUp(element), 30);
    } else {
      if (target >= 1000) {
        element.innerText = target.toLocaleString('vi-VN');
      } else {
        element.innerText = target;
      }
    }
  };

  const statsObserver = new IntersectionObserver((entries, observer) => {
    entries.forEach(entry => {
      if (entry.isIntersecting) {
        const targetElement = entry.target;
        countUp(targetElement);
        observer.unobserve(targetElement);
      }
    });
  }, { threshold: 0.5 });

  stats.forEach(stat => {
    statsObserver.observe(stat);
  });

  /* ==================== 4. INTERACTIVE FEATURES TABS ==================== */
  const segmentBtns = document.querySelectorAll('.segment-btn');
  const studentFeaturesList = document.getElementById('student-features-list');
  const instructorFeaturesList = document.getElementById('instructor-features-list');
  const featureDisplayCard = document.getElementById('feature-display-card');

  // Role switching
  segmentBtns.forEach(btn => {
    btn.addEventListener('click', () => {
      segmentBtns.forEach(b => b.classList.remove('active'));
      btn.classList.add('active');
      
      const role = btn.getAttribute('data-role');
      if (role === 'student') {
        studentFeaturesList.style.display = 'flex';
        instructorFeaturesList.style.display = 'none';
        // Auto click first student item
        const firstStudent = studentFeaturesList.querySelector('.feature-item');
        if (firstStudent) firstStudent.click();
      } else {
        studentFeaturesList.style.display = 'none';
        instructorFeaturesList.style.display = 'flex';
        // Auto click first instructor item
        const firstInstructor = instructorFeaturesList.querySelector('.feature-item');
        if (firstInstructor) firstInstructor.click();
      }
    });
  });

  // Tab items switching
  const featureItems = document.querySelectorAll('.feature-item');
  featureItems.forEach(item => {
    item.addEventListener('click', () => {
      // Deactivate items in current visible list
      const parentList = item.closest('.features-list');
      parentList.querySelectorAll('.feature-item').forEach(i => i.classList.remove('active'));
      
      // Activate clicked item
      item.classList.add('active');
      
      const key = item.getAttribute('data-feature-key');
      const targetPane = document.getElementById(`pane-${key}`);
      
      if (targetPane) {
        // Smooth transition overlay
        featureDisplayCard.style.opacity = '0.3';
        featureDisplayCard.style.transform = 'translateY(5px)';
        
        setTimeout(() => {
          // Hide all panes
          document.querySelectorAll('.feature-pane').forEach(p => p.classList.remove('active'));
          // Show target pane
          targetPane.classList.add('active');
          
          featureDisplayCard.style.opacity = '1';
          featureDisplayCard.style.transform = 'translateY(0)';
        }, 150);
      }
    });
  });

  /* ==================== 5. INTERFACE DASHBOARD SLIDER ==================== */
  const slides = document.querySelectorAll('.interface-slide');
  const prevBtn = document.querySelector('.slider-arrow.prev');
  const nextBtn = document.querySelector('.slider-arrow.next');
  const dots = document.querySelectorAll('.slider-dot-item');
  const browserAddressText = document.getElementById('browser-address-text');
  let currentSlide = 0;

  const showSlide = (index) => {
    if (index >= slides.length) currentSlide = 0;
    else if (index < 0) currentSlide = slides.length - 1;
    else currentSlide = index;

    slides.forEach(slide => slide.classList.remove('active'));
    dots.forEach(dot => dot.classList.remove('active'));

    slides[currentSlide].classList.add('active');
    dots[currentSlide].classList.add('active');

    // Update address bar mockup depending on active view
    if (currentSlide === 0) {
      browserAddressText.innerText = 'welearning.vn/student/dashboard';
    } else {
      browserAddressText.innerText = 'welearning.vn/instructor/dashboard';
    }
  };

  if (prevBtn && nextBtn) {
    prevBtn.addEventListener('click', () => showSlide(currentSlide - 1));
    nextBtn.addEventListener('click', () => showSlide(currentSlide + 1));
    
    dots.forEach((dot, index) => {
      dot.addEventListener('click', () => showSlide(index));
    });

    setInterval(() => {
      showSlide(currentSlide + 1);
    }, 8000);
  }

  /* ==================== 6. VIDEO MODAL & SIMULATION ==================== */
  const playVideoTrigger = document.getElementById('play-video-trigger');
  const videoModal = document.getElementById('video-modal');
  const closeVideoTrigger = document.getElementById('close-video-trigger');
  const timelineFill = document.querySelector('.mock-timeline-fill');
  const mockTimeline = document.querySelector('.mock-timeline');
  const mockPlayBtn = document.querySelector('.mock-play-btn i');
  const mockTime = document.querySelector('.mock-time');

  let timelineInterval = null;
  let videoProgress = 1;
  const videoTotalSecs = 195;

  const formatVideoTime = (seconds) => {
    const mins = Math.floor(seconds / 60);
    const secs = Math.floor(seconds % 60);
    return `${mins}:${secs < 10 ? '0' : ''}${secs}`;
  };

  const startTimelineSimulation = () => {
    if (timelineInterval) clearInterval(timelineInterval);
    
    timelineInterval = setInterval(() => {
      videoProgress += 0.5;
      if (videoProgress >= 100) {
        videoProgress = 0;
        clearInterval(timelineInterval);
        mockPlayBtn.className = 'bx bx-play';
      }
      
      timelineFill.style.width = `${videoProgress}%`;
      const currentSeconds = (videoProgress / 100) * videoTotalSecs;
      mockTime.innerText = `${formatVideoTime(currentSeconds)} / ${formatVideoTime(videoTotalSecs)}`;
    }, 500);
  };

  const stopTimelineSimulation = () => {
    clearInterval(timelineInterval);
  };

  if (playVideoTrigger && videoModal && closeVideoTrigger) {
    playVideoTrigger.addEventListener('click', () => {
      videoModal.classList.add('active');
      document.body.style.overflow = 'hidden';
      mockPlayBtn.className = 'bx bx-pause';
      startTimelineSimulation();
    });

    const closeModal = () => {
      videoModal.classList.remove('active');
      document.body.style.overflow = 'auto';
      stopTimelineSimulation();
    };

    closeVideoTrigger.addEventListener('click', closeModal);
    videoModal.addEventListener('click', (e) => {
      if (e.target === videoModal) {
        closeModal();
      }
    });

    const playToggleBtn = document.querySelector('.mock-play-btn');
    if (playToggleBtn) {
      playToggleBtn.addEventListener('click', () => {
        if (mockPlayBtn.className === 'bx bx-pause') {
          mockPlayBtn.className = 'bx bx-play';
          stopTimelineSimulation();
        } else {
          mockPlayBtn.className = 'bx bx-pause';
          startTimelineSimulation();
        }
      });
    }

    if (mockTimeline) {
      mockTimeline.addEventListener('click', (e) => {
        const rect = mockTimeline.getBoundingClientRect();
        const clickX = e.clientX - rect.left;
        const width = rect.width;
        videoProgress = (clickX / width) * 100;
        
        timelineFill.style.width = `${videoProgress}%`;
        const currentSeconds = (videoProgress / 100) * videoTotalSecs;
        mockTime.innerText = `${formatVideoTime(currentSeconds)} / ${formatVideoTime(videoTotalSecs)}`;
        
        if (mockPlayBtn.className === 'bx bx-pause') {
          startTimelineSimulation();
        }
      });
    }
  }

  /* ==================== 7. CONSULTATION FORM SUBMISSION ==================== */
  const consultForm = document.getElementById('consultation-form');
  const formSuccessBlock = document.getElementById('form-success-block');

  if (consultForm && formSuccessBlock) {
    consultForm.addEventListener('submit', (e) => {
      e.preventDefault();
      
      const fullname = document.getElementById('fullname').value.trim();
      const phone = document.getElementById('phone').value.trim();
      const email = document.getElementById('email').value.trim();
      const school = document.getElementById('school').value.trim();
      
      if (!fullname || !phone || !email || !school) {
        alert('Vui lòng điền đầy đủ các thông tin bắt buộc.');
        return;
      }
      
      const submitButton = consultForm.querySelector('button[type="submit"]');
      const originalContent = submitButton.innerHTML;
      
      submitButton.disabled = true;
      submitButton.innerHTML = `<i class="bx bx-loader-alt bx-spin"></i> <span>Đang gửi thông tin...</span>`;
      
      setTimeout(() => {
        submitButton.disabled = false;
        submitButton.innerHTML = originalContent;
        
        // Hide form and show success block inside card
        consultForm.style.display = 'none';
        
        // Update header & subtitle text to hidden for cleaner layout
        const cardHeader = consultForm.previousElementSibling?.previousElementSibling;
        const cardSub = consultForm.previousElementSibling;
        if (cardHeader && cardHeader.tagName === 'H3') cardHeader.style.display = 'none';
        if (cardSub && cardSub.classList.contains('form-subtitle')) cardSub.style.display = 'none';

        formSuccessBlock.style.display = 'flex';
        formSuccessBlock.innerHTML = `
          <div class="success-icon"><i class="bx bx-check"></i></div>
          <h4>Đăng ký thành công!</h4>
          <p style="color: var(--text-muted); font-size: 0.95rem; line-height: 1.5; margin-bottom: 20px;">
            Cảm ơn <strong>${fullname}</strong> đã liên hệ. OES sẽ gọi lại cho bạn qua SĐT <strong>${phone}</strong> hoặc gửi thư đến email <strong>${email}</strong> sớm nhất trong vòng 24h làm việc.
          </p>
          <button class="btn btn-secondary btn-sm" onclick="location.reload();" style="font-size:0.8rem;padding:8px 16px;">
            <i class="bx bx-refresh"></i> Quay lại form
          </button>
        `;
        
        consultForm.reset();
      }, 1500);
    });
  }

});
