#include <Button.hpp>

extern TIM_HandleTypeDef htim6;

Button::Button(GPIO_TypeDef *GPIOx, uint8_t pin) {
	this->GPIOx = GPIOx;
	this->pin = pin;
	this->debounce_counter = 0;
}

uint8_t Button::clicked() {
	if ((this->GPIOx->IDR & (1 << pin)) == 1 && this->debounce_counter == 0) {
		this->debounce_counter = 1;
		HAL_TIM_Base_Start_IT (&htim6); // ��������� ������� 6
	} else if ((this->GPIOx->IDR & (1 << pin)) == 1 && this->debounce_counter == 10) {
		this->debounce_counter = 0;
		return 1;
	}
	return 0;
}

uint8_t Button::unclicked() {
	if ((this->GPIOx->IDR & (1 << pin)) == 1 && this->debounce_counter == 0) {
		this->debounce_counter = 1;
		HAL_TIM_Base_Start_IT (&htim6); // ��������� ������� 6
	} else if ((this->GPIOx->IDR & (1 << pin)) == 1 && this->debounce_counter == 10) {
		this->debounce_counter = 0;
		return 1;
	}
	return 0;
}

void Button::interrupt() {
	if ((this->debounce_counter) > 0 && (this->debounce_counter) < 10) {
		++this->debounce_counter;
		(this->debounce_counter) == 10 ? HAL_TIM_Base_Stop_IT(&htim6) : 0;
	}
}
