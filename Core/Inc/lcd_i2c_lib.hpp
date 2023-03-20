#include "main.hpp"

#ifndef INC_LCD_I2C_LIB_HPP_
#define INC_LCD_I2C_LIB_HPP_

#define EN  0b00000100 // Пин EN
#define LED 0b00001000 // Пин включения светодиодной подсветки
#define DDRAM_ADDR_COMMAND 0b10000000 // Команда записи адреса DDRAM памяти в адресный указатель

struct I2CSettings {
	I2C_HandleTypeDef *hi2c;
	uint8_t i2cAddr;

	//I2CSettings(I2C_HandleTypeDef *hi2c, uint8_t lcdAddr);
};

/* Фунуция кодирования кириллических символов
 ******************************************************************************
 * cyrillic_character- символ для кодирования
 */
char* cyrillic_characters_encoding(char *cyrillic_character);


/* Фунуция поиска адреса i2c дисплея */
void i2c_addr_scan(I2C_HandleTypeDef *hi2c);


/* Фунуция отправки одного байта
 ******************************************************************************
 * bite- отправляемый байт
 * rs = 0- отправка настроек, rs = 1- отправка символа
 */
void lcd_send_bite(uint8_t bite, uint8_t rs, I2CSettings settings); // Фунуция поиска адреса i2c исплея


/* Фунуция отправки строки
 ******************************************************************************
 * str- отправляемая строка
 * cyrillic = 0- нет кириллических символов, cyrillic = 1- есть кириллические символы
 */
void lcd_send_string(char *str,uint8_t cyrillic, I2CSettings settings);


/* Фунуция очистки дисплея */
void lcd_clear(I2CSettings settings);


/* Фунуция записи адреса DDRAM памяти в адресный указатель
 ******************************************************************************
 * ddram_addr- адрес памяти
 */
void ddram_set_addr(uint8_t ddram_addr, I2CSettings settings);


/* Фунуция инициализации дисплея */
void lcd_initialization(I2CSettings settings);

#endif
