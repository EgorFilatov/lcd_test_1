#ifndef INC_LCD_I2C_LIB_H_
#define INC_LCD_I2C_LIB_H_

#include <main.h>
#include <unordered_map>

#define EN  0b00000100 // Пин EN
#define LED 0b00001000 // Пин включения светодиодной подсветки
#define DDRAM_ADDR_COMMAND 0b10000000 // Команда записи адреса DDRAM памяти в адресный указатель

struct I2CSettings {
	I2C_HandleTypeDef *hi2c;
	uint8_t i2cAddr;
};

/* Фунуция кодирования кириллических символов
 ******************************************************************************
 * cyrillic_character- символ для кодирования
 */
char *recodeCyr(char *charCyr);


/* Фунуция поиска адреса i2c дисплея */
void ScanI2C(I2C_HandleTypeDef *hi2c);


void sendLcdInstruction(uint8_t instruction, I2CSettings settings);
void sendLcdChar(uint8_t character, uint8_t ddramAddr, I2CSettings settings);
void sendLcdByte(uint8_t character, I2CSettings settings);


/* Фунуция отправки строки
 ******************************************************************************
 * str- отправляемая строка
 * cyrillic = 0- нет кириллических символов, cyrillic = 1- есть кириллические символы
 */
void sendLcdStr(char *string, uint8_t ddramAddr, I2CSettings settings);
void sendLcdStrAB(char *string, uint8_t a, uint8_t b, uint8_t ddramAddr, I2CSettings settings);


/* Фунуция очистки дисплея */
void clearLcd(I2CSettings settings);

/* Фунуция очистки символа на дисплее */
void clearChar(uint8_t charPos, I2CSettings settings);


/* Фунуция записи адреса DDRAM памяти в адресный указатель
 ******************************************************************************
 * ddram_addr- адрес памяти
 */
void setDdramAddr(uint8_t ddramAddr, I2CSettings settings);


/* Фунуция инициализации дисплея */
void lcdInit(I2CSettings settings);

#endif
