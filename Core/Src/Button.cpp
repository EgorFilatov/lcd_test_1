#include <Button.hpp>

extern TIM_HandleTypeDef htim6;

Button::Button(GPIO_TypeDef *port, uint8_t pin) {
	this->port = port;
	this->pin = pin;
	this->prevSt = 0;
	this->debounceCounter = 0;
}

uint8_t Button::getPrevSt() {
	return this->prevSt;
}

void Button::setPrevSt(uint8_t prevSt) {
	this->prevSt = prevSt;
}

uint8_t Button::clicked() {
	if ((this->port->IDR & (1 << pin)) == 1 && this->debounceCounter == 0) {
		this->debounceCounter = 1;
		HAL_TIM_Base_Start_IT (&htim6);
	} else if ((this->port->IDR & (1 << pin)) == 1 && this->debounceCounter == 10) {
		HAL_TIM_Base_Stop_IT(&htim6);
		this->debounceCounter = 0;
		return 1;
	}
	return 0;
}

uint8_t Button::unclicked() {
	if ((this->port->IDR & (1 << pin)) == 0 && this->debounceCounter == 0) {
		this->debounceCounter = 1;
		HAL_TIM_Base_Start_IT (&htim6);
	} else if ((this->port->IDR & (1 << pin)) == 0 && this->debounceCounter == 10) {
		HAL_TIM_Base_Stop_IT(&htim6);
		this->debounceCounter = 0;
		return 1;
	}
	return 0;
}

void Button::interrupt() {
	if ((this->debounceCounter) > 0 && (this->debounceCounter) < 10) {
		++this->debounceCounter;
	}
}
