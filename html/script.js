// JavaScript cho tính năng tương tác trên trang web

document.addEventListener('DOMContentLoaded', function() {
    const normalizePollCounts = function(value) {
        const source = value && typeof value === 'object' ? value : {};
        return {
            mammal: Math.max(0, Math.trunc(Number(source.mammal) || 0)),
            bird: Math.max(0, Math.trunc(Number(source.bird) || 0)),
            reptile: Math.max(0, Math.trunc(Number(source.reptile) || 0))
        };
    };

    // Khởi tạo biến đếm cho bình chọn
    let pollCounts = normalizePollCounts();
    
    // Lấy dữ liệu từ localStorage nếu có
    if (localStorage.getItem('pollCounts')) {
        try {
            pollCounts = normalizePollCounts(JSON.parse(localStorage.getItem('pollCounts')));
        } catch (error) {
            localStorage.removeItem('pollCounts');
        }
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
                if (!Object.prototype.hasOwnProperty.call(pollCounts, animalType)) return;
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
        
        pollResult.replaceChildren('Kết quả bình chọn:', document.createElement('br'));
        appendPollLine('Động vật có vú', pollCounts.mammal, mammalPercent);
        appendPollLine('Chim', pollCounts.bird, birdPercent);
        appendPollLine('Bò sát', pollCounts.reptile, reptilePercent);
        const summary = document.createElement('small');
        summary.textContent = `Tổng số phiếu: ${total}`;
        pollResult.appendChild(summary);
    }

    function appendPollLine(label, count, percent) {
        const labelNode = document.createElement('strong');
        labelNode.textContent = `${label}:`;
        pollResult.append(labelNode, ` ${count} phiếu (${percent}%)`, document.createElement('br'));
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
