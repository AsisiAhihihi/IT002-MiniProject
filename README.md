Bạn có thể thêm file **README.md** này vào GitHub của nhóm:

````md
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
````

---

### Cầu 1-1

Nếu Player và Banker đang thắng luân phiên, chương trình dự đoán ván tiếp theo sẽ đổi bên so với ván gần nhất.

Ví dụ:

```text
Player - Banker - Player - Banker
=> ván sau đặt Player
```

---

### Cầu 1-2 / 1-3

Chương trình tìm các mẫu lặp lại dạng:

```text
Player - Banker - Banker
```

hoặc:

```text
Player - Banker - Banker - Banker
```

Nếu lịch sử gần nhất khớp mẫu, chương trình đặt theo kết quả tiếp theo của mẫu đó.

---

### Cầu nghiêng

Chương trình xét một số ván gần nhất. Nếu Player hoặc Banker thắng áp đảo rõ rệt thì đặt theo bên đang áp đảo.

Ví dụ:

```text
Trong 12 ván gần nhất:
Banker thắng 8 ván
Player thắng 4 ván

=> Banker đang áp đảo
=> ván sau đặt Banker
```

---

### Tổng hợp soi cầu

Chiến lược này kết hợp nhiều kỹ thuật soi cầu với thứ tự ưu tiên:

1. Cầu bệt
2. Cầu 1-1
3. Cầu 1-2 / 1-3
4. Cầu nghiêng
5. Nếu không có tín hiệu rõ thì mặc định đặt Banker

Chiến lược tổng hợp mô phỏng cách người chơi thực tế thường quan sát nhiều loại cầu trước khi quyết định.

---

## 5. Các chỉ số đánh giá

### EV/cược

EV là giá trị kỳ vọng, cho biết trung bình mỗi 1 đơn vị tiền cược người chơi lời hoặc lỗ bao nhiêu.

```text
EV > 0: người chơi có lợi thế
EV < 0: nhà cái có lợi thế
EV càng gần 0: chiến lược càng ít bất lợi
```

Ví dụ:

```text
EV/cược = -0.01
```

Nghĩa là trung bình mỗi lần đặt 1 đơn vị, người chơi lỗ khoảng 0.01 đơn vị.

---

### MaxDrawdown

MaxDrawdown là mức sụt vốn lớn nhất trong quá trình chơi.

Ví dụ:

```text
Vốn đang cao nhất: 1000
Sau đó giảm xuống: 700

MaxDrawdown = 300
```

MaxDrawdown càng cao thì chiến lược càng rủi ro, vì người chơi cần vốn lớn hơn để chịu được chuỗi thua.

---

## 6. Kết quả mô phỏng

Khi chạy mô phỏng nhiều ván, kết quả có thể thay đổi nhẹ do bài được trộn ngẫu nhiên.

Ví dụ cấu hình chạy:

```text
Số ván: 1,000,000
Số bộ bài: 8
Mỗi cược: 1 đơn vị
```

Chương trình sẽ in ra:

* Tần suất Player thắng
* Tần suất Banker thắng
* Tần suất Tie
* Lời/lỗ của từng chiến lược
* EV/cược
* MaxDrawdown

Kết quả mô phỏng thường cho thấy:

* Banker có tần suất thắng cao hơn Player một chút.
* Tie có tỉ lệ xuất hiện thấp nên rủi ro cao.
* Các chiến lược soi cầu có thể có hiệu quả trong một số đoạn ngắn, nhưng không đảm bảo lợi nhuận dài hạn.
* Khi chạy số ván lớn, EV của các chiến lược thường có xu hướng âm.

---

## 7. Nhận xét về chiến lược soi cầu

Các chiến lược soi cầu như cầu bệt, cầu 1-1, cầu 1-2/1-3 và cầu nghiêng chỉ dựa trên lịch sử kết quả trước đó.

Điều này giúp mô phỏng cách người chơi quan sát bàn chơi, nhưng không chứng minh rằng ván tiếp theo sẽ đi đúng theo mẫu.

Vì vậy, nhóm không xem soi cầu là cách thắng chắc. Trong dự án này, soi cầu chỉ được dùng như một nhóm chiến lược để kiểm chứng bằng mô phỏng.

---

## 8. Trả lời câu hỏi đề tài

### Nếu là người chơi

Không có chiến lược nào đảm bảo thắng chắc trong dài hạn.

Lựa chọn hợp lý hơn là:

* Tránh đặt Tie quá nhiều vì rủi ro cao.
* Ưu tiên Banker khi không có tín hiệu rõ.
* Không nên phụ thuộc hoàn toàn vào soi cầu.
* Cần quan tâm đến EV và MaxDrawdown thay vì chỉ nhìn số ván thắng.

---

### Nếu là chủ trò chơi

Chủ trò chơi có lợi thế vì:

* Luật trả thưởng được thiết kế để EV của người chơi thường âm.
* Cược Banker bị trừ hoa hồng khi thắng.
* Cược Tie trả thưởng cao nhưng xác suất xuất hiện thấp.
* Khi số ván đủ lớn, lợi thế xác suất của nhà cái thể hiện rõ hơn.

Vì vậy, chủ trò chơi cần duy trì luật trả thưởng chuẩn, giới hạn mức cược và quản lý vốn để giảm rủi ro.

---

## 9. Cách chạy chương trình

### Cách 1: Chạy bằng Code::Blocks

Mở file project:

```text
Baccarat_OOP.cbp
```

Sau đó chọn:

```text
Build and Run
```

---

### Cách 2: Chạy bằng g++

Nếu dùng terminal, có thể biên dịch bằng lệnh:

```bash
g++ main.cpp Card.cpp Shoe.cpp Hand.cpp BaccaratGame.cpp Strategy.cpp -o Baccarat_OOP
```

Sau đó chạy:

```bash
./Baccarat_OOP
```

---

## 10. Cấu trúc thư mục

```text
Baccarat_OOP/
│
├── main.cpp
├── Card.h
├── Card.cpp
├── Shoe.h
├── Shoe.cpp
├── Hand.h
├── Hand.cpp
├── BaccaratGame.h
├── BaccaratGame.cpp
├── Strategy.h
├── Strategy.cpp
├── Baccarat_OOP.cbp
├── So_do_lop_Baccarat.png
└── README.md
```

---

## 11. Hạn chế của dự án

Dự án vẫn còn một số hạn chế:

* Kết quả có thể dao động do yếu tố ngẫu nhiên.
* Chưa có giao diện người dùng.
* Chưa xuất dữ liệu ra file CSV.
* Chưa vẽ biểu đồ trực tiếp từ chương trình.
* Chưa mô phỏng nhiều kiểu quản lý vốn khác nhau.

---

## 12. Hướng phát triển

Trong tương lai có thể mở rộng thêm:

* Xuất kết quả ra file CSV.
* Vẽ biểu đồ EV và MaxDrawdown.
* Thêm chiến lược quản lý vốn.
* Cho phép người dùng chọn số ván mô phỏng.
* Tạo giao diện đơn giản để chọn chiến lược.
* So sánh kết quả giữa chạy ngắn hạn và dài hạn.

---

## 13. Kết luận

Dự án đã áp dụng lập trình hướng đối tượng để mô phỏng trò chơi Baccarat và phân tích các chiến lược đặt cược.

Thông qua mô phỏng, nhóm nhận thấy rằng các chiến lược soi cầu có thể tạo cảm giác hiệu quả trong ngắn hạn, nhưng không đảm bảo lợi nhuận dài hạn.

Kết quả quan trọng nhất của dự án không phải là tìm ra cách thắng chắc, mà là dùng dữ liệu mô phỏng để đánh giá khách quan từng chiến lược thông qua EV và MaxDrawdown.

```

