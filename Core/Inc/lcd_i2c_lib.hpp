#include "main.hpp"

#ifndef INC_LCD_I2C_LIB_HPP_
#define INC_LCD_I2C_LIB_HPP_

#define EN  0b00000100 // ��� EN
#define LED 0b00001000 // ��� ��������� ������������ ���������
#define DDRAM_ADDR_COMMAND 0b10000000 // ������� ������ ������ DDRAM ������ � �������� ���������

#define LCD_ADDR (0x27 << 1) // ����� i2c �������

/* ������� ����������� ������������� ��������
 ******************************************************************************
 * cyrillic_character- ������ ��� �����������
 */
char* cyrillic_characters_encoding(char *cyrillic_character);


/* ������� ������ ������ i2c ������� */
void i2c_addr_scan(I2C_HandleTypeDef *hi2c);


/* ������� �������� ������ �����
 ******************************************************************************
 * bite- ������������ ����
 * rs = 0- �������� ��������, rs = 1- �������� �������
 */
void lcd_send_bite(uint8_t bite, uint8_t rs, I2C_HandleTypeDef *hi2c); // ������� ������ ������ i2c ������


/* ������� �������� ������
 ******************************************************************************
 * str- ������������ ������
 * cyrillic = 0- ��� ������������� ��������, cyrillic = 1- ���� ������������� �������
 */
void lcd_send_string(char *str,uint8_t cyrillic, I2C_HandleTypeDef *hi2c);


/* ������� ������� ������� */
void lcd_clear(I2C_HandleTypeDef *hi2c);


/* ������� ������ ������ DDRAM ������ � �������� ���������
 ******************************************************************************
 * ddram_addr- ����� ������
 */
void ddram_set_addr(uint8_t ddram_addr, I2C_HandleTypeDef *hi2c);


/* ������� ������������� ������� */
void lcd_initialization(I2C_HandleTypeDef *hi2c);

#endif