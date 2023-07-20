#ifndef INC_FOURCOLSCREEN_H_
#define INC_FOURCOLSCREEN_H_

#include <Screen.h>

class FourColScreen : public Screen {
public:
	FourColScreen(Screen *parentScreen);
	void show(int8_t shiftVal) override;
	void cursorDown() override;
	void cursorUp() override;
};

#endif /* INC_FOURCOLSCREEN_H_ */
