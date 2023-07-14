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
	static I2CSettings i2cSettings;
	Screen *parentScreen;
	uint8_t cursorChar;
	uint8_t cursorPos;
	uint8_t rowPos[4];
	std::vector<Line> line;
	uint8_t linesNum {};
	//uint8_t menuShift;
	uint8_t shiftFlag;

	friend class OneColMenuScreen;
	friend class TwoColMenuScreen;

public:
	Screen(Screen *parentScreen);
	void setI2CSettings(I2C_HandleTypeDef *hi2c, uint8_t i2cAddr);
	virtual void cursorDown();
	virtual void cursorUp();
	virtual void show(uint8_t shiftMenu);
	void setCursorPos(uint8_t position);
	void setShiftFlag(uint8_t shiftFlag);
	void displayDateTime();
	void addLine(std::string value, Screen *childScreen);
	void resetLine(std::string value, uint8_t lineNum);
	Screen* selectLine();
	Screen* getParent();
	uint8_t getShiftFlag();
};

#endif
