#include <Screen.h>

I2CSettings Screen::i2cSettings;

Screen::Screen(Screen *parentScreen) :
		parentScreen(parentScreen), cursorChar(0xC9), cursorPos(0), rowPos { 0x00, 0x40, 0x14, 0x54 } {
	i2cSettings.hi2c = &hi2c1;
	i2cSettings.i2cAddr = 0x4E;
}

void Screen::setI2CSettings(I2C_HandleTypeDef *hi2c, uint8_t i2cAddr) {
	i2cSettings.hi2c = hi2c;
	i2cSettings.i2cAddr = i2cAddr;
}

Screen* Screen::selectLine() {
	for (uint8_t i = 0; i < 4; i++) {
		if (cursorPos == rowPos[i]) {
			return line[i + menuShift].getChild();
		}
	}
	return 0;
}

void Screen::addLine(std::string value, Screen *childScreen) {
	line.resize(line.size() + 1);
	line[line.size() - 1].setValue(value);
	line[line.size() - 1].setChild(childScreen);
	linesNum = line.size();
}

void Screen::resetLine(uint8_t lineNum, std::string value) {
	line[lineNum].setValue(value);
}

Screen* Screen::getParent() {
	return parentScreen;
}

uint8_t Screen::getMenuShift() {
	return menuShift;
}

void Screen::setCursorPos(uint8_t position) {
	cursorPos = rowPos[position];
}

void Screen::setMenuShift(uint8_t shiftVal) {
	menuShift = shiftVal;
}

Screen::Line::Line() {
	value = "";
}

void Screen::Line::setValue(std::string value) {
	this->value = value;
}

void Screen::Line::setChild(Screen *childScreen) {
	this->childScreen = childScreen;
}

Screen* Screen::Line::getChild() {
	return childScreen;
}

std::string Screen::Line::getValue() {
	return value;
}


