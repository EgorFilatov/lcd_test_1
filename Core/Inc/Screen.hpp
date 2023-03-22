#include "main.hpp"
#include "lcd_i2c_lib.hpp"
#include <vector>

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

	std::vector<char> line;
	std::vector<int> lineSize;

	char line1[13] = "Время и дата";
	char line2[11] = "Сигналы ТС";
	char line3[11] = "Сигналы ТУ";
	char line4[11] = "Сигналы ТИ";
	char line5[10] = "Настройки";
public:
	Screen(I2C_HandleTypeDef *hi2c, uint8_t i2cAddr);
	void cursorDown();

	void cursorUp();

	void display();

	void setLine(char *line);
};

#endif
