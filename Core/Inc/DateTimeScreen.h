#ifndef INC_DATETIMESCREEN_H_
#define INC_DATETIMESCREEN_H_

#include <Screen.h>

class DateTimeScreen : public Screen {
public:
	DateTimeScreen(Screen *parentScreen);
	void show(int8_t shiftVal) override;
};

#endif /* INC_DATETIMESCREEN_H_ */
