#ifndef INC_ONECOLMENUSCREEN_H_
#define INC_ONECOLMENUSCREEN_H_

#include "Screen.h"

class OneColMenuScreen : public Screen {
public:
	OneColMenuScreen(Screen *parentScreen);
	void show(int8_t shiftMenu);
	void cursorDown();
	void cursorUp();
};

#endif /* INC_ONECOLMENUSCREEN_H_ */
