#include <avr/io.h>
#include <avr/interrupt.h> 
#include <util/delay.h>

#include "spi.h"
#include "max7219.h"

// 이미지 데이터 배열
const uint64_t IMAGES[] = {
    0x7e7e181818187e7e, //각 패턴 64bit 비트맵 데이터
    0x1824428181996600,
    0x7effc3c3c3c3c3c3,
    0x003c427e00a54200,
    0x3c4299a581a5423c
};

const int IMAGES_LEN = sizeof(IMAGES)/sizeof(IMAGES[0]);

volatile uint8_t current_mode = 0; // 0-수동, 1-자동
volatile uint8_t image_index = 0;  // 현재 이미지 인덱스

// 스위치 초기화
void Switch_Init(void) {
    DDRE &= ~((1 << PE4) | (1 << PE5)); // PE4, PE5를 입력으로 설정
    PORTE |= (1 << PE4) | (1 << PE5);   // 내부 풀업 저항 활성화

    EICRB |= (1 << ISC41) | (1 << ISC51);
    EIMSK |= (1 << INT4) | (1 << INT5); 
}

// SW1(PE4) 인터럽트
ISR(INT4_vect) {
    _delay_ms(50); // 디바운싱
    if (!(PINE & (1 << PE4))) {  //눌리면
        current_mode = 0; // 수동 모드
        image_index = (image_index + 1) % IMAGES_LEN; // 다음 이미지로 index+1
        MAX7219_DisplayBitmap(IMAGES[image_index]);   // 해당 인덱스 이미지 출력
    }
}

// SW2(PE5) 인터럽트
ISR(INT5_vect) {
    _delay_ms(50); // 디바운싱
    if (!(PINE & (1 << PE5))) { //눌리면
        current_mode = 1; // 자동 모드
    }
}

int main(void) {
    SPI_Init();       // SPI 초기화
    MAX7219_Init();   // MAX7219 초기화
    Switch_Init();    // 스위치 및 인터럽트 초기화

    sei();           

    while (1) {
        // 자동 모드
        if (current_mode == 1) {
            image_index = (image_index + 1) % IMAGES_LEN; // 다음 이미지로
            MAX7219_DisplayBitmap(IMAGES[image_index]);   // 출력
            _delay_ms(1000); // 1초 대기
        }
    }
    return 0;
}