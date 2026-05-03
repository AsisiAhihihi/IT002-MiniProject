# DỰ ÁN: MÔ PHỎNG VÀ PHÂN TÍCH CHIẾN LƯỢC BACCARAT

## 0. Khái niệm Baccarat

Baccarat là một trò chơi bài trong đó kết quả mỗi ván thuộc một trong ba trường hợp:

- **Player thắng**
- **Banker thắng**
- **Tie**: hòa

Mỗi bên ban đầu được chia 2 lá bài. Tổng điểm của mỗi bên được tính bằng cách cộng điểm các lá bài rồi lấy chữ số hàng đơn vị.

Giá trị lá bài:

- A = 1 điểm
- 2 đến 9 = đúng giá trị trên lá
- 10, J, Q, K = 0 điểm

Nếu Player hoặc Banker đạt 8 hoặc 9 điểm từ 2 lá đầu tiên thì ván bài kết thúc. Nếu không, chương trình sẽ xét luật rút lá thứ 3 để xác định kết quả cuối cùng.

Dự án này chỉ dùng Baccarat làm bài toán mô phỏng xác suất và chiến lược bằng lập trình hướng đối tượng, không nhằm khuyến khích cá cược.

---

## 1. Tóm tắt nhanh: Nhóm đang làm gì?

Dự án này không phải là một trò chơi giao diện để người dùng bấm chơi trực tiếp. Nhóm xây dựng một chương trình mô phỏng tự động nhiều ván Baccarat bằng C++.

Thông qua mô phỏng, nhóm muốn trả lời các câu hỏi:

- Nếu là người chơi, nên chọn chiến lược nào để ít bất lợi hơn?
- Nếu là chủ trò chơi, vì sao luật trả thưởng và hoa hồng giúp duy trì lợi thế?
- Các kỹ thuật soi cầu có thật sự hiệu quả trong dài hạn không?

Chương trình sẽ mô phỏng nhiều ván bài, thống kê kết quả và so sánh các chiến lược thông qua các chỉ số như:

- Tỉ lệ thắng của Player, Banker, Tie
- Lời/lỗ của từng chiến lược
- EV/cược
- MaxDrawdown

---

## 2. Luật chơi được mô phỏng

Trong chương trình, Baccarat được mô phỏng với các luật cơ bản:

- Sử dụng 8 bộ bài.
- Mỗi ván chia bài cho Player và Banker.
- Điểm mỗi bên lấy theo tổng điểm modulo 10.
- Nếu có Natural 8 hoặc 9 thì dừng rút bài.
- Player rút lá thứ 3 nếu điểm ban đầu từ 0 đến 5.
- Banker rút lá thứ 3 theo bảng luật phụ thuộc vào điểm Banker và lá thứ 3 của Player.
- Nếu Shoe còn quá ít bài thì chương trình tạo lại Shoe mới.

Kết quả mỗi ván được lưu lại để dùng cho việc thống kê và kiểm tra chiến lược.

---

## 3. Thiết kế hướng đối tượng

Chương trình được chia thành nhiều lớp để thể hiện đúng tư duy OOP.

### Card

Đại diện cho một lá bài.

Nhiệm vụ chính:

- Lưu rank và suit của lá bài.
- Trả về giá trị điểm của lá bài trong Baccarat.

Ví dụ:

- A có giá trị 1
- 2 đến 9 giữ nguyên giá trị
- 10, J, Q, K có giá trị 0

---

### Shoe

Đại diện cho bộ bài dùng để chia trong Baccarat.

Nhiệm vụ chính:

- Tạo 8 bộ bài.
- Trộn bài ngẫu nhiên.
- Rút một lá bài.
- Kiểm tra số lá bài còn lại.

---

### Hand

Đại diện cho bài trên tay Player hoặc Banker.

Nhiệm vụ chính:

- Thêm lá bài vào tay.
- Tính tổng điểm.
- Xóa bài sau khi kết thúc ván.

---

### BaccaratGame

Đại diện cho một ván Baccarat.

Nhiệm vụ chính:

- Chia bài cho Player và Banker.
- Tính điểm ban đầu.
- Kiểm tra Natural 8/9.
- Xử lý luật rút lá thứ 3.
- Xác định kết quả thắng thua.

---

### Strategy

Lớp cha cho các chiến lược đặt cược.

Mỗi chiến lược con sẽ cài đặt hàm chọn cửa cược dựa trên lịch sử kết quả các ván trước.

---

## 4. Các chiến lược được mô phỏng

Nhóm chia chiến lược thành 2 nhóm chính:

---

## 4.1. Chiến lược cược cố định

Đây là nhóm chiến lược đơn giản nhất. Người chơi luôn đặt vào một cửa cố định, không quan tâm kết quả các ván trước.

Các chiến lược gồm:

- Luôn đặt Banker
- Luôn đặt Player
- Luôn đặt Tie

Nhóm chiến lược này được dùng làm mốc so sánh với các chiến lược soi cầu.

---

## 4.2. Chiến lược soi cầu

Các chiến lược soi cầu dùng lịch sử kết quả trước đó để đưa ra quyết định cho ván tiếp theo.

### Cầu bệt

Nếu một bên thắng liên tiếp từ 3 ván trở lên thì tiếp tục đặt theo bên đó.

Ví dụ:

```text
Banker - Banker - Banker
=> ván sau đặt Banker
