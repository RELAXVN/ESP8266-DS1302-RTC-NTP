# ESP8266-DS1302-RTC-NTP
-Make clock using Esp8266 with ds1302 and oled 0.96. First ESP8266 get NTP time and write to DS1302. Then just get from DS1302 to display.

-Tạo một đồng hồ bằng esp8266 với ds1302 và oled 0.96. Lần đầu ESP8266 lấy thời gian NTP và ghi vào DS1302. Sau đó chỉ lấy từ DS1302 để hiển thị.


-Copy the DS1302 folder to the libraries.

-Sao chép thư mục DS1302 vào thư thư mục libraries.

-You can edit the code to match your region's time at the // NTP line.

|   device   | ESP8266 pin |
| ---------- | ----------- |
| DS1302 CLK | D5 (GPIO14) |
| DS1302 DAT | D6 (GPIO12) |
| DS1302 RST | D7 (GPIO13) |
| OLED SDA   | D2 (GPIO4)  |
| OLED SCL   | D1 (GPIO5)  |

