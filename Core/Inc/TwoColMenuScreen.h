#ifndef INC_TWOCOLMENUSCREEN_H_
#define INC_TWOCOLMENUSCREEN_H_

#include <Screen.h>

class TwoColMenuScreen : public Screen {
public:
	TwoColMenuScreen(Screen *parentScreen);
	void show(int8_t shiftMenu);
	void cursorDown();
	void cursorUp();
};

#endif /* INC_TWOCOLMENUSCREEN_H_ */
