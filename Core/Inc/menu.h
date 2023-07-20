#ifndef INC_MENU_H_
#define INC_MENU_H_

#include <main.h>
#include <Screen.h>
#include <OneColMenuScreen.h>
#include <TwoColMenuScreen.h>
#include <DateTimeScreen.h>
#include <FourColScreen.h>

DateTimeScreen dateTimeScreen(&dateTimeScreen);
OneColMenuScreen mainScreen(&dateTimeScreen);
FourColScreen portStateScreen(&mainScreen);
TwoColMenuScreen tsScreen(&mainScreen);
TwoColMenuScreen tyScreen(&mainScreen);
OneColMenuScreen measurements(&mainScreen);
OneColMenuScreen eventScreen(&mainScreen);
OneColMenuScreen settingsScreen(&mainScreen);

void menuInit() {
	dateTimeScreen.addLine("00:00", &mainScreen);
	dateTimeScreen.addLine("00-00-0000", &mainScreen);

	portStateScreen.addLine("1.", &portStateScreen);
	portStateScreen.addLine("2.", &portStateScreen);
	portStateScreen.addLine("3.", &portStateScreen);
	portStateScreen.addLine("4.", &portStateScreen);
	portStateScreen.addLine("5.", &portStateScreen);
	portStateScreen.addLine("6.", &portStateScreen);
	portStateScreen.addLine("7.", &portStateScreen);
	portStateScreen.addLine("8.", &portStateScreen);
	portStateScreen.addLine("9.", &portStateScreen);
	portStateScreen.addLine("10.", &portStateScreen);
	portStateScreen.addLine("11.", &portStateScreen);
	portStateScreen.addLine("12.", &portStateScreen);
	portStateScreen.addLine("13.", &portStateScreen);
	portStateScreen.addLine("14.", &portStateScreen);
	portStateScreen.addLine("15.", &portStateScreen);
	portStateScreen.addLine("16.", &portStateScreen);
	portStateScreen.addLine("17.", &portStateScreen);
	portStateScreen.addLine("18.", &portStateScreen);
	portStateScreen.addLine("19.", &portStateScreen);
	portStateScreen.addLine("20.", &portStateScreen);
	portStateScreen.addLine("21.", &portStateScreen);
	portStateScreen.addLine("22.", &portStateScreen);


	mainScreen.addLine("Состояние портов", &portStateScreen);
	mainScreen.addLine("Сигналы ТС", &tsScreen);
	mainScreen.addLine("Сигналы ТУ", &tyScreen);
	mainScreen.addLine("Измерения", &measurements);
	mainScreen.addLine("Журнал событий", &eventScreen);
	mainScreen.addLine("Настройки", &settingsScreen);

	tsScreen.addLine("Порт 1", &tsScreen);
	tsScreen.addLine("Порт 2", &tsScreen);
	tsScreen.addLine("Порт 3", &tsScreen);
	tsScreen.addLine("Порт 4", &tsScreen);
	tsScreen.addLine("Порт 5", &tsScreen);
	tsScreen.addLine("Порт 6", &tsScreen);
	tsScreen.addLine("Порт 7", &tsScreen);
	tsScreen.addLine("Порт 8", &tsScreen);
	tsScreen.addLine("Порт 9", &tsScreen);
	tsScreen.addLine("Порт 10", &tsScreen);
	tsScreen.addLine("Порт 11", &tsScreen);
	tsScreen.addLine("Порт 12", &tsScreen);
	tsScreen.addLine("Порт 13", &tsScreen);
	tsScreen.addLine("Порт 14", &tsScreen);
	tsScreen.addLine("Порт 15", &tsScreen);
	tsScreen.addLine("Порт 16", &tsScreen);

	tyScreen.addLine("Порт 1", &tyScreen);
	tyScreen.addLine("Порт 2", &tyScreen);
	tyScreen.addLine("Порт 3", &tyScreen);
	tyScreen.addLine("Порт 4", &tyScreen);
	tyScreen.addLine("Порт 5", &tyScreen);
	tyScreen.addLine("Порт 6", &tyScreen);
	tyScreen.addLine("Порт 7", &tyScreen);
	tyScreen.addLine("Порт 8", &tyScreen);
	tyScreen.addLine("Порт 9", &tyScreen);
	tyScreen.addLine("Порт 10", &tyScreen);
	tyScreen.addLine("Порт 11", &tyScreen);
	tyScreen.addLine("Порт 12", &tyScreen);
	tyScreen.addLine("Порт 13", &tyScreen);
	tyScreen.addLine("Порт 14", &tyScreen);
	tyScreen.addLine("Порт 15", &tyScreen);
	tyScreen.addLine("Порт 16", &tyScreen);

	measurements.addLine("Фаза А", &measurements);
	measurements.addLine("Фаза В", &measurements);
	measurements.addLine("Фаза С", &measurements);

	eventScreen.addLine("События ТС", &eventScreen);
	eventScreen.addLine("События ТУ", &eventScreen);

	settingsScreen.addLine("Проверка LED", &settingsScreen);
	settingsScreen.addLine("Проверка ТУ", &settingsScreen);
	settingsScreen.addLine("Подсветка", &settingsScreen);
}

#endif /* INC_MENU_H_ */
