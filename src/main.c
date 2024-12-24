/*  16 Bit Timer 실습 - RGB LED 색상 변경
    - 16 Bit Timer 1번을 이용하여 RGB LED 색상 변경
    - RGB LED의 색상을 부드럽게 빨 -> 초 -> 파 -> 빨로 변경
*/
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/iom128.h>
#include <util/delay.h>
#define MODE_R 1
#define MODE_G 2
#define MODE_B 4

unsigned char number[10] = {
    0x3F, 0x06, 0x5B, 0x4F, 0x66, 
    0x6D, 0x7D, 0x07, 0x7F, 0x6F}; // 0 ~ 9 숫자 패턴
unsigned char dot_number[10] = {
    0xBF, 0x86, 0xDB, 0xCF, 0xE6, 
    0xED, 0xFD, 0xA7, 0xFF, 0xEF}; // 0 ~ 9 숫자 패턴 WITH .
unsigned char fnd_select[4] = {0x08, 0x04, 0x02, 0x01}; // FND 선택 패턴

volatile int time=0;

ISR(TIMER1_COMPA_vect) {
    time++;
}

// ISR(INT4_vect) {

// }

// ISR(INT5_vect) {
//     time=0;
// }



int main(void) {
    TCCR1A |= (1 << WGM10) | (1 << COM1A1) | (1 << COM1B1) | (1 << COM1C1);
    TCCR1B |= (1 << CS11);
    OCR1A = 1562.5;


    DDRC = 0xFF; //fnd 출력 설정 c
    DDRG = 0x0F; //fnd 자리 설정 g
    DDRE = 0x00;   // 포트 E를 입력으로 설정

    while(1) {

        PORTC=number[time%10];
        PORTG=fnd_select[0];
        _delay_ms(1);

        PORTC=number[(time/10)%10];
        PORTG=fnd_select[1];
        _delay_ms(1);

        PORTC=dot_number[(time/100)%10];
        PORTG=fnd_select[2];
        _delay_ms(1);

        PORTC=number[(time/1000)%10];
        PORTG=fnd_select[3];
        _delay_ms(1);
    }
}