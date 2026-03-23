#include <stdint.h>

// 1. ĐỊNH NGHĨA ĐỊA CHỈ THANH GHI (Manual Mapping)
#define RCC_BASE      0x40023800
#define RCC_AHB1ENR   (*(volatile uint32_t *)(RCC_BASE + 0x30))
#define RCC_APB1ENR   (*(volatile uint32_t *)(RCC_BASE + 0x40))

#define GPIOA_BASE    0x40020000
#define GPIOA_MODER   (*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_AFRL    (*(volatile uint32_t *)(GPIOA_BASE + 0x20))

#define USART2_BASE   0x40004400
#define USART2_SR     (*(volatile uint32_t *)(USART2_BASE + 0x00))
#define USART2_DR     (*(volatile uint32_t *)(USART2_BASE + 0x04))
#define USART2_BRR    (*(volatile uint32_t *)(USART2_BASE + 0x08))
#define USART2_CR1    (*(volatile uint32_t *)(USART2_BASE + 0x0C))

// 2. HÀM GỬI UART TRẦN (No Library)
void uart_print(char *c) {
    while (*c) {
        while (!(USART2_SR & (1 << 7))); // Chờ thanh ghi đệm trống (TXE)
        USART2_DR = (*c & 0xFF);
        c++;
    }
}

// 3. MAIN - ĐIỀU KHIỂN PHẦN CỨNG
void main_os(void) {
    // Bật Clock cho GPIOA và USART2
    RCC_AHB1ENR |= (1 << 0);  // Enable GPIOA clock
    RCC_APB1ENR |= (1 << 17); // Enable USART2 clock

    // Cấu hình PA2 (TX) là Alternate Function
    GPIOA_MODER |= (2 << 4);  
    GPIOA_AFRL  |= (7 << 8);  // AF7 cho UART2

    // Cấu hình Baudrate 115200 (Với PCLK1 = 16MHz mặc định khi reset)
    USART2_BRR = 0x008B; 
    USART2_CR1 |= (1 << 3) | (1 << 13); // TE (Transmit Enable) và UE (UART Enable)

    uart_print("Hello World! This is my own OS from scratch.\r\n");

    while(1); // Treo máy ở đây
}

// 4. VECTOR TABLE & STARTUP
void Reset_Handler(void) {
    // Trong thực tế, tại đây bạn cần copy .data từ Flash sang RAM 
    // và xóa .bss. Nhưng để "Hello World" chạy ngay, ta nhảy thẳng vào main.
    main_os();
}

// Vector Table: Bắt buộc phải có 2 giá trị đầu tiên này
__attribute__((section(".isr_vector")))
uint32_t *vector_table[] = {
    (uint32_t *)0x20018000, // 1. Stack Pointer (Top of RAM)
    (uint32_t *)Reset_Handler // 2. Reset Handler
};