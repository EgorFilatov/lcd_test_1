#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include <main.h>
#include <timer.h>

class Button {
private:
	GPIO_TypeDef* port;
	uint8_t pin { };
	uint8_t prevSt { };
	CTimer debounceTim;

public:
	Button(GPIO_TypeDef *port, uint8_t pin, uint8_t debounceTime);

	uint8_t getPrevSt();

	void setPrevSt(uint8_t prevSt);

	uint8_t clicked();

	uint8_t pressed();

	uint8_t unpressed();

	void interrupt();
};

#endif /* INC_BUTTON_H_ */
