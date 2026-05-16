// JavaScript cho tính năng tương tác trên trang web

document.addEventListener('DOMContentLoaded', function() {
    // Khởi tạo biến đếm cho bình chọn
    let pollCounts = {
        mammal: 0,
        bird: 0,
        reptile: 0
    };
    
    // Lấy dữ liệu từ localStorage nếu có
    if (localStorage.getItem('pollCounts')) {
        pollCounts = JSON.parse(localStorage.getItem('pollCounts'));
    }
    
    // Xử lý bình chọn
    const pollButtons = document.querySelectorAll('.poll-btn');
    const pollResult = document.getElementById('poll-result');
    
    if (pollButtons.length > 0) {
        // Cập nhật kết quả ban đầu
        updatePollResult();
        
        // Thêm sự kiện click cho các nút bình chọn
        pollButtons.forEach(button => {
            button.addEventListener('click', function() {
                const animalType = this.getAttribute('data-animal');
                pollCounts[animalType]++;
                
                // Lưu vào localStorage
                localStorage.setItem('pollCounts', JSON.stringify(pollCounts));
                
                // Cập nhật kết quả hiển thị
                updatePollResult();
                
                // Hiệu ứng cho nút được nhấn
                this.style.backgroundColor = '#2ecc71';
                this.style.color = 'white';
                
                // Reset màu sau 1 giây
                setTimeout(() => {
                    this.style.backgroundColor = '';
                    this.style.color = '';
                }, 1000);
            });
        });
    }
    
    function updatePollResult() {
        if (!pollResult) return;
        
        const total = pollCounts.mammal + pollCounts.bird + pollCounts.reptile;
        
        if (total === 0) {
            pollResult.textContent = "Hãy chọn một loài để xem kết quả!";
            return;
        }
        
        const mammalPercent = Math.round((pollCounts.mammal / total) * 100);
        const birdPercent = Math.round((pollCounts.bird / total) * 100);
        const reptilePercent = Math.round((pollCounts.reptile / total) * 100);
        
        pollResult.innerHTML = `
            Kết quả bình chọn:<br>
            <strong>Động vật có vú:</strong> ${pollCounts.mammal} phiếu (${mammalPercent}%)<br>
            <strong>Chim:</strong> ${pollCounts.bird} phiếu (${birdPercent}%)<br>
            <strong>Bò sát:</strong> ${pollCounts.reptile} phiếu (${reptilePercent}%)<br>
            <small>Tổng số phiếu: ${total}</small>
        `;
    }
    
    // Hiệu ứng cuộn mượt cho các liên kết nội bộ
    document.querySelectorAll('a[href^="#"]').forEach(anchor => {
        anchor.addEventListener('click', function(e) {
            e.preventDefault();
            
            const targetId = this.getAttribute('href');
            if (targetId === '#') return;
            
            const targetElement = document.querySelector(targetId);
            if (targetElement) {
                window.scrollTo({
                    top: targetElement.offsetTop - 80,
                    behavior: 'smooth'
                });
            }
        });
    });
    
    // Thêm hiệu ứng hover cho các item
    const featuredItems = document.querySelectorAll('.featured-item, .sub-page-item');
    featuredItems.forEach(item => {
        item.addEventListener('mouseenter', function() {
            this.style.boxShadow = '0 10px 25px rgba(0, 0, 0, 0.15)';
        });
        
        item.addEventListener('mouseleave', function() {
            this.style.boxShadow = '';
        });
    });
    
    // Hiển thị thông báo chào mừng
    if (window.location.pathname.endsWith('index.html') || window.location.pathname === '/') {
        setTimeout(() => {
            console.log('Chào mừng đến với trang web Thế giới Động vật!');
        }, 500);
    }
});
