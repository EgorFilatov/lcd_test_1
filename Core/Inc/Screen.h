#ifndef INC_SCREEN_H_
#define INC_SCREEN_H_

#include <lcd_i2c_lib.h>
#include <main.h>
#include <vector>
#include <string>

extern I2C_HandleTypeDef hi2c1;

class Screen {

	class Line {
	private:
		std::string value;
		Screen *childScreen;
	public:
		Line();
		void setValue(std::string val);
		void setChild(Screen *childScreen);
		std::string getValue();
		Screen* getChild();
	};

private:
	static I2CSettings i2cSettings;
	Screen *parentScreen;
	uint8_t cursorChar;
	uint8_t cursorPos;
	uint8_t rowPos[4];
	std::vector<Line> line;
	uint8_t linesNum {};
	int8_t menuShift;

	friend class OneColMenuScreen;
	friend class TwoColMenuScreen;
	friend class DateTimeScreen;

public:
	Screen(Screen *parentScreen);
	void setI2CSettings(I2C_HandleTypeDef *hi2c, uint8_t i2cAddr);
	virtual void cursorDown() {}
	virtual void cursorUp() {}
	virtual void show(int8_t shiftVal) {}
	virtual Screen* selectLine();
	void setCursorPos(uint8_t position);
	void setMenuShift(uint8_t shiftVal);
	void displayDateTime();
	void addLine(std::string value, Screen *childScreen);
	void resetLine(uint8_t lineNum, std::string value);
	Screen* getParent();
	uint8_t getMenuShift();
};

#endif
