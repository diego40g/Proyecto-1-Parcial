#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
#include<stdio.h>


int main()
{
	char horaEntrada[80];
	char fecha[50];
	char hora[30];
	GetDateFormat(LOCALE_USER_DEFAULT, DATE_LONGDATE, NULL, NULL, fecha, 50);
	GetTimeFormat(LOCALE_USER_DEFAULT, TIME_FORCE24HOURFORMAT, NULL, NULL, hora, 30);
	strcpy_s(horaEntrada, strlen(fecha) + 1, fecha);
	strcat_s(horaEntrada, sizeof horaEntrada, hora);

	printf("\n%s", horaEntrada);
	system("pause");
	return 0;
}