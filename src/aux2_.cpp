#include "aux2_.h"


string getDate() // codigo de https://xtokio.github.io/blog/2017/c-obtener-fecha-actual/
{
	time_t t = time(NULL);
	tm* timePtr = localtime(&t);

	stringstream ss_year;
	ss_year << timePtr->tm_year + 1900;
	string Year = ss_year.str();

	stringstream ss_month;
	ss_month << timePtr->tm_mon + 1;
	string Month = ss_month.str();
	if (atoi(Month.c_str()) < 10)
		Month = "0" + Month;

	stringstream ss_day;
	ss_day << timePtr->tm_mday;
	string Day = ss_day.str();
	if (atoi(Day.c_str()) < 10)
		Day = "0" + Day;

	stringstream ss_hour;
	ss_hour << timePtr->tm_hour;
	string Hour = ss_hour.str();
	if (atoi(Hour.c_str()) < 10)
		Hour = "0" + Hour;

	stringstream ss_min;
	ss_min << timePtr->tm_min;
	string Min = ss_min.str();
	if (atoi(Min.c_str()) < 10)
		Min = "0" + Min;

	stringstream ss_sec;
	ss_sec << timePtr->tm_sec;
	string Sec = ss_sec.str();
	if (atoi(Sec.c_str()) < 10)
		Sec = "0" + Sec;

	string Fecha = Year + "/" + Month + "/" + Day + "_" + Hour + ":" + Min + ":" + Sec;

	return Fecha;

}