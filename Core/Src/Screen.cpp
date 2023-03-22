#include "Screen.hpp"

Screen::Screen(I2C_HandleTypeDef *hi2c, uint8_t i2cAddr) {
	this->i2cSettings.hi2c = hi2c;
	this->i2cSettings.i2cAddr = i2cAddr;
}

void Screen::cursorDown() {
	if (this->cursorPos == this->rowPos1) {
		setDdramAddr(this->cursorPos, this->i2cSettings);
		sendLcdByte(0b10000000, 1, this->i2cSettings);
		this->cursorPos = this->rowPos2;
		setDdramAddr(this->cursorPos, this->i2cSettings);
		sendLcdByte(this->cursor, 1, this->i2cSettings);
	} else if (this->cursorPos == this->rowPos2) {
		setDdramAddr(this->cursorPos, this->i2cSettings);
		sendLcdByte(0b10000000, 1, this->i2cSettings);
		this->cursorPos = this->rowPos3;
		setDdramAddr(this->cursorPos, this->i2cSettings);
		sendLcdByte(this->cursor, 1, this->i2cSettings);
	} else if (this->cursorPos == this->rowPos3) {
		setDdramAddr(this->cursorPos, this->i2cSettings);
		sendLcdByte(0b10000000, 1, this->i2cSettings);
		this->cursorPos = this->rowPos4;
		setDdramAddr(this->cursorPos, this->i2cSettings);
		sendLcdByte(this->cursor, 1, this->i2cSettings);
	} else if (this->cursorPos == this->rowPos4) {
		clearLcd(this->i2cSettings);
		HAL_Delay(2);

		sendLcdByte(0b00000111, 0, this->i2cSettings);

		setDdramAddr(this->cursorPos, this->i2cSettings);
		sendLcdByte(this->cursor, 1, this->i2cSettings);

		setDdramAddr(this->rowPos1 + 1, this->i2cSettings);
		sendLcdStr(this->line2, this->i2cSettings);

		setDdramAddr(this->rowPos2 + 1, this->i2cSettings);
		sendLcdStr(this->line3, this->i2cSettings);

		setDdramAddr(this->rowPos3 + 1, this->i2cSettings);
		sendLcdStr(this->line4, this->i2cSettings);

		setDdramAddr(this->rowPos4 + 1, this->i2cSettings);
		sendLcdStr(this->line5, this->i2cSettings);
	}
}

void Screen::display() {
	setDdramAddr(this->cursorPos, this->i2cSettings);
	sendLcdByte(this->cursor, 1, this->i2cSettings);

	setDdramAddr(this->rowPos1 + 1, this->i2cSettings);
	//sendLcdStr(&(this->my_line.my_string[0]), this->i2cSettings);

	setDdramAddr(this->rowPos2 + 1, this->i2cSettings);
	sendLcdStr(this->line2, this->i2cSettings);

	setDdramAddr(this->rowPos3 + 1, this->i2cSettings);
	sendLcdStr(this->line3, this->i2cSettings);

	setDdramAddr(this->rowPos4 + 1, this->i2cSettings);
	sendLcdStr(this->line4, this->i2cSettings);
}

void Screen::setLine(char *line) {
	uint8_t lineSize { };
	while (*line) {
		++lineSize;
		this->line.push_back(*line);
		++line;
	}
	this->lineSize.push_back(lineSize);
}




