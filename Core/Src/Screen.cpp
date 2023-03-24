#include "Screen.hpp"

Screen::Screen(I2C_HandleTypeDef *hi2c, uint8_t i2cAddr) {
	this->i2cSettings.hi2c = hi2c;
	this->i2cSettings.i2cAddr = i2cAddr;
}

void Screen::cursorDown() {
	if (this->cursorPos == this->rowPos1 && this->linesNum > 1) {
		clearChar(this->cursorPos, this->i2cSettings);
		this->cursorPos = this->rowPos2;
		displayOneCol(1, 0, 0);
	} else if (this->cursorPos == this->rowPos2 && this->linesNum > 2) {
		clearChar(this->cursorPos, this->i2cSettings);
		this->cursorPos = this->rowPos3;
		displayOneCol(1, 0, 0);
	} else if (this->cursorPos == this->rowPos3 && this->linesNum > 3) {
		clearChar(this->cursorPos, this->i2cSettings);
		this->cursorPos = this->rowPos4;
		displayOneCol(1, 0, 0);
	} else if (this->cursorPos == this->rowPos4 && this->linesNum > 4) {
		(this->shiftFlag < (this->linesNum - 4)) ? (++this->shiftFlag) : 0;
		clearLcd(this->i2cSettings);
		HAL_Delay(2);
		displayOneCol(1, 0, this->shiftFlag);
	}
}

void Screen::cursorUp() {
	if (this->cursorPos == this->rowPos4) {
		clearChar(this->cursorPos, this->i2cSettings);
		this->cursorPos = this->rowPos3;
		displayOneCol(1, 0, 0);
	} else if (this->cursorPos == this->rowPos3) {
		clearChar(this->cursorPos, this->i2cSettings);
		this->cursorPos = this->rowPos2;
		displayOneCol(1, 0, 0);
	} else if (this->cursorPos == this->rowPos2) {
		clearChar(this->cursorPos, this->i2cSettings);
		this->cursorPos = this->rowPos1;
		displayOneCol(1, 0, 0);
	} else if (this->cursorPos == this->rowPos1) {
		(this->shiftFlag > 0) ? (--this->shiftFlag) : 0;
		clearLcd(this->i2cSettings);
		HAL_Delay(2);
		displayOneCol(1, 0, this->shiftFlag);
	}
}

void Screen::displayOneCol(uint8_t shiftRight, uint8_t shiftDown, int8_t shiftMenu) {

	sendLcdChar(this->cursorChar, this->cursorPos, this->i2cSettings);

	if (this->linesNum > 3) {
		sendLcdStrAB(&(this->line[this->startPos[0 + shiftMenu]]), this->startPos[0 + shiftMenu], this->endPos[0 + shiftMenu], this->rowPos1 + shiftRight, this->i2cSettings);
		sendLcdStrAB(&(this->line[this->startPos[1 + shiftMenu]]), this->startPos[1 + shiftMenu], this->endPos[1 + shiftMenu], this->rowPos2 + shiftRight, this->i2cSettings);
		sendLcdStrAB(&(this->line[this->startPos[2 + shiftMenu]]), this->startPos[2 + shiftMenu], this->endPos[2 + shiftMenu], this->rowPos3 + shiftRight, this->i2cSettings);
		sendLcdStrAB(&(this->line[this->startPos[3 + shiftMenu]]), this->startPos[3 + shiftMenu], this->endPos[3 + shiftMenu], this->rowPos4 + shiftRight, this->i2cSettings);
	} else if (this->linesNum > 2) {
		sendLcdStrAB(&(this->line[this->startPos[0 + shiftMenu]]), this->startPos[0 + shiftMenu], this->endPos[0 + shiftMenu], this->rowPos1 + shiftRight, this->i2cSettings);
		sendLcdStrAB(&(this->line[this->startPos[1 + shiftMenu]]), this->startPos[1 + shiftMenu], this->endPos[1 + shiftMenu], this->rowPos2 + shiftRight, this->i2cSettings);
		sendLcdStrAB(&(this->line[this->startPos[2 + shiftMenu]]), this->startPos[2 + shiftMenu], this->endPos[2 + shiftMenu], this->rowPos3 + shiftRight, this->i2cSettings);
	} else if (this->linesNum > 1) {
			sendLcdStrAB(&(this->line[this->startPos[0 + shiftMenu]]), this->startPos[0 + shiftMenu], this->endPos[0 + shiftMenu], this->rowPos1 + shiftRight, this->i2cSettings);
			sendLcdStrAB(&(this->line[this->startPos[1 + shiftMenu]]), this->startPos[1 + shiftMenu], this->endPos[1 + shiftMenu], this->rowPos2 + shiftRight, this->i2cSettings);

	} else if (this->linesNum > 0) {
			sendLcdStrAB(&(this->line[this->startPos[0 + shiftMenu]]), this->startPos[0 + shiftMenu], this->endPos[0 + shiftMenu], this->rowPos1 + shiftRight, this->i2cSettings);
	}
}

void Screen::setLine(char *line) {
	this->startPos.push_back(this->line.size());
	while (*line) {
		this->line.push_back(*line);
		++line;
	}
	this->endPos.push_back(this->line.size());
	this->linesNum = this->startPos.size();
}




