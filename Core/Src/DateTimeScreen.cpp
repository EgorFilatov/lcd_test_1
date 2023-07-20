#include <DateTimeScreen.h>

DateTimeScreen::DateTimeScreen(Screen *parentScreen) : Screen(parentScreen) {
}

void DateTimeScreen::show(int8_t shiftVal) {
	for (uint8_t i = 0; i <= 1; i++) {
		sendLcdStr(&(line[i].getValue()[0]), rowPos[i + 1] + 5, i2cSettings);
	}
}
