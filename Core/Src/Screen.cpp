#include "Screen.hpp"

Screen::Screen(I2C_HandleTypeDef *hi2c, Screen *parentScreen, uint8_t i2cAddr) {
	this->i2cSettings.hi2c = hi2c;
	this->i2cSettings.i2cAddr = i2cAddr;
}

Screen::Screen(const Screen &screen) :
		parentScreen(screen.parentScreen), i2cSettings(screen.i2cSettings), i2cAddr(
				screen.i2cAddr), cursorChar(screen.cursorChar), cursorPos(
				screen.cursorPos), rowPos1(screen.rowPos1), rowPos2(
				screen.rowPos2), rowPos3(screen.rowPos3), rowPos4(
				screen.rowPos4), line(screen.line), linesNum(
				screen.linesNum), shiftFlag(screen.shiftFlag) {
}

void Screen::cursorDown() {
	if (this->cursorPos == this->rowPos1 && this->linesNum > 1) {
		clearChar(this->cursorPos, this->i2cSettings);
		this->cursorPos = this->rowPos2;
		displayOneCol(1, 0, this->shiftFlag);
	} else if (this->cursorPos == this->rowPos2 && this->linesNum > 2) {
		clearChar(this->cursorPos, this->i2cSettings);
		this->cursorPos = this->rowPos3;
		displayOneCol(1, 0, this->shiftFlag);
	} else if (this->cursorPos == this->rowPos3 && this->linesNum > 3) {
		clearChar(this->cursorPos, this->i2cSettings);
		this->cursorPos = this->rowPos4;
		displayOneCol(1, 0, this->shiftFlag);
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
		displayOneCol(1, 0, this->shiftFlag);
	} else if (this->cursorPos == this->rowPos3) {
		clearChar(this->cursorPos, this->i2cSettings);
		this->cursorPos = this->rowPos2;
		displayOneCol(1, 0, this->shiftFlag);
	} else if (this->cursorPos == this->rowPos2) {
		clearChar(this->cursorPos, this->i2cSettings);
		this->cursorPos = this->rowPos1;
		displayOneCol(1, 0, this->shiftFlag);
	} else if (this->cursorPos == this->rowPos1) {
		(this->shiftFlag > 0) ? (--this->shiftFlag) : 0;
		clearLcd(this->i2cSettings);
		HAL_Delay(2);
		displayOneCol(1, 0, this->shiftFlag);
	}
}

Screen* Screen::selectItem() {
	if (this->cursorPos == this->rowPos1) {
		return this->line[0 + this->shiftFlag].getChild();
	}
	if (this->cursorPos == this->rowPos2) {
		return this->line[1 + this->shiftFlag].getChild();
	}
	if (this->cursorPos == this->rowPos3) {
		return this->line[2 + this->shiftFlag].getChild();
	}
	if (this->cursorPos == this->rowPos4) {
		return this->line[3 + this->shiftFlag].getChild();
	}
	return 0;
}


void Screen::displayOneCol(uint8_t shiftRight, uint8_t shiftDown, int8_t shiftMenu) {

	sendLcdChar(this->cursorChar, this->cursorPos, this->i2cSettings);

	if (this->linesNum > 3) {
		sendLcdStr(&(this->line[0 + shiftMenu].getVal()[0]), this->rowPos1 + shiftRight, this->i2cSettings);
		sendLcdStr(&(this->line[1 + shiftMenu].getVal()[0]), this->rowPos2 + shiftRight, this->i2cSettings);
		sendLcdStr(&(this->line[2 + shiftMenu].getVal()[0]), this->rowPos3 + shiftRight, this->i2cSettings);
		sendLcdStr(&(this->line[3 + shiftMenu].getVal()[0]), this->rowPos4 + shiftRight, this->i2cSettings);
	} else if (this->linesNum > 2) {
		sendLcdStr(&(this->line[0 + shiftMenu].getVal()[0]), this->rowPos1 + shiftRight, this->i2cSettings);
		sendLcdStr(&(this->line[1 + shiftMenu].getVal()[0]), this->rowPos2 + shiftRight, this->i2cSettings);
		sendLcdStr(&(this->line[2 + shiftMenu].getVal()[0]), this->rowPos3 + shiftRight, this->i2cSettings);
	} else if (this->linesNum > 1) {
		sendLcdStr(&(this->line[0 + shiftMenu].getVal()[0]), this->rowPos1 + shiftRight, this->i2cSettings);
		sendLcdStr(&(this->line[1 + shiftMenu].getVal()[0]), this->rowPos2 + shiftRight, this->i2cSettings);
	} else if (this->linesNum > 0) {
		sendLcdStr(&(this->line[0 + shiftMenu].getVal()[0]), this->rowPos1 + shiftRight, this->i2cSettings);
	}
}

void Screen::setLineVal(std::string value, Screen *childScreen) {
	this->line.resize(this->line.size() + 1);
	this->line[this->line.size() - 1].setVal(value);
	this->line[this->line.size() - 1].setChild(childScreen);
	this->linesNum = this->line.size();
}

Screen* Screen::getParent() {
	return this->parentScreen;
}







Screen::Line::Line() {
	this->val = "";
}

void Screen::Line::setVal(std::string val) {
	this->val = val;
}

void Screen::Line::setChild(Screen *childScreen) {
	this->childScreen = childScreen;
}

Screen* Screen::Line::getChild() {
	return this->childScreen;
}

std::string Screen::Line::getVal() {
	return this->val;
}




