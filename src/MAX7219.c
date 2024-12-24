#include <avr/io.h>
#include "spi.h"
#include "max7219.h"

// MAX7219에 데이터 전송
void MAX7219_Write(uint8_t address, uint8_t data) {
    PORTB &= ~(1 << PB0); // CS/LOAD 핀 LOW (데이터 전송 시작)
    SPI_Write(address);   // 레지스터 주소 전송
    SPI_Write(data);      // 데이터 전송
    PORTB |= (1 << PB0);  // CS/LOAD 핀 HIGH (데이터 전송 종료)
}

// MAX7219 설정 초기화
void MAX7219_Init(void) {
    MAX7219_Write(0x0C, 0x01); 
    MAX7219_Write(0x09, 0x00); 
    MAX7219_Write(0x0A, 0x0F); // 밝기 설정
    MAX7219_Write(0x0B, 0x07); // 스캔 한도 설정 
    MAX7219_Write(0x0F, 0x00); // 디스플레이 테스트 비활성화
}

// 8x8 데이터를 MAX7219에 출력
void MAX7219_DisplayBitmap(uint64_t bitmap) {
    for (uint8_t row = 0; row < 8; row++) {
        uint8_t rowData = (bitmap >> (row * 8)) & 0xFF; // 8비트씩 분할
        MAX7219_Write(row + 1, rowData);               // 1번행부터 8번행까지 전송
    }
}
