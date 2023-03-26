#ifndef SRC_SCREEN_HPP_
#define SRC_SCREEN_HPP_

#include "main.hpp"
#include "Line.hpp"
#include "lcd_i2c_lib.hpp"
#include <vector>
#include <string>

extern I2C_HandleTypeDef hi2c1;

class Screen {
private:
	Screen *childScreen;
	Screen *parentScreen;

	I2CSettings i2cSettings;

	uint8_t i2cAddr;

	uint8_t cursorChar { 0xC9 };
	uint8_t cursorPos { 0x00 };

	uint8_t rowPos1 { 0x00 };
	uint8_t rowPos2 { 0x40 };
	uint8_t rowPos3 { 0x14 };
	uint8_t rowPos4 { 0x54 };

	std::vector<char> line;
	std::vector<uint8_t> startPos;
	std::vector<uint8_t> endPos;
	std::vector<uint8_t> lineLcdPos;
	uint8_t linesNum {};

	std::vector<Line> lines;

	uint8_t shiftFlag {};

public:
	Screen(I2C_HandleTypeDef *hi2c, uint8_t i2cAddr);
	void cursorDown();

	void cursorUp();

	void displayOneCol(uint8_t shiftRight, uint8_t shiftDown, int8_t shiftMenu);

	void setLineVal(char *line);

	void LineVal(std::string value);

	void selectItem();
};

#endif
