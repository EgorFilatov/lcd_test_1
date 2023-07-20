#include <lcd_i2c_lib.h>

char* recodeCyr(char *charCyr) {
	switch (*charCyr) {
	case '�':
		*charCyr = 'A';
		break;
	case '�':
		*charCyr = 'a';
		break;
	case '�':
		*charCyr = 0b10100000;
		break;
	case '�':
		*charCyr = 0b10110010;
		break;
	case '�':
		*charCyr = 'B';
		break;
	case '�':
		*charCyr = 0b10110011;
		break;
	case '�':
		*charCyr = 0b10100001;
		break;
	case '�':
		*charCyr = 0b10110100;
		break;
	case '�':
		*charCyr = 0b11100000;
		break;
	case '�':
		*charCyr = 0b11100011;
		break;
	case '�':
		*charCyr = 'E';
		break;
	case '�':
		*charCyr = 'e';
		break;
	case '�':
		*charCyr = 0b10100010;
		break;
	case '�':
		*charCyr = 0b10110101;
		break;
	case '�':
		*charCyr = 0b10100011;
		break;
	case '�':
		*charCyr = 0b10110110;
		break;
	case '�':
		*charCyr = 0b10100100;
		break;
	case '�':
		*charCyr = 0b10110111;
		break;
	case '�':
		*charCyr = 0b10100101;
		break;
	case '�':
		*charCyr = 0b10111000;
		break;
	case '�':
		*charCyr = 0b10100110;
		break;
	case '�':
		*charCyr = 0b10111001;
		break;
	case '�':
		*charCyr = 'K';
		break;
	case '�':
		*charCyr = 0b10111010;
		break;
	case '�':
		*charCyr = 0b10100111;
		break;
	case '�':
		*charCyr = 0b10111011;
		break;
	case '�':
		*charCyr = 'M';
		break;
	case '�':
		*charCyr = 0b10111100;
		break;
	case '�':
		*charCyr = 'H';
		break;
	case '�':
		*charCyr = 0b10111101;
		break;
	case '�':
		*charCyr = 'O';
		break;
	case '�':
		*charCyr = 'o';
		break;
	case '�':
		*charCyr = 0b10101000;
		break;
	case '�':
		*charCyr = 0b10111110;
		break;
	case '�':
		*charCyr = 'P';
		break;
	case '�':
		*charCyr = 'p';
		break;
	case '�':
		*charCyr = 'C';
		break;
	case '�':
		*charCyr = 'c';
		break;
	case '�':
		*charCyr = 'T';
		break;
	case '�':
		*charCyr = 0b10111111;
		break;
	case '�':
		*charCyr = 0b10101001;
		break;
	case '�':
		*charCyr = 'y';
		break;
	case '�':
		*charCyr = 0b10101010;
		break;
	case '�':
		*charCyr = 0b11100100;
		break;
	case '�':
		*charCyr = 'X';
		break;
	case '�':
		*charCyr = 'x';
		break;
	case '�':
		*charCyr = 0b11100001;
		break;
	case '�':
		*charCyr = 0b11100101;
		break;
	case '�':
		*charCyr = 0b10101011;
		break;
	case '�':
		*charCyr = 0b11000000;
		break;
	case '�':
		*charCyr = 0b10101100;
		break;
	case '�':
		*charCyr = 0b11000001;
		break;
	case '�':
		*charCyr = 0b11100010;
		break;
	case '�':
		*charCyr = 0b11100110;
		break;
	case '�':
		*charCyr = 0b11000010;
		break;
	case '�':
		*charCyr = 0b10101110;
		break;
	case '�':
		*charCyr = 0b11000011;
		break;
	case '�':
		*charCyr = 0b11000100;
		break;
	case '�':
		*charCyr = 0b10101111;
		break;
	case '�':
		*charCyr = 0b11000101;
		break;
	case '�':
		*charCyr = 0b10110000;
		break;
	case '�':
		*charCyr = 0b11000110;
		break;
	case '�':
		*charCyr = 0b10110001;
		break;
	case '�':
		*charCyr = 0b11000111;
		break;
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

void sendLcdInstruction(uint8_t instruction, I2CSettings settings) {
	uint8_t upperBite = instruction & 0xF0;
	uint8_t lowerBite = (instruction << 4) & 0xF0;

	uint8_t ByteArr[4] {};

	ByteArr[0] = upperBite | LED | EN;
	ByteArr[1] = 0;
	ByteArr[2] = lowerBite | LED | EN;
	ByteArr[3] = 0;

	HAL_I2C_Master_Transmit_DMA(settings.hi2c, settings.i2cAddr, ByteArr, 4);
	while (settings.hi2c->State == HAL_I2C_STATE_BUSY_TX)  {
	}
}


void sendLcdChar(uint8_t character, uint8_t ddramAddr, I2CSettings settings) {
	setDdramAddr(ddramAddr, settings);

	uint8_t upperBite = character & 0xF0;
	uint8_t lowerBite = (character << 4) & 0xF0;

	uint8_t ByteArr[4] {};

	ByteArr[0] = upperBite | 1 | LED | EN;
	ByteArr[1] = 0;
	ByteArr[2] = lowerBite | 1 | LED | EN;
	ByteArr[3] = 0;

	HAL_I2C_Master_Transmit_DMA(settings.hi2c, settings.i2cAddr, ByteArr, 4);
	while (settings.hi2c->State == HAL_I2C_STATE_BUSY_TX)  {
	}
}

void sendLcdByte(uint8_t character, I2CSettings settings) {
	uint8_t upperBite = character & 0xF0;
	uint8_t lowerBite = (character << 4) & 0xF0;

	uint8_t ByteArr[4] {};

	ByteArr[0] = upperBite | 1 | LED | EN;
	ByteArr[1] = 0;
	ByteArr[2] = lowerBite | 1 | LED | EN;
	ByteArr[3] = 0;

	HAL_I2C_Master_Transmit_DMA(settings.hi2c, settings.i2cAddr, ByteArr, 4);
	while (settings.hi2c->State == HAL_I2C_STATE_BUSY_TX)  {
	}
}

void sendLcdStr(char *string, uint8_t ddramAddr, I2CSettings settings) {
	setDdramAddr(ddramAddr, settings);
	while (*string) {
		char stringCopy = *string;
		stringCopy = *recodeCyr(&stringCopy);
		sendLcdByte(uint8_t(stringCopy), settings);
		++string;
	}
}


void sendLcdStrAB(char *string, uint8_t a, uint8_t b, uint8_t ddramAddr, I2CSettings settings) {
	setDdramAddr(ddramAddr, settings);
	for (uint8_t i = a; i < b; ++i) {
		char stringCopy = *string;
		stringCopy = *recodeCyr(&stringCopy);
		sendLcdByte(uint8_t(stringCopy), settings);
		++string;
	}
}

void clearLcd(I2CSettings settings) {
	uint8_t ByteArr[4] { 4, 0, 20, 0 };

	HAL_I2C_Master_Transmit_DMA(settings.hi2c, settings.i2cAddr, ByteArr, 4);
	while (settings.hi2c->State == HAL_I2C_STATE_BUSY_TX) {
	}
}

void clearChar(uint8_t charPos, I2CSettings settings) {
	sendLcdChar(0b10000000, charPos, settings);
}

void setDdramAddr(uint8_t ddramAddr, I2CSettings settings) {
	uint8_t upperBite = (ddramAddr | 0x80) & 0xF0;
	uint8_t lowerBite = (ddramAddr << 4) & 0xF0;

	uint8_t ByteArr[4]{};

	ByteArr[0] = upperBite | EN;
	ByteArr[1] = 0;
	ByteArr[2] = lowerBite | EN;
	ByteArr[3] = 0;

	HAL_I2C_Master_Transmit_DMA(settings.hi2c, settings.i2cAddr, ByteArr, 4);
	while (settings.hi2c->State == HAL_I2C_STATE_BUSY_TX) {
	}
}

void lcdInit(I2CSettings settings) {
	HAL_Delay(50);

	sendLcdInstruction(0b00110000, settings);   // 8�� ������ ���������
	HAL_Delay(40);

	sendLcdInstruction(0b00000010, settings);   // ��������� ������� � ������ ������
	HAL_Delay(40);

	sendLcdInstruction(0b00001100, settings);   // ���������� ����� ������, ���� ������
	HAL_Delay(40);

	sendLcdInstruction(0b00000100, settings);
	HAL_Delay(40);

	sendLcdInstruction(0b00000001, settings);   // ������� �������
	HAL_Delay(2);
}
