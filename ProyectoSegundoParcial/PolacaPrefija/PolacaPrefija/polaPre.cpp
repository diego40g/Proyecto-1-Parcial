#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <conio.h>
#include "PDF.h"
#include "Pila.h"
#include "qrcodegen.h"
#include "Librerias.h"

using namespace std;

int  PDF() 
{
	int x;
	int imp;
	printf("\nPresione Enter ");
	for (;; ) {
		x = _getch();//captura la tecla de funci�n ,pertenece a la libreria conio.h
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


int factorial(int num)
{
	if (num == 0)
		return num = 1;
	else
		return(num*factorial(num - 1));
}

//TAYLOR
typedef struct taylor
{
	int n=0;
	float x=0.0f, sin=0.0f, cos=0.0f, tan=0.0f;
};

taylor funtrigono(taylor var, char *car)
{
	float aux;
	int n;
	var.n=10;
	var.x=atof(car);
	
	n=var.x;
	if(var.x>360)
	do{
		var.x-=360;
	}while(var.x>360);
	
	//primer cuadrante
	if((var.x<=90)&&(var.x>=0))
	{
		var.sin=0;
		var.cos=0;
		aux=var.x*3.141592654/180;
		//sen(x)
		for(int i=0;i<var.n;i++)
		{
			var.sin+=(pow(-1,i)*(pow(aux,((2*i)+1)))/factorial(2*i+1));
		}
		//cos(x)
		for(int i=0;i<var.n;i++)
		{
			var.cos+=(pow(-1,i)*(pow(aux,(2*i)))/factorial(2*i));
		}
	}
		
	//segundo cuadrante
	if((var.x<=180)&&(var.x>=91))
	{
		var.sin=0;
		var.cos=0;
		aux=0;
		aux=var.x-90;
		aux=aux*3.141592654/180;
		//sen(x)
		for(int i=0;i<var.n;i++)
		{
			var.sin+=(pow(-1,i)*(pow(aux,(2*i)))/factorial(2*i));
		}
		//cos(x)
		for(int i=0;i<var.n;i++)
		{
			var.cos+=(pow(-1,i)*(pow(aux,((2*i)+1)))/factorial(2*i+1));
		}
		var.cos=-var.cos;
	}
			
	//tercer cuadrante
	if((var.x<=270)&&(var.x>=181))
	{
		var.sin=0;
		var.cos=0;
		aux=0;
		aux=var.x-180;
		aux=aux*3.141592654/180;
		//sen(x)
		for(int i=0;i<var.n;i++)
		{
			var.sin+=(pow(-1,i)*(pow(aux,((2*i)+1)))/factorial(2*i+1));
		}
		var.sin=-var.sin;
		//cos(x)
		for(int i=0;i<var.n;i++)
		{
			var.cos+=(pow(-1,i)*(pow(aux,(2*i)))/factorial(2*i));
		}
		var.cos=-var.cos;
	}
		
	//cuarto cuadrante
	if((var.x<=360)&&(var.x>=271))
	{
		var.sin=0;
		var.cos=0;
		aux=0;
		aux=var.x-270;
		aux=aux*3.141592654/180;
		//sen(x)
		for(int i=0;i<var.n;i++)
		{
			var.sin+=(pow(-1,i)*(pow(aux,(2*i)))/factorial(2*i));
		}
		var.sin=-var.sin;
		//cos(x)
		for(int i=0;i<var.n;i++)
		{
			var.cos+=(pow(-1,i)*(pow(aux,((2*i)+1)))/factorial(2*i+1));
		}
	}
		
	var.tan=(var.sin/var.cos);
	return var;
}


void ingresar(char *cad)
{
	int c, i = 0;
	while ((c = _getch()) != 13)
	{
		if ((c >= 48 && c <= 57) || (c == 42) || (c == 43) || (c == 45) || (c == 47) || (c == 32) || (c == 65) || (c == 67) || (c == 73) || (c == 78) || (c == 79) || (c == 83) || (c == 84) || (c == 97) || (c == 99) || (c == 105) || (c == 110) || (c == 111) || (c == 115) || (c == 116))
		{
			*(cad + i) = c;
			printf("%c", c);
			i++;
			if (i == 48)
			{
				break;
			}
		}
		*(cad + i) = '\0';
	}
}

int main()
{
	char *cad = (char*)malloc(75 * sizeof(char));
	char *cad1 = (char*)malloc(75 * sizeof(char));
	char *QR = (char*)malloc(75 * sizeof(char));
	char *ptr;
	int val = 0;
	float res=0, num, trigo;
	bool bandera=false;
	taylor var;
	Pila *numero = new Pila();
	Pila *signo = new Pila();
	ingresar(cad);
	strcpy(cad1, cad);
	strcpy(QR, cad);
	while (strcmp(cad, "") != 0)
	{
		val++;
		strtok_s(cad, " ", &ptr);
		if ((*cad == 42) || (*cad == 43) || (*cad == 45) || (*cad == 47))
		{
			signo = signo->push(signo, cad);
			if (val == 1)
			{
				bandera = true;
			}
			cad = ptr;
		}
		//if((*cad != 42) || (*cad != 43) || (*cad != 45) || (*cad != 47))
		else
		{
			if (strcmp(cad, "sin") == 0)
			{
				cad = ptr;
				strtok_s(cad, " ", &ptr);
				var=funtrigono(var, cad);
				numero = numero->push(numero, var.sin);
				cad = ptr;
			}
			else
			{
				if (strcmp(cad, "cos") == 0)
				{
					cad = ptr;
					strtok_s(cad, " ", &ptr);
					var = funtrigono(var, cad);
					numero = numero->push(numero, var.cos);
					cad = ptr;
				}
				else
				{
					if (strcmp(cad, "tan") == 0)
					{
						cad = ptr;
						strtok_s(cad, " ", &ptr);
						var = funtrigono(var, cad);
						numero = numero->push(numero, var.tan);
						cad = ptr;
					}
					else
					{
						if (strcmp(cad, "") == 0)
							break;
						else
						{
							float num = atof(cad);
							numero = numero->push(numero, num);
							cad = ptr;
						}
					}
				}
			}
		}
	}
	
	printf("\nSIGNOS\n");
	signo->imprimirsig(signo);
	/*printf("\nNUMEROS\n");
	numero->imprimirnum(numero);*/
	
	Pila *numero1 = new Pila();
	// voltear pila
	
	int cont = 0;

	while (numero!=NULL)
	{
		cont++;
		num = numero->getnum(numero);
		numero1=numero1->push(numero1, num);
		numero = numero->pop(numero);
	}

	numero = numero1->pop(numero1);
	cont--;

	/*printf("\nRESULTADO DE CADENA INVERTIDAD%d\n",cont);
	numero->imprimirnum(numero);*/

	char sig='0';

	sig = signo->getsig(signo);

	for (int i = 0; i < cont; i++)
	{
		sig = signo->getsig(signo);
		printf("\n\t%.2f",res);
		switch (sig)
		{
		case '+':
		{
			if (i == 0)
			{
				res = numero->getnum(numero);
				numero = numero->pop(numero);
				num = numero->getnum(numero);
				numero = numero->pop(numero);
				res += num;
				i++;
				break;
			}
			else
			{
				num = numero->getnum(numero);
				numero = numero->pop(numero);
				res += num;
				i++;
				break;
			}
		}
		case '-':
		{
			if (i == 0)
			{
				res = numero->getnum(numero);
				numero = numero->pop(numero);
				num = numero->getnum(numero);
				numero = numero->pop(numero);
				res -= num;
				i++;
				break;
			}
			else
			{
				num = numero->getnum(numero);
				numero = numero->pop(numero);
				res -= num;
				i++;
				break;
			}
		}
		case '*':
		{
			if (i == 0)
			{
				res = numero->getnum(numero);
				numero = numero->pop(numero);
				num = numero->getnum(numero);
				numero = numero->pop(numero);
				res *= num;
				i++;
				break;
			}
			else
			{
				num = numero->getnum(numero);
				numero = numero->pop(numero);
				res *= num;
				i++;
				break;
			}
		}
		case '/':
		{
			if (i == 0)
			{
				res = numero->getnum(numero);
				numero = numero->pop(numero);
				num = numero->getnum(numero);
				numero = numero->pop(numero);
				if (num == 0)
				{
					printf("\nLAS OPERACIONES INGRESADAS NO SON VALIDAS\n");
				}
				else
				{
					res /= num;
				}
				i++;
				break;
			}
			else
			{
				num = numero->getnum(numero);
				numero = numero->pop(numero);
				res /= num;
				i++;
				break;
			}
		}
		default:
			break;
		}
		signo = signo->pop(signo);
	}

	std::string str=to_string(res);
	char *aux1 = _strdup(str.c_str());
	strcat(QR, " = ");
	strcat(QR,aux1);
	printf("\nOperacion %s",QR);
	printf("\nResultado de la polaca: %.2f\n\n", res);
	system("pause");
	printf("\n\t\t\t\tQR");
	generarQr(QR);
	system("pause");
	//txt
	ofstream datos("Operaciones.txt");
	if (QR == NULL) {
		printf("No hay operaciones ingresadas!\n\n");
		datos << "No hay  operaciones ingresadas!\n\n" << endl;
	}
	else
	{
		datos << "\t\t\tOPERACACIONES\n" << endl;
		datos << "\nSerie ingresada de la Polaca: " << cad1 << endl;
		datos << "\nNotacion prefija polaca: " << QR << endl;
		datos.close();
	}
	//pdf
	int imp;
	system("cls");
	imp = PDF();
	if (imp == 1)
	{
		ofstream datos;
		datos.open("Operaciones.txt", ios::out | ios::app);
		tifstream in(TEXT("Operaciones.txt"));
		PrintFile(in);
		ShellExecute(NULL, TEXT("open"), TEXT("D:\\TERCER LV\\Estructura de Datos\\SegundoParcial\\PolacaPrefija\\PolacaPrefija\\Operaciones.pdf"), NULL, NULL, SW_SHOWNORMAL);
	}
	system("pause");
	_getch;
}