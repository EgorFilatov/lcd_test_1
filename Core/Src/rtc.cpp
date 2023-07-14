#include <rtc.h>

extern RTC_HandleTypeDef hrtc;
extern char time[10];
extern char date[10];

void setDateTime(uint8_t hours, uint8_t minutes, uint8_t seconds, uint8_t day, uint8_t month, uint8_t date, uint8_t year) {
	RTC_TimeTypeDef sTime = {0};
	RTC_DateTypeDef sDate = {0};

	/* Initialize RTC and set the Time and Date */
	sTime.Hours = hours;
	sTime.Minutes = minutes;
	sTime.Seconds = seconds;
	sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	sTime.StoreOperation = RTC_STOREOPERATION_RESET;
	if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK) {
		Error_Handler();
	}
	sDate.WeekDay = day;
	sDate.Month = month;
	sDate.Date = date;
	sDate.Year = year;
	if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK) {
		Error_Handler();
	}
}

void getDateTime()
{
 RTC_DateTypeDef gDate;
 RTC_TimeTypeDef gTime;
/* Get the RTC current Time */
 HAL_RTC_GetTime(&hrtc, &gTime, RTC_FORMAT_BIN);
/* Get the RTC current Date */
 HAL_RTC_GetDate(&hrtc, &gDate, RTC_FORMAT_BIN);
/* Display time Format: hh:mm:ss */
	sprintf((char*) time, "%02d:%02d:%02d", gTime.Hours, gTime.Minutes, gTime.Seconds);
/* Display date Format: dd-mm-yy */
	sprintf((char*) date, "%02d-%02d-%2d", gDate.Date, gDate.Month, 2000 + gDate.Year);
}
