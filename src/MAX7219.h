#ifndef MAX7219_H
#define MAX7219_H

#include <stdint.h>

// MAX7219에 데이터 전송 함수
void MAX7219_Write(uint8_t address, uint8_t data);

// MAX7219 초기화 함수
void MAX7219_Init(void);

// 8x8 비트맵 출력 함수
void MAX7219_DisplayBitmap(uint64_t bitmap);

#endif // MAX7219_H
