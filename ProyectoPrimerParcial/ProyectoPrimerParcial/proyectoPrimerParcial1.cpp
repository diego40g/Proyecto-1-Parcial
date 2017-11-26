/*UNIVERSIDAD DE LAS FUERZAS ARMADAS "ESPE"
INGENIERIA EN SISTEMAS E INFORMATICA
PROYECTO PRIMER PARCIAL
INTEGRANTES: MICHAEL MORALES, DIEGO PAZ
PROFESOR: FERNANDO SOLIS
*/
#include<iostream>
#include<stdio.h>
#include<conio.h>
#include<string>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#include<time.h>

struct Nodo {
	char placaAuto[10];
	char horaEntrada[10];
	char horaSalida[10];
	long numeroCedula;
	char modeloAuto[10];
	float tarifaPagar;
	struct Nodo *siguienteDireccion;
	struct Nodo *anteriorDireccion;
};
typedef struct Nodo *ListaDoble;
struct Placas {
	char letrasPlaca[3];
	char numerosPlaca[4];
};
typedef struct Placas placa;
void letras(char* validar) {

	int c, i = 0;
	printf("\nIngrese");
	i = 0;
	while ((c = _getch()) != 13) {

		if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == 32) {
			*(validar + i) = c;
			printf("%c", c);
			i++;
		}

	}
	printf("\nsi");
	return;
}
void numeros(char *validar) {
	int c, i = 0;
	i = 0;
	while ((c = _getch()) != 13) {
		if ((c >= 48 && c <= 57)) {

			*(validar + i) = c;
			printf("%c", c);
			i++;
		}
	}
}
void flotantes(char *validar) {
	int c, i = 0;
	i = 0;
	while ((c = _getch()) != 13) {
		if ((c >= 48 && c <= 57) || c == 46) {

			*(validar + i) = c;
			printf("%c", c);
			i++;
		}
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

	int* c;
	c = (int*)malloc(10 * sizeof(int));

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

void ingresarPrimerDato(ListaDoble &lista) {
	char todo[80], lpDateStr[50], lpTimeStr[30];
	Nodo *aux = new Nodo();
	//char *letrasPlaca=(char*)malloc(3*sizeof(char));
	char letrasPlaca[3];
	//char *numeroPlaca = (char*)malloc(4 * sizeof(char));
	char numeroPlaca[4];
	char fecha[50];
	char hora[30];
	Placas placa;

	/*aux->numeroCedula = atoi(cedula());
	printf("\nINGRESE PLACA");
	printf("\nINGRESE LETRAS DE LA PLACA:");
	letras(letrasPlaca);
	strcpy_s(placa.letrasPlaca, letrasPlaca);
	strcpy_s(aux->placaAuto, letrasPlaca);
	strcat_s(aux->placaAuto, "-");
	printf("\nINGRESE NUMEROS DE LA PLACA:");
	numeros(numeroPlaca);
	strcat_s(aux->placaAuto, numeroPlaca);*/
	GetDateFormat(LOCALE_USER_DEFAULT, DATE_LONGDATE, NULL, NULL, fecha, 50);
	GetTimeFormat(LOCALE_USER_DEFAULT, TIME_FORCE24HOURFORMAT, NULL, NULL, hora, 30);
	strcpy_s(todo, fecha);
	strcat_s(todo, hora);
	printf("\n%s", todo);
	//	aux->anteriorDireccion = aux->siguienteDireccion = NULL;
	//lista = aux;
}
void ingresarUltimaPosicion(ListaDoble &lista) {

	if (lista != NULL) {
		Nodo *aux1, *aux2;
		aux1 = new Nodo();
		aux1->numeroCedula = atoi(cedula());
		printf("\nINGRESE PLACA");
		gets_s(aux1->placaAuto);
		aux2 = lista;
		while (aux2->siguienteDireccion != NULL) {
			aux2 = aux2->siguienteDireccion;
		}
		aux1->siguienteDireccion = aux2->siguienteDireccion;
		aux2->siguienteDireccion = aux1;
		aux1->anteriorDireccion = aux2;
		printf("\nDATO INGRESADO!");
	}
	else {
		printf("\nDEBE INGRESAR EL PRIMER ELEMENTO!!\n");
	}
}
void ingresarPrimeraPosicion(ListaDoble &lista) {
	if (lista != NULL) {
		Nodo *aux = new Nodo();
		aux->numeroCedula = atoi(cedula());
		printf("\nINGRESE PLACA");
		gets_s(aux->placaAuto);
		aux->siguienteDireccion = lista;
		aux->anteriorDireccion = lista->anteriorDireccion;
		lista->anteriorDireccion = aux;
		lista = aux;
		printf("\nDATO INGRESADO!!!\n");
	}
	else {
		printf("\nDEBE INGRESAR EL PRIMER ELEMENTO!!\n");
	}
}
void ingresarEntre(ListaDoble lista) {
	system("pause");
	int posicion;
	printf("\nINGRESE POSICION A INSERTAR");
	scanf_s("%d", &posicion);
	//posicion+=1;
	if (lista != NULL) {
		int iterador = 1, bandera = 0;
		if (posicion == 0) {
			ingresarPrimeraPosicion(lista);
		}
		else {

			Nodo *aux2 = lista;
			while (aux2->siguienteDireccion != NULL) {
				if (posicion == iterador) {
					Nodo *aux1 = new Nodo();
					aux1->numeroCedula = atoi(cedula());
					printf("\nINGRESE PLACA");
					gets_s(aux1->placaAuto);
					aux1->siguienteDireccion = aux2->siguienteDireccion;
					aux2->siguienteDireccion = aux1;
					aux1->anteriorDireccion = aux2;
					aux1->siguienteDireccion->anteriorDireccion = aux1;
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
	printf("\nSE INSERTo ENTRE %d y %d", posicion, posicion + 1);
}




int main()
{
	ListaDoble lista = NULL;
	ingresarPrimerDato(lista);
	char *a;
	a = (char*)malloc(10 * sizeof(char));

	letras(a);
	printf("\n%s", a);
	system("pause");

	return 0;
}
