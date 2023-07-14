
#include <Screen.h>

Screen::Screen(Screen *parentScreen) :
		parentScreen(parentScreen), cursorChar(0xC9), cursorPos(0), rowPos {0x00, 0x40, 0x14, 0x54 } {
}

void Screen::setI2CSettings(I2C_HandleTypeDef *hi2c, uint8_t i2cAddr) {
	i2cSettings.hi2c = hi2c;
	i2cSettings.i2cAddr = i2cAddr;
}



/*
void Screen::cursorDown() {
	if (cursorPos != rowPos[3]) {
		for (uint8_t i = 0; i <= 2; i++) {
			if (cursorPos == rowPos[i]
					&& linesNum > (i + 1)) {
				clearChar(cursorPos, i2cSettings);
				cursorPos = rowPos[i + 1];
				break;
			}
		}
	} else {
		if (shiftFlag < (linesNum - 4)) {
			++shiftFlag;
			clearLcd(i2cSettings);
		}
	}
	HAL_Delay(3);
	show(1, shiftFlag);
}

void Screen::cursorUp() {
	switch (colNum) {
	case 1:
		if (cursorPos != rowPos[0]) {
			for (uint8_t i = 1; i <= 3; i++) {
				if (cursorPos == rowPos[i]) {
					clearChar(cursorPos, i2cSettings);
					cursorPos = rowPos[i - 1];
					break;
				}
			}
		} else {
			if (shiftFlag > 0) {
				--shiftFlag;
				clearLcd(i2cSettings);
			}
		}
		HAL_Delay(3);
		show(1, shiftFlag);
		break;
	case 2:
		if (cursorPos != rowPos[0]) {
			for (uint8_t i = 1; i <= 3; i++) {
				if (cursorPos == rowPos[i]) {
					clearChar(cursorPos, i2cSettings);
					cursorPos = rowPos[i - 1];
					break;
				}
			}
		} else {
			if (shiftFlag > 0) {
				--shiftFlag;
				clearLcd(i2cSettings);
			}
		}
		HAL_Delay(3);
		show(1, shiftFlag);
		break;
	}





















}

Screen* Screen::selectLine() {
	for (uint8_t i = 0; i < 4; i++) {
		if (cursorPos == rowPos[i]) {
			return line[i + shiftFlag].getChild();
		}
	}
	return 0;
}



void Screen::displayDateTime() {
	for (uint8_t i = 0; i <= 1; i++) {
		sendLcdStr(&(line[i].getVal()[0]), rowPos[i + 1] + 5, i2cSettings);
	}
}

void Screen::addLine(std::string value, Screen *childScreen) {
	line.resize(line.size() + 1);
	line[line.size() - 1].setVal(value);
	line[line.size() - 1].setChild(childScreen);
	linesNum = line.size();
}

void Screen::resetLine(std::string value, uint8_t lineNum) {
	line[lineNum].setVal(value);
}

Screen* Screen::getParent() {
	return parentScreen;
}

uint8_t Screen::getShiftFlag() {
	return shiftFlag;
}

void Screen::setCursorPos(uint8_t position) {
	cursorPos = rowPos[position];
}

void Screen::setShiftFlag(uint8_t shiftFlag) {
	shiftFlag = shiftFlag;
}

Screen::Line::Line() {
	val = "";
}

void Screen::Line::setVal(std::string val) {
	val = val;
}

void Screen::Line::setChild(Screen *childScreen) {
	childScreen = childScreen;
}

Screen* Screen::Line::getChild() {
	return childScreen;
}

std::string Screen::Line::getVal() {
	return val;
}


*/

