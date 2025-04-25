# Twilight Run - hoanganh
Twilight Run là một game platformer 2D đầy hành động đưa người chơi vào cuộc phiêu lưu ly kỳ trong thế giới năng động, cuộn liên tục. Là một anh hùng dũng cảm, bạn phải vượt qua những địa hình hiểm trở, chiến đấu với kẻ thù hung dữ và vượt qua chướng ngại vật để sống sót và đạt điểm cao nhất. Trò chơi kết hợp cơ chế platformer cổ điển với các tính năng hiện đại như nút giao diện người dùng tương tác, hoạt ảnh mượt mà và âm thanh sống động.

# Công nghệ sử dụng
Trò chơi được xây dựng bằng C++ và sử dụng các thư viện SDL2 để xử lý đồ họa, âm thanh, và đầu vào người dùng:<br/>

-SDL2: Quản lý cửa sổ, render đồ họa, và xử lý sự kiện (phím, chuột).<br/>
-SDL2_image: Tải hình ảnh (PNG) cho sprite, background, và UI.<br/>
-SDL2_ttf: Hiển thị văn bản (ví dụ: điểm số, thông báo Pause/Game Over).<br/>
-SDL2_mixer: Phát nhạc nền và hiệu ứng âm thanh (như nhảy, tấn công).<br/>
-Tile Map System: Sử dụng file văn bản (.txt) để định nghĩa các bản đồ tile, hỗ trợ cuộn liên tục.

# Cách tải game
Tải game đã được nén thành file Zip tại đường dẫn sau: https://drive.google.com/drive/folders/171PBU7xCG6Dwi8uEEAM9gWBq93Yl-5x2?usp=sharing<br/>
Sau khi cài xong, giải nén file, mở twilight_run.exe và trải nghiệm.

# Tính năng chính
-Bản đồ cuộn liên tục: Người chơi di chuyển qua các bản đồ tile được tạo từ file .txt, với hiệu ứng chuyển đổi mượt mà. Tốc độ cuộn sẽ tăng lên khi người chơi đạt đến một số điểm nhất định.<br/>
-Nhân vật và chuyển động: Nhân vật có thể chạy, nhảy, và tấn công kẻ thù bằng đòn năng lượng.<br/>
-Kẻ thù: Kẻ thù di chuyển và bắn đạn về phía người chơi, hồi sinh sau một khoảng thời gian.<br/>
-Hệ thống điểm số: Điểm tăng theo thời gian sống sót, lưu điểm cao và hiển thị khi Game Over.<br/>
-Tạm dừng: Nút Pause cho phép tạm dừng game.<br/>
-Hiệu ứng Game Over: Phát hoạt hình chết trước khi hiển thị màn hình Game Over, với tùy chọn khởi động lại.<br/>
-Âm thanh: Nhạc nền liên tục, hiệu ứng âm thanh cho các hành động như nhảy, tấn công.

# Cơ chế
-Di chuyển bản đồ: Bản đồ cuộn tự động từ phải sang trái với tốc độ cố định (scrollSpeed). Người chơi phải di chuyển để tránh bị đẩy ra khỏi màn hình.<br/>
-Va chạm: Nhân vật và kẻ thù va chạm với tile map (dùng CollisionManager) để đứng trên nền, tránh rơi xuyên.<br/>
-Đạn của kẻ thù và đòn tấn công của người chơi gây sát thương khi va chạm.<br/>
-Kẻ thù tự động hồi sinh sau một khoảng thời gian (deathTimer).<br/>
-Hiệu ứng tạm dừng: Khi tạm dừng, mọi chuyển động (background, tile map, nhân vật, kẻ thù) dừng lại, hiển thị màn hình "Paused".<br/>
-Hoạt hình: Nhân vật có các trạng thái hoạt hình: chạy, nhảy, tấn công, và chết, được điều khiển bằng animationTimer và các frame tương ứng.<br/>
-Hoạt hình chết chạy hết trước khi hiển thị màn hình Game Over.

# Cách chơi
-Điều khiển nhân vật: Phím A và D: Di chuyển trái/phải.<br/>
-SPACE: Nhảy.<br/>
-Phím J: Kích hoạt đòn năng lượng để tấn công kẻ thù.<br/>
-Tạm dừng: Nhấn P hoặc nhấp nút Pause (góc trên bên phải) để tạm dừng game.<br/>
-Game Over và khởi động lại: Khi nhân vật va chạm với đạn kẻ thù, hoạt ảnh chết sẽ phát, sau đó hiển thị màn hình Game Over. Nhấn R để khởi động lại game, hoặc có thể tương tác với các nút trên giao diện.<br/>
-Mục tiêu: Sống sót lâu nhất có thể, tiêu diệt kẻ thù, và đạt điểm cao nhất.<br/>
