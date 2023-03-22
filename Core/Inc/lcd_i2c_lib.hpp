#include "main.hpp"

#ifndef INC_LCD_I2C_LIB_HPP_
#define INC_LCD_I2C_LIB_HPP_

#define EN  0b00000100 // ��� EN
#define LED 0b00001000 // ��� ��������� ������������ ���������
#define DDRAM_ADDR_COMMAND 0b10000000 // ������� ������ ������ DDRAM ������ � �������� ���������

struct I2CSettings {
	I2C_HandleTypeDef *hi2c;
	uint8_t i2cAddr;
};

/* ������� ����������� ������������� ��������
 ******************************************************************************
 * cyrillic_character- ������ ��� �����������
 */
char *recodeCyr(char *charCyr);


/* ������� ������ ������ i2c ������� */
void ScanI2C(I2C_HandleTypeDef *hi2c);


/* ������� �������� ������ �����
 ******************************************************************************
 * bite- ������������ ����
 * rs = 0- �������� ��������, rs = 1- �������� �������
 */
void sendLcdByte(uint8_t bite, uint8_t rs, I2CSettings settings); // ������� ������ ������ i2c ������


/* ������� �������� ������
 ******************************************************************************
 * str- ������������ ������
 * cyrillic = 0- ��� ������������� ��������, cyrillic = 1- ���� ������������� �������
 */
void sendLcdStr(char *string, I2CSettings settings);
void sendLcdStrAB(char *string, I2CSettings settings, uint8_t a, uint8_t b);


/* ������� ������� ������� */
void clearLcd(I2CSettings settings);


/* ������� ������ ������ DDRAM ������ � �������� ���������
 ******************************************************************************
 * ddram_addr- ����� ������
 */
void setDdramAddr(uint8_t ddramAddr, I2CSettings settings);


/* ������� ������������� ������� */
void initLcd(I2CSettings settings);

#endif
