# HANGMAN
 - Họ và tên: Võ Huy Hoàng
 - MSV: 24021493
 - Đây là tựa game HangMan nổi tiếng, nhiệm vụ của bạn trong trò chơi này là đoán (chọn) các chữ cái từ những chữ cái được hiển thị ở trên màn hình để ghép thành 1 cụm từ – từ vựng có nghĩa. Người chơi được phép đoán sai tối đa 7 lượt, với mỗi lần đoán sai thì hình vẽ "người treo cổ" sẽ dần hoàn thiện. Sau 7 lần đoán sai thì hình vẽ "người treo cổ" được hoàn thành, đồng nghĩa với việc bạn thua cuộc.
 - Số điểm mong muốn: 8.5 - 9
 - Game tự viết có đồ họa, âm thanh, animation, hiệu ứng. Được phát triển dựa trên các slide bài giảng về game HangMan của giảng viên và có sự cải thiện đáng kể về mặt đồ họa, các chức năng. Các từ khóa được lấy ngẫu nhiên từ file words.txt gồm 200 từ. Các chức năng do tự em học và hoàn thiện, có sử dụng AI hỗ trợ mỗi khi gặp khó khăn trong việc phát hiện lỗi hoặc không hiểu chỗ nào hay một số khái niệm mới. Sử dụng AI code khoảng 30%. Animation, quản lí FPS cho game mượt mà, hiệu ứng khi di chuột đều do em được AI hướng dẫn.
 1. Các hàm trong file graphics.cpp được tham khảo từ code của cô Châu trên Github của cô. Các chức năng khác đều do em tự viết cùng với sự hỗ trợ của AI mỗi khi gặp lỗi, khó khăn khi code.
 2. Em có tham khảo về cách hoạt động của SDL2 trên https://lazyfoo.net/tutorials/SDL/index.php; âm thanh được lấy từ https://pixabay.com/; hình nền của game được lấy từ Google; Logo game, hình ảnh người treo cổ và animation khi thắng hoặc thua đều do em tự thiết kế bằng canva; các button trong game được em tham khảo từ https://poki.com/en/g/hangman 
 3. Dùng các lệnh vẽ hình
 4. Có Texture
 5. Có Background
 6. Có Event bàn phím
 7. Có Event chuột
 8. Có Animation (hoạt hình)
 9. Có Xử lý va chạm (giữa chuột và các nút chức năng)
 10. Có tính điểm
 11. Có tính highscore
 12. Có sound effect
 13. Có tắt/bật âm thanh
 14. Có background music
 15. Có Font
 16. Có màn hình chính
 17. Có Pause/Resume/Replay/Home
 18. Không có trạng thái máu
 19. Có hiệu ứng zoom nhẹ khi di chuột qua các button trong game
