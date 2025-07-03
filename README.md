Rogue Slide on STM32F429 Discovery

Mô tả dự án

Dự án hướng đến việc xây dựng trò chơi Rogue Slide trên nền tảng phần cứng nhúng sử dụng vi điều khiển STM32F429ZiT6, kết hợp với màn hình LCD và hệ điều hành thời gian thực FreeRTOS.

Mục tiêu là tái hiện một trò chơi dạng phiêu lưu chiến đấu kết hợp cơ chế trượt kiểu 2048, nơi người chơi di chuyển, tấn công và vượt qua các màn chơi ngày càng khó.

Dự án nhằm rèn luyện kỹ năng lập trình nhúng , quản lý thực thể động và giao tiếp phần cứng.

🛠 Công cụ phát triển

Tool Version Mục đích

STM32CubeMX 6.x.x Cấu hình Clock, GPIO, Middleware

STM32CubeIDE 1.18.1 IDE biên dịch mã cho STM32F429

TouchGFX Designer 4.25 Thiết kế giao diện đồ họa

ST-Link Utility Mới nhất Flash firmware vào board

GCC ARM Embedded Tích hợp sẵn Trình biên dịch trong STM32CubeIDE

FreeRTOS: v10.6.1 (CMSIS-RTOS V2)

Git: v2.30+

⚙ Hướng dẫn cài đặt & build

Bước 1: Cài đặt Tool Cài đặt STM32CubeIDE: https://www.st.com/en/development-tools/stm32cubeide.html

Cài đặt TouchGFX Designer: https://www.st.com/en/development-tools/touchgfx.html

Clone repository: git clone https://github.com/DangZz07/STM32F429ZIT6_Game2048.git

Bước 2: Mở Project

Mở STM32CubeIDE.

Chọn File > Import > Existing Project into Workspace.

Chọn thư mục chứa project.

Bước 3: Build & Flash

Click Build Project (Ctrl + B).

Kết nối STM32F429 Discovery qua USB.

Nhấn Run > Debug để nạp chương trình.
