#include "main.hpp"

#ifndef INC_BUTTON_HPP_
#define INC_BUTTON_HPP_

class Button {
private:
	GPIO_TypeDef *GPIOx;
	uint8_t pin;
	uint8_t prev_st;
	uint8_t debounce_counter;
public:
	Button(GPIO_TypeDef *GPIOx, uint8_t pin);

	uint8_t get_prev_st();

	void set_prev_st(uint8_t prev_st);

	uint8_t clicked();

	uint8_t unclicked();

	void interrupt();
};

#endif /* INC_BUTTON_HPP_ */
