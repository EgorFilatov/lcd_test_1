#include <FourColScreen.h>

FourColScreen::FourColScreen(Screen *parentScreen) :
		Screen(parentScreen) {
}

void FourColScreen::show(int8_t shiftVal) {
	uint8_t a { 0 };
	uint8_t b { 0 };
	uint8_t c { 0 };
	uint8_t d { 0 };
	if (linesNum - menuShift >= 4) {
		a = 4;
		if (linesNum - menuShift >= 8) {
			b = 4;
			if (linesNum - menuShift >= 12) {
				c = 4;
				if (linesNum - menuShift >= 16) {
					d = 4;
				} else {
					d = linesNum - menuShift - 12;
				}
			} else {
				c = linesNum - menuShift - 8;
			}
		} else {
			b = linesNum - menuShift - 4;
		}
	} else {
		a = linesNum - menuShift;
	}
	for (uint8_t i = 0; i < a; i++) {
		sendLcdStr(&(line[i + shiftVal].getValue()[0]), Screen::rowPos[i], i2cSettings);
	}
	for (uint8_t i = 0; i < b; i++) {
		sendLcdStr(&(line[i + shiftVal + 4].getValue()[0]), Screen::rowPos[i] + 5, i2cSettings);
	}
	for (uint8_t i = 0; i < c; i++) {
		sendLcdStr(&(line[i + shiftVal + 8].getValue()[0]), Screen::rowPos[i] + 10, i2cSettings);
	}
	for (uint8_t i = 0; i < d; i++) {
		sendLcdStr(&(line[i + shiftVal + 12].getValue()[0]), Screen::rowPos[i] + 15, i2cSettings);
	}
}

void FourColScreen::cursorDown() {
	if (menuShift < linesNum - 16) {
		menuShift = menuShift + 16;
		clearLcd(i2cSettings);
		HAL_Delay(3);
		show(menuShift);
	}
}

void FourColScreen::cursorUp() {
	if (menuShift > 0) {
		menuShift = menuShift - 16;
		clearLcd(i2cSettings);
		HAL_Delay(3);
		show(menuShift);
	}
}
