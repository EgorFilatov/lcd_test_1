#include "lcd_i2c_lib.hpp"

uint8_t i2cLcdState { };

char *recodeCyr(char *charCyr) {
	if (*charCyr == 'А') {
		*charCyr = 'A';
	} else if (*charCyr == 'а') {
		*charCyr = 'a';
	} else if (*charCyr == 'Б') {
		*charCyr = 0b10100000;
	} else if (*charCyr == 'б') {
		*charCyr = 0b10110010;
	} else if (*charCyr == 'В') {
		*charCyr = 'B';
	} else if (*charCyr == 'в') {
		*charCyr = 0b10110011;
	} else if (*charCyr == 'Г') {
		*charCyr = 0b10100001;
	} else if (*charCyr == 'г') {
		*charCyr = 0b10110100;
	} else if (*charCyr == 'Д') {
		*charCyr = 0b11100000;
	} else if (*charCyr == 'д') {
		*charCyr = 0b11100011;
	} else if (*charCyr == 'Е') {
		*charCyr = 'E';
	} else if (*charCyr == 'е') {
		*charCyr = 'e';
	} else if (*charCyr == 'Ж') {
		*charCyr = 0b10100011;
	} else if (*charCyr == 'ж') {
		*charCyr = 0b10110110;
	} else if (*charCyr == 'З') {
		*charCyr = 0b10100100;
	} else if (*charCyr == 'з') {
		*charCyr = 0b10110111;
	} else if (*charCyr == 'И') {
		*charCyr = 0b10100101;
	} else if (*charCyr == 'и') {
		*charCyr = 0b10111000;
	} else if (*charCyr == 'Й') {
		*charCyr = 0b10100110;
	} else if (*charCyr == 'й') {
		*charCyr = 0b10111001;
	} else if (*charCyr == 'К') {
		*charCyr = 'K';
	} else if (*charCyr == 'к') {
		*charCyr = 0b10111010;
	} else if (*charCyr == 'Л') {
		*charCyr = 0b10100111;
	} else if (*charCyr == 'л') {
		*charCyr = 0b10111011;
	} else if (*charCyr == 'М') {
		*charCyr = 'M';
	} else if (*charCyr == 'м') {
		*charCyr = 0b10111100;
	} else if (*charCyr == 'Н') {
		*charCyr = 'H';
	} else if (*charCyr == 'н') {
		*charCyr = 0b10111101;
	} else if (*charCyr == 'О') {
		*charCyr = 'O';
	} else if (*charCyr == 'о') {
		*charCyr = 'o';
	} else if (*charCyr == 'П') {
		*charCyr = 0b10101000;
	} else if (*charCyr == 'п') {
		*charCyr = 0b10111110;
	} else if (*charCyr == 'Р') {
		*charCyr = 'P';
	} else if (*charCyr == 'р') {
		*charCyr = 'p';
	} else if (*charCyr == 'С') {
		*charCyr = 'C';
	} else if (*charCyr == 'с') {
		*charCyr = 'c';
	} else if (*charCyr == 'Т') {
		*charCyr = 'T';
	} else if (*charCyr == 'т') {
		*charCyr = 0b10111111;
	} else if (*charCyr == 'У') {
		*charCyr = 0b10101001;
	} else if (*charCyr == 'у') {
		*charCyr = 'y';
	} else if (*charCyr == 'Ф') {
		*charCyr = 0b10101010;
	} else if (*charCyr == 'ф') {
		*charCyr = 0b11100100;
	} else if (*charCyr == 'Х') {
		*charCyr = 'X';
	} else if (*charCyr == 'х') {
		*charCyr = 'x';
	} else if (*charCyr == 'Ц') {
		*charCyr = 0b11100001;
	} else if (*charCyr == 'ц') {
		*charCyr = 0b11100101;
	} else if (*charCyr == 'Ч') {
		*charCyr = 0b10101011;
	} else if (*charCyr == 'ч') {
		*charCyr = 0b11000000;
	} else if (*charCyr == 'Ш') {
		*charCyr = 0b10101100;
	} else if (*charCyr == 'ш') {
		*charCyr = 0b11000001;
	} else if (*charCyr == 'Щ') {
		*charCyr = 0b11100010;
	} else if (*charCyr == 'щ') {
		*charCyr = 0b11100110;
	} else if (*charCyr == 'ъ') {
		*charCyr = 0b11000010;
	} else if (*charCyr == 'ы') {
		*charCyr = 0b11000011;
	} else if (*charCyr == 'ь') {
		*charCyr = 0b11000100;
	} else if (*charCyr == 'Э') {
		*charCyr = 0b10101111;
	} else if (*charCyr == 'э') {
		*charCyr = 0b11000101;
	} else if (*charCyr == 'Ю') {
		*charCyr = 0b10110000;
	} else if (*charCyr == 'ю') {
		*charCyr = 0b11000110;
	} else if (*charCyr == 'Я') {
		*charCyr = 0b10110001;
	} else if (*charCyr == 'я') {
		*charCyr = 0b11000111;
	}

	return charCyr;
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

void sendLcdByte(uint8_t bite, uint8_t rs, I2CSettings settings) {
	uint8_t upperBite = bite & 0xF0;
	uint8_t lowerBite = (bite << 4) & 0xF0;

	uint8_t ByteArr[4] {};

	ByteArr[0] = upperBite | rs | LED | EN;
	ByteArr[1] = 0;
	ByteArr[2] = lowerBite | rs | LED | EN;
	ByteArr[3] = 0;

	i2cLcdState = 1;
	HAL_I2C_Master_Transmit_DMA(settings.hi2c, settings.i2cAddr, ByteArr, 4);
	while (i2cLcdState == 1) {
	}
}

void sendLcdStr(char *string, I2CSettings settings) {
	while (*string) {
		char stringCopy = *string;
		stringCopy = *recodeCyr(&stringCopy);
		sendLcdByte(uint8_t(stringCopy), 1, settings);
		++string;
	}
}


void sendLcdStrAB(char *string, I2CSettings settings, uint8_t a, uint8_t b) {
	for (uint8_t i = a; i < b; ++i) {
		char stringCopy = *string;
		stringCopy = *recodeCyr(&stringCopy);
		sendLcdByte(uint8_t(stringCopy), 1, settings);
		++string;
	}
}

void clearLcd(I2CSettings settings) {
	uint8_t ByteArr[4] { 4, 0, 20, 0 };

	i2cLcdState = 1;
	HAL_I2C_Master_Transmit_DMA(settings.hi2c, settings.i2cAddr, ByteArr, 4);
	while (i2cLcdState == 1) {
	}
}

void setDdramAddr(uint8_t ddramAddr, I2CSettings settings) {
	uint8_t upperBite = (ddramAddr | 0x80) & 0xF0;
	uint8_t lowerBite = (ddramAddr << 4) & 0xF0;

	uint8_t ByteArr[4]{};

	ByteArr[0] = upperBite | EN;
	ByteArr[1] = 0;
	ByteArr[2] = lowerBite | EN;
	ByteArr[3] = 0;

	i2cLcdState = 1;
	HAL_I2C_Master_Transmit_DMA(settings.hi2c, settings.i2cAddr, ByteArr, 4);
	while (i2cLcdState == 1) {
	}
}

void initLcd(I2CSettings settings) {
	HAL_Delay(50);

	sendLcdByte(0b00110000, 0, settings);   // 8ми битный интерфейс
	HAL_Delay(40);

	sendLcdByte(0b00000010, 0, settings);   // установка курсора в начале строки
	HAL_Delay(40);

	sendLcdByte(0b00001100, 0, settings);   // нормальный режим работы, выкл курсор
	HAL_Delay(40);

	sendLcdByte(0b00000100, 0, settings);
	HAL_Delay(40);

	sendLcdByte(0b00000001, 0, settings);   // очистка дисплея
	HAL_Delay(2);
}
