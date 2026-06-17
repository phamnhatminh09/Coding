document.addEventListener('DOMContentLoaded', () => {
  // 1. Navigation scroll effect
  const navbar = document.querySelector('.navbar');
  window.addEventListener('scroll', () => {
    if (window.scrollY > 20) {
      navbar.classList.add('scrolled');
    } else {
      navbar.classList.remove('scrolled');
    }
  });

  // 2. Mobile Menu Toggle
  const hamburger = document.querySelector('.hamburger');
  const navMenu = document.querySelector('.nav-menu');

  hamburger.addEventListener('click', () => {
    hamburger.classList.toggle('active');
    navMenu.classList.toggle('active');
  });

  // Close mobile menu when clicking a link
  document.querySelectorAll('.nav-link').forEach(link => {
    link.addEventListener('click', () => {
      hamburger.classList.remove('active');
      navMenu.classList.remove('active');
    });
  });

  // 3. Block 3: Key Features Interactive Tabs
  const segmentBtns = document.querySelectorAll('.segment-btn');
  const adminFeaturesList = document.getElementById('admin-features-list');
  const studentFeaturesList = document.getElementById('student-features-list');
  const displayCard = document.getElementById('feature-display-card');

  // Feature Data
  const featureData = {
    // Administrator Features
    'admin-dashboard': {
      title: 'Dashboard tổng quan đào tạo',
      desc: 'Cung cấp cái nhìn toàn diện về hoạt động đào tạo, biểu đồ thống kê trực quan về số lượng học viên, tiến độ hoàn thành khóa học và các chỉ số đo lường hiệu quả tức thời.',
      img: 'assets/hero_dashboard.png'
    },
    'admin-users': {
      title: 'Quản lý người dùng',
      desc: 'Quản trị viên dễ dàng quản lý danh sách học viên, giảng viên và nhân sự hỗ trợ. Hỗ trợ import dữ liệu hàng loạt từ file Excel, tạo tài khoản và quản lý trạng thái hoạt động.',
      img: 'assets/student_learning.png'
    },
    'admin-roles': {
      title: 'Phân quyền và thiết lập vai trò linh hoạt',
      desc: 'Định nghĩa chi tiết các vai trò (Admin, Trợ giảng, Giảng viên, Học viên) với các quyền hạn cụ thể, đảm bảo tính bảo mật và tính chuyên biệt trong quản lý hệ thống.',
      img: 'assets/hero_dashboard.png'
    },
    'admin-enrollment': {
      title: 'Ghi danh thủ công/tự động',
      desc: 'Hỗ trợ ghi danh thủ công từng học viên vào lớp học hoặc thiết lập các quy tắc ghi danh tự động dựa trên phòng ban, chức vụ hoặc các khóa học tiên quyết.',
      img: 'assets/student_learning.png'
    },
    'admin-repository': {
      title: 'Quản lý học liệu tập trung',
      desc: 'Kho lưu trữ tài liệu dùng chung cho toàn bộ hệ thống, hỗ trợ nhiều định dạng tệp tin (PDF, Docx, PPT, MP4, SCORM). Dễ dàng chia sẻ và cập nhật phiên bản mới.',
      img: 'assets/hero_dashboard.png'
    },
    'admin-courses': {
      title: 'Tạo & quản lý khóa học',
      desc: 'Giao diện trực quan giúp xây dựng cấu trúc khóa học theo chương mục bài bản. Hỗ trợ thiết lập điều kiện học tập, thời gian kích hoạt bài học và thứ tự bắt buộc.',
      img: 'assets/student_learning.png'
    },
    'admin-questions': {
      title: 'Ngân hàng câu hỏi, đề thi',
      desc: 'Tạo lập và phân loại hàng nghìn câu hỏi trắc nghiệm, tự luận, nối chéo. Xây dựng đề thi tự động từ ma trận đề thi hoặc chọn ngẫu nhiên theo độ khó.',
      img: 'assets/hero_dashboard.png'
    },
    'admin-gamification': {
      title: 'Gamification',
      desc: 'Tích hợp các yếu tố trò chơi vào học tập thông qua hệ thống điểm thưởng, bảng xếp hạng năng động và bộ huy chương thành tích để tăng động lực tự học.',
      img: 'assets/student_learning.png'
    },
    'admin-custom': {
      title: 'Tùy chỉnh giao diện website',
      desc: 'Cho phép tùy chỉnh màu sắc thương hiệu, logo, banner trang chủ để tạo ra một không gian học tập mang đậm bản sắc văn hóa riêng của từng đơn vị.',
      img: 'assets/hero_dashboard.png'
    },
    'admin-reports': {
      title: 'Tạo báo cáo học tập',
      desc: 'Hệ thống báo cáo đa chiều từ tổng quan đến chi tiết từng cá nhân. Xuất dữ liệu thống kê trực quan giúp người quản lý đánh giá chất lượng học tập nhanh chóng.',
      img: 'assets/student_learning.png'
    },
    'admin-emails': {
      title: 'Gửi và quản lý email thông báo',
      desc: 'Tự động gửi email nhắc nhở học tập, thông báo có bài kiểm tra mới, xác nhận hoàn thành khóa học hoặc chúc mừng sinh nhật theo cài đặt sẵn.',
      img: 'assets/hero_dashboard.png'
    },

    // Student Features
    'student-dashboard': {
      title: 'Dashboard cá nhân',
      desc: 'Trang cá nhân trực quan tổng hợp các khóa học đang tham gia, tiến độ hoàn thành, nhiệm vụ hàng tuần cùng lịch học và kiểm tra sắp diễn ra.',
      img: 'assets/student_learning.png'
    },
    'student-courses': {
      title: 'Quản lý các khóa học',
      desc: 'Dễ dàng lọc, tìm kiếm và truy cập các khóa học đã đăng ký. Hệ thống tự động ghi nhớ vị trí học cuối cùng giúp học viên tiếp tục bài học một cách liền mạch.',
      img: 'assets/hero_dashboard.png'
    },
    'student-exams': {
      title: 'Tham gia thi cử dễ dàng',
      desc: 'Làm bài kiểm tra, bài thi trực tuyến với giao diện đồng hồ đếm ngược trực quan, tự động lưu bài khi mất kết nối mạng và hiển thị kết quả chi tiết lập tức.',
      img: 'assets/student_learning.png'
    },
    'student-certificates': {
      title: 'Nhận chứng chỉ sau khóa học',
      desc: 'Chứng chỉ hoàn thành khóa học được cấp tự động dưới dạng PDF tiêu chuẩn khi học viên vượt qua các bài kiểm tra cuối khóa đạt điều kiện tối thiểu.',
      img: 'assets/hero_dashboard.png'
    },
    'student-reports': {
      title: 'Báo cáo kết quả học tập',
      desc: 'Giúp học viên theo dõi điểm số các bài kiểm tra, biểu đồ tiến trình học và nhận diện những kỹ năng cần cải thiện để nâng cao năng lực.',
      img: 'assets/student_learning.png'
    },
    'student-library': {
      title: 'Truy cập thư viện tài liệu',
      desc: 'Tìm kiếm nhanh các tài liệu học tập, sách điện tử, slide bài giảng được chia sẻ rộng rãi trong kho học liệu chung của hệ thống mọi lúc mọi nơi.',
      img: 'assets/hero_dashboard.png'
    },
    'student-leaderboard': {
      title: 'Đua top xếp hạng thành tích',
      desc: 'Bảng vinh danh các học viên xuất sắc nhất tuần, tháng dựa trên điểm tích lũy học tập, khuyến khích tinh thần học tập thi đua lành mạnh.',
      img: 'assets/student_learning.png'
    },
    'student-ai': {
      title: 'Tương tác với trợ giảng AI',
      desc: 'Hỗ trợ giải đáp các thắc mắc về kiến thức bài học tức thời 24/7, tóm tắt nội dung bài giảng và gợi ý lộ trình học tập tối ưu cho từng cá nhân.',
      img: 'assets/hero_dashboard.png'
    },
    'student-forums': {
      title: 'Diễn đàn và thảo luận chung',
      desc: 'Không gian mở để trao đổi kiến thức giữa các học viên và giảng viên, đặt câu hỏi, thảo luận chủ đề bài học và tăng cường gắn kết cộng đồng học tập.',
      img: 'assets/student_learning.png'
    }
  };

  // Function to switch Feature Roles (Admin / Student)
  segmentBtns.forEach(btn => {
    btn.addEventListener('click', () => {
      const role = btn.dataset.role;
      
      // Update active button state
      segmentBtns.forEach(b => b.classList.remove('active'));
      btn.classList.add('active');

      // Toggle visible list
      if (role === 'admin') {
        adminFeaturesList.style.display = 'flex';
        studentFeaturesList.style.display = 'none';
        
        // Select first admin item
        const firstAdminItem = adminFeaturesList.querySelector('.feature-item');
        if (firstAdminItem) firstAdminItem.click();
      } else {
        adminFeaturesList.style.display = 'none';
        studentFeaturesList.style.display = 'flex';
        
        // Select first student item
        const firstStudentItem = studentFeaturesList.querySelector('.feature-item');
        if (firstStudentItem) firstStudentItem.click();
      }
    });
  });

  // Function to handle clicking an individual feature item
  const featureItems = document.querySelectorAll('.feature-item');
  featureItems.forEach(item => {
    item.addEventListener('click', () => {
      const key = item.dataset.featureKey;
      
      // Update active item in list
      const activeList = item.closest('.features-list');
      activeList.querySelectorAll('.feature-item').forEach(i => i.classList.remove('active'));
      item.classList.add('active');

      // Update Detail Display with transition animation
      const data = featureData[key];
      if (data) {
        const titleEl = displayCard.querySelector('.feature-display-title');
        const descEl = displayCard.querySelector('.feature-display-desc');
        const imgEl = displayCard.querySelector('.feature-display-img');

        // Apply smooth fade out, update, and fade in
        displayCard.style.opacity = '0.3';
        displayCard.style.transform = 'translateY(5px)';
        
        setTimeout(() => {
          titleEl.textContent = data.title;
          descEl.textContent = data.desc;
          imgEl.src = data.img;
          imgEl.alt = data.title;
          
          displayCard.style.opacity = '1';
          displayCard.style.transform = 'translateY(0)';
        }, 150);
      }
    });
  });

  // Trigger click on first feature on load
  const activeSegmentBtn = document.querySelector('.segment-btn.active');
  if (activeSegmentBtn) {
    const role = activeSegmentBtn.dataset.role;
    if (role === 'admin') {
      adminFeaturesList.querySelector('.feature-item').click();
    } else {
      studentFeaturesList.querySelector('.feature-item').click();
    }
  }

  // 4. Modal handling (CTA triggers)
  const modal = document.getElementById('consultation-modal');
  const openModalBtns = document.querySelectorAll('.trigger-modal');
  const closeModalBtn = document.getElementById('close-modal');

  openModalBtns.forEach(btn => {
    btn.addEventListener('click', (e) => {
      e.preventDefault();
      modal.classList.add('active');
      document.body.style.overflow = 'hidden'; // Lock body scroll
    });
  });

  const closeModal = () => {
    modal.classList.remove('active');
    document.body.style.overflow = 'auto'; // Unlock body scroll
  };

  closeModalBtn.addEventListener('click', closeModal);
  modal.addEventListener('click', (e) => {
    if (e.target === modal) {
      closeModal();
    }
  });

  // 5. Contact Form Validation & Submission Simulation
  const handleFormSubmit = (formId, successId) => {
    const form = document.getElementById(formId);
    const successBlock = document.getElementById(successId);

    if (!form || !successBlock) return;

    form.addEventListener('submit', (e) => {
      e.preventDefault();

      // Simple HTML5 validation triggered, let's gather data
      const fullname = form.querySelector('[name="fullname"]').value.trim();
      const phone = form.querySelector('[name="phone"]').value.trim();
      const email = form.querySelector('[name="email"]').value.trim();
      const company = form.querySelector('[name="company"]').value.trim();
      const requirements = form.querySelector('[name="requirements"]').value.trim();

      if (!fullname || !phone || !email || !company) {
        alert('Vui lòng điền đầy đủ các trường thông tin bắt buộc.');
        return;
      }

      // Show submitting state on button
      const submitBtn = form.querySelector('button[type="submit"]');
      const originalText = submitBtn.innerHTML;
      submitBtn.disabled = true;
      submitBtn.innerHTML = '<i class="fas fa-spinner fa-spin"></i> Đang gửi yêu cầu...';

      // Simulate API call
      setTimeout(() => {
        // Reset button
        submitBtn.disabled = false;
        submitBtn.innerHTML = originalText;

        // Hide form and show success message
        form.style.display = 'none';
        
        // Update title/sub if in card
        const cardHeader = form.previousElementSibling?.previousElementSibling;
        const cardSub = form.previousElementSibling;
        if (cardHeader && cardHeader.tagName === 'H3') cardHeader.style.display = 'none';
        if (cardSub && cardSub.classList.contains('form-subtitle')) cardSub.style.display = 'none';

        successBlock.style.display = 'flex';

        // Clear form fields
        form.reset();
      }, 1500);
    });
  };

  // Bind to main registration form and modal registration form
  handleFormSubmit('main-contact-form', 'main-form-success');
  handleFormSubmit('modal-contact-form', 'modal-form-success');
});
