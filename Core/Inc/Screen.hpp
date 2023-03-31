#ifndef SRC_SCREEN_HPP_
#define SRC_SCREEN_HPP_

#include "main.hpp"
#include "lcd_i2c_lib.hpp"
#include <vector>
#include <string>

extern I2C_HandleTypeDef hi2c1;

class Screen {

	class Line {
	private:
		std::string val;
		Screen *childScreen;
	public:
		Line();

		void setVal(std::string val);

		std::string getVal();

		void setChild(Screen *childScreen);

		Screen* getChild();
	};

private:
	Screen *parentScreen;

	I2CSettings i2cSettings;

	uint8_t i2cAddr;

	uint8_t cursorChar { 0xC9 };
	uint8_t cursorPos { 0x00 };

	uint8_t rowPos1 { 0x00 };
	uint8_t rowPos2 { 0x40 };
	uint8_t rowPos3 { 0x14 };
	uint8_t rowPos4 { 0x54 };

	std::vector<Line> line;

	uint8_t linesNum {};

	uint8_t shiftFlag {};

public:
	Screen(Screen *parentScreen, I2C_HandleTypeDef *hi2c = &hi2c1, uint8_t i2cAddr = 0x4E);

	Screen(const Screen &screen);

	Screen* operator =(const Screen *screen);

	void cursorDown();

	void cursorUp();

	Screen* selectItem();

	Screen* getParent();

	void displayOneCol(uint8_t shiftRight, int8_t shiftMenu);

	void displayDateTime();

	void setLineVal(std::string value, Screen *childScreen);

	void resetLineVal(std::string value, uint8_t lineNum);
};

#endif
