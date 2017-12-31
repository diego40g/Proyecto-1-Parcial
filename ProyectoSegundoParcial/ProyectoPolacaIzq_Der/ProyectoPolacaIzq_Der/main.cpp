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

string ingresar(char *cad)
{
	int c, i = 0;
	while ((c=_getch())!=13)
	{
		if ((c >= 48 && c <= 57)||(c==42)||(c==43)||(c==45)||(c==47)||(c==32)||(c==65)||(c==67)||(c==69)||(c==78)||(c==79)||(c==83)||(c==84)||(c==97)||(c==99)||(c==101)||(c==110)||(c==111)||(c==115)||(c==116))
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
	string res=cad;
	return res;
}

int main()
{
	char *cad, *aux, *ptr=NULL, *cad1=NULL, **str;
	int cont = 0, i = 0, z = 0;
	str = (char **)malloc(25 * sizeof(char *));
	for (int j = 0; j < 25; j++)
	{
		*(str + j) = (char *)malloc(25 * sizeof(char));
	}

	cad = (char *)malloc(50 * sizeof(char));
	aux = (char *)malloc(75 * sizeof(char));
	cad1 = (char *)malloc(75 * sizeof(char));
	fflush(stdin);
	ingresar(cad);
	Pila *numero = new Pila();
	Pila *signo = new Pila();

	strcpy(aux, cad);

	while (strcmp(cad, "") != 0)
	{
		strtok_s(cad, " ", &ptr);
		strcpy(*(str + cont), cad);
		cad = ptr;
		cont++;
	}

	for (int j = 0; j < cont; j++)
	{
		printf("\n%s\n", *(str + j));
	}

	strcpy(cad1, *(str + cont - 1));
	cont--;
	do {
		strcat(cad1, " ");
		strcat(cad1, *(str + cont - 1));
		cont--;
	} while (cont != 0);
	
	printf("\t\n%s\n", cad1);

	while(strcmp(cad1,"")!=0)
	{
		strtok_s(cad1, " ",&ptr);
		//printf("%s", cad);
		if ((*cad1 == 42) || (*cad1 == 43) || (*cad1 == 45) || (*cad1 == 47))
		{
			signo=signo->push(signo, cad);
		}
		if ((*cad >= 48) && (*cad <= 57))
		{
			numero = numero->push(numero, cad);
		}
		if (strcmp(cad, "sen") == 0)
		{

		}
		if (strcmp(cad, "cos") == 0)
		{

		}
		if (strcmp(cad, "tan") == 0)
		{

		}
		cad = ptr;
	}
	printf("\n");
	numero->imprimir(numero);
	printf("\n");
	signo->imprimir(signo);
	system("pause"); system("pause");
	return 0;
}

