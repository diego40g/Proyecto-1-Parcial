// PDF.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Header.h"
#include "Librerias.h"

using namespace std;

int  AyudaF1()
{
	int x;
	int imp;
	printf("\nPresione Enter ");
	for (;; ) {
		x = _getch();//captura la tecla de función ,pertenece a la libreria conio.h
		if (x == 13)
		{
			imp = 1;
			printf("\nGenerando...");
			break;
		}
	}
	return imp;
}

int main()
{
	int nume;
	printf("Ingrese numero:");
	scanf_s("%d", &nume);
	FILE *fs;
	fopen_s(&fs,"DATOS.txt","w+");
	fprintf(fs,"Hola %d",nume);
	fclose(fs);

	/***********************************/

	int imp;
	system("cls");
	imp = AyudaF1();
	if (imp == 1)
	{
		ofstream LeerDatos;
		LeerDatos.open("Datos.txt", ios::out | ios::app);
		tifstream in(TEXT("Datos.txt"));
		PrintFile(in);
		ShellExecute(NULL, TEXT("open"), TEXT("D:\\Programacion 1\\C++\\Proyecto\\PDF QR\\pdf\\Datos.pdf"), NULL, NULL, SW_SHOWNORMAL);
	}
	system("pause");
	_getch();
	return 0;
}