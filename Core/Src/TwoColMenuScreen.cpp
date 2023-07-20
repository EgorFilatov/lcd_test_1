#include <TwoColMenuScreen.h>

TwoColMenuScreen::TwoColMenuScreen(Screen *parentScreen) :
		Screen(parentScreen) {
}

void TwoColMenuScreen::show(int8_t shiftVal) {
	uint8_t a { 0 };
	uint8_t b { 0 };
	sendLcdChar(cursorChar, cursorPos, i2cSettings);
	if (linesNum >= 4) {
		a = 4;
		if (linesNum >= 8) {
			b = 4;
		} else {
			b = linesNum - 4;
		}
	} else {
		a = linesNum;
	}
	for (uint8_t i = 0; i < a; i++) {
		sendLcdStr(&(line[i + shiftVal].getValue()[0]), Screen::rowPos[i] + 1, i2cSettings);
	}
	for (uint8_t i = 0; i < b; i++) {
		sendLcdStr(&(line[i +  + shiftVal + 4].getValue()[0]), Screen::rowPos[i] + 11, i2cSettings);
	}

}

void TwoColMenuScreen::cursorDown() {
	if (cursorPos == rowPos[0] || cursorPos == rowPos[1] || cursorPos == rowPos[2]) {
		for (uint8_t i = 0; i <= 2; i++) {
			if (cursorPos == rowPos[i] && linesNum > (i + 1)) {
				clearChar(cursorPos, i2cSettings);
				cursorPos = rowPos[i + 1];
				break;
			}
		}
	} else if (cursorPos == rowPos[3]) {
		clearChar(cursorPos, i2cSettings);
		cursorPos = rowPos[0] + 10;
	} else if (cursorPos == rowPos[0] + 10 || cursorPos == rowPos[1] + 10 || cursorPos == rowPos[2] + 10) {
		for (uint8_t i = 0; i <= 2; i++) {
			if (cursorPos == (rowPos[i] + 10) && linesNum > (i + 5)) {
				clearChar(cursorPos, i2cSettings);
				cursorPos = rowPos[i + 1] + 10;
				break;
			}
		}
	} else if (cursorPos == rowPos[3] + 10) {
		if (menuShift < (linesNum - 8)) {
			menuShift = menuShift + 8;
			cursorPos = rowPos[0];
			clearLcd(i2cSettings);
		}
	}
	HAL_Delay(3);
	show(menuShift);
}

void TwoColMenuScreen::cursorUp() {
	if (cursorPos == rowPos[1] || cursorPos == rowPos[2] || cursorPos == rowPos[3]) {
		for (uint8_t i = 1; i <= 3; i++) {
			if (cursorPos == rowPos[i]) {
				clearChar(cursorPos, i2cSettings);
				cursorPos = rowPos[i - 1];
				break;
			}
		}
	} else if (cursorPos == rowPos[1] + 10 || cursorPos == rowPos[2] + 10 || cursorPos == rowPos[3] + 10) {
		for (uint8_t i = 1; i <= 3; i++) {
			if (cursorPos == rowPos[i] + 10) {
				clearChar(cursorPos, i2cSettings);
				cursorPos = rowPos[i - 1] + 10;
				break;
			}
		}
	} else if (cursorPos == rowPos[0] + 10) {
		clearChar(cursorPos, i2cSettings);
		cursorPos = rowPos[3];
	} else if (cursorPos == rowPos[0]) {
		if (menuShift > 0) {
			menuShift = menuShift - 8;
			cursorPos = rowPos[3] + 10;
			clearLcd(i2cSettings);
		}
	}
	HAL_Delay(3);
	show(menuShift);
}

Screen* TwoColMenuScreen::selectLine() {
	for (uint8_t i = 0; i < 4; i++) {
		if (cursorPos == rowPos[i]) {
			return line[i + menuShift].getChild();
		}
		if (cursorPos == rowPos[i] + 10) {
			return line[i + 4 + menuShift].getChild();
		}
	}
	return 0;
}

