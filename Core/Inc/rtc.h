#ifndef INC_RTC_H_
#define INC_RTC_H_

#include <main.h>
#include "stdio.h"

void setDateTime(uint8_t hours = 0x00, uint8_t minutes = 0x00, uint8_t seconds = 0x00, uint8_t day = 0x00, uint8_t month = 0x00, uint8_t date = 0x00, uint8_t year = 0x00);

void getDateTime();

#endif /* INC_RTC_H_ */
