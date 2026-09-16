// JavaScript cho tính năng tương tác trên trang web

document.addEventListener('DOMContentLoaded', function() {
    // Khởi tạo biến đếm cho bình chọn
    const defaultPollCounts = {
        mammal: 0,
        bird: 0,
        reptile: 0
    };

    function normalizePollCounts(value) {
        return {
            mammal: Number(value?.mammal) || 0,
            bird: Number(value?.bird) || 0,
            reptile: Number(value?.reptile) || 0
        };
    }

    let pollCounts = { ...defaultPollCounts };
    
    // Lấy dữ liệu từ localStorage nếu có
    if (localStorage.getItem('pollCounts')) {
        try {
            pollCounts = normalizePollCounts(JSON.parse(localStorage.getItem('pollCounts')));
        } catch (error) {
            pollCounts = { ...defaultPollCounts };
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

        const createResultLine = (label, count, percent) => {
            const fragment = document.createDocumentFragment();
            const strong = document.createElement('strong');
            strong.textContent = label;
            fragment.append(strong, ` ${count} phiếu (${percent}%)`);
            return fragment;
        };

        const totalLine = document.createElement('small');
        totalLine.textContent = `Tổng số phiếu: ${total}`;

        pollResult.replaceChildren(
            'Kết quả bình chọn:',
            document.createElement('br'),
            createResultLine('Động vật có vú:', pollCounts.mammal, mammalPercent),
            document.createElement('br'),
            createResultLine('Chim:', pollCounts.bird, birdPercent),
            document.createElement('br'),
            createResultLine('Bò sát:', pollCounts.reptile, reptilePercent),
            document.createElement('br'),
            totalLine
        );
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
