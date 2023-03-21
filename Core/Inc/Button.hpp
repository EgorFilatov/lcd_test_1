#include "main.hpp"

#ifndef INC_BUTTON_HPP_
#define INC_BUTTON_HPP_

class Button {
private:
	GPIO_TypeDef *GPIOx;
	uint8_t pin;
	uint8_t prevSt;
	uint8_t debounceCounter;
public:
	Button(GPIO_TypeDef *GPIOx, uint8_t pin);

	uint8_t getPrevSt();

	void setPrevSt(uint8_t prevSt);

	uint8_t clicked();

	uint8_t unclicked();

	void interrupt();
};

#endif /* INC_BUTTON_HPP_ */
