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


	mainScreen.addLine("��������� ������", &portStateScreen);
	mainScreen.addLine("������� ��", &tsScreen);
	mainScreen.addLine("������� ��", &tyScreen);
	mainScreen.addLine("���������", &measurements);
	mainScreen.addLine("������ �������", &eventScreen);
	mainScreen.addLine("���������", &settingsScreen);

	tsScreen.addLine("���� 1", &tsScreen);
	tsScreen.addLine("���� 2", &tsScreen);
	tsScreen.addLine("���� 3", &tsScreen);
	tsScreen.addLine("���� 4", &tsScreen);
	tsScreen.addLine("���� 5", &tsScreen);
	tsScreen.addLine("���� 6", &tsScreen);
	tsScreen.addLine("���� 7", &tsScreen);
	tsScreen.addLine("���� 8", &tsScreen);
	tsScreen.addLine("���� 9", &tsScreen);
	tsScreen.addLine("���� 10", &tsScreen);
	tsScreen.addLine("���� 11", &tsScreen);
	tsScreen.addLine("���� 12", &tsScreen);
	tsScreen.addLine("���� 13", &tsScreen);
	tsScreen.addLine("���� 14", &tsScreen);
	tsScreen.addLine("���� 15", &tsScreen);
	tsScreen.addLine("���� 16", &tsScreen);

	tyScreen.addLine("���� 1", &tyScreen);
	tyScreen.addLine("���� 2", &tyScreen);
	tyScreen.addLine("���� 3", &tyScreen);
	tyScreen.addLine("���� 4", &tyScreen);
	tyScreen.addLine("���� 5", &tyScreen);
	tyScreen.addLine("���� 6", &tyScreen);
	tyScreen.addLine("���� 7", &tyScreen);
	tyScreen.addLine("���� 8", &tyScreen);
	tyScreen.addLine("���� 9", &tyScreen);
	tyScreen.addLine("���� 10", &tyScreen);
	tyScreen.addLine("���� 11", &tyScreen);
	tyScreen.addLine("���� 12", &tyScreen);
	tyScreen.addLine("���� 13", &tyScreen);
	tyScreen.addLine("���� 14", &tyScreen);
	tyScreen.addLine("���� 15", &tyScreen);
	tyScreen.addLine("���� 16", &tyScreen);

	measurements.addLine("���� �", &measurements);
	measurements.addLine("���� �", &measurements);
	measurements.addLine("���� �", &measurements);

	eventScreen.addLine("������� ��", &eventScreen);
	eventScreen.addLine("������� ��", &eventScreen);

	settingsScreen.addLine("�������� LED", &settingsScreen);
	settingsScreen.addLine("�������� ��", &settingsScreen);
	settingsScreen.addLine("���������", &settingsScreen);
}

#endif /* INC_MENU_H_ */
