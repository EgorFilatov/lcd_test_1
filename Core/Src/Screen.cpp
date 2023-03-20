#include "Screen.hpp"

Screen::Screen(I2C_HandleTypeDef *hi2c, uint8_t i2cAddr) {
	this->i2cSettings.hi2c = hi2c;
	this->i2cSettings.i2cAddr = i2cAddr;
}

void Screen::move_cursor_pos() {
	if (this->cursorPos == 0x00) {
		ddram_set_addr(this->cursorPos, this->i2cSettings);
		lcd_send_bite(0b10000000, 1, this->i2cSettings);
		this->cursorPos = 0x40;
		ddram_set_addr(this->cursorPos, this->i2cSettings);
		lcd_send_bite(this->cursor, 1, this->i2cSettings);
	} else if (this->cursorPos == 0x40) {
		ddram_set_addr(this->cursorPos, this->i2cSettings);
		lcd_send_bite(0b10000000, 1, this->i2cSettings);
		this->cursorPos = 0x14;
		ddram_set_addr(this->cursorPos, this->i2cSettings);
		lcd_send_bite(this->cursor, 1, this->i2cSettings);
	} else if (this->cursorPos == 0x14) {
		ddram_set_addr(this->cursorPos, this->i2cSettings);
		lcd_send_bite(0b10000000, 1, this->i2cSettings);
		this->cursorPos = 0x54;
		ddram_set_addr(this->cursorPos, this->i2cSettings);
		lcd_send_bite(this->cursor, 1, this->i2cSettings);
	} else if (this->cursorPos == 0x54) {
		lcd_clear(this->i2cSettings);
		HAL_Delay(5);

		ddram_set_addr(this->cursorPos, this->i2cSettings);
		lcd_send_bite(this->cursor, 1, this->i2cSettings);

		ddram_set_addr(this->rowPos1 + 1, this->i2cSettings);
		lcd_send_string(this->line2, 1, this->i2cSettings);

		ddram_set_addr(this->rowPos2 + 1, this->i2cSettings);
		lcd_send_string(this->line3, 1, this->i2cSettings);

		ddram_set_addr(this->rowPos3 + 1, this->i2cSettings);
		lcd_send_string(this->line4, 1, this->i2cSettings);

		ddram_set_addr(this->rowPos4 + 1, this->i2cSettings);
		lcd_send_string(this->line5, 1, this->i2cSettings);
	}
}

void Screen::display() {
	ddram_set_addr(this->cursorPos, this->i2cSettings);
	lcd_send_bite(this->cursor, 1, this->i2cSettings);

	ddram_set_addr(this->rowPos1 + 1, this->i2cSettings);
	lcd_send_string(this->line1, 1, this->i2cSettings);

	ddram_set_addr(this->rowPos2 + 1, this->i2cSettings);
	lcd_send_string(this->line2, 1, this->i2cSettings);

	ddram_set_addr(this->rowPos3 + 1, this->i2cSettings);
	lcd_send_string(this->line3, 1, this->i2cSettings);

	ddram_set_addr(this->rowPos4 + 1, this->i2cSettings);
	lcd_send_string(this->line4, 1, this->i2cSettings);
}



