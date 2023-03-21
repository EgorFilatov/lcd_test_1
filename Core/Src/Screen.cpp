#include "Screen.hpp"

Screen::Screen(I2C_HandleTypeDef *hi2c, uint8_t i2cAddr) {
	this->i2cSettings.hi2c = hi2c;
	this->i2cSettings.i2cAddr = i2cAddr;
}

void Screen::cursorDown() {
	if (this->cursorPos == 0x00) {
		setDdramAddr(this->cursorPos, this->i2cSettings);
		sendLcdByte(0b10000000, 1, this->i2cSettings);
		this->cursorPos = 0x40;
		setDdramAddr(this->cursorPos, this->i2cSettings);
		sendLcdByte(this->cursor, 1, this->i2cSettings);
	} else if (this->cursorPos == 0x40) {
		setDdramAddr(this->cursorPos, this->i2cSettings);
		sendLcdByte(0b10000000, 1, this->i2cSettings);
		this->cursorPos = 0x14;
		setDdramAddr(this->cursorPos, this->i2cSettings);
		sendLcdByte(this->cursor, 1, this->i2cSettings);
	} else if (this->cursorPos == 0x14) {
		setDdramAddr(this->cursorPos, this->i2cSettings);
		sendLcdByte(0b10000000, 1, this->i2cSettings);
		this->cursorPos = 0x54;
		setDdramAddr(this->cursorPos, this->i2cSettings);
		sendLcdByte(this->cursor, 1, this->i2cSettings);
	} else if (this->cursorPos == 0x54) {
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
	sendLcdStr(this->line1, this->i2cSettings);

	setDdramAddr(this->rowPos2 + 1, this->i2cSettings);
	sendLcdStr(this->line2, this->i2cSettings);

	setDdramAddr(this->rowPos3 + 1, this->i2cSettings);
	sendLcdStr(this->line3, this->i2cSettings);

	setDdramAddr(this->rowPos4 + 1, this->i2cSettings);
	sendLcdStr(this->line4, this->i2cSettings);
}



