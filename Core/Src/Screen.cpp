#include "Screen.hpp"

Screen::Screen(uint8_t cursor_pos) {
	this->cursor = 0b11001001;
	this->cursor_pos = cursor_pos;
}

void Screen::move_cursor_pos() {
	if (this->cursor_pos == 0x00) {
		ddram_set_addr(0x40, &hi2c1, this->addr);
		lcd_send_bite(this->cursor, 1, &hi2c1, this->addr);
	}
	if (this->cursor_pos == 0x40) {
		ddram_set_addr(0x15, &hi2c1, this->addr);
		lcd_send_bite(this->cursor, 1, &hi2c1, this->addr);
	}
	if (this->cursor_pos == 0x14) {
		ddram_set_addr(0x40, &hi2c1, this->addr);
		lcd_send_bite(this->cursor, 1, &hi2c1, this->addr);
	}
	if (this->cursor_pos == 0x14) {
		ddram_set_addr(0x54, &hi2c1, this->addr);
		lcd_send_bite(this->cursor, 1, &hi2c1, this->addr);
	}
	if (this->cursor_pos == 0x54) {
		ddram_set_addr(0x00, &hi2c1, this->addr);
		lcd_send_bite(this->cursor, 1, &hi2c1, this->addr);
	}
}

void Screen::display() {
	ddram_set_addr(this->cursor_pos, &hi2c1, this->addr);
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



