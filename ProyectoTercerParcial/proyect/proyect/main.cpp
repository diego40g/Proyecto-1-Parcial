/*
UNIVERSIDAD DE LAS FUERZAS ARMADAS"ESPE"
PROYECTO TERCER PARCIAL
Ingreso y grafico de arboles 
Binario, B, B+, AVL 
Menu con mouse
Generera QR
genera txt
genera pdf
Cancion de fondo
Imagen del grupo
Opcion Ayuda
Ingreso inicio,fin,medio
Instalador
y proyecto ejecutado en phyton
Autores:	Michael Morales
			Diego Paz
Fecha de Creacion: 28-01-2018	Fecha de Modificacion: 18-02-2018
Profesor: Ing. Edgar Fernando Solis Acosta
Carrera: Ingenieria en Sitemas e Informatica
*/

#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include <MMsystem.h>
#include <ctype.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#include<string>
#include<time.h>
#include"bmas.h"
#include<iostream>
#include"qrcodegen.h"
#include"PDF.h"
#include"b.h"
#include"btree.h"
#include"avl.h"

#include<allegro5/allegro.h> // Librería inicial de Allegro
#include<allegro5/allegro_primitives.h> // Addon de primitivas (figuras)
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>
#define VENTANA_X 750
#define VENTANA_Y 450
//int x = 130, y = 0;
// Redefinición de tipos
typedef ALLEGRO_DISPLAY aDisplay;

using namespace std;

// Variables globales
ALLEGRO_DISPLAY *dis = NULL;
int VY = 0, VX = 130;
// Funciones
void inicializar(void)
{
	// Inicializar los addons
	if (!al_init())
	{
		fprintf(stderr, "Error al inicializar Allegro."); // Imprimir errores en stream STDERR
		exit(-1);
	}
	if (!al_init_primitives_addon())
	{
		fprintf(stderr, "Error al inicializar el addon de primitivas."); // Imprimir errores en stream STDERR
		exit(-2);
	}

	dis = al_create_display(VENTANA_X, VENTANA_Y); // Crear el display de tamaño 500x300 píxeles

	al_set_window_title(dis, "ARBOL BINARIO MORALES/PAZ"); // Establecer el título de la ventana
}
void finalizar()
{
	al_shutdown_primitives_addon(); // Finalizar el addon de primitivas
	al_destroy_display(dis); // Destruir la ventana
}
void colorearPantalla()
{
	al_clear_to_color(al_map_rgb_f(7, 7, 7)); // Limpiar la ventana y establecer un color de fondo RGB (color rojo: R=0=0.0, G=255=1.0, B=0=0.0)
}

HANDLE hStdin;
DWORD fdwSaveOldMode;
void ErrorExit(LPSTR);
void KeyEventProc(KEY_EVENT_RECORD);
void MouseEventProc(MOUSE_EVENT_RECORD);
void ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD);
void GetMousePosWin(MOUSE_EVENT_RECORD);
void gotoXY(int x, int y);

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void gotoxy(int x, int y) {
	HANDLE cualquiera;
	cualquiera = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(cualquiera, pos);
}
void membrete() {
	printf("\t\tUNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE\n");
	printf("Integrantes: Michael Morales\tDiego Paz\n");
	printf("Fecha de creacion: 2018-01-28\t\tFecha de modificacion: 2018-01-30\n");
	printf("Profesor:Fernando Solis\n");
	printf("Carrera: Ingenieria en Istemas e Informatica\n\n");
}


//-----------------------
struct nodoBinario
{
	int nro;
	struct nodoBinario *izq, *der;
};
typedef struct nodoBinario *ABB;
ABB crearNodo(int x)
{
	ABB nuevoNodo = new(struct nodoBinario);
	nuevoNodo->nro = x;
	nuevoNodo->izq = NULL;
	nuevoNodo->der = NULL;

	return nuevoNodo;
}
void insertar(ABB &arbol, int x)
{
	if (arbol == NULL)
	{
		arbol = crearNodo(x);
	}
	else if (x < arbol->nro)
		insertar(arbol->izq, x);
	else if (x > arbol->nro)
		insertar(arbol->der, x);
}

//-------------------------
void preOrden(ABB arbol, ALLEGRO_FONT *font)
{
	if (arbol != NULL)
	{
		VX += 5;
		al_draw_textf(font, al_map_rgb_f(0, 0, 0), VX, VY, 0, "%d ", arbol->nro);
		VX += 10;
		preOrden(arbol->izq, font);
		preOrden(arbol->der, font);
	}
}

void enOrden(ABB arbol, ALLEGRO_FONT *font)
{
	if (arbol != NULL)
	{
		enOrden(arbol->izq, font);
		VX += 5;
		al_draw_textf(font, al_map_rgb_f(0, 0, 0), VX, VY, 0, "%d ", arbol->nro);
		VX += 10;
		enOrden(arbol->der, font);
	}
}

void postOrden(ABB arbol, ALLEGRO_FONT *font)
{
	if (arbol != NULL)
	{
		postOrden(arbol->izq, font);
		postOrden(arbol->der, font);
		VX += 5;
		al_draw_textf(font, al_map_rgb_f(0, 0, 0), VX, VY, 0, "%d ", arbol->nro);
		VX += 10;
	}
}

void limpiar(char *cad, int tam) {
	for (int i = 0; i<tam; i++) {
		*(cad + i) = '\0';
	}
}

void FOR(char *espacios, int n, int i)
{
	if (i == n)
	{
		return;
	}
	else
	{
		strcat(espacios, "   ");
		FOR(espacios, n, ++i);
	}
}
int cont = 0;
int verArbol(ABB arbol, int n, ALLEGRO_FONT *font, char* espacios, int **mat)
{
	//int aux = *i;
	if (arbol == NULL) {
		al_flip_display(); // Dibujar en pantalla todo lo almacenado en el buffer, en este caso solamente está el círculo de arriba
		return cont;
	}
	else {
		*(*(mat + 0) + cont) = n * 9;
		printf("%d=%d->%d=%d//%d\t%d\n", *(*(mat + 0) + cont), n * 9, *(*(mat + 1) + cont), VY, cont, arbol->nro);
		cont++;
		// j+=15;
		//*i+=1;
		verArbol(arbol->der, n + 1, font, espacios, mat);
		limpiar(espacios, 100);
		FOR(espacios, n, 0);

		al_draw_circle((n * 9) + 10, VY + 6, 10, al_map_rgb_f(1, 0, 0), 2);
		al_draw_textf(font, al_map_rgb_f(0, 0, 0), 0/*posicion en x*/, VY/*posicion en y*/, 0, "%s  %d", espacios, arbol->nro);//es como printf



																															   //coordenadas de Y no esta bien xD
		*(*(mat + 1) + cont - 1) = VY;



		VY += 30;

		verArbol(arbol->izq, n + 1, font, espacios, mat);
	}
}
int verif(int *cad,int tam){
	int verificar=0,cont=0;
	for(int i=0;i<tam;i++){
		for(int j=i+1;j<tam;j++){
			if(*(cad+i)==*(cad+j)){
				verificar=0;
				return verificar;
			}
		}
	}
	for(int i=0;i<tam;i++){
		if(*(cad+i)<*(cad+i+1)){
			verificar=2;
			cont++;
		}
	}
	printf("\ncont%d\n",cont);
	if(cont==tam-1){
		verificar = 1;
	}
		if((*(cad+tam-1)<*(cad+tam-2))&&(*(cad+0)<*(cad+tam-1))){
			verificar=3;
		}

	return verificar;
}
//---------------------------------------------para B----------


//--------------------------------------Hasta aqui para B--------------------------


void color(int X){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), X);
}
void menu(int y) 
{
	color(07);
	gotoXY(25, 1);
	printf("MENU");
	int aux = 3;
	if ((y == 1) || (y == 3) || (y == 5) || (y == 7) || (y == 9) || (y == 11) || (y == 13) || (y == 15) || (y == 17) || (y == 19) || (y == 21) || (y == 23))
	{
		if (y == 1)
		{
			PlaySound(TEXT("D:\\TERCER LV\\Estructura de Datos\\TercerPArcial\\allegro_visual\\proyect\\proyect\\Audio Inicio\\Introduccion.wav"), NULL, SND_ASYNC);
			color(112);
		}

		if (y == aux)
		{
			PlaySound(TEXT("D:\\TERCER LV\\Estructura de Datos\\TercerPArcial\\allegro_visual\\proyect\\proyect\\Audio Inicio\\arbolBinario.wav"), NULL, SND_ASYNC);
			color(112);
		}
		else
		{
			color(07);
		}
		gotoXY(13, aux);
		printf("\xDB Arbol Binario"); aux += 2;
		if (y == aux)
		{
			PlaySound(TEXT("D:\\TERCER LV\\Estructura de Datos\\TercerPArcial\\allegro_visual\\proyect\\proyect\\Audio Inicio\\arbolB.wav"), NULL, SND_ASYNC);
			color(112);
		}
		else
		{
			color(07);
		}
		gotoXY(13, aux);
		printf("\xDB Arbol B"); aux += 2;
		if (y == aux)
		{
			PlaySound(TEXT("D:\\TERCER LV\\Estructura de Datos\\TercerPArcial\\allegro_visual\\proyect\\proyect\\Audio Inicio\\arbolBmas.wav"), NULL, SND_ASYNC);
			color(112);
		}
		else
		{
			color(07);
		}
		gotoXY(13, aux);
		printf("\xDB Arbol B+"); aux += 2;
		if (y == aux)
		{
			PlaySound(TEXT("D:\\TERCER LV\\Estructura de Datos\\TercerPArcial\\allegro_visual\\proyect\\proyect\\Audio Inicio\\arbolAVL.wav"), NULL, SND_ASYNC);
			color(112);
		}
		else
		{
			color(07);
		}
		gotoXY(13, aux);
		printf("\xDB Arbol AVL"); aux += 2;
		if (y == aux)
		{
			PlaySound(TEXT("D:\\TERCER LV\\Estructura de Datos\\TercerPArcial\\allegro_visual\\proyect\\proyect\\Audio Inicio\\pdf.wav"), NULL, SND_ASYNC);
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
			PlaySound(TEXT("D:\\TERCER LV\\Estructura de Datos\\TercerPArcial\\allegro_visual\\proyect\\proyect\\Audio Inicio\\ayuda.wav"), NULL, SND_ASYNC);
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
			PlaySound(TEXT("D:\\TERCER LV\\Estructura de Datos\\TercerPArcial\\allegro_visual\\proyect\\proyect\\Audio Inicio\\imagen.wav"), NULL, SND_ASYNC);
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
			PlaySound(TEXT("D:\\TERCER LV\\Estructura de Datos\\TercerPArcial\\allegro_visual\\proyect\\proyect\\Audio Inicio\\backup.wav"), NULL, SND_ASYNC);
			color(112);
		}
		else
		{
			color(07);
		}
		gotoXY(13, aux);
		printf("\xDB Back up's"); aux += 2;
		if (y == aux)
		{
			PlaySound(TEXT("D:\\TERCER LV\\Estructura de Datos\\TercerPArcial\\allegro_visual\\proyect\\proyect\\Audio Inicio\\phyton.wav"), NULL, SND_ASYNC);
			color(112);
		}
		else
		{
			color(07);
		}
		gotoXY(13, aux); aux += 2;
		printf("\xDB Python");
		if (y == aux)
		{
			PlaySound(TEXT("D:\\TERCER LV\\Estructura de Datos\\TercerPArcial\\allegro_visual\\proyect\\proyect\\Audio Inicio\\mongo.wav"), NULL, SND_ASYNC);
			color(112);
		}
		else
		{
			color(07);
		}
		gotoXY(13, aux); aux += 2;
		printf("\xDB Mongo");
		if (y == aux)
		{
			PlaySound(TEXT("D:\\TERCER LV\\Estructura de Datos\\TercerPArcial\\allegro_visual\\proyect\\proyect\\Audio Inicio\\salir.wav"), NULL, SND_ASYNC);
			color(112);
		}
		else
		{
			color(07);
		}
		gotoXY(13, aux);
		printf("\xDB Salir");
	}
	else
	{
		color(00);
		PlaySound(NULL, NULL, 0);
	}
}
void ingresar(char *cad)
{
	int c, i = 0;
	while ((c = _getch()) != 13)
	{
		if ((c >= 48 && c <= 57) || (c == 44))
		{
			*(cad + i) = c;
			printf("%c", c);
			i++;
		}
		*(cad + i) = '\0';
	}
	return;
}
int *tok(char *cad, int *tam)
{
	char *ptr;
	int i = 0;
	int *res = (int*)malloc(50 * sizeof(int));
	char aux;
	strtok_s(cad, ",", &ptr);
	printf("\n%s",ptr);
	*(res + i) = atof(cad);
	while (strcmp (cad,"") != 0)
	{
		printf("\n%s", cad);
		cad = ptr;
		i++;
		strtok_s(cad, ",", &ptr);		
		*(res + i) = atof(cad);		
	}
	system("pause");
	*tam = i;
	return res;
}

void prueba(ALLEGRO_FONT *font) {
	colorearPantalla();
	int fps = 50;
	al_draw_textf(font, al_map_rgb_f(0, 0, 0), 0/*posicion en x*/, 0/*posicion en y*/, 0, "%d", fps);//es como printf
	al_flip_display(); // Dibujar en pantalla todo lo almacenado en el buffer, en este caso solamente está el círculo de arriba

					   //system("read -t 5"); // Cerrar la ventana después de 5 segundos (Linux)

	system("pause");
}
void audio(char *cad)
{
	for (int i = 0; i < strlen(cad); i++)
	{
		switch (*(cad + i))
		{
		case '1':
		{
			//PlaySound(TEXT("D:\\TERCER LV\\Estructura de Datos\\TercerPArcial\\allegro_visual\\proyect\\proyect\\Audio Inicio\\1.wav"), NULL, SND_SYNC);
			break;
		}
		case '2':
		{
			//PlaySound(TEXT("D:\\TERCER LV\\Estructura de Datos\\TercerPArcial\\allegro_visual\\proyect\\proyect\\Audio Inicio\\2.wav"), NULL, SND_SYNC);
			break;
		}
		case '3':
		{
			//PlaySound(TEXT("D:\\TERCER LV\\Estructura de Datos\\TercerPArcial\\allegro_visual\\proyect\\proyect\\Audio Inicio\\3.wav"), NULL, SND_SYNC);
			break;
		}
		case '4':
		{
			//PlaySound(TEXT("D:\\TERCER LV\\Estructura de Datos\\TercerPArcial\\allegro_visual\\proyect\\proyect\\Audio Inicio\\4.wav"), NULL, SND_SYNC);
			break;
		}
		case '5':
		{
			//PlaySound(TEXT("D:\\TERCER LV\\Estructura de Datos\\TercerPArcial\\allegro_visual\\proyect\\proyect\\Audio Inicio\\5.wav"), NULL, SND_SYNC);
			break;
		}
		case '6':
		{
			//PlaySound(TEXT("D:\\TERCER LV\\Estructura de Datos\\TercerPArcial\\allegro_visual\\proyect\\proyect\\Audio Inicio\\6.wav"), NULL, SND_SYNC);
			break;
		}
		case '7':
		{
			//PlaySound(TEXT("D:\\TERCER LV\\Estructura de Datos\\TercerPArcial\\allegro_visual\\proyect\\proyect\\Audio Inicio\\7.wav"), NULL, SND_SYNC);
			break;
		}
		case '8':
		{
			//PlaySound(TEXT("D:\\TERCER LV\\Estructura de Datos\\TercerPArcial\\allegro_visual\\proyect\\proyect\\Audio Inicio\\8.wav"), NULL, SND_SYNC);
			break;
		}
		case '9':
		{
			//PlaySound(TEXT("D:\\TERCER LV\\Estructura de Datos\\TercerPArcial\\allegro_visual\\proyect\\proyect\\Audio Inicio\\9.wav"), NULL, SND_SYNC);
			break;
		}
		case '0':
		{
			//PlaySound(TEXT("D:\\TERCER LV\\Estructura de Datos\\TercerPArcial\\allegro_visual\\proyect\\proyect\\Audio Inicio\\0.wav"), NULL, SND_SYNC);
			break;
		}
		case ',':
		{
			//PlaySound(TEXT("D:\\TERCER LV\\Estructura de Datos\\TercerPArcial\\allegro_visual\\proyect\\proyect\\Audio Inicio\\,.wav"), NULL, SND_SYNC);
			break;
		}
		default:
		{
			//PlaySound(NULL, NULL, 0);
			break;
		}
		}
	}
}
void buck() {
	FILE *His;
	FILE *buc;
	int pau, c;
	char lectura[50];
	char *fecha = (char*)malloc(40 * sizeof(char));
	char *fechaAux = (char*)malloc(40 * sizeof(char));
	time_t current_time;
	limpiar(fecha, 40);
	limpiar(fechaAux, 40);
	current_time = time(NULL);
	ctime(&current_time);
	strcpy(fecha, ctime(&current_time));
	for (int i = 0; i < 24; i++) {
		*(fechaAux + i) = *(fecha + i);
	}
	strcat(fechaAux, ".txt");

	if ((His = fopen("HISTORIAL.txt", "r")) == 0) {
		printf("\nNO SE HAN REALIZADO OPERACIONES\n");
		system("pause");
		return;
	}
	for (int i = 0; i < strlen(fechaAux); i++) {
		if (*(fechaAux + i) == ':') {
			*(fechaAux + i) = '-';
		}
	}
	printf("%s", fechaAux);
	system("pause");
	His = fopen("HISTORIAL.txt", "r");
	buc = fopen(fechaAux, "w");
	/*while ((pau = fgetc(His)) != EOF) {
	if (pau == '\n') {
	printf("\n");
	fprintf_s(buc, "\n");
	}
	else {
	printf("%c", pau);
	fprintf_s(buc, "%c", pau);
	}
	fflush(stdin);
	}*/
	//---------
	for (int i = 0; !feof(His); i++) {
		fflush(stdin);
		fscanf(His, "%[^\n]", &lectura);
		printf("%s\n", lectura);
		fprintf_s(buc, "%s\n", lectura);
		if ((c = getc(His)) == EOF) {
			break;
		}
	}
	//----------
	printf("\n\n\nBACKUP CON FECHA Y HORA ACTUAL CREADO\n");

	system("pause");
	fflush(stdin);

	fclose(His);
	fclose(buc);
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
void pdf1()
{
	//PDF 1
	int imp;
	system("cls");
	imp = AyudaF1();
	if (imp == 1)
	{
		ofstream LeerDatos;
		LeerDatos.open("Posfija.txt", ios::out | ios::app);
		tifstream in(TEXT("Posfija.txt"));
		PrintFile(in);
		ShellExecute(NULL, TEXT("open"), TEXT("D:\\TERCER LV\\Estructura de Datos\\Proyecto - 1 - Parcial\\ProyectoSegundoParcial\\clases anidadas\\Posfija.pdf"), NULL, NULL, SW_SHOWNORMAL);
	}
	system("pause");
	_getch;
}

int main()
{

	//	encabezado();

	//system("pause");
	system("cls");
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

int menuB() 
{
	VY = 0;
	const char *titulo = "MENU ARBOL BINARIO";
	const char *opciones[] = { "Ingresar inOrden","Ingresar preOrden","Ingresar postOrden","Ingresar nodos para dibujar arbol","Regresar al menu" };
	int n = 5;
	int selec = 1;
	int tecla;
	bool repite = true;
	gotoxy(7, 8 + selec);
	printf(">");
	do {
		gotoxy(7, 8 + selec);
		printf(">");
		gotoxy(15, 2); printf("%s", titulo);
		for (int i = 0; i<n; i++) {
			gotoxy(10, 9 + i); printf("%s", opciones[i]);
		}
		tecla = _getch();
		gotoxy(7, 8 + selec);
		printf("   ");
		switch (tecla) {
		case 72:
			selec--;
			if (selec<1) {
				selec = n;
			}
			break;
		case 80:
			selec++;
			if (selec>n) {
				selec = 1;
			}
			break;
		case 13:
			repite = false;
			break;
		}
	} while (repite);
	return selec;
}

// get Window pos through windows api
void GetMousePosWin(MOUSE_EVENT_RECORD mer)
{
	int x = 0, y = 0;
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
	{/*
	 BINARIO
	 */
		printf("\nArbol binario \n");
		//----------------------------------------------------------------------
		int raiz;
		char *espacios = (char*)malloc(100 * sizeof(char));
		limpiar(espacios, 100);
		ABB arbol = NULL;   // creado Arbol
		int tam1;
		char *cadena = (char*)malloc(500 * sizeof(char));  // numero de nodos del arbol
		int val, n, tam, opc; // elemento a insertar en cada nodo

		printf("\n\t\t  ..[ ARBOL BINARIO DE BUSQUEDA ]..  \n\n");
		int *res = (int*)malloc(50 * sizeof(int));

		int *aux = res;
	ini:
		system("cls");
		opc = menuB();
		switch (opc)
		{
		case 1:
		{
			VX = 130;
			arbol = NULL;
			VY = 6;
			system("cls");
			printf(" Ingresar expresion y separe los numeros con \",\":  \n");
			ingresar(cadena);
			audio(cadena);
			strcat(cadena, ",");
			res = tok(cadena, &tam);
			if (verif(res, tam) != 1)
			{
				if (verif(res, tam) == 0)
				{
					printf("\nCADENA MAL INGREADA...\n");
				}
				else
				{
					printf("\nLA CADENA NO ESTA INGRESADA EN inOrden...\n");
					system("pause");
					goto ini;
				}
			}
			else
			{
				printf("\nIN ORDEN\n");
				if (tam % 2 == 0)
				{
					raiz = *(res + ((tam / 2) - 1));
				}
				else
				{
					raiz = *(res + ((tam / 2)));
				}
				insertar(arbol, raiz);
				printf("\n");
				for (int i = 0; i<tam; i++)
				{
					val = *(res + i);
					insertar(arbol, val);
				}
				printf("\n Mostrando ARBOL... \n\n");
				system("pause");
				inicializar();
				al_init();
				al_init_font_addon();
				al_init_ttf_addon();
				al_install_keyboard();
				ALLEGRO_FONT *font = al_load_ttf_font("ARIAL.ttf", 11, 0);
				int i, **mat = (int**)malloc(500 * sizeof(int));
				for (i = 0; i < 50; i++)
				{
					*(mat + i) = (int*)malloc(50 * sizeof(int));
				}
				for (i = 0; i < 50; i++)
				{
					for (int j = 0; j < 50; j++)
					{
						*(*(mat + i) + j) = 0;
					}
				}
				i = 0;
				colorearPantalla();
				verArbol(arbol, 0, font, espacios, mat);
				int auxiliar = 0;
				for (int j = 0; j < i; j++)
				{
					*(*(mat + 1) + j) = 6 + auxiliar;
					auxiliar += 30;
				}
				VY += 20;
				VX = 130;
				al_draw_textf(font, al_map_rgb_f(0, 0, 0), 0/*posicion en x*/, VY/*posicion en y*/, 0, "PRE ORDEN:");//es como printf
																													 //printf("\n\n Pre Orden  :  ");
				preOrden(arbol, font);
				VY += 20;
				VX = 130;
				al_draw_textf(font, al_map_rgb_f(0, 0, 0), 0/*posicion en x*/, VY/*posicion en y*/, 0, "POST ORDEN:");//es como printf
																													  //printf("\n\n Post Orden :  ");
				postOrden(arbol, font);
				printf("MATRIZ \n");
				for (int j = 0; j < i - 1; j++)
				{
					printf("%d=%d\n", *(*(mat + 0) + j), *(*(mat + 1) + j + 1));
					al_draw_line(*(*(mat + 0) + j), *(*(mat + 1) + j), *(*(mat + 0) + j + 1), *(*(mat + 1) + j + 1), al_map_rgb_f(0, 1, 0), 2);
				}
				al_flip_display(); // Dibujar en pantalla todo lo almacenado en el buffer, en este caso solamente está el círculo de arriba
				printf("\n");
				system("pause");
				finalizar(/*display*/);
				system("pause");
			}
			goto ini;
			break;
		}
		case 2:
		{
			arbol = NULL;
			VY = 6;
			VX = 130;
			system("cls");
			printf(" Ingresar expresion y separe los numeros con \",\":  \n");
			ingresar(cadena);
			audio(cadena);
			strcat(cadena, ",");
			res = tok(cadena, &tam);
			if (verif(res, tam) != 2)
			{
				if (verif(res, tam) == 0)
				{
					printf("\nCADENA MAL INGREADA...\n");
				}
				else
				{
					printf("\nLA CADENA NO ESTA INGRESADA EN preOrden...\n");
					system("pause");
					goto ini;
				}
			}
			else
			{
				printf("\nPRE ORDEN\n");
				printf("\n");
				for (int i = 0; i<tam; i++)
				{
					val = *(res + i);
					insertar(arbol, val);
				}
				printf("\n Mostrando ARBOL... \n\n");
				system("pause");
				inicializar();
				al_init();
				al_init_font_addon();
				al_init_ttf_addon();
				al_install_keyboard();
				ALLEGRO_FONT *font = al_load_ttf_font("ARIAL.ttf", 11, 0);
				ALLEGRO_BITMAP *text_img = al_create_bitmap(al_get_text_width(font, "PRIMERO"), al_get_font_ascent(font));
				colorearPantalla();
				int i, **mat = (int**)malloc(500 * sizeof(int));
				for (i = 0; i < 2; i++)
				{
					*(mat + i) = (int*)malloc(2 * sizeof(int));
				}
				i = 0;
				verArbol(arbol, 0, font, espacios, mat);
				VY += 20;
				VX = 130;
				al_draw_textf(font, al_map_rgb_f(0, 0, 0), 0/*posicion en x*/, VY/*posicion en y*/, 0, "IN ORDEN:");//es como printf
				printf("\n\n En orden   :  ");
				enOrden(arbol, font);
				VY += 20;
				VX = 130;
				al_draw_textf(font, al_map_rgb_f(0, 0, 0), 0/*posicion en x*/, VY/*posicion en y*/, 0, "POST ORDEN:");//es como printf
				printf("\n\n Post Orden :  ");
				postOrden(arbol, font);
				al_flip_display(); // Dibujar en pantalla todo lo almacenado en el buffer, en este caso solamente está el círculo de arriba
				printf("\n");
				system("pause");
				finalizar(/*display*/);
			}
			goto ini;
			break;
		}
		case 3:
		{
			arbol = NULL;
			VY = 6;
			VX = 130;
			system("cls");
			printf(" Ingresar expresion y separe los numeros con \",\":  \n");
			ingresar(cadena);
			audio(cadena);
			strcat(cadena, ",");
			res = tok(cadena, &tam);
			if (verif(res, tam) != 3)
			{
				if (verif(res, tam) == 0)
				{
					printf("\nCADENA MAL INGREADA...\n");
					system("pause");
				}
				else
				{
					printf("\nLA CADENA NO ESTA INGRESADA EN postOrden...\n");
					system("pause");
					goto ini;
				}
			}
			else
			{
				printf("\nPOST ORDEN\n");
				printf("\n");
				for (int i = tam - 1; i >= 0; i--)
				{
					val = *(res + i);
					insertar(arbol, val);
				}
				printf("\n Mostrando ARBOL... \n\n");
				system("pause");
				inicializar();
				al_init();
				al_init_font_addon();
				al_init_ttf_addon();
				al_install_keyboard();
				ALLEGRO_FONT *font = al_load_ttf_font("ARIAL.ttf", 11, 0);
				ALLEGRO_BITMAP *text_img = al_create_bitmap(al_get_text_width(font, "PRIMERO"), al_get_font_ascent(font));
				colorearPantalla();
				int i, **mat = (int**)malloc(500 * sizeof(int));
				for (i = 0; i < 2; i++)
				{
					*(mat + i) = (int*)malloc(2 * sizeof(int));
				}
				i = 0;
				verArbol(arbol, 0, font, espacios, mat);
				VY += 20;
				VX = 130;
				al_draw_textf(font, al_map_rgb_f(0, 0, 0), 0/*posicion en x*/, VY/*posicion en y*/, 0, "IN ORDEN:");//es como printf
				printf("\n\n En orden   :  ");
				enOrden(arbol, font);
				VY += 20;
				VX = 130;
				al_draw_textf(font, al_map_rgb_f(0, 0, 0), 0/*posicion en x*/, VY/*posicion en y*/, 0, "PRE ORDEN:");//es como printf
				printf("\n\n Pre Orden  :  ");
				preOrden(arbol, font);
				al_flip_display(); // Dibujar en pantalla todo lo almacenado en el buffer, en este caso solamente está el círculo de arriba
				printf("\n");
				system("pause");
				finalizar(/*display*/);
			}
			goto ini;
			break;
		}
		case 4:
		{
			arbol = NULL;
			VY = 6;
			VX = 130;
			system("cls");
			printf(" Ingresar expresion y separe los numeros con \",\":  \n");
			ingresar(cadena);
			audio(cadena);
			strcat(cadena, ",");
			res = tok(cadena, &tam);
			for (int i = tam - 1; i >= 0; i--)
			{
				val = *(res + i);
				insertar(arbol, val);
			}
			system("pause");
			system("cls");
			printf("\n Mostrando ARBOL... \n\n");
			system("pause");
			inicializar();
			al_init();
			al_init_font_addon();
			al_init_ttf_addon();
			al_install_keyboard();
			ALLEGRO_FONT *font = al_load_ttf_font("ARIAL.ttf", 11, 0);
			ALLEGRO_BITMAP *text_img = al_create_bitmap(al_get_text_width(font, "PRIMERO"), al_get_font_ascent(font));
			colorearPantalla();
			int i, **mat = (int**)malloc(500 * sizeof(int));
			for (i = 0; i < 2; i++)
			{
				*(mat + i) = (int*)malloc(2 * sizeof(int));
			}
			i = 0;
			i = verArbol(arbol, 0, font, espacios, mat);
			VY += 20;
			VX = 130;
			al_draw_textf(font, al_map_rgb_f(0, 0, 0), 0/*posicion en x*/, VY/*posicion en y*/, 0, "IN ORDEN:");//es como printf
			printf("\n\n En orden   :  ");
			enOrden(arbol, font);
			VY += 20;
			VX = 130;
			al_draw_textf(font, al_map_rgb_f(0, 0, 0), 0/*posicion en x*/, VY/*posicion en y*/, 0, "PRE ORDEN:");//es como printf
			printf("\n\n Pre Orden  :  ");
			preOrden(arbol, font);
			VY += 20;
			VX = 130;
			al_draw_textf(font, al_map_rgb_f(0, 0, 0), 0/*posicion en x*/, VY/*posicion en y*/, 0, "POST ORDEN:");//es como printf
			printf("\n\n Post Orden :  ");
			postOrden(arbol, font);
			al_flip_display(); // Dibujar en pantalla todo lo almacenado en el buffer, en este caso solamente está el círculo de arriba
			system("pause");
			finalizar(/*display*/);
			goto ini;
			break;
		}
		}
		system("pause");
		main();
		//------------------------------------------------
	}
	if (y == 5 && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
	{
		/***************************************		
		Arbol B
		****************************************/
		system("cls");
		printf("arbol b");
		//--------------------------------------

		//----------------------------------------
		/*float res;
		ingresopolapre(&res);
		audio(res*/
		system("pause");
		system("cls");
		main();
	}
	if (y == 7 && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
	{
		/************************************************************		
		ARbol b+
		************************************************************/
		system("cls");
		printf("arbol b+");
		bmas ar;
		char *cad = (char*)malloc(500 * sizeof(char));
		limpiar(cad, 500);
		int *res = (int*)malloc(50 * sizeof(int));
		int tam, pointer, val1;
		ar.reiniciarBmas();
		printf("\nIngrese el valor de m: ");
		scanf_s("%d", &pointer);
		val1 = pointer - 1;
		ar.valores(pointer, val1);
		printf(" Ingresar expresion y separe los numeros con \",\":  \n");
		ingresar(cad);
		strcat(cad, ",");
		res = tok(cad, &tam);
		int val;
		printf("nPointer = %d\n", pointer);
		for (int i = 0; i < tam; i++) {
			val = *(res + i);
			ar.insert2(val, NULL);

		}
		printf("\n Mostrando ARBOL... \n\n");
		system("pause");
		inicializar();
		al_init();
		al_init_font_addon();
		al_init_ttf_addon();
		al_install_keyboard();
		ALLEGRO_FONT *font = al_load_ttf_font("ARIAL.ttf", 11, 0);
		colorearPantalla();
		ar.imp(font);			//	siiiiiiiiiiiiiiiiiiiiiii
		system("pause");
		system("cls");
		finalizar(/*display*/);
		main();
	}
	if (y == 9 && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
	{
		/***********************************AVL*****************************/
		system("cls");
		printf("arbol avl");

		avl_node *root = NULL;
		int choice, item;
		avl avl;
		char *cadenaAvl = (char*)malloc(500 * sizeof(char));
		int *resAvl = (int*)malloc(50 * sizeof(char));
		int tam, val;
		printf(" Ingresar expresion y separe los numeros con \",\":  \n");
		limpiar(cadenaAvl, 500);
		ingresar(cadenaAvl);
		strcat(cadenaAvl, ",");
		resAvl = tok(cadenaAvl, &tam);
		for (int i = 0; i<tam; i++)
		{
			val = *(resAvl + i);
			root = avl.insert(root, val);
		}
		/*if (root == NULL)
		{
		printf("Tree is Empty");
		}*/
		printf("Balanced AVL Tree:");
		printf("\n Mostrando ARBOL... \n\n");
		system("pause");
		inicializar();
		al_init();
		al_init_font_addon();
		al_init_ttf_addon();
		al_install_keyboard();
		ALLEGRO_FONT *font = al_load_ttf_font("ARIAL.ttf", 11, 0);
		colorearPantalla();
		avl.reiniciar();
		avl.display(root, 1,font);
		al_flip_display(); // Dibujar en pantalla todo lo almacenado en el buffer, en este caso solamente está el círculo de arriba
		system("pause");
		finalizar(/*display*/);
		printf("\n\nIn-Orden:");
		avl.inorder(root);
		printf("\n\npre-Orden:");
		avl.preorder(root);
		printf("\n\npost-Orden:");
		avl.postorder(root);
		printf("\n");
		system("pause");
		system("cls");
		main();
	}
	if (y == 11 && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
	{
		system("cls");
		printf("pdf");
		system("pause");
		main();
	}
	if (y == 13 && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
	{
		system("cls");
		printf("ayuda");
		//ShellExecute(NULL, TEXT("open"), TEXT("Ayuda.chm"), NULL, NULL, SW_SHOWNORMAL);
		system("pause");
		system("cls");
		main();
	}
	if (y == 15 && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
	{
		system("cls");
		printf("foto");
		//ShellExecute(NULL, TEXT("open"), TEXT("FotoGrupal.exe"), NULL, NULL, SW_SHOWNORMAL);		
		system("pause");
		main();
	}
	if (y == 17 && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
	{
		system("cls");
		//buck();
		printf("buck");
		system("pause");
		system("cls");
		main();
	}
	if (y == 19 && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
	{
		system("cls");
		//ShellExecute(NULL, TEXT("open"), TEXT("Proyecto.py"), NULL, NULL, SW_SHOWNORMAL);
		printf("python");
		system("pause");
		system("cls");
		main();
	}
	if (y == 21 && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
	{
		system("cls");
		printf("mongo");
		//system("java -jar conexion_mongo.jar");

		system("pause");		
		system("cls");
		main();
	}
	if (y == 23 && mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
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
