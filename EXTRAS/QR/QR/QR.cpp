// QR.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <time.h>
#include <string>
#include <string.h>
#include "qrcodegen.h"
struct Datos
{
	char nombre[10] = { "fact" };
	char apellido[10] = { "0" };
	char TODO[50] = { "Msxtr" };
};
static void generarQrBasico(char *dato1);
static void printQr(const uint8_t qrcode[]);
typedef Datos dat;
int main()
{
	dat user;
	char *dato, cad;
	dato = (char *)malloc(50 * sizeof(char));
	int i;
	srand(time(NULL));
	i = rand() % 9999999;
	//strcpy(user.nombre,"fact");
	strcat_s(user.TODO, user.nombre);
	//itoa(i,dato,10);
	strcat_s(user.TODO, "0001");
	//strcat_s(user.TODO, "@espe.edu.ec");
	generarQrBasico(user.TODO);
	system("pause");

}

static void generarQrBasico(char *dato1) {
	char *dato = dato1; // User-supplied text
	enum qrcodegen_Ecc errCorLvl = qrcodegen_Ecc_LOW;  // Error correction level

													   // Make and print the QR Code symbol
	uint8_t qrcode[qrcodegen_BUFFER_LEN_MAX];
	uint8_t tempBuffer[qrcodegen_BUFFER_LEN_MAX];
	bool ok = qrcodegen_encodeText(dato, tempBuffer, qrcode, errCorLvl,
		qrcodegen_VERSION_MIN, qrcodegen_VERSION_MAX, qrcodegen_Mask_AUTO, true);
	if (ok)
		printQr(qrcode);
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

