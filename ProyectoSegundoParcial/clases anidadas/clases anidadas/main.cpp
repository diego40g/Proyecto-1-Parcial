/*
UNIVERSIDAD DE LAS FUERZAS ARMADAS"ESPE"
PROYECTO SEGUNDO PARCIAL
Calcular polaca ingresado de forma infija
con pilas
Menu con mouse
Generera QR
genera txt
genera pdf
Cancion de fondo
Imagen del grupo
Opcion Ayuda
Ingreso inicio,fin,medio
Salir del Parqueadero
Salir del Sistema
Instalador
y proyecto ejecutado en phyton
Autores: Diego Paz
		 Michael Morales
Fecha de Creacion: 17-11-2017	Fecha de Modificacion: 29-11-2017
Profesor: Ing. Edgar Fernando Solis Acosta
Carrera: Ingenieria en Sitemas e Informatica
*/

	//PERMITE UTILIZAR FUNCIONES COMO strcpy()
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <conio.h>
#include <windows.h>
#include "qrcodegen.h"
#include "PDF.h"
#include "Pila.h"
using namespace std;
HANDLE hStdin;
DWORD fdwSaveOldMode;
void ErrorExit(LPSTR);
void KeyEventProc(KEY_EVENT_RECORD);
void MouseEventProc(MOUSE_EVENT_RECORD);
void ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD);
void GetMousePosWin(MOUSE_EVENT_RECORD);
void gotoXY(int x, int y);
int  AyudaF1();
void gotoxy(int x, int y)
{
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon, dwPos);
}
static void printQr(const uint8_t qrcode[]);
static void generarQr(char *loqueimprime);
void limpiar(char[], int), pasar(char[], char[]),
conv_pre(char[], char[], char Simb[4][2], char), conv_pos(char[], char[], char Simb[4][2], char),
rec_exp(char[]), inver(char[], char[], char);
int verif(char[]), tama(char[]), sim(char, char Simb[4][2], char *),
prio(char, char, char Simb[4][2]);
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void color(int X)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), X);
}
void encabezado()
{
	printf("\tUNIVERSIDAD DE LAS FUERZAS ARMADAS \"ESPE\"\n");
	printf("\n\t\tPROYECTO PRIMER PARCIAL\n");
	printf("\n\t\t  ESTRUCTURA DE DATOS\n");
	printf("\n\t\t      PARQUEADERO\n");
	printf("\n\tAUTORES: Michael Morales\n");
	printf("\t         Diego Paz\n");
	printf("\n\tNRC: 2479\n");
	color(0);
	system("pause");
	color(07);
	system("cls");
}

void menu(int y)
{
	color(07);
	gotoXY(25, 1);
	printf("MENU");
	int aux = 3; 
	if (y == aux)
	{
		color(112);
	}
	else
	{
		color(07);
	}
	gotoXY(13, aux);
	printf("\xDB Calculo de la Polaca en Posfijo"); aux += 2;
	if (y == aux)
	{
		color(112);
	}
	else
	{
		color(07);
	}
	gotoXY(13, aux);
	printf("\xDB Calculo de la Polaca en Prefijo"); aux += 2;
	if (y == aux)
	{
		color(112);
	}
	else
	{
		color(07);
	}
	gotoXY(13, aux);
	printf("\xDB Generar archivo .pdf"); aux += 2;
	if (y == aux)
	{
		color(112);
	}
	else
	{
		color(07);
	}
	gotoXY(13, aux);
	printf("\xDB Archivo de ayuda"); aux += 2;
	if (y == aux)
	{
		color(112);
	}
	else
	{
		color(07);
	}
	gotoXY(13, aux);
	printf("\xDB Imagen del Grupo"); aux += 2;
	if (y == aux)
	{
		color(112);
	}
	else
	{
		color(07);
	}
	gotoXY(13, aux);
	printf("\xDB Salir"); 
}

void ingresar(char *cad)
{
	int c, i = 0;
	while ((c = _getch()) != 13)
	{
		if ((c >= 48 && c <= 57) || (c == 44) || (c == 46) || (c == 42) || (c == 43) || (c == 45) || (c == 47) || (c == 32) || (c == 99) || (c == 115) || (c == 116) || (c == 40) || (c == 41) || (c == 91) || (c == 123) || (c == 125) || (c == 93))
		{
			if (c == 91 || c == 123 || c == 93 || c == 125) {
				if (c == 91 || c == 123) {
					printf("%c", c);
					c = 40;
					*(cad + i) = c;
					i++;
				}
				if (c == 93 || c == 125) {
					printf("%c", c);
					c = 41;
					*(cad + i) = c;
					i++;
				}

			}
			else {
				if (c == 115)//sin
				{
					*(cad + i) = c;
					printf("%c", c);
					i++;
					c = 105;
					*(cad + i) = c;//i
					printf("%c", c);
					i++;
					c = 110;
					*(cad + i) = c;//n
					printf("%c", c);
					i++;
					c = 40;
					*(cad + i) = c;
					printf("%c", c);
					i++;
				}
				else
				{
					if (c == 99)//cos
					{
						*(cad + i) = c;
						printf("%c", c);
						i++;
						c = 111;
						*(cad + i) = c;
						printf("%c", c);
						i++;
						c = 115;
						*(cad + i) = c;
						printf("%c", c);
						i++;
						c = 40;
						*(cad + i) = c;
						printf("%c", c);
						i++;
					}
					else
					{
						if (c == 116)//tan
						{
							*(cad + i) = c;
							printf("%c", c);
							i++;
							c = 97;
							*(cad + i) = c;
							printf("%c", c);
							i++;
							c = 110;
							*(cad + i) = c;
							printf("%c", c);
							i++;
							c = 40;
							*(cad + i) = c;
							printf("%c", c);
							i++;
						}
						else
						{
							*(cad + i) = c;
							printf("%c", c);
							i++;
						}
					}

				}
			}


			if (i == 48)
			{
				break;
			}
		}
		*(cad + i) = '\0';
	}
}

void reducir(char epos[], char e[], int j) 
{
	limpiar(e, strlen(e));
	for (int i = 0; i<strlen(epos); i++) {
		if (epos[i] == ' '&&epos[i + 1] == ' ') {
			e[j] = epos[i];
			i++;
			j++;
		}
		else {
			e[j] = epos[i];
			j++;
		}
	}
	strcpy(epos, e);
}

///TAYLOR

double factorial(int n)
{
	if (n == 0)
	{
		return 1;
	}
	else
	{
		return n * factorial(n - 1);
	}
}

double Radianes(float x)
{
	double PI = 3.14159;
	double y;
	y = (x*PI) / 180;
	return y;
}

float seno(float x, int n)
{
	float seno = 0;
	if (n>0)
	{
		double signo = 1.0, p = Radianes(x), q = 1;

		for (int i = 0; i <= n; i++)
		{
			seno = seno + signo * (p / factorial(2 * i + 1));
			p = p * Radianes(x)*Radianes(x);
			signo = signo * (-1);
		}
	}
	return seno;
}

float coseno(float x, int n)
{
	float coseno = 0;
	if (n>0)
	{
		double signo = 1.0, p = Radianes(x), q = 1;

		for (int i = 0; i <= n; i++)
		{

			coseno = coseno + signo * (q / factorial(2 * i));
			q = q * Radianes(x)*Radianes(x);
			signo = signo * (-1);
		}
	}
	return coseno;
}

///FIN TAYLOR

int main()
{
	color(07);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	DWORD cNumRead, fdwMode, i;
	INPUT_RECORD irInBuf[128];
	int counter = 0;
	// Get the standard input handle. 
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	if (hStdin == INVALID_HANDLE_VALUE)
		ErrorExit("GetStdHandle");
	// Save the current input mode, to be restored on exit. 
	if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
		ErrorExit("GetConsoleMode");
	// Enable the window and mouse input events. 
	fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	if (!SetConsoleMode(hStdin, fdwMode))
		ErrorExit("SetConsoleMode");
	// Loop to read and handle the next 100 input events. 
	menu(-1);
	
	while (!counter)//++ <= 200) 
	{
		// Wait for the events. 
		if (!ReadConsoleInput(
			hStdin,      // input buffer handle 
			irInBuf,     // buffer to read into 
			128,         // size of read buffer 
			&cNumRead)) // number of records read 
			ErrorExit("ReadConsoleInput");
		// Dispatch the events to the appropriate handler. 
		for (i = 0; i < cNumRead; i++)
		{
			switch (irInBuf[i].EventType)
			{
			case KEY_EVENT: // keyboard input 
				KeyEventProc(irInBuf[i].Event.KeyEvent);
				break;
			case MOUSE_EVENT: // mouse input 
				MouseEventProc(irInBuf[i].Event.MouseEvent);
				GetMousePosWin(irInBuf[i].Event.MouseEvent);
				break;
			case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing 
				ResizeEventProc(irInBuf[i].Event.WindowBufferSizeEvent);
				break;
			case FOCUS_EVENT:  // disregard focus events 
			case MENU_EVENT:   // disregard menu events 
				break;
			default:
				ErrorExit("Unknown event type");
				break;
			}
		}
	}
	// Restore input mode on exit.
	SetConsoleMode(hStdin, fdwSaveOldMode);
	return 0;
}

VOID ErrorExit(LPSTR lpszMessage)
{
	fprintf(stderr, "%s\n", lpszMessage);
	// Restore input mode on exit.
	SetConsoleMode(hStdin, fdwSaveOldMode);
	ExitProcess(0);
}

VOID KeyEventProc(KEY_EVENT_RECORD ker)
{

}

VOID MouseEventProc(MOUSE_EVENT_RECORD mer)
{
#ifndef MOUSE_HWHEELED
#define MOUSE_HWHEELED 0x0008
#endif
	gotoXY(13, 12);
	INPUT_RECORD Inrec;
	int x, y = 0;
	//printf("Posicion del Mouse:\n");
	switch (mer.dwEventFlags)
	{

	case 0:
		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			//printf("\nleft button pressed\n");
		}
		else if (mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
		{
			//printf("\nright button pressed\n");
		}
		else
		{
			//printf("\nBoton aplastado\n");
		}
		break;
	case DOUBLE_CLICK:
		//printf("\nDoble click\n");
		break;
	case MOUSE_HWHEELED:
		//printf("\nhorizontal mouse wheel\n");
		break;
	case MOUSE_MOVED:
		//printf("Moviendo");
		break;
	case MOUSE_WHEELED:
		//printf("vertical mouse wheel");
		break;
	default:
		//printf("unknown");
		break;
	}

}

// get Window pos through windows api
void GetMousePosWin(MOUSE_EVENT_RECORD mer)
{
///INICIO polaca infija 
	char Simb[4][2] = { { '(',')' },{ '-','+' },{ '/','*' },{ '$','\0' } },
		expr[1000], pila[1000], expr_c[1000], epre[1000], epos[1000],
		simb = '1', auxiliar[1000];

	int i = 0, tope, val, cont1, cont2, v, tamanio, j = 0, posicion, op, tam;

	int x=0, y=0;
	// creates the handle i need to use
	//HANDLE OutputH;
	INPUT_RECORD Inrec;
	DWORD evRead;
	HANDLE hStdIn;
	DWORD dwMode;
	bool Captured = false;

	hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	dwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	if (SetConsoleMode(hStdIn, dwMode | ENABLE_MOUSE_INPUT) == TRUE)
		GetConsoleMode(hStdIn, &dwMode);
	SetConsoleMode(hStdIn, (dwMode & (ENABLE_MOUSE_INPUT)));
	// grab the handle to the console so i can use it
	//OutputH = GetStdHandle(STD_OUTPUT_HANDLE);
	//printf("Strated"); //Debug line.
	do
	{
		PeekConsoleInput(hStdIn, &Inrec, 1, &evRead);
		if (evRead)
		{
			ReadConsoleInput(hStdIn, &Inrec, 1, &evRead);
			x = Inrec.Event.MouseEvent.dwMousePosition.X;
			y = Inrec.Event.MouseEvent.dwMousePosition.Y;
			
			switch (Inrec.EventType)
			{
				case MOUSE_EVENT:
				{
					Captured = true;
//					printf("x-> %d ", x);
	//				printf("y-> %d ", y);
					menu(y);
					break;
				}
			}
		}
	} while (!Captured);

	if (y == 3 && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
	{
	ingreso:
		limpiar(expr, 1000);
		limpiar(pila, 1000);
		limpiar(expr_c, 1000);
		limpiar(epre, 1000);
		limpiar(epos, 1000);
		do {
			system("cls");
			limpiar(expr, 1000);
			printf("\nIntroduzca la expresión infija: ");
			ingresar(expr);
			tamanio = strlen(expr);
			tamanio *= 2;
			char expresion[1000];
			for (int i = 0; i<strlen(expr); i++) {
				if (expr[i] != '('&&expr[i] != ')') {
					expresion[j] = expr[i];
					j++;
				}
				if (expr[i] == '(') {
					expresion[j] = expr[i];
					j++;
				}
				if (expr[i] == ')'&&expr[i + 1] == '(') {
					expresion[j] = expr[i];
					i++;
					j++;
					expresion[j] = '*';
					j++;
					expresion[j] = expr[i];
					j++;
				}
				if (expr[i] == ')') {
					expresion[j] = expr[i];
					j++;
				}
				if (expr[i] != '('&&expr[i] != ')'&&expr[i] != 'n'&&expr[i] != 's'&&expr[i] != '+'&&expr[i] != '-'&&expr[i] != '*'&&expr[i] != '/'&&expr[i + 1] == '(') {
					expresion[j] = '*';
					j++;
					i++;	expresion[j] = expr[i];
					j++;
					expresion[j] = expr[i + 1];
					//i++;
				}
			}
			expresion[j] = '\0';
			strcpy(expr, expresion);
			strcat(expr, " ");
			printf("\n\n%s    aqio", expr);
			system("pause");
			int tamAux;
			tamAux = strlen(expr) * 2;
			char auxiliar[1000];
			char t;
			int posicion = 0;
			for (int i = 0; i<tamanio; i++) {//-----------------------------------------------				
				if (expr[i] == '*' || expr[i] == '+' || expr[i] == '-' || expr[i] == '/' || expr[i] == '(' || expr[i] == ')') {
					if (expr[i] == '*') {
						auxiliar[posicion] = ' ';
						posicion++;
						auxiliar[posicion] = expr[i];
						posicion++;
						auxiliar[posicion] = ' ';
						posicion++;
					}
					if (expr[i] == '(' && (expr[i - 1] != 'n'&&expr[i - 1] != 's')) {
						auxiliar[posicion] = ' ';
						posicion++;
						auxiliar[posicion] = expr[i];
						posicion++;
						auxiliar[posicion] = ' ';
						posicion++;

					}
					if (expr[i] == '(' && (expr[i - 1] == 'n' || expr[i - 1] == 's')) {
						auxiliar[posicion] = ' ';
						posicion++;
						auxiliar[posicion] = expr[i];
						posicion++;
						auxiliar[posicion] = ' ';
						posicion++;
					}
					if (expr[i] == '+' || expr[i] == '-' || expr[i] == '/') {
						auxiliar[posicion] = ' ';
						posicion++;
						auxiliar[posicion] = expr[i];
						posicion++;
						auxiliar[posicion] = ' ';
						posicion++;
					}
					if (expr[i] == ')') {
						auxiliar[posicion] = ' ';
						posicion++;
						auxiliar[posicion] = expr[i];
						posicion++;
						auxiliar[posicion] = ' ';
						posicion++;
					}
				}
				else {
					auxiliar[posicion] = expr[i];
					posicion++;
				}

			}
			auxiliar[posicion] = '\0';
			strcpy(expr, auxiliar);//-----------------------------------------------
			strcat(expr, " ");
			/*	posicion=0;
			for(int i=0;i<strlen(expr);i++){
			if(expr[i]=='*'){
			auxiliar[posicion]=' ';
			posicion++;
			auxiliar[posicion]=expr[i];
			posicion++;
			auxiliar[posicion]=' ';
			posicion++;
			}else{
			auxiliar[posicion]=expr[i];
			posicion++;
			}
			}
			auxiliar[posicion]='\0';
			strcpy(expr,auxiliar);//-----------------------------------------------
			strcat(expr," ");*/
			int op = 0;
			int tam = strlen(epos);
			char e[1000];
			limpiar(e, strlen(epos));
			while (op<2) {
				j = 0;
				reducir(expr, e, j);
				op++;
			}
			printf("\n\n%s1", expr);
			system("pause");
			if (verif(expr) != 3) {
				printf("\nLa expresión %s no es valida, ", expr);
				switch (verif(expr)) {
				case 0: printf("esta mal la función.");
				case 1: printf("le faltan paréntesis derechos.");
				case 2: printf("le faltan paréntesis izquierdos.");
				}
				_getche();
			}
		} while (verif(expr) != 3);
		inver(expr_c, expr, simb);
		conv_pre(expr_c, epre, Simb, simb);
		printf("\nLa conversión a Prefija es: %s", epre);
		pasar(expr_c, expr);
		conv_pos(expr_c, epos, Simb, simb);
		//--------------------------------------
		char m[1000];
		int q = 0;
		//limpiar(epos,1000);
		limpiar(m, 1000);
		for (int i = 0; i<strlen(epos); i++) {
			if (epos[i] == '+' || epos[i] == '-') {
				m[q] = ' ';
				q++;
				m[q] = epos[i];
				q++;
			}
			else {
				m[q] = epos[i];
				q++;
			}
		}
		limpiar(epos, 1000);
		strcpy(epos, m);
		char e[1000];
		limpiar(e, 1000);
		int it = 0;
		while (it<2) {
			j = 0;
			reducir(epos, e, j);
			it++;
		}
		//----------------------------------------
		printf("\nLa conversión a Posfija es: %s", epos);
		_getche();
		limpiar(e, 1000);
		///Fin ingreso polaca posfijo

		char *cad = (char*)malloc(75 * sizeof(char));
		char *cad1 = (char*)malloc(75 * sizeof(char));
		char *QR = (char*)malloc(75 * sizeof(char));
		char *auxCad;
		//int val = 0;
		float val1, val2;
		float res = 0, num, trigo = 0, trigo1 = 0;
		bool bandera = false;
		Pila *numero = new Pila();
		Pila *signo = new Pila();
		//ingresar(cad);
		strcpy(cad, epos);
		strcpy(cad1, cad);
		while (strcmp(cad, "") != 0) {
			strtok_s(cad, " ", &auxCad);
			switch (*cad) {
			case 's':
				cad = auxCad;
				strtok_s(cad, " ", &auxCad);
				trigo = seno(atof(cad), 100);
				numero = numero->push(numero, trigo);
				printf("\n%.2f", trigo);
				//cad = auxCad;
				//strtok_s(cad, " ", &auxCad);
				break;
			case 'c':
				cad = auxCad;
				strtok_s(cad, " ", &auxCad);
				trigo = coseno(atof(cad), 100);
				numero = numero->push(numero, trigo);
				//cad = auxCad;
				//strtok_s(cad, " ", &auxCad);
				break;
			case 't':
				cad = auxCad;
				strtok_s(cad, " ", &auxCad);
				trigo = coseno(atof(cad), 100);
				if (trigo < 0.1)
				{
					printf("\nERROR SINTACTICO EN LA EXPRECION!!!");
					system("pause");
					system("cls");
					goto ingreso;
				}
				else
				{
					trigo1 = seno(atof(cad), 100);
					numero = numero->push(numero, trigo1 / trigo);
				}

				//cad = auxCad;
				//strtok_s(cad, " ", &auxCad);
				break;
			case '+':
				val1 = numero->getnum(numero);
				numero = numero->pop(numero);
				val2 = numero->getnum(numero);
				numero = numero->pop(numero);
				numero = numero->push(numero, val1 + val2);
				break;
			case '-':
				val1 = numero->getnum(numero);
				numero = numero->pop(numero);
				val2 = numero->getnum(numero);
				numero = numero->pop(numero);
				numero = numero->push(numero, val2 - val1);
				break;
			case '*':
				val1 = numero->getnum(numero);
				numero = numero->pop(numero);
				val2 = numero->getnum(numero);
				numero = numero->pop(numero);
				numero = numero->push(numero, val2 * val1);
				break;
			case '/':
				val1 = numero->getnum(numero);
				numero = numero->pop(numero);
				val2 = numero->getnum(numero);
				numero = numero->pop(numero);
				if (val1 == 0.0f) {
					printf("\nEXPRESION ALGEBRAICA MAL INGRESADA");
					system("pause");
					//return 0;
				}
				numero = numero->push(numero, val2 / val1);
				break;
			default:
				float num = atof(cad);
				printf("\n%.2f", num);
				numero = numero->push(numero, num);
				break;
			}
			printf("\n%s(cad),%s(auxcad)", cad, auxCad);
			cad = auxCad;
		}

		printf("\nEl resultado es: %.2f\n\n", numero->getnum(numero));
		system("pause");

		system("cls");
		printf("1");
		system("pause");
		system("cls");
		main();
	}
	if (y == 5 && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
	{
		system("cls");
		printf("2");
		system("pause");
		system("cls");
		main();
	}
	if (y == 7 && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
	{
		system("cls");
		printf("3");
		system("pause");
		system("cls");
		main();
	}
	if (y == 9 && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
	{
		system("cls");
		printf("4");
		system("pause");
		system("cls");
		main();
	}
	if (y == 11 && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
	{
		system("cls");
		printf("5");
		system("pause");
		system("cls");
		main();
	}
	if (y == 13 && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
	{
		exit(0);
	}
}

VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD wbsr)
{
	printf("Resize event\n");
	printf("Console screen buffer is %d columns by %d rows.\n", wbsr.dwSize.X, wbsr.dwSize.Y);
}

void gotoXY(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

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

//-----Limpia la variable 
void limpiar(char a[], int n) {
	for (int i = 0; i<n; i++) {
		a[i] = '\0';
	}
}

//-----Pasa de una variable a otra 
void pasar(char a[], char b[]) {
	int n1, n2;
	n1 = tama(a);
	n2 = tama(b);
	if (n1>n2) {
		for (int i = 0; i<n1; i++) {
			a[i] = b[i];
		}
	}
	if (n1<n2) {
		for (int i = 0; i<n2; i++) {
			a[i] = b[i];
		}
	}
}

//-----Cuenta cuantos caracteres hay en la variable 
int tama(char var[]) {
	int n;
	for (n = 0; var[n] != '\0'; ++n);
	return(n);
}

//-----Verifica si no le faltan paréntesis a la función 
int verif(char ex[]) {
	char elem, pila[1000];
	int val = 0;
	int n = tama(ex);
	if (n>0) {
		int tope = 0;
		int cont1 = 0; int cont2 = 0;
		for (int i = 0; i<n; i++) {
			elem = ex[i];
			if (elem == '(') {
				pila[tope] = elem;
				tope += 1;
				pila[tope] = '\0';
			}
			else {
				if (elem == ')') {
					if (tope>0) {
						if (pila[tope - 1] == '(') {
							tope -= 1;
							pila[tope] = '\0';
						}
					}
					else {
						pila[tope] = elem;
						tope += 1;
						pila[tope] = '\0';
					}
				}
			}
		}
		if (tope>0) {
			for (int i = 0; i<tope; i++) {
				if (pila[i] == '(') {
					cont1 += 1;
				}
				if (pila[i] == ')') {
					cont2 += 1;
				}
			}
			if (cont1<cont2) {
				val = 2;
			}
			if (cont1>cont2) {
				val = 1;
			}
		}
		else {
			val = 3;
		}
	}
	else {
		val = 0;
	}
	return(val);
}

//-----Conversión de la función a prefija 
void conv_pre(char ex[], char epre[], char Simb[4][2], char simb) {
	char expre[50];
	limpiar(expre, 50);
	conv_pos(ex, expre, Simb, simb);
	inver(epre, expre, simb);
}

//-----Conversión de la función a postfija 
void conv_pos(char ex[], char epos[], char Simb[4][2], char simb) {
	int tope = -1;
	int n = tama(ex);
	char pila[1000];
	while (ex[0] != '\0') {
		simb = ex[0];
		rec_exp(ex);
		n -= 1;
		if (simb == '(') {
			tope += 1;
			pila[tope] = simb;
		}
		else {
			if (simb == ')') {
				while (pila[tope] != '(') {
					int x = tama(epos);
					epos[x] = pila[tope];
					pila[tope] = '\0';
					tope -= 1;
				}
				pila[tope] = '\0';
				tope -= 1;
			}
			else {
				if (sim(simb, Simb, epos) == 0) {
					int x = tama(epos);
					epos[x] = simb;
				}

				else {
					if (tama(pila)>0) {
						while (prio(simb, pila[tope], Simb) <= 0) {
							int x = tama(epos);
							epos[x] = pila[tope];
							pila[tope] = '\0';
							tope -= 1;
							if (tope<0) {
								break;
							}
						}
					}
					tope += 1;
					pila[tope] = simb;
				}
			}
		}
	}
	while (tope >= 0) {
		int x = tama(epos);
		epos[x] = pila[tope];
		pila[tope] = '\0';
		tope -= 1;
	}
}

//-----Recorre los caracteres un lugar 
void rec_exp(char a[]) {
	int x = tama(a), i;
	for (i = 0; i<(x - 1); i++) {
		a[i] = a[i + 1];
	}
	a[i] = '\0';
}

//-----Verifica si es un operador 
int sim(char s, char Simb[4][2], char *epos) {
	int v = 0;
	for (int i = 0; i<4; i++) {
		for (int j = 0; j<2; j++) {
			if (s == Simb[i][j]) {
				v = 1;
			}
		}
	}
	return(v);
}

//-----Verifica la prioridad para colocar en la pila 
int prio(char s1, char s2, char Simb[4][2]) {
	int p1, p2, i, j;
	p1 = p2 = 0;
	for (i = 0; i<4; i++) {
		for (j = 0; j<2; j++) {
			if (s1 == Simb[i][j]) {
				p1 = i;
			}
			if (s2 == Simb[i][j]) {
				p2 = i;
			}
		}
	}
	if (p1<p2) {
		i = -1;
	}
	else {
		if (p1 == p2) {
			i = 0;
		}
		else {
			i = 1;
		}
	}
	return(i);
}

//-----Invierte la función completa 
void inver(char a[], char b[], char simb) {
	int x = tama(b);
	int n = 0;
	for (int i = (x - 1); i >= 0; i--) {
		simb = b[i];
		if (simb == ')') {
			a[n] = '(';
		}
		else {
			if (simb == '(') {
				a[n] = ')';
			}
			else {
				a[n] = simb;
			}
		}
		n++;
	}
}