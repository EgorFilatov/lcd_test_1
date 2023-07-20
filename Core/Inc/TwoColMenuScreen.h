#ifndef INC_TWOCOLMENUSCREEN_H_
#define INC_TWOCOLMENUSCREEN_H_

#include <Screen.h>

class TwoColMenuScreen : public Screen {
public:
	TwoColMenuScreen(Screen *parentScreen);
	void show(int8_t shiftVal) override;
	void cursorDown() override;
	void cursorUp() override;
	virtual Screen* selectLine() override;
};

#endif /* INC_TWOCOLMENUSCREEN_H_ */
