# Mô phỏng và phân tích chiến lược Baccarat bằng C++

## Giới thiệu

Baccarat là một trò chơi bài có ba kết quả chính: Player thắng, Banker thắng hoặc hòa Tie.  
Mỗi bên được chia bài và tính điểm theo chữ số hàng đơn vị. Các lá 10, J, Q, K được tính là 0 điểm, A được tính là 1 điểm.

Tuy luật chơi khá đơn giản, kết quả Baccarat vẫn phụ thuộc nhiều vào xác suất và cách rút bài. Vì vậy, nhóm chọn trò chơi này để mô phỏng bằng lập trình hướng đối tượng và phân tích các chiến lược đặt cược bằng dữ liệu.

Dự án chỉ dùng Baccarat như một bài toán mô phỏng xác suất, không nhằm khuyến khích cá cược.

## Lý do chọn đề tài

Nhóm chọn Baccarat vì trò chơi này có luật rõ ràng, dễ mô phỏng và phù hợp để áp dụng kiến thức OOP trong C++.

Thông qua chương trình, nhóm có thể mô phỏng nhiều ván chơi, thống kê kết quả và so sánh các chiến lược khác nhau. Từ đó, nhóm đánh giá chiến lược dựa trên số liệu thay vì chỉ dựa vào cảm tính.

## Nội dung mô phỏng

Chương trình mô phỏng các ván Baccarat với 8 bộ bài.  
Sau mỗi ván, kết quả được lưu lại để thống kê tỉ lệ thắng của Player, Banker và Tie.

Ngoài ra, chương trình còn tính các chỉ số như:

- Lời hoặc lỗ của từng chiến lược
- EV trên mỗi lần cược
- MaxDrawdown, tức mức sụt vốn lớn nhất trong quá trình chơi

EV giúp biết trung bình mỗi lần cược người chơi lời hay lỗ bao nhiêu.  
MaxDrawdown giúp đánh giá mức rủi ro của chiến lược.

## Các chiến lược được áp dụng

Nhóm chia chiến lược thành hai nhóm chính.

Chiến lược cược cố định:

- Luôn đặt Banker
- Luôn đặt Player
- Luôn đặt Tie

Chiến lược soi cầu:

- Cầu bệt: đặt theo bên đang thắng liên tiếp
- Cầu 1-1: đặt theo mẫu Player và Banker thắng luân phiên
- Cầu 1-2 hoặc 1-3: tìm mẫu lặp lại trong lịch sử ván trước
- Cầu nghiêng: đặt theo bên đang thắng áp đảo trong một số ván gần nhất
- Tổng hợp soi cầu: kết hợp nhiều loại cầu, nếu không có tín hiệu rõ thì mặc định đặt Banker

Các chiến lược soi cầu được đưa vào để kiểm chứng bằng mô phỏng, không xem là cách thắng chắc.

## Nếu là người chơi

Nếu là người chơi, lựa chọn hợp lý hơn là tránh đặt Tie quá nhiều vì tuy tiền thưởng cao nhưng xác suất xuất hiện thấp và rủi ro lớn.

Trong các lựa chọn cơ bản, Banker thường là cửa ít bất lợi hơn vì có tỉ lệ thắng nhỉnh hơn Player, dù khi thắng bị trừ hoa hồng.

Các chiến lược soi cầu có thể dùng để quan sát ngắn hạn, nhưng không nên phụ thuộc hoàn toàn. Khi chạy nhiều ván, EV của người chơi thường vẫn có xu hướng âm.

Vì vậy, người chơi nên quan tâm đến EV, MaxDrawdown và quản lý vốn thay vì chỉ nhìn vào chuỗi thắng thua trước đó.

## Nếu là chủ trò chơi

Nếu là chủ trò chơi, lợi thế đến từ luật trả thưởng và xác suất dài hạn.

Banker bị trừ hoa hồng khi thắng, Tie có xác suất thấp, còn Player và Banker đều có mức trả thưởng được thiết kế sao cho người chơi khó có lợi thế lâu dài.

Để quản lý trò chơi tốt, chủ cần giữ luật trả thưởng ổn định, giới hạn mức cược và đảm bảo số ván đủ lớn để lợi thế xác suất thể hiện rõ hơn.

## Kết luận

Qua mô phỏng, nhóm nhận thấy Baccarat là trò chơi có yếu tố ngẫu nhiên cao. Một số chiến lược soi cầu có thể cho kết quả tốt trong ngắn hạn, nhưng không đảm bảo hiệu quả dài hạn.

Kết quả quan trọng nhất của dự án là dùng chương trình để kiểm chứng các chiến lược bằng số liệu. Từ đó, nhóm thấy rằng không có chiến lược nào chắc chắn thắng, còn nhà cái vẫn có lợi thế khi xét trong thời gian dài.
