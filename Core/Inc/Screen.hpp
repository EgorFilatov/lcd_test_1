#include "main.hpp"
#include "lcd_i2c_lib.hpp"

#ifndef SRC_SCREEN_HPP_
#define SRC_SCREEN_HPP_

extern I2C_HandleTypeDef hi2c1;

class Screen {
private:
	I2CSettings i2cSettings;

	uint8_t i2cAddr;

	uint8_t cursor { 0xC9 };
	uint8_t cursorPos { 0x00 };

	uint8_t rowPos1 { 0x00 };
	uint8_t rowPos2 { 0x40 };
	uint8_t rowPos3 { 0x14 };
	uint8_t rowPos4 { 0x54 };

	char line1[13] = "Время и дата";
	char line2[11] = "Сигналы ТС";
	char line3[11] = "Сигналы ТУ";
	char line4[11] = "Сигналы ТИ";
	char line5[10] = "Настройки";

/*
	char line1[14] = "Date and time";
	char line2[11] = "Sigtals TS";
	char line3[11] = "Signals TY";
	char line4[11] = "Signals TI";
	char line5[9] = "Settings";
*/
public:
	Screen(I2C_HandleTypeDef *hi2c, uint8_t i2cAddr);

	void move_cursor_pos();

	void display();
};

#endif
