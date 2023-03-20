#include "lcd_i2c_lib.hpp"

uint8_t lcd_i2c_state { };

/*
I2CSettings::I2CSettings(I2C_HandleTypeDef *hi2c, uint8_t lcdAddr) {
	this->hi2c = hi2c;
	this->lcdAddr = lcdAddr;
}
*/

char *cyrillic_characters_encoding(char *cyrillic_character) {
	if (*cyrillic_character == '�') {
		*cyrillic_character = 'A';
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 'a';
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 0b10100000;
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 0b10110010;
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 'B';
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 0b10110011;
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 0b10100001;
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 0b10110100;
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 0b11100000;
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 0b11100011;
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 'E';
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 'e';
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 0b10100011;
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 0b10110110;
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 0b10100100;
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 0b10110111;
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 0b10100101;
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 0b10111000;
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 0b10100110;
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 0b10111001;
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 'K';
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 0b10111010;
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 0b10100111;
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 0b10111011;
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 'M';
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 0b10111100;
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 'H';
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 0b10111101;
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 'O';
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 'o';
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 0b10101000;
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 0b10111110;
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 'P';
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 'p';
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 'C';
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 'c';
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 'T';
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 0b10111111;
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 0b10101001;
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 'y';
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 0b10101010;
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 0b11100100;
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 'X';
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 'x';
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 0b11100001;
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 0b11100101;
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 0b10101011;
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 0b11000000;
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 0b10101100;
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 0b11000001;
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 0b11100010;
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 0b11100110;
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 0b11000010;
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 0b11000011;
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 0b11000100;
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 0b10101111;
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 0b11000101;
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 0b10110000;
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 0b11000110;
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 0b10110001;
	} else if (*cyrillic_character == '�') {
		*cyrillic_character = 0b11000111;
	}

	return cyrillic_character;
}


/*
void i2c_addr_scan(I2C_HandleTypeDef *hi2c) {
	for (uint16_t i = 0; i < 128; i++) {
		if ((HAL_I2C_IsDeviceReady(hi2c, i << 1, 1, HAL_MAX_DELAY))
				== HAL_OK) {
			addr = i;
			i = 129;
		}
	}
}
*/

void lcd_send_bite(uint8_t bite, uint8_t rs, I2CSettings settings) {
	uint8_t up = bite & 0xF0;
	uint8_t lo = (bite << 4) & 0xF0;

	uint8_t data_arr[4] {};

	data_arr[0] = up | rs | LED | EN;
	data_arr[1] = 0;
	data_arr[2] = lo | rs | LED | EN;
	data_arr[3] = 0;

	lcd_i2c_state = 1;
	HAL_I2C_Master_Transmit_DMA(settings.hi2c, settings.i2cAddr, data_arr, 4);
	while (lcd_i2c_state == 1) {
	}
}

void lcd_send_string(char *str,uint8_t cyrillic, I2CSettings settings) {
	while (*str) {
		if (cyrillic == 1) {
			*str = *cyrillic_characters_encoding(&*str);
		}
		lcd_send_bite((uint8_t) (*str), 1, settings);
		str++;
	}
}

void lcd_clear(I2CSettings settings) {
	uint8_t data_arr[4] { 4, 0, 20, 0 };

	lcd_i2c_state = 1;
	HAL_I2C_Master_Transmit_DMA(settings.hi2c, settings.i2cAddr, data_arr, 4);
	while (lcd_i2c_state == 1) {
	}
}

void ddram_set_addr(uint8_t ddram_addr, I2CSettings settings) {
	uint8_t up = (ddram_addr | 0x80) & 0xF0;
	uint8_t lo = (ddram_addr << 4) & 0xF0;

	uint8_t data_arr[4]{};

	data_arr[0] = up | EN;
	data_arr[1] = 0;
	data_arr[2] = lo | EN;
	data_arr[3] = 0;

	lcd_i2c_state = 1;
	HAL_I2C_Master_Transmit_DMA(settings.hi2c, settings.i2cAddr, data_arr, 4);
	while (lcd_i2c_state == 1) {
	}
}

void lcd_initialization(I2CSettings settings) {
	HAL_Delay(50);

	lcd_send_bite(0b00110000, 0, settings);   // 8�� ������ ���������
	HAL_Delay(40);

	lcd_send_bite(0b00000010, 0, settings);   // ��������� ������� � ������ ������
	HAL_Delay(40);

	lcd_send_bite(0b00001100, 0, settings);   // ���������� ����� ������, ���� ������
	HAL_Delay(40);

	lcd_send_bite(0b00000001, 0, settings);   // ������� �������
	HAL_Delay(2);
}
