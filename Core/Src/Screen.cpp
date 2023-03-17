#include "Screen.hpp"

Screen::Screen() {
}

void Screen:: display() {
	ddram_set_addr(0x00, &hi2c1, this->addr);
	lcd_send_bite(this->cursor, 1, &hi2c1, this->addr);

	ddram_set_addr(0x01, &hi2c1, this->addr);
	lcd_send_string(this->string_1, 1, &hi2c1, this->addr);

	ddram_set_addr(0x41, &hi2c1, this->addr);
	lcd_send_string(this->string_2, 1, &hi2c1, this->addr);

	ddram_set_addr(0x15, &hi2c1, this->addr);
	lcd_send_string(this->string_3, 1, &hi2c1, this->addr);

	ddram_set_addr(0x55, &hi2c1, this->addr);
	lcd_send_string(this->string_4, 1, &hi2c1, this->addr);
}



