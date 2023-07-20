#include <OneColMenuScreen.h>

OneColMenuScreen::OneColMenuScreen(Screen *parentScreen) : Screen(parentScreen) {
}

void OneColMenuScreen::show(int8_t shiftVal) {
	sendLcdChar(cursorChar, cursorPos, i2cSettings);
	uint8_t a;
	(linesNum >= 4) ? (a = 4) : (a = linesNum);
	for (uint8_t i = 0; i < a; i++) {
		sendLcdStr(&(line[i + shiftVal].getValue()[0]), Screen::rowPos[i] + 1, i2cSettings);
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
		if (menuShift < (linesNum - 4)) {
			++menuShift;
			clearLcd(i2cSettings);
		}
	}
	HAL_Delay(3);
	show(menuShift);
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
		if (menuShift > 0) {
			--menuShift;
			clearLcd(i2cSettings);
		}
	}
	HAL_Delay(3);
	show(menuShift);
}

