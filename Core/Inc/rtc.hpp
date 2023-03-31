#ifndef SRC_RTC_HPP_
#define SRC_RTC_HPP_

#include <main.hpp>
#include "stdio.h"

void setDateTime(uint8_t hours = 0x00, uint8_t minutes = 0x00, uint8_t seconds = 0x00, uint8_t day = 0x00, uint8_t month = 0x00, uint8_t date = 0x00, uint8_t year = 0x00);

void getDateTime();

#endif /* SRC_RTC_HPP_ */
