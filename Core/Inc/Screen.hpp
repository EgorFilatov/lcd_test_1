#include "main.hpp"
#include "lcd_i2c_lib.hpp"

#ifndef SRC_SCREEN_HPP_
#define SRC_SCREEN_HPP_
extern I2C_HandleTypeDef hi2c1;

class Screen {
private:
	uint8_t addr = 0x4E;

	uint8_t cursor;
	uint8_t cursor_pos;

	char string_1[13] = "����� � ����";
	uint8_t string_1_pos { };

	char string_2[11] = "������� ��";
	uint8_t string_2_pos { };

	char string_3[11] = "������� ��";
	uint8_t string_3_pos { };

	char string_4[11] = "������� ��";
	uint8_t string_4_pos { };

	char string_5[10] = "���������";
	uint8_t string_5_pos { };

public:
	Screen(uint8_t cursor_pos);

	void move_cursor_pos();

	void display();
};

#endif
