#include <avr/io.h>

void SPI_Init(void) {
    DDRB |= (1 << PB2) | (1 << PB1) | (1 << PB0); // MOSI(PB2), SCK(PB1), SS(PB0) 출력
    DDRB &= ~(1 << PB3);                         // MISO(PB3) 입력 -따로 사용x

    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0); // SPI 활성화, 마스터 모드, fosc/16
    SPSR &= ~(1 << SPI2X); 
}

void SPI_Write(uint8_t data) {
    SPDR = data;                   // 데이터 전송 시작
    while (!(SPSR & (1 << SPIF))); // 전송 완료 대기
}
