/*UNIVERSIDAD DE LAS FUERZAS ARMADAS "ESPE"
INGENIERIA EN SISTEMAS E INFORMATICA
PROYECTO PRIMER PARCIAL
INTEGRANTES: MICHAEL MORALES, DIEGO PAZ
PROFESOR: FERNANDO SOLIS
*/
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#include<time.h>

struct Nodo {
	char horaEntrada[30];
	char fechaEntrada[50];
	char horaSalida[30];
	char fechaSalida[50];
	long numeroCedula;
	char modeloAuto[10];
	float tarifaPagar;
	char nombrePropietario[50];
	char placaAuto[8];
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
void letras(char *validar) {
	int c, i = 0;
	i = 0;
	while ((c = _getch()) != 13) {
		if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == 32) {
			*(validar + i) = c;
			printf("%c", c);
			i++;
		}
	}
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

int menu() {
	char c;
	const char *fr[50] = { "INGRESAR PRIMER AUTO AL PARQUEADERO ","INGRESAR AUTO ALINICIO DEL PARQUEADERO ","INGRESAR AUTO AL FINAL DEL PARQUEADERO "
		,"INGRESAR AUTO ENTRE PARQUEADEROS","MOSTRAR AUTOS EN ELPARQUEADERO","SALIR DEL PARQUEADERO ","SALIR DEL SISTEMA                    " };
	system("cls");
	gotoxy(40, 1);
	printf("MENU");
	int y = 2, n;
	for (int i = 1; i<8; i++) {
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
		for (int i = y; i<9; i++) {
			gotoxy(20, i + 1);
			printf("%s", fr[i - 2]);
		}

		if (c == -32) {
			c = _getch();
			if (c == 72) {
				if (y == 2) {
					y = 8;
				}
				else {
					y--;
				}

			}
			if (c == 80) {
				if (y == 8) {
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
	
	Nodo *aux = new Nodo();
	char *letrasPlaca = (char*)malloc(3 * sizeof(char));
	//char letrasPlaca[3], numeroPlaca[4], fecha[50], hora[30];
	char *numeroPlaca = (char*)malloc(4 * sizeof(char));
	char plac[30];
	char *fecha=(char*)malloc(50*sizeof(char));
	char *hora= (char*)malloc(30 * sizeof(char));;
	Placas placa;

	aux->numeroCedula = atoi(cedula());
	printf("\nINGRESE NOMBRE DEL PROPIETARIO:");
	//fflush(stdin);
	letras(aux->nombrePropietario);
	printf("\nINGRESE PLACA");
	printf("\nINGRESE LETRAS DE LA PLACA:");
	//fflush(stdin);
	letras(letrasPlaca);
	//fflush(stdin);
	//strcpy_s(aux->placaAuto, strlen(letrasPlaca)+1, letrasPlaca);
	//strcpy_s(aux->placaAuto[10], letrasPlaca);
	//strcpy_s((&aux->placaAuto)[3], letrasPlaca);

	strcat_s(aux->placaAuto, sizeof aux->placaAuto, letrasPlaca);
	printf("\nSI PASO");
	//fflush(stdin);
	strcat_s(aux->placaAuto, sizeof aux->placaAuto, "-");
	//fflush(stdin);
	printf("\nINGRESE NUMEROS DE LA PLACA:");
	numeros(numeroPlaca);
	//fflush(stdin);
	strcat_s(aux->placaAuto, sizeof aux->placaAuto, numeroPlaca);
	printf("\nINGRESE MODELO DEL AUTO: ");
	letras(aux->modeloAuto);
	GetDateFormat(LOCALE_USER_DEFAULT, DATE_LONGDATE, NULL, NULL, aux->fechaEntrada, 50);
	GetTimeFormat(LOCALE_USER_DEFAULT, TIME_FORCE24HOURFORMAT, NULL, NULL, aux->horaEntrada, 30);
	aux->anteriorDireccion = aux->siguienteDireccion = NULL;
	lista = aux;
}
void ingresarUltimaPosicion(ListaDoble &lista) {
	Placas placa;
	Nodo *aux2=lista, *aux = new Nodo();
	
	char *letrasPlaca=(char*)malloc(3*sizeof(char));
	//char letrasPlaca[3], numeroPlaca[4], fecha[50], hora[30];
	char *numeroPlaca = (char*)malloc(4 * sizeof(char));

	char *fecha=(char*)malloc(50*sizeof(char));
	char *hora= (char*)malloc(30 * sizeof(char));;
	
	if (lista != NULL) {
		
		aux->numeroCedula = atoi(cedula());
		printf("\nINGRESE NOMBRE DEL PROPIETARIO:");
		//fflush(stdin);
		letras(aux->nombrePropietario);
		printf("\nINGRESE PLACA");
		printf("\nINGRESE LETRAS DE LA PLACA:");
		//fflush(stdin);
		letras(letrasPlaca);
		//fflush(stdin);
		strcpy_s(aux->placaAuto, strlen(letrasPlaca) + 1, letrasPlaca);

		//fflush(stdin);
		strcat_s(aux->placaAuto, sizeof aux->placaAuto, "-");
		//fflush(stdin);
		printf("\nINGRESE NUMEROS DE LA PLACA:");
		numeros(numeroPlaca);
		//fflush(stdin);
		strcat_s(aux->placaAuto, sizeof aux->placaAuto, numeroPlaca);
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
		printf("\nDATO INGRESADO!");
	}
	else {
		printf("\nDEBE INGRESAR EL PRIMER ELEMENTO!!\n");
	}
}
void ingresarPrimeraPosicion(ListaDoble &lista) {
	Nodo *aux = new Nodo(), *aux2 = lista;
	Placas placa;
	char *letrasPlaca=(char*)malloc(3*sizeof(char));
	//char letrasPlaca[3], numeroPlaca[4], fecha[50], hora[30];
	char *numeroPlaca = (char*)malloc(4 * sizeof(char));

	char *fecha=(char*)malloc(50*sizeof(char));
	char *hora= (char*)malloc(30 * sizeof(char));;
	if (lista != NULL) {
		
		aux->numeroCedula = atoi(cedula());
		printf("\nINGRESE NOMBRE DEL PROPIETARIO:");
		//fflush(stdin);
		letras(aux->nombrePropietario);
		printf("\nINGRESE PLACA");
		printf("\nINGRESE LETRAS DE LA PLACA:");
		//fflush(stdin);
		letras(letrasPlaca);
		//fflush(stdin);
		strcpy_s(aux->placaAuto, strlen(letrasPlaca) + 1, letrasPlaca);

		//fflush(stdin);
		strcat_s(aux->placaAuto, sizeof aux->placaAuto, "-");
		//fflush(stdin);
		printf("\nINGRESE NUMEROS DE LA PLACA:");
		numeros(numeroPlaca);
		//fflush(stdin);
		strcat_s(aux->placaAuto, sizeof aux->placaAuto, numeroPlaca);
		printf("\nINGRESE MODELO DEL AUTO: ");
		letras(aux->modeloAuto);
		GetDateFormat(LOCALE_USER_DEFAULT, DATE_LONGDATE, NULL, NULL, aux->fechaEntrada, 50);
		GetTimeFormat(LOCALE_USER_DEFAULT, TIME_FORCE24HOURFORMAT, NULL, NULL, aux->horaEntrada, 30);
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
	Placas placa;
	char *letrasPlaca=(char*)malloc(3*sizeof(char));
	//char letrasPlaca[3], numeroPlaca[4], fecha[50], hora[30];
	char *numeroPlaca = (char*)malloc(4 * sizeof(char));

	char *fecha=(char*)malloc(50*sizeof(char));
	char *hora= (char*)malloc(30 * sizeof(char));;
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
					printf("\nINGRESE LETRAS DE LA PLACA:");
					//fflush(stdin);
					letras(letrasPlaca);
					//fflush(stdin);
					strcpy_s(aux->placaAuto, strlen(letrasPlaca) + 1, letrasPlaca);

					//fflush(stdin);
					strcat_s(aux->placaAuto, sizeof aux->placaAuto, "-");
					//fflush(stdin);
					printf("\nINGRESE NUMEROS DE LA PLACA:");
					numeros(numeroPlaca);
					//fflush(stdin);
					strcat_s(aux->placaAuto, sizeof aux->placaAuto, numeroPlaca);
					printf("\nINGRESE MODELO DEL AUTO: ");
					letras(aux->modeloAuto);
					GetDateFormat(LOCALE_USER_DEFAULT, DATE_LONGDATE, NULL, NULL, aux->fechaEntrada, 50);
					GetTimeFormat(LOCALE_USER_DEFAULT, TIME_FORCE24HOURFORMAT, NULL, NULL, aux->horaEntrada, 30);
					aux->siguienteDireccion = aux2->siguienteDireccion;
					aux2->siguienteDireccion = aux;
					aux->anteriorDireccion = aux2;
					aux->siguienteDireccion->anteriorDireccion = aux;
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

/*float calcularTarifa(ListaDoble lista, long ced, char* placa) {
	if (lista != NULL) {
		while (lista->siguienteDireccion != NULL) {
			if (ced==lista->numeroCedula && strcmp(placa, lista->placaAuto) == 0) {

			}
		}

	}
	else {
		printf("\nNO HAY AUTOS");
	}
}*/

int salirParqueadero(ListaDoble lista) {
	int comp=0;
	long cedulaAux;
	char *placaAux = (char*)malloc(10 * sizeof(char));
	char *letrasPlaca = (char*)malloc(3 * sizeof(char));
	char *numeroPlaca = (char*)malloc(4 * sizeof(char));
	printf("\nINGRESE SU CEDULA PARA SACAR SU AUTO");
	cedulaAux = atoi(cedula());
	printf("\nINGRESE LAS PLACAS DE SU AUTO PARA PODER SACARLO");
	printf("\nINGRESE LAS LETRAS DE SU PLACA: ");
	letras(letrasPlaca);
	strcpy_s(placaAux, strlen(letrasPlaca), letrasPlaca);
	strcat_s(placaAux, sizeof placaAux, "-");
	printf("\nINGRESE LOS NUMEROS DE SU PLACA: ");
	numeros(numeroPlaca);
	strcat_s(placaAux, sizeof placaAux, numeroPlaca);
	if (lista != NULL) {
		if (cedulaAux == lista->numeroCedula&&strcmp(placaAux,lista->placaAuto)==0&&lista->siguienteDireccion == NULL&&lista->anteriorDireccion == NULL) {
			comp++;
			printf("\nLA LISTA SOLO TIENE UN ELEMENTO, SE BORRARA TODO");
			return comp;
		}
	
		while (lista->siguienteDireccion != NULL) {
			if (cedulaAux == lista->numeroCedula&&strcmp(placaAux, lista->placaAuto) == 0) {
				if (lista->anteriorDireccion == NULL) {
					comp += 2;
					return comp;
				}
				if (lista->siguienteDireccion != NULL&&lista->anteriorDireccion != NULL) {
					comp += 3;
					return comp;
				}

			}


			lista = lista->siguienteDireccion;
			if (cedulaAux == lista->numeroCedula&&strcmp(placaAux, lista->placaAuto) == 0 && lista->siguienteDireccion == NULL&&lista->anteriorDireccion != NULL) {
				comp += 4;
				return comp;
			}
		}
	}else{
		printf("\n\nNO HAY AUTOS REGISTRADOS...");
	}
	return 0;
}

void imprimirLista(ListaDoble lista) {
	if (lista == NULL) {
		printf("No hay elementos en la lista!\n\n");
	}
	else {
		while (lista != NULL) {
			printf("%d", lista->numeroCedula);
			printf("%s", lista->placaAuto);
			printf("\n\n");
			lista = lista->siguienteDireccion;
		}
	}
}


int main()
{
	ListaDoble lista = NULL;
	//char a;
	int opcionDelMenu, comp;
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
		comp = 0;
		system("cls");
		//verNumerosPrimos(listaDoble,listaPrimos);
		/*comp = eliminarDeLista(listaDoble);
		printf("\n%d", comp);
		if (comp == 1) {
			listaDoble = NULL;
		}
		if (comp == 2) {
			printf("\nSI PASO");
			aux1 = listaDoble;
			listaDoble = listaDoble->siguienteDireccion;
			aux1->siguienteDireccion = aux1->anteriorDireccion = NULL;
			aux1 = NULL;
			listaDoble->anteriorDireccion = NULL;
		}
		if (comp == 3) {
			while (listaDoble->siguienteDireccion != NULL) {
				listaDoble = listaDoble->siguienteDireccion;
			}
			//		aux1=listaDoble;
			listaDoble = listaDoble->anteriorDireccion;
			listaDoble->siguienteDireccion = NULL;
			comp = 0;
			while (listaDoble->anteriorDireccion != NULL) {
				listaDoble = listaDoble->anteriorDireccion;
			}
		}*/


		system("pause");
		goto inicio;
		break;
	}
	case 7: {
		return 0;
		break;
	}
	}
	system("pause");

	return 0;
}
