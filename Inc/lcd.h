/* lcd.h */
#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "stm32f4xx_hal.h"

// Fonksiyon Prototipleri
void LCD_Init(void);                      // LCD Başlatma
void LCD_SendCommand(uint8_t cmd);        // Komut Gönderme
void LCD_SendData(uint8_t data);          // Veri Gönderme
void LCD_Clear(void);                     // Ekran Temizleme
void LCD_SetCursor(uint8_t row, uint8_t col); // İmleç Konumlandırma
void LCD_Print(char *str);                // Metin Yazdırma

#endif /* INC_LCD_H_ */
