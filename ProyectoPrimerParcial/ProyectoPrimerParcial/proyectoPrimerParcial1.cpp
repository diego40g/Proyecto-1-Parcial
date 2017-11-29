/*UNIVERSIDAD DE LAS FUERZAS ARMADAS "ESPE"
INGENIERIA EN SISTEMAS E INFORMATICA
PROYECTO PRIMER PARCIAL
INTEGRANTES: MICHAEL MORALES, DIEGO PAZ
PROFESOR: FERNANDO SOLIS
*/
//PERMITE UTILIZAR FUNCIONES COMO strcpy()
#define _CRT_SECURE_NO_WARNINGS
/*#ifdef _MSC_VER
#define _CTR_SECURE_NO_WARNINGS
#endif*/
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h> 
#include <string.h>
#include <string>
#include <MMsystem.h>
#include <ctype.h>
#include <fstream>
#include <iomanip>
#include"PDF.h"
#include"stdafx.h"
#include"Librerias.h"
#include"qrcodegen.h"
using namespace std;

struct Nodo {
	char horaEntrada[11];
	char fechaEntrada[35];
	char horaSalida[11];
	char fechaSalida[35];
	long int numeroCedula;
	char modeloAuto[10];
	float tarifaPagar;
	char nombrePropietario[15];
	char placaAuto[10];
	struct Nodo *siguienteDireccion;
	struct Nodo *anteriorDireccion;
};
typedef struct Nodo *ListaDoble;
struct Placas {
	char letrasPlaca[3];
	char numerosPlaca[4];
};
typedef struct Placas placa;
void color(int X) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), X);
}
void gotoxy(int x, int y) {
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon, dwPos);
}
void imprimirCar(int x)
{
	system("cls");
	color(9);
	gotoxy(30, 5);
	printf("INGRESO AL PARQUEADERO");
	gotoxy(x, 10);
	printf("  //////////////////");
	gotoxy(x, 11);
	printf(" /////////////     //");
	gotoxy(x, 12);
	printf("//////////////////////////");
	gotoxy(x, 13);
	printf("/////////////////////////");
	gotoxy(x, 14);
	printf("   (  )            (  )");
}
void carrito()
{
	int x = 2, aux = 13;

	for (;;)
	{
		aux = _getch();
		imprimirCar(x);
		x++;
		if (aux == 13)
		{
			break;
		}
		if (x == 54)
		{
			x = 0;
		}
	}
	system("cls");
	printf("TOMAR EL TICK");
}

string convertir(char *c, int i) {
	return string(*c, i);
}
char* covertStringChar(string cadena) {
	char* aux = new char[cadena.size()];
	strcpy(aux, cadena.c_str());
	return aux;
}

/*
llamar a la ayuda
ShellExecute(NULL, TEXT("open"), TEXT("ayuda.chm"), NULL, NULL, SW_SHOWNORMAL);
ex = 'n';
break;
*/
int  AyudaF1()//23 esc y 13 intro
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
void letras(char* val) {
	int c, i = 0;
	i = 0;
	while ((c = _getch()) != 13) {
		if ((c >= 65 && c <= 90) ||  c == 32) {
			*(val + i) = c;
			printf("%c", c);
			i++;
		}
		*(val + i) = '\0';
	}

	return;
}
static void printQr(const uint8_t qrcode[]) {
	int size = qrcodegen_getSize(qrcode);
	int border = 4;
	for (int y = -border; y < size + border; y++) {
		for (int x = -border; x < size + border; x++) {
			fputs((qrcodegen_getModule(qrcode, x, y) ? "\333\333" : "  "), stdout);
		}
		fputs("\n", stdout);
	}
}

static void generarQr(char *loqueimprime)
{
	char *dato = loqueimprime;
	enum qrcodegen_Ecc errCorLvl = qrcodegen_Ecc_LOW;  // Error correction level

													   // Make and print the QR Code symbol
	uint8_t qrcode[qrcodegen_BUFFER_LEN_MAX];
	uint8_t tempBuffer[qrcodegen_BUFFER_LEN_MAX];
	bool ok = qrcodegen_encodeText(dato, tempBuffer, qrcode, errCorLvl,
		qrcodegen_VERSION_MIN, qrcodegen_VERSION_MAX, qrcodegen_Mask_AUTO, true);
	if (ok)
		printQr(qrcode);
}
void numeros(char* val) {
	int c, i = 0;
	i = 0;
	while ((c = _getch()) != 13) {
		if ((c >= 48 && c <= 57)) {

			*(val + i) = c;
			printf("%c", c);
			i++;
		}
		*(val + i) = '\0';
	}
}
void flotantes(char* val) {
	int c, i = 0;
	i = 0;
	while ((c = _getch()) != 13) {
		if ((c >= 48 && c <= 57) || c == 46) {

			*(val + i) = c;
			printf("%c", c);
			i++;
		}
		*(val + i) = '\0';
	}
}
void ingresar(char *ced) {
	int  i = 0, asc = 48, num = 0;
	do {
		i = 0;
		printf("Ingrese su cedula\n");

		int c;
		while ((c = _getch()) != 13) {
			if ((c >= 48 && c <= 57)) {

				*(ced + i) = c;
				printf("%c", c);
				i++;
			}
		}
	} while (i>10 || i <= 9);

	printf("\n");

}
int cambio(int a, int asc, int num) {
	if (a == asc) {
		return num;
	}
	else {
		cambio(a, asc += 1, num += 1);
	}
}
int verificar(char *d) {
	int sum = 0, mult = 0, sum1 = 0, sum2 = 0, tot = 0, asc = 48, num = 0;

	//int* c;
	//	c = (int*)malloc(10 * sizeof(int));
	int c[10];
	for (int i = 0; i<10; i++) {
		*(c + i) = cambio(*(d + i), asc, num);
	}

	printf("\n");

	for (int i = 0; i<10; i = i + 2) {
		mult = *(c + i) * 2;
		sum1 = mult;
		if (sum1>9) {
			sum += sum1 - 9;
		}
		else {
			sum = sum + mult;
		}
	}

	for (int i = 1; i<8; i = i + 2) {
		sum2 += *(c + i);
		tot = sum + sum2;
		tot = tot % 10;
		tot = 10 - tot;
		if (tot == 10)
			tot = 0;
	}
	if (*(c + 9) == tot)
		return 1;
	else
		return 0;
}
void imprimir(int a) {
	if (a == 1) {
		printf("la cedula es correcta");
	}
	else {
		printf("la cedula es incorrecta");
	}
}
char* cedula() {

	int a;
	char *ced;
	ced = (char *)malloc(10 * sizeof(char));
	do {
		ingresar(ced);
		a = verificar(ced);
		if (a == 0) {
			printf("\nLa cedula es incorrecta\n");
		}
	} while (a == 0);
	imprimir(a);
	return ced;

}
int menu() {
	char c;
	const char *fr[50] = {"INGRESAR PRIMER AUTO AL PARQUEADERO		",
						  "INGRESAR AUTO ALINICIO DEL PARQUEADERO	",
						  "INGRESAR AUTO AL FINAL DEL PARQUEADERO	",
						  "INGRESAR AUTO ENTRE PARQUEADEROS			",
						  "MOSTRAR LISTA DE AUTOS EN EL PARQUEADERO	",
						  "AYUDA DEL PROGRAMA						",
						  "IMAGEN DEL GRUPO							",
						  "SALIR DEL PARQUEADERO					",
						  "SALIR DEL SISTEMA						" };
	system("cls");
	gotoxy(40, 1);
	printf("MENU");
	int y = 2, n;
	for (int i = 1; i<10; i++) {
		if (i == 1) {
			color(78);
			gotoxy(20, y + i);
			printf("%s", fr[i - 1]);
			color(07);
		}
		else {
			color(07);
			gotoxy(20, y + i);
			printf("%s", fr[i - 1]);
		}
	}
	do {
		c = _getch();
		gotoxy(20, y + 1);
		color(07);
		for (int i = y; i<11; i++) {
			gotoxy(20, i + 1);
			printf("%s", fr[i - 2]);
		}

		if (c == -32) {
			c = _getch();
			if (c == 72) {
				if (y == 2) {
					y = 10;
				}
				else {
					y--;
				}

			}
			if (c == 80) {
				if (y == 10) {
					y = 2;
				}
				else {
					y++;
				}
			}
		}
		if (c == 13) {
			n = y - 1;
			break;
		}
		else {
			gotoxy(20, y + 1);
			color(78);
			printf("%s", fr[y - 2]);
		}
	} while (1);
	return n;
}
void ingresarPrimerDato(ListaDoble &lista) {
	char*QR = (char*)malloc(50 * sizeof(char));
	char*cad1 = (char*)malloc(10 * sizeof(char));
	FILE *ticket;
	Nodo *aux = new Nodo();
	char *modeloAuto = (char*)malloc(10 * sizeof(char));
	char *nombrePropietario = (char*)malloc(15 * sizeof(char));
	char *placaAuto = (char*)malloc(10 * sizeof(char));
	char *letrasPlaca = (char*)malloc(3 * sizeof(char));
	char *numerosPlaca = (char*)malloc(4 * sizeof(char));
	if (lista == NULL) {
	aux->numeroCedula = atoi(cedula());
	printf("\nINGRESE NOMBRE DEL PROPIETARIO:");
	letras(aux->nombrePropietario);
	printf("\nINGRESE PLACA");
	do {
		printf("\nINGRESE LETRAS DE LA PLACA:");
		letras(letrasPlaca);
	} while (strlen(letrasPlaca) < 3 || strlen(letrasPlaca) > 3);
	strcpy(aux->placaAuto, letrasPlaca);
	strcat(aux->placaAuto, "-");
	do {
		printf("\nINGRESE NUMEROS DE LA PLACA:");
		printf("\nSI SU PLACA TIENE TRES NUMEROS ANTEPONGA EL NUMERO 0\n");
		numeros(numerosPlaca);
	} while (strlen(numerosPlaca) < 4 || strlen(numerosPlaca) > 4);
	strcat(aux->placaAuto, numerosPlaca);
	printf("\nINGRESE MODELO DEL AUTO: ");
	letras(aux->modeloAuto);
	GetDateFormat(LOCALE_USER_DEFAULT, DATE_LONGDATE, NULL, NULL, aux->fechaEntrada, 35);
	GetTimeFormat(LOCALE_USER_DEFAULT, TIME_FORCE24HOURFORMAT, NULL, NULL, aux->horaEntrada, 11);
	aux->anteriorDireccion = aux->siguienteDireccion = NULL;
	lista = aux;
	carrito(); color(07);
	system("pause");
	system("CLS");
	fopen("TICKET DE ENTRADA.txt", "w");
	system("cls");
	ticket = fopen("TICKET DE ENTRADA.txt", "w");
	printf("*****************************************************");
	gotoxy(18, 1);
	printf("TICKET DE ENTRADA");
	gotoxy(0, 1);
	printf("*");
	gotoxy(52, 1);
	printf("*");
	gotoxy(0, 2);
	printf("* NOMBRE CLIENTE: %s", aux->nombrePropietario);
	gotoxy(52, 2);
	printf("*");
	gotoxy(0, 3);
	printf("* CEDULA DEL CLIENTE: %d", aux->numeroCedula);
	gotoxy(52, 3);
	printf("*");
	gotoxy(0, 4);
	printf("* FECHA DE ENTRADA: %s", aux->fechaEntrada);
	gotoxy(52, 4);
	printf("*");
	gotoxy(0, 5);
	printf("* HORA DE ENTRADA: %s", aux->horaEntrada);
	gotoxy(52, 5);
	printf("*");
	gotoxy(0, 6);
	printf("* PLACA DEL VEHICULO: %s", aux->placaAuto);
	gotoxy(52, 6);
	printf("*");
	gotoxy(0, 7);
	printf("* VEHICULO: %s", aux->modeloAuto);
	gotoxy(52, 7);
	printf("*");
	gotoxy(18, 8);
	printf("HORA O FRACCION");
	gotoxy(0, 8);
	printf("*");
	gotoxy(52, 8);
	printf("*");
	gotoxy(0, 9);
	printf("*****************************************************\n");
	fprintf(ticket, "*********************************************************");
	fprintf(ticket, "\n*\t\tTICKET DE ENTRADA\t\t\t*");
	fprintf(ticket, "\n* NOMBRE CLIENTE: %s\t\t\t*", aux->nombrePropietario);
	fprintf(ticket, "\n* CEDULA DEL CLIENTE: %d\t\t\t*", aux->numeroCedula);
	fprintf(ticket, "\n* FECHA DE ENTRADA: %s\t*", aux->fechaEntrada);
	fprintf(ticket, "\n* HORA DE ENTRADA: %s\t\t\t\t*", aux->horaEntrada);
	fprintf(ticket, "\n* PLACA DEL VEHICULO: %s\t\t\t\t*", aux->placaAuto);
	fprintf(ticket, "\n* VEHICULO: %s\t\t\t\t\t*", aux->modeloAuto);
	fprintf(ticket, "\n*\t\tHORA O FRACCION\t\t\t\t*");
	fprintf(ticket, "\n*********************************************************");
	fclose(ticket);
	system("pause");
	system("CLS");
	strcpy(QR, aux->nombrePropietario);
	strcat(QR, "\n");
	_itoa(aux->numeroCedula, cad1, 10);
	strcat(QR, cad1 );
	strcat(QR, "\n");
	strcat(QR, aux->fechaEntrada);
	strcat(QR, "\n");
	strcat(QR, aux->horaEntrada);
	strcat(QR, "\n");
	strcat(QR, aux->placaAuto);
	strcat(QR, "\n");
	strcat(QR, aux->modeloAuto);
	strcat(QR, "\n");
	strcat(QR, "HORA O FRACCION");
	generarQr(QR);
	}
	else {
		printf("\nEL PRIMER VEHICULO YA ESTA EN EL PARQUEADERO\n");
	}

}
void ingresarUltimaPosicion(ListaDoble &lista) {
	char*QR = (char*)malloc(50 * sizeof(char));
	char*cad1 = (char*)malloc(10 * sizeof(char));
	FILE *ticket;
	Placas placa;
	Nodo *aux2 = lista, *aux = new Nodo();

	char *letrasPlaca = (char*)malloc(3 * sizeof(char));
	//char letrasPlaca[3], numeroPlaca[4], fecha[50], hora[30];
	char *numeroPlaca = (char*)malloc(4 * sizeof(char));

	char *fecha = (char*)malloc(50 * sizeof(char));
	char *hora = (char*)malloc(30 * sizeof(char));;

	if (lista != NULL) {

		aux->numeroCedula = atoi(cedula());
		printf("\nINGRESE NOMBRE DEL PROPIETARIO:");
		//fflush(stdin);
		letras(aux->nombrePropietario);
		printf("\nINGRESE PLACA");
		do {
			printf("\nINGRESE LETRAS DE LA PLACA:");
			letras(letrasPlaca);
		} while (strlen(letrasPlaca) < 3 || strlen(letrasPlaca) > 3);
		strcpy(aux->placaAuto, letrasPlaca);
		strcat(aux->placaAuto, "-");
		do {
			printf("\nINGRESE NUMEROS DE LA PLACA:");
			printf("\nSI SU PLACA TIENE TRES NUMEROS ANTEPONGA EL NUMERO 0\n");
			numeros(numeroPlaca);
		} while (strlen(numeroPlaca) < 4 || strlen(numeroPlaca) > 4);
		strcat(aux->placaAuto, numeroPlaca);
		if (lista->siguienteDireccion == NULL) {
			if (strcmp(lista->placaAuto, aux->placaAuto) == 0) {
				printf("\nEL AUTO NO PUEDE INGRESAR PUES YA ESTA DENTRO DEL PARQUEADERO");
				return;
			}
		}
		if (lista->siguienteDireccion != NULL) {

			while (lista->siguienteDireccion != NULL) {
				if (strcmp(lista->placaAuto, aux->placaAuto) == 0) {
					printf("\nEL AUTO NO PUEDE INGRESAR PUES YA ESTA DENTRO DEL PARQUEADERO");
					while (lista->anteriorDireccion != NULL) {
						lista = lista->anteriorDireccion;
					}
					return;
				}
				lista = lista->siguienteDireccion;
				if (lista->siguienteDireccion == NULL) {
					if (strcmp(lista->placaAuto, aux->placaAuto) == 0) {
						printf("\nEL AUTO NO PUEDE INGRESAR PUES YA ESTA DENTRO DEL PARQUEADERO");
						while (lista->anteriorDireccion != NULL) {
							lista = lista->anteriorDireccion;
						}
						return;
					}
				}
			}
		}
		while (lista->anteriorDireccion != NULL) {
			lista = lista->anteriorDireccion;
		}
		printf("\nINGRESE MODELO DEL AUTO: ");
		letras(aux->modeloAuto);
		GetDateFormat(LOCALE_USER_DEFAULT, DATE_LONGDATE, NULL, NULL, aux->fechaEntrada, 50);
		GetTimeFormat(LOCALE_USER_DEFAULT, TIME_FORCE24HOURFORMAT, NULL, NULL, aux->horaEntrada, 30);
		//aux2 = lista;
		while (aux2->siguienteDireccion != NULL) {
			aux2 = aux2->siguienteDireccion;
		}
		aux->siguienteDireccion = aux2->siguienteDireccion;
		aux2->siguienteDireccion = aux;
		aux->anteriorDireccion = aux2;
		carrito(); color(07);
		printf("\nDATO INGRESADO!");
		system("pause");
		system("cls");
		fopen("TICKET DE ENTRADA.txt", "w");
		system("cls");
		ticket = fopen("TICKET DE ENTRADA.txt", "w");
		printf("*****************************************************");
		gotoxy(18, 1);
		printf("TICKET DE ENTRADA");
		gotoxy(0, 1);
		printf("*");
		gotoxy(52, 1);
		printf("*");
		gotoxy(0, 2);
		printf("* NOMBRE CLIENTE: %s", aux->nombrePropietario);
		gotoxy(52, 2);
		printf("*");
		gotoxy(0, 3);
		printf("* CEDULA DEL CLIENTE: %d", aux->numeroCedula);
		gotoxy(52, 3);
		printf("*");
		gotoxy(0, 4);
		printf("* FECHA DE ENTRADA: %s", aux->fechaEntrada);
		gotoxy(52, 4);
		printf("*");
		gotoxy(0, 5);
		printf("* HORA DE ENTRADA: %s", aux->horaEntrada);
		gotoxy(52, 5);
		printf("*");
		gotoxy(0, 6);
		printf("* PLACA DEL VEHICULO: %s", aux->placaAuto);
		gotoxy(52, 6);
		printf("*");
		gotoxy(0, 7);
		printf("* VEHICULO: %s", aux->modeloAuto);
		gotoxy(52, 7);
		printf("*");
		gotoxy(18, 8);
		printf("HORA O FRACCION");
		gotoxy(0, 8);
		printf("*");
		gotoxy(52, 8);
		printf("*");
		gotoxy(0, 9);
		printf("*****************************************************\n");
		fprintf(ticket, "*********************************************************");
		fprintf(ticket, "\n*\t\tTICKET DE ENTRADA\t\t\t*");
		fprintf(ticket, "\n* NOMBRE CLIENTE: %s\t\t\t*", aux->nombrePropietario);
		fprintf(ticket, "\n* CEDULA DEL CLIENTE: %d\t\t\t*", aux->numeroCedula);
		fprintf(ticket, "\n* FECHA DE ENTRADA: %s\t*", aux->fechaEntrada);
		fprintf(ticket, "\n* HORA DE ENTRADA: %s\t\t\t\t*", aux->horaEntrada);
		fprintf(ticket, "\n* PLACA DEL VEHICULO: %s\t\t\t\t*", aux->placaAuto);
		fprintf(ticket, "\n* VEHICULO: %s\t\t\t\t\t*", aux->modeloAuto);
		fprintf(ticket, "\n*\t\tHORA O FRACCION\t\t\t\t*");
		fprintf(ticket, "\n*********************************************************");
		fclose(ticket);
		system("pause");
		system("CLS");
		strcpy(QR, aux->nombrePropietario);
		strcat(QR, "\n");
		_itoa(aux->numeroCedula, cad1, 10);
		strcat(QR, cad1);
		strcat(QR, "\n");
		strcat(QR, aux->fechaEntrada);
		strcat(QR, "\n");
		strcat(QR, aux->horaEntrada);
		strcat(QR, "\n");
		strcat(QR, aux->placaAuto);
		strcat(QR, "\n");
		strcat(QR, aux->modeloAuto);
		strcat(QR, "\n");
		strcat(QR, "HORA O FRACCION");
		generarQr(QR);
	}
	else {
		printf("\nDEBE INGRESAR EL PRIMER ELEMENTO!!\n");
	}
}
void ingresarPrimeraPosicion(ListaDoble &lista) {
	char*QR = (char*)malloc(50 * sizeof(char));
	char*cad1 = (char*)malloc(10 * sizeof(char));
	FILE *ticket;
	Nodo *aux = new Nodo(), *aux2 = lista;
	Placas placa;
	char *letrasPlaca = (char*)malloc(3 * sizeof(char));
	//char letrasPlaca[3], numeroPlaca[4], fecha[50], hora[30];
	char *numeroPlaca = (char*)malloc(4 * sizeof(char));

	char *fecha = (char*)malloc(50 * sizeof(char));
	char *hora = (char*)malloc(30 * sizeof(char));;
	if (lista != NULL) {

		aux->numeroCedula = atoi(cedula());
		printf("\nINGRESE NOMBRE DEL PROPIETARIO DEL AUTO:");
		//fflush(stdin);
		letras(aux->nombrePropietario);
		printf("\nINGRESE PLACA");
		do {
			printf("\nINGRESE LETRAS DE LA PLACA:");
			letras(letrasPlaca);
		} while (strlen(letrasPlaca) <3 || strlen(letrasPlaca)>3);
		strcpy(aux->placaAuto, letrasPlaca);
		strcat(aux->placaAuto, "-");
		do {
			printf("\nINGRESE NUMEROS DE LA PLACA:");
			printf("\nSI SU PLACA TIENE TRES NUMEROS ANTEPONGA EL NUMERO 0\n");
			numeros(numeroPlaca);
		} while (strlen(numeroPlaca) < 4 || strlen(numeroPlaca) > 4);
		strcat(aux->placaAuto, numeroPlaca);
		if (lista->siguienteDireccion == NULL) {
			if (strcmp(lista->placaAuto, aux->placaAuto) == 0) {
				printf("\nEL AUTO NO PUEDE INGRESAR PUES YA ESTA DENTRO DEL PARQUEADERO");
				return;
			}
		}
		if(lista->siguienteDireccion!=NULL) {

			while (lista->siguienteDireccion != NULL) {
				if (strcmp(lista->placaAuto, aux->placaAuto) == 0) {
					printf("\nEL AUTO NO PUEDE INGRESAR PUES YA ESTA DENTRO DEL PARQUEADERO");
					while (lista->anteriorDireccion != NULL) {
						lista = lista->anteriorDireccion;
					}
					return;
				}
				lista = lista->siguienteDireccion;
				if (lista->siguienteDireccion == NULL) {
					if (strcmp(lista->placaAuto, aux->placaAuto) == 0) {
						printf("\nEL AUTO NO PUEDE INGRESAR PUES YA ESTA DENTRO DEL PARQUEADERO");
						while (lista->anteriorDireccion != NULL) {
							lista = lista->anteriorDireccion;
						}
						return;
					}
				}
			}
		}
		while (lista->anteriorDireccion != NULL) {
			lista = lista->anteriorDireccion;
		}
		printf("\nINGRESE MODELO DEL AUTO: ");
		letras(aux->modeloAuto);
		GetDateFormat(LOCALE_USER_DEFAULT, DATE_LONGDATE, NULL, NULL, aux->fechaEntrada, 50);
		GetTimeFormat(LOCALE_USER_DEFAULT, TIME_FORCE24HOURFORMAT, NULL, NULL, aux->horaEntrada, 30);
		aux->siguienteDireccion = lista;
		aux->anteriorDireccion = lista->anteriorDireccion;
		lista->anteriorDireccion = aux;
		lista = aux;
		carrito(); color(07);
		printf("\nDATO INGRESADO!!!\n");
		system("pause");
		system("cls");
		fopen("TICKET DE ENTRADA.txt", "w");
		system("cls");
		ticket = fopen("TICKET DE ENTRADA.txt", "w");
		printf("*****************************************************");
		gotoxy(18, 1);
		printf("TICKET DE ENTRADA");
		gotoxy(0, 1);
		printf("*");
		gotoxy(52, 1);
		printf("*");
		gotoxy(0, 2);
		printf("* NOMBRE CLIENTE: %s", aux->nombrePropietario);
		gotoxy(52, 2);
		printf("*");
		gotoxy(0, 3);
		printf("* CEDULA DEL CLIENTE: %d", aux->numeroCedula);
		gotoxy(52, 3);
		printf("*");
		gotoxy(0, 4);
		printf("* FECHA DE ENTRADA: %s", aux->fechaEntrada);
		gotoxy(52, 4);
		printf("*");
		gotoxy(0, 5);
		printf("* HORA DE ENTRADA: %s", aux->horaEntrada);
		gotoxy(52, 5);
		printf("*");
		gotoxy(0, 6);
		printf("* PLACA DEL VEHICULO: %s", aux->placaAuto);
		gotoxy(52, 6);
		printf("*");
		gotoxy(0, 7);
		printf("* VEHICULO: %s", aux->modeloAuto);
		gotoxy(52, 7);
		printf("*");
		gotoxy(18, 8);
		printf("HORA O FRACCION");
		gotoxy(0, 8);
		printf("*");
		gotoxy(52, 8);
		printf("*");
		gotoxy(0, 9);
		printf("*****************************************************\n");
		fprintf(ticket, "*********************************************************");
		fprintf(ticket, "\n*\t\tTICKET DE ENTRADA\t\t\t*");
		fprintf(ticket, "\n* NOMBRE CLIENTE: %s\t\t\t*", aux->nombrePropietario);
		fprintf(ticket, "\n* CEDULA DEL CLIENTE: %d\t\t\t*", aux->numeroCedula);
		fprintf(ticket, "\n* FECHA DE ENTRADA: %s\t*", aux->fechaEntrada);
		fprintf(ticket, "\n* HORA DE ENTRADA: %s\t\t\t\t*", aux->horaEntrada);
		fprintf(ticket, "\n* PLACA DEL VEHICULO: %s\t\t\t\t*", aux->placaAuto);
		fprintf(ticket, "\n* VEHICULO: %s\t\t\t\t\t*", aux->modeloAuto);
		fprintf(ticket, "\n*\t\tHORA O FRACCION\t\t\t\t*");
		fprintf(ticket, "\n*********************************************************");
		fclose(ticket);
		system("pause");
		system("CLS");
		strcpy(QR, aux->nombrePropietario);
		strcat(QR, "\n");
		_itoa(aux->numeroCedula, cad1, 10);
		strcat(QR, cad1);
		strcat(QR, "\n");
		strcat(QR, aux->fechaEntrada);
		strcat(QR, "\n");
		strcat(QR, aux->horaEntrada);
		strcat(QR, "\n");
		strcat(QR, aux->placaAuto);
		strcat(QR, "\n");
		strcat(QR, aux->modeloAuto);
		strcat(QR, "\n");
		strcat(QR, "HORA O FRACCION");
		generarQr(QR);
	}
	else {
		printf("\nDEBE INGRESAR EL PRIMER ELEMENTO!!\n");
	}
}
void ingresarEntre(ListaDoble lista) {
	char*QR = (char*)malloc(50 * sizeof(char));
	char*cad1 = (char*)malloc(10 * sizeof(char));
	FILE *ticket;
	Placas placa;
	char *letrasPlaca = (char*)malloc(3 * sizeof(char));
	//char letrasPlaca[3], numeroPlaca[4], fecha[50], hora[30];
	char *numeroPlaca = (char*)malloc(4 * sizeof(char));

	char *fecha = (char*)malloc(50 * sizeof(char));
	char *hora = (char*)malloc(30 * sizeof(char));;
	system("pause");
	Nodo *aux2 = lista;
	Nodo *aux = new Nodo();
	int posicion;
	printf("\nINGRESE POSICION A INSERTAR");
	scanf_s("%d", &posicion);
	//posicion+=1;
	if (lista != NULL) {
		int iterador = 1, bandera = 0;
		if (posicion == 0) {
			printf("\nUSTED INGRESARA AL INICIO DE LA LISTA\n");
			ingresarPrimeraPosicion(lista);
		}
		else {


			while (aux2->siguienteDireccion != NULL) {
				if (posicion == iterador) {
					aux->numeroCedula = atoi(cedula());
					printf("\nINGRESE NOMBRE DEL PROPIETARIO:");
					//fflush(stdin);
					letras(aux->nombrePropietario);
					printf("\nINGRESE PLACA");
					do {
						printf("\nINGRESE LETRAS DE LA PLACA:");
						letras(letrasPlaca);
					} while (strlen(letrasPlaca) < 3 || strlen(letrasPlaca) > 3);
					strcpy(aux->placaAuto, letrasPlaca);
					strcat(aux->placaAuto, "-");
					do {
						printf("\nINGRESE NUMEROS DE LA PLACA:");
						printf("\nSI SU PLACA TIENE TRES NUMEROS ANTEPONGA EL NUMERO 0\n");
						numeros(numeroPlaca);
					} while (strlen(numeroPlaca) < 4 || strlen(numeroPlaca) > 4);
					strcat(aux->placaAuto, numeroPlaca);
					if (lista->siguienteDireccion == NULL) {
						if (strcmp(lista->placaAuto, aux->placaAuto) == 0) {
							printf("\nEL AUTO NO PUEDE INGRESAR PUES YA ESTA DENTRO DEL PARQUEADERO");
							return;
						}
					}
					if (lista->siguienteDireccion != NULL) {

						while (lista->siguienteDireccion != NULL) {
							if (strcmp(lista->placaAuto, aux->placaAuto) == 0) {
								printf("\nEL AUTO NO PUEDE INGRESAR PUES YA ESTA DENTRO DEL PARQUEADERO");
								while (lista->anteriorDireccion != NULL) {
									lista = lista->anteriorDireccion;
								}
								return;
							}
							lista = lista->siguienteDireccion;
							if (lista->siguienteDireccion == NULL) {
								if (strcmp(lista->placaAuto, aux->placaAuto) == 0) {
									printf("\nEL AUTO NO PUEDE INGRESAR PUES YA ESTA DENTRO DEL PARQUEADERO");
									while (lista->anteriorDireccion != NULL) {
										lista = lista->anteriorDireccion;
									}
									return;
								}
							}
						}
					}
					while (lista->anteriorDireccion != NULL) {
						lista = lista->anteriorDireccion;
					}
					printf("\nINGRESE MODELO DEL AUTO: ");
					letras(aux->modeloAuto);
					GetDateFormat(LOCALE_USER_DEFAULT, DATE_LONGDATE, NULL, NULL, aux->fechaEntrada, 50);
					GetTimeFormat(LOCALE_USER_DEFAULT, TIME_FORCE24HOURFORMAT, NULL, NULL, aux->horaEntrada, 30);
					aux->siguienteDireccion = aux2->siguienteDireccion;
					aux2->siguienteDireccion = aux;
					aux->anteriorDireccion = aux2;
					aux->siguienteDireccion->anteriorDireccion = aux;
					printf("\nSE INSERTo ENTRE %d y %d", posicion, posicion + 1);
					carrito(); color(07);
					system("pause");
					system("cls");
					fopen("TICKET DE ENTRADA.txt", "w");
					system("cls");
					ticket = fopen("TICKET DE ENTRADA.txt", "w");
					printf("*****************************************************");
					gotoxy(18, 1);
					printf("TICKET DE ENTRADA");
					gotoxy(0, 1);
					printf("*");
					gotoxy(52, 1);
					printf("*");
					gotoxy(0, 2);
					printf("* NOMBRE CLIENTE: %s", aux->nombrePropietario);
					gotoxy(52, 2);
					printf("*");
					gotoxy(0, 3);
					printf("* CEDULA DEL CLIENTE: %d", aux->numeroCedula);
					gotoxy(52, 3);
					printf("*");
					gotoxy(0, 4);
					printf("* FECHA DE ENTRADA: %s", aux->fechaEntrada);
					gotoxy(52, 4);
					printf("*");
					gotoxy(0, 5);
					printf("* HORA DE ENTRADA: %s", aux->horaEntrada);
					gotoxy(52, 5);
					printf("*");
					gotoxy(0, 6);
					printf("* PLACA DEL VEHICULO: %s", aux->placaAuto);
					gotoxy(52, 6);
					printf("*");
					gotoxy(0, 7);
					printf("* VEHICULO: %s", aux->modeloAuto);
					gotoxy(52, 7);
					printf("*");
					gotoxy(18, 8);
					printf("HORA O FRACCION");
					gotoxy(0, 8);
					printf("*");
					gotoxy(52, 8);
					printf("*");
					gotoxy(0, 9);
					printf("*****************************************************\n");
					fprintf(ticket, "*********************************************************");
					fprintf(ticket, "\n*\t\tTICKET DE ENTRADA\t\t\t*");
					fprintf(ticket, "\n* NOMBRE CLIENTE: %s\t\t\t*", aux->nombrePropietario);
					fprintf(ticket, "\n* CEDULA DEL CLIENTE: %d\t\t\t*", aux->numeroCedula);
					fprintf(ticket, "\n* FECHA DE ENTRADA: %s\t*", aux->fechaEntrada);
					fprintf(ticket, "\n* HORA DE ENTRADA: %s\t\t\t\t*", aux->horaEntrada);
					fprintf(ticket, "\n* PLACA DEL VEHICULO: %s\t\t\t\t*", aux->placaAuto);
					fprintf(ticket, "\n* VEHICULO: %s\t\t\t\t\t*", aux->modeloAuto);
					fprintf(ticket, "\n*\t\tHORA O FRACCION\t\t\t\t*");
					fprintf(ticket, "\n*********************************************************");
					fclose(ticket);
					system("pause");
					system("CLS");
					strcpy(QR, aux->nombrePropietario);
					strcat(QR, "\n");
					_itoa(aux->numeroCedula, cad1, 10);
					strcat(QR, cad1);
					strcat(QR, "\n");
					strcat(QR, aux->fechaEntrada);
					strcat(QR, "\n");
					strcat(QR, aux->horaEntrada);
					strcat(QR, "\n");
					strcat(QR, aux->placaAuto);
					strcat(QR, "\n");
					strcat(QR, aux->modeloAuto);
					strcat(QR, "\n");
					strcat(QR, "HORA O FRACCION");
					generarQr(QR);
					//	printf("\n\nDATO INGRESADO!\n\n");
					while (aux2->anteriorDireccion != NULL) {
						aux2 = aux2->anteriorDireccion;
					}
					lista = aux2;
					bandera = 1;
					break;
				}
				aux2 = aux2->siguienteDireccion;
				iterador++;
			}
			if (posicion == iterador&&bandera == 0) {
				printf("\n\nUsted intenta ingresar un dato al final de la lista!\n\n");
				system("pause");
				ingresarUltimaPosicion(lista);
			}
			if (iterador<posicion&&bandera == 0) {
				printf("\n\nLa posicion ingresada es superior al numero de los elementos de la lista!\n\n");
			}
			// else{
			//   printf("\nDEBE INGRESAR EL PRIMER ELEMENTO!!\n");
			//}
		}
	}
	else {
		printf("\nDEBE INGRESAR EL PRIMER ELEMENTO!!\n");
	}
	
}
void calcularTarifa(ListaDoble lista, long ced, char* placa, int comp) {
	char*QR = (char*)malloc(50 * sizeof(char));
	char*cad1 = (char*)malloc(10 * sizeof(char));
	FILE *ticket;
	if (lista != NULL) {
		if (comp == 0) {
			printf("\nNOEXISTE NINGUN VEHICULO INGRESADO\n!!!");
			return;
		}
		if (comp == 1) {
			if (ced == lista->numeroCedula && strcmp(placa, lista->placaAuto) == 0) {
				GetDateFormat(LOCALE_USER_DEFAULT, DATE_LONGDATE, NULL, NULL, lista->fechaSalida, 35);
				GetTimeFormat(LOCALE_USER_DEFAULT, TIME_FORCE24HOURFORMAT, NULL, NULL, lista->horaSalida, 11);
				int horasEnteroEntrada, minutosEnteroEntrada, segundosEnteroEntrada, i = 0;
				int horasEnteroSalida, minutosEnteroSalida, segundosEnteroSalida;
				char *horasEntrada, *minutosEntrada, *segundosEntrada, *horasSalida, *minutosSalida, *segundosSalida;
				char *aux = lista->horaEntrada, *aux1 = lista->horaSalida;
				
				while (i<1) {
					horasEntrada = strtok(aux, ":");
					minutosEntrada = strtok(NULL, ":");
					segundosEntrada = strtok(NULL, ":");
					horasEnteroEntrada = atoi(horasEntrada);
					minutosEnteroEntrada = atoi(minutosEntrada);
					segundosEnteroEntrada = atoi(segundosEntrada);
					horasSalida = strtok(aux1, ":");
					minutosSalida = strtok(NULL, ":");
					segundosSalida = strtok(NULL, ":");
					horasEnteroSalida = atoi(horasSalida);
					minutosEnteroSalida = atoi(minutosSalida);
					segundosEnteroSalida = atoi(segundosSalida);
					i++;
				}
				for (int i = 0; i <= horasEnteroSalida - horasEnteroSalida; i++) {
					lista->tarifaPagar += 0.75;
				}
				printf("\nSU TARIFA A PAGAR ES %.2f\n", lista->tarifaPagar);
				system("pause");
				system("cls");
				fopen("TICKET DE SALIDA.txt", "w");
				system("cls");
				ticket = fopen("TICKET DE SALIDA.txt", "w");
				printf("*****************************************************");
				gotoxy(18, 1);
				printf("TICKET DE SALIDA");
				gotoxy(0, 1);
				printf("*");
				gotoxy(52, 1);
				printf("*");
				gotoxy(0, 2);
				printf("* NOMBRE CLIENTE: %s", lista->nombrePropietario);
				gotoxy(52, 2);
				printf("*");
				gotoxy(0, 3);
				printf("* CEDULA DEL CLIENTE: %d", lista->numeroCedula);
				gotoxy(52, 3);
				printf("*");
				gotoxy(0, 4);
				printf("* FECHA DE ENTRADA: %s", lista->fechaEntrada);
				gotoxy(52, 4);
				printf("*");
				gotoxy(0, 5);
				printf("* HORA DE ENTRADA: %d:%d:%d", horasEnteroEntrada,minutosEnteroEntrada,segundosEnteroEntrada);
				gotoxy(52, 5);
				printf("*");
				gotoxy(0, 6);
				printf("* FECHA DE SALIDA: %s", lista->fechaSalida);
				gotoxy(52, 6);
				printf("*");
				gotoxy(0, 7);
				printf("\n* HORA DE SALIDA: %d:%d:%d", horasEnteroSalida,minutosEnteroSalida,segundosEnteroSalida);
				gotoxy(52, 7);
				printf("*");
				gotoxy(0, 8);
				printf("\n* TARIFA PAGADA: %.2f", lista->tarifaPagar);
				gotoxy(52, 8);
				printf("*");
				gotoxy(0, 9);
				printf("* PLACA DEL VEHICULO: %s", lista->placaAuto);
				gotoxy(52, 9);
				printf("*");
				gotoxy(0, 10);
				printf("* VEHICULO: %s", lista->modeloAuto);
				gotoxy(52, 10);
				printf("*");
				gotoxy(0, 11);
				printf("*****************************************************\n");
				fprintf(ticket, "*********************************************************");
				fprintf(ticket, "\n*\t\tTICKET DE ENTRADA\t\t\t*");
				fprintf(ticket, "\n* NOMBRE CLIENTE: %s\t\t\t*", lista->nombrePropietario);
				fprintf(ticket, "\n* CEDULA DEL CLIENTE: %d\t\t\t*", lista->numeroCedula);
				fprintf(ticket, "\n* FECHA DE ENTRADA: %s\t*", lista->fechaEntrada);
				fprintf(ticket, "\n* HORA DE ENTRADA: %s\t\t\t\t*", lista->horaEntrada);
				fprintf(ticket, "\n* FECHA DE SALIDA: %s\t*", lista->fechaSalida);
				fprintf(ticket, "\n* HORA DE SALIDA: %s\t\t\t\t*", lista->horaSalida);
				fprintf(ticket, "\n* PLACA DEL VEHICULO: %s\t\t\t\t*", lista->placaAuto);
				fprintf(ticket, "\n* VEHICULO: %s\t\t\t\t\t*", lista->modeloAuto);
				fprintf(ticket, "\n*********************************************************");
				fclose(ticket);
				system("pause");
				system("CLS");
				strcpy(QR, lista->nombrePropietario);
				strcat(QR, "\n");
				_itoa(lista->numeroCedula, cad1, 10);
				strcat(QR, cad1);
				strcat(QR, "FECHA DE ENTRADA\n");
				strcat(QR, lista->fechaEntrada);
				strcat(QR, "HORA DE ENTRADA\n");
				strcat(QR, lista->horaEntrada);
				strcat(QR, "FECHA DE SALIDA\n");
				strcat(QR, lista->fechaSalida);
				strcat(QR, "HORA DE SALIDA\n");
				strcat(QR, lista->horaSalida);
				strcat(QR, "\n");
				strcat(QR, lista->placaAuto);
				strcat(QR, "\n");
				strcat(QR, lista->modeloAuto);
				strcat(QR, "\n");
				strcat(QR, "HORA O FRACCION");
				generarQr(QR);
			}
		}
		if (comp == 4) {
			if (ced == lista->numeroCedula && strcmp(placa, lista->placaAuto) == 0) {
				GetDateFormat(LOCALE_USER_DEFAULT, DATE_LONGDATE, NULL, NULL, lista->fechaSalida, 35);
				GetTimeFormat(LOCALE_USER_DEFAULT, TIME_FORCE24HOURFORMAT, NULL, NULL, lista->horaSalida, 11);
				int horasEnteroEntrada, minutosEnteroEntrada, segundosEnteroEntrada, i = 0;
				int horasEnteroSalida, minutosEnteroSalida, segundosEnteroSalida;
				char *horasEntrada, *minutosEntrada, *segundosEntrada, *horasSalida, *minutosSalida, *segundosSalida;
				while (i<1) {
					horasEntrada = strtok(lista->horaEntrada, ":");
					minutosEntrada = strtok(NULL, ":");
					segundosEntrada = strtok(NULL, ":");
					horasEnteroEntrada = atoi(horasEntrada);
					minutosEnteroEntrada = atoi(minutosEntrada);
					segundosEnteroEntrada = atoi(segundosEntrada);
					horasSalida = strtok(lista->horaSalida, ":");
					minutosSalida = strtok(NULL, ":");
					segundosSalida = strtok(NULL, ":");
					horasEnteroSalida = atoi(horasSalida);
					minutosEnteroSalida = atoi(minutosSalida);
					segundosEnteroSalida = atoi(segundosSalida);
					i++;
				}
				for (int i = 0; i <= horasEnteroSalida - horasEnteroSalida; i++) {
					lista->tarifaPagar += 0.75;
				}
				printf("\nSU TARIFA A PAGAR ES %.2f", lista->tarifaPagar);
				system("pause");
				system("cls");
				fopen("TICKET DE SALIDA.txt", "w");
				system("cls");
				ticket = fopen("TICKET DE SALIDA.txt", "w");
				printf("*****************************************************");
				gotoxy(18, 1);
				printf("TICKET DE SALIDA");
				gotoxy(0, 1);
				printf("*");
				gotoxy(52, 1);
				printf("*");
				gotoxy(0, 2);
				printf("* NOMBRE CLIENTE: %s", lista->nombrePropietario);
				gotoxy(52, 2);
				printf("*");
				gotoxy(0, 3);
				printf("* CEDULA DEL CLIENTE: %d", lista->numeroCedula);
				gotoxy(52, 3);
				printf("*");
				gotoxy(0, 4);
				printf("* FECHA DE ENTRADA: %s", lista->fechaEntrada);
				gotoxy(52, 4);
				printf("*");
				gotoxy(0, 5);
				printf("* HORA DE ENTRADA: %d:%d:%d", horasEnteroEntrada, minutosEnteroEntrada, segundosEnteroEntrada);
				gotoxy(52, 5);
				printf("*");
				gotoxy(0, 6);
				printf("* FECHA DE SALIDA: %s", lista->fechaSalida);
				gotoxy(52, 6);
				printf("*");
				gotoxy(0, 7);
				printf("\n* HORA DE SALIDA: %d:%d:%d", horasEnteroSalida, minutosEnteroSalida, segundosEnteroSalida);
				gotoxy(52, 7);
				printf("*");
				gotoxy(0, 8);
				printf("\n* TARIFA PAGADA: %.2f", lista->tarifaPagar);
				gotoxy(52, 8);
				printf("*");
				gotoxy(0, 9);
				printf("* PLACA DEL VEHICULO: %s", lista->placaAuto);
				gotoxy(52, 9);
				printf("*");
				gotoxy(0, 10);
				printf("* VEHICULO: %s", lista->modeloAuto);
				gotoxy(52, 10);
				printf("*");
				gotoxy(0, 11);
				printf("*****************************************************\n");
				fprintf(ticket, "*********************************************************");
				fprintf(ticket, "\n*\t\tTICKET DE ENTRADA\t\t\t*");
				fprintf(ticket, "\n* NOMBRE CLIENTE: %s\t\t\t*", lista->nombrePropietario);
				fprintf(ticket, "\n* CEDULA DEL CLIENTE: %d\t\t\t*", lista->numeroCedula);
				fprintf(ticket, "\n* FECHA DE ENTRADA: %s\t*", lista->fechaEntrada);
				fprintf(ticket, "\n* HORA DE ENTRADA: %s\t\t\t\t*", lista->horaEntrada);
				fprintf(ticket, "\n* FECHA DE SALIDA: %s\t*", lista->fechaSalida);
				fprintf(ticket, "\n* HORA DE SALIDA: %s\t\t\t\t*", lista->horaSalida);
				fprintf(ticket, "\n* PLACA DEL VEHICULO: %s\t\t\t\t*", lista->placaAuto);
				fprintf(ticket, "\n* VEHICULO: %s\t\t\t\t\t*", lista->modeloAuto);
				fprintf(ticket, "\n*********************************************************");
				fclose(ticket);
				system("pause");
				system("CLS");
				strcpy(QR, lista->nombrePropietario);
				strcat(QR, "\n");
				_itoa(lista->numeroCedula, cad1, 10);
				strcat(QR, cad1);
				strcat(QR, "FECHA DE ENTRADA\n");
				strcat(QR, lista->fechaEntrada);
				strcat(QR, "HORA DE ENTRADA\n");
				strcat(QR, lista->horaEntrada);
				strcat(QR, "FECHA DE SALIDA\n");
				strcat(QR, lista->fechaSalida);
				strcat(QR, "HORA DE SALIDA\n");
				strcat(QR, lista->horaSalida);
				strcat(QR, "\n");
				strcat(QR, lista->placaAuto);
				strcat(QR, "\n");
				strcat(QR, lista->modeloAuto);
				strcat(QR, "\n");
				strcat(QR, "HORA O FRACCION");
				generarQr(QR);
			}
		}
		while (lista->siguienteDireccion != NULL) {
			if (ced == lista->numeroCedula && strcmp(placa, lista->placaAuto) == 0) {
				GetDateFormat(LOCALE_USER_DEFAULT, DATE_LONGDATE, NULL, NULL, lista->fechaSalida, 35);
				GetTimeFormat(LOCALE_USER_DEFAULT, TIME_FORCE24HOURFORMAT, NULL, NULL, lista->horaSalida, 11);
				int horasEnteroEntrada, minutosEnteroEntrada, segundosEnteroEntrada, i = 0;
				int horasEnteroSalida, minutosEnteroSalida, segundosEnteroSalida;
				char *horasEntrada, *minutosEntrada, *segundosEntrada, *horasSalida, *minutosSalida, *segundosSalida;
				while (i<1) {
					horasEntrada = strtok(lista->horaEntrada, ":");
					minutosEntrada = strtok(NULL, ":");
					segundosEntrada = strtok(NULL, ":");
					horasEnteroEntrada = atoi(horasEntrada);
					minutosEnteroEntrada = atoi(minutosEntrada);
					segundosEnteroEntrada = atoi(segundosEntrada);
					horasSalida = strtok(lista->horaSalida, ":");
					minutosSalida = strtok(NULL, ":");
					segundosSalida = strtok(NULL, ":");
					horasEnteroSalida = atoi(horasSalida);
					minutosEnteroSalida = atoi(minutosSalida);
					segundosEnteroSalida = atoi(segundosSalida);
					i++;
				}
				for (int i = 0; i <= horasEnteroSalida - horasEnteroSalida; i++) {
					lista->tarifaPagar += 0.75;
				}
				printf("\nSU TARIFA A PAGAR ES %.2f\n", lista->tarifaPagar);
				system("pause");
				system("cls");
				fopen("TICKET DE SALIDA.txt", "w");
				system("cls");
				ticket = fopen("TICKET DE SALIDA.txt", "w");
				printf("*****************************************************");
				gotoxy(18, 1);
				printf("TICKET DE SALIDA");
				gotoxy(0, 1);
				printf("*");
				gotoxy(52, 1);
				printf("*");
				gotoxy(0, 2);
				printf("* NOMBRE CLIENTE: %s", lista->nombrePropietario);
				gotoxy(52, 2);
				printf("*");
				gotoxy(0, 3);
				printf("* CEDULA DEL CLIENTE: %d", lista->numeroCedula);
				gotoxy(52, 3);
				printf("*");
				gotoxy(0, 4);
				printf("* FECHA DE ENTRADA: %s", lista->fechaEntrada);
				gotoxy(52, 4);
				printf("*");
				gotoxy(0, 5);
				printf("* HORA DE ENTRADA: %d:%d:%d", horasEnteroEntrada, minutosEnteroEntrada, segundosEnteroEntrada);
				gotoxy(52, 5);
				printf("*");
				gotoxy(0, 6);
				printf("* FECHA DE SALIDA: %s", lista->fechaSalida);
				gotoxy(52, 6);
				printf("*");
				gotoxy(0, 7);
				printf("\n* HORA DE SALIDA: %d:%d:%d", horasEnteroSalida, minutosEnteroSalida, segundosEnteroSalida);
				gotoxy(52, 7);
				printf("*");
				gotoxy(0, 8);
				printf("\n* TARIFA PAGADA: %.2f", lista->tarifaPagar);
				gotoxy(52, 8);
				printf("*");
				gotoxy(0, 9);
				printf("* PLACA DEL VEHICULO: %s", lista->placaAuto);
				gotoxy(52, 9);
				printf("*");
				gotoxy(0, 10);
				printf("* VEHICULO: %s", lista->modeloAuto);
				gotoxy(52, 10);
				printf("*");
				gotoxy(0, 11);
				printf("*****************************************************\n");
				fprintf(ticket, "*********************************************************");
				fprintf(ticket, "\n*\t\tTICKET DE ENTRADA\t\t\t*");
				fprintf(ticket, "\n* NOMBRE CLIENTE: %s\t\t\t*", lista->nombrePropietario);
				fprintf(ticket, "\n* CEDULA DEL CLIENTE: %d\t\t\t*", lista->numeroCedula);
				fprintf(ticket, "\n* FECHA DE ENTRADA: %s\t*", lista->fechaEntrada);
				fprintf(ticket, "\n* HORA DE ENTRADA: %s\t\t\t\t*", lista->horaEntrada);
				fprintf(ticket, "\n* FECHA DE SALIDA: %s\t*", lista->fechaSalida);
				fprintf(ticket, "\n* HORA DE SALIDA: %s\t\t\t\t*", lista->horaSalida);
				fprintf(ticket, "\n* PLACA DEL VEHICULO: %s\t\t\t\t*", lista->placaAuto);
				fprintf(ticket, "\n* VEHICULO: %s\t\t\t\t\t*", lista->modeloAuto);
				fprintf(ticket, "\n*********************************************************");
				fclose(ticket);
				system("pause");
				system("CLS");
				strcpy(QR, lista->nombrePropietario);
				strcat(QR, "\n");
				_itoa(lista->numeroCedula, cad1, 10);
				strcat(QR, cad1);
				strcat(QR, "FECHA DE ENTRADA\n");
				strcat(QR, lista->fechaEntrada);
				strcat(QR, "HORA DE ENTRADA\n");
				strcat(QR, lista->horaEntrada);
				strcat(QR, "FECHA DE SALIDA\n");
				strcat(QR, lista->fechaSalida);
				strcat(QR, "HORA DE SALIDA\n");
				strcat(QR, lista->horaSalida);
				strcat(QR, "\n");
				strcat(QR, lista->placaAuto);
				strcat(QR, "\n");
				strcat(QR, lista->modeloAuto);
				strcat(QR, "\n");
				strcat(QR, "HORA O FRACCION");
				generarQr(QR);
				return;
			}
		}

	}
	else {
		printf("\nNO HAY AUTOS");
	}
}

int salirParqueadero(ListaDoble lista) {
	int comp = 0;
	long cedulaAux;
	char *placaAux = (char*)malloc(10 * sizeof(char));
	char *letrasPlaca = (char*)malloc(3 * sizeof(char));
	char *numeroPlaca = (char*)malloc(4 * sizeof(char));
	Nodo *aux1 = new Nodo(), *aux = lista;
	printf("\nINGRESE SU CEDULA PARA SACAR SU AUTO");
	cedulaAux = atoi(cedula());
	printf("\nINGRESE LAS PLACAS DE SU AUTO PARA PODER SACARLO");
	do {
		printf("\nINGRESE LAS LETRAS DE SU PLACA:");
		letras(letrasPlaca);
	} while (strlen(letrasPlaca) <3 || strlen(letrasPlaca)>3);
	strcpy(placaAux, letrasPlaca);
	strcat(placaAux, "-");
	do {
		printf("\nINGRESE NUMEROS DE SU PLACA:");
		printf("\nNO SEOLVIDE QUE SI SU PLACA TIENE TRES NUMEROS ANTEPONGA EL NUMERO 0\n");
		numeros(numeroPlaca);
	} while (strlen(numeroPlaca) < 4 || strlen(numeroPlaca) > 4);
	strcat(placaAux, numeroPlaca);
	
	if (lista != NULL) {
		if (cedulaAux == lista->numeroCedula&&strcmp(placaAux, lista->placaAuto) == 0 && lista->siguienteDireccion == NULL&&lista->anteriorDireccion == NULL) {
			comp++;
			calcularTarifa(aux, cedulaAux, placaAux, comp);
			//printf("\nLA LISTA SOLO TIENE UN ELEMENTO, SE BORRARA TODO");
			return comp;
		}

		while (lista->siguienteDireccion != NULL) {
			if (cedulaAux == lista->numeroCedula&&strcmp(placaAux, lista->placaAuto) == 0) {
				if (lista->anteriorDireccion == NULL&&lista->siguienteDireccion!=NULL) {
					comp += 2;
					calcularTarifa(lista, cedulaAux, placaAux, comp);
					return comp;
				}
				if (lista->siguienteDireccion != NULL&&lista->anteriorDireccion != NULL) {
					comp += 3;
					calcularTarifa(lista, cedulaAux, placaAux, comp);
					aux1 = lista->siguienteDireccion;
					lista = lista->anteriorDireccion;
					lista->siguienteDireccion = aux1;

					aux1->anteriorDireccion = lista;
					return comp;
				}

			}


			lista = lista->siguienteDireccion;
			if (cedulaAux == lista->numeroCedula&&strcmp(placaAux, lista->placaAuto) == 0 && lista->siguienteDireccion == NULL&&lista->anteriorDireccion != NULL) {
				comp += 4;
				calcularTarifa(lista, cedulaAux, placaAux, comp);
				return comp;
			}
		}
	}
	else {
		printf("\n\nNO HAY AUTOS REGISTRADOS...");
	}
	return 0;
}

void imprimirLista(ListaDoble lista) {
	ofstream datos ("LISTA PARQUEADERO.txt");
	if (lista == NULL) {
		printf("No hay elementos en la lista!\n\n");
		datos << "No hay elementos en la lista!\n\n" << endl;
	}
	else {
		while (lista != NULL) {
			printf("%s", lista->nombrePropietario);
			datos<< lista->nombrePropietario<<endl;
			printf("\n%d", lista->numeroCedula);
			datos<<"\n"<< lista->numeroCedula<<endl;
			printf("\n%s", lista->fechaEntrada);
			datos<<"\n"<< lista->fechaEntrada<<endl;
			printf("\n%s", lista->horaEntrada);
			datos<<"\n"<< lista->horaEntrada<<endl;
			printf("\n%s", lista->placaAuto);
			datos<<"\n"<< lista->placaAuto<<endl;
			printf("\n%s", lista->modeloAuto);
			datos<<"\n"<< lista->modeloAuto<<endl;
			printf("\n\n");
			datos<<"\n\n"<<endl;
			lista = lista->siguienteDireccion;
		}
	}
	datos.close();
	system("pause");
	//PDF
	int imp;
	system("cls");
	imp = AyudaF1();
	if (imp == 1)
	{
		ofstream LeerDatos;
		LeerDatos.open("LISTA PARQUEADERO.txt", ios::out | ios::app);
		tifstream in(TEXT("LISTA PARQUEADERO.txt"));
		PrintFile(in);
		ShellExecute(NULL, TEXT("open"), TEXT("D:\\Programacion 1\\C++\\Proyecto\\PDF QR\\pdf\\Datos.pdf"), NULL, NULL, SW_SHOWNORMAL);
	}
	system("pause");
	_getch;
}


int main()
{
	ListaDoble lista = NULL;
	Nodo *aux1 = new Nodo();
	int opcionDelMenu, comp;
	PlaySound("D:\\Universidad\\Programacion 1\\Traductor\\ZZ Top - La Grange.wav", NULL, SND_ASYNC);
	inicio:
	opcionDelMenu = menu();
	
	switch (opcionDelMenu) {
	case 1: {
		system("cls");
		ingresarPrimerDato(lista);
		system("pause");
		goto inicio;
		break;
	}
	case 2: {
		system("cls");
		ingresarPrimeraPosicion(lista);
		system("pause");
		goto inicio;
		break;
	}
	case 3: {
		system("cls");
		ingresarUltimaPosicion(lista);
		system("pause");
		goto inicio;
		break;
	}
	case 4: {
		system("cls");
		ingresarEntre(lista);
		system("pause");
		goto inicio;
		break;
	}
	case 5: {
		system("cls");
		imprimirLista(lista);
		system("pause");
		goto inicio;
		break;
	}
	case 6: {
		ShellExecute(NULL, TEXT("open"), TEXT("ayuda.chm"), NULL, NULL, SW_SHOWNORMAL);
		goto inicio;
		break;
	}
	case 7: {
		ShellExecute(NULL, TEXT("open"), TEXT("FotoGrupal.exe"), NULL, NULL, SW_SHOWNORMAL);
		goto inicio;
		break;
	}
	case 8: {
		comp = 0;
		system("cls");
		comp = salirParqueadero(lista);
		if (comp == 0) {
			printf("\nNO SE HA INGRESADO UN VEHICULO CON ESAS ESPECIFICACIONES!!!\n");
		}
		if (comp == 1) {
			lista = NULL;
		}
		if (comp == 2) {
			aux1 = lista;
			lista = lista->siguienteDireccion;
			aux1->siguienteDireccion = aux1->anteriorDireccion = NULL;
			aux1 = NULL;
			lista->anteriorDireccion = NULL;
		}
		/*if (comp == 3) {
			aux1 = lista->siguienteDireccion;
			lista = lista->anteriorDireccion;
			lista->siguienteDireccion = aux1;

			aux1->anteriorDireccion = lista;
		}*/
		if (comp == 4) {
			while (lista->siguienteDireccion != NULL) {
				lista = lista->siguienteDireccion;
			}
			//		aux1=listaDoble;
			lista = lista->anteriorDireccion;
			lista->siguienteDireccion = NULL;
			comp = 0;
			while (lista->anteriorDireccion != NULL) {
				lista = lista->anteriorDireccion;
			}
		}
		system("pause");
		goto inicio;
		break;
	}
	case 9: {
		return 0;
		break;
	}
	}
	system("pause");

	return 0;
}