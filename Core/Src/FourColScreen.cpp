#include <FourColScreen.h>

FourColScreen::FourColScreen(Screen *parentScreen) :
		Screen(parentScreen) {
}

void FourColScreen::show(int8_t shiftVal) {
	uint8_t a { 0 };
	uint8_t b { 0 };
	uint8_t c { 0 };
	uint8_t d { 0 };
	if (linesNum >= 4) {
		a = 4;
		if (linesNum >= 8) {
			b = 4;
			if (linesNum >= 12) {
				c = 12;
				if (linesNum >= 8) {
					d = 4;
				} else {
					d = linesNum - 4;
				}
			} else {
				c = linesNum - 4;
			}
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
		sendLcdStr(&(line[i + shiftVal + 4].getValue()[0]), Screen::rowPos[i] + 11, i2cSettings);
	}
	for (uint8_t i = 0; i < c; i++) {
		sendLcdStr(&(line[i + shiftVal + 8].getValue()[0]), Screen::rowPos[i] + 11, i2cSettings);
	}
	for (uint8_t i = 0; i < d; i++) {
		sendLcdStr(&(line[i + shiftVal + 12].getValue()[0]), Screen::rowPos[i] + 11, i2cSettings);
	}
}

void FourColScreen::cursorDown() {
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

void FourColScreen::cursorUp() {
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
