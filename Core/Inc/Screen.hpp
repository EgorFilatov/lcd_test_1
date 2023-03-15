#include "main.hpp"

#ifndef SRC_SCREEN_HPP_
#define SRC_SCREEN_HPP_

class Screen {
public:
	Screen(uint8_t num = 0, uint8_t pos = 0, uint8_t cursor_pos = 0);

	uint8_t num { };
	uint8_t pos { };
	uint8_t cursor_pos { };
};

#endif
