#include <OneColMenuScreen.h>

OneColMenuScreen::OneColMenuScreen(Screen *parentScreen) : Screen(parentScreen) {
}

void OneColMenuScreen::show(int8_t shiftMenu) {
	sendLcdChar(cursorChar, cursorPos, i2cSettings);
	uint8_t a;
	(linesNum >= 4) ? (a = 4) : (a = linesNum);
	for (uint8_t i = 0; i < a; i++) {
		sendLcdStr(&(line[i + shiftMenu].getVal()[0]), Screen::rowPos[i] + 1, i2cSettings);
	}
}

void OneColMenuScreen::cursorDown() {
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

void OneColMenuScreen::cursorUp() {
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

