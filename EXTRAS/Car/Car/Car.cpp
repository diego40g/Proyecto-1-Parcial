// CAR.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

void gotoxy(int x,int y)
{
	HANDLE hcon;
	hcon=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X= x;
	dwPos.Y=y;
	SetConsoleCursorPosition(hcon, dwPos);
}

void imprimirCar(int x)
{
	gotoxy(30, 5);
	printf("INGRESO AL PARQUEADERO");
	gotoxy(x, 10);
	printf("  //////////////////////");
	gotoxy(x, 11);
	printf(" //////////////        //////");
	gotoxy(x, 12);
	printf("/////////////////////////////");
	gotoxy(x, 13);
	printf("/////////////////////////////");
	gotoxy(x, 14);
	printf("   (  )            (  )");
	system("cls");
}

int main()
{
	int x=2,aux=13;
	for(;;)
	{
		aux=_getch();
		imprimirCar(x);
		x++;
		if(aux==13)
		{
			break;
		}
		if(x==54)
		{
			x = 0;
		}
	}
	printf("TOMAR EL TICK");
	return 0;
}