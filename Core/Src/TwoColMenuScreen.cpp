#include <TwoColMenuScreen.h>

TwoColMenuScreen::TwoColMenuScreen(Screen *parentScreen) :
		Screen(parentScreen) {
}

void TwoColMenuScreen::show(int8_t shiftMenu) {
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
		sendLcdStr(&(line[i].getVal()[0]), Screen::rowPos[i] + 1, i2cSettings);
	}
	for (uint8_t i = 0; i < b; i++) {
		sendLcdStr(&(line[i + 4].getVal()[0]), Screen::rowPos[i] + 13, i2cSettings);
	}

}

void TwoColMenuScreen::cursorDown() {
	if (cursorPos != rowPos[3]) {
		for (uint8_t i = 0; i <= 2; i++) {
			if (cursorPos == rowPos[i] && linesNum > (i + 1)) {
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
	show(shiftFlag);
}

void TwoColMenuScreen::cursorUp() {
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
	show(shiftFlag);
}

