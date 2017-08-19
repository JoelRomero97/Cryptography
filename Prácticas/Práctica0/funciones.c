#include <stdio.h>
#include <stdlib.h>
#define TAM_ALFABETO 26
#include "funciones.h"

void cifrar (int alfa, int beta)
{
	int i, j;
	char * mensaje, * mensajeCifrado;
	mensaje = leerMensaje ();										//Recibimos el mensaje a cifrar y lo guardamos en un arreglo
	printf("%s\n", mensaje);										//Imprimimos el arreglo para saber que llego correctamente
}

char * leerMensaje ()
{
	FILE * mensaje;													//Para leer el archivo a cifrar
	char c, * msj = (char *) malloc (sizeof (char));				//Para guardar el mensaje y leer el archivo
	int i = 0;														//Indice para guardar el mensaje
	mensaje = fopen ("m.txt", "r");									//Abrimos el archivo 'm.txt' en modo lectura
	if (mensaje == NULL)
		printf("Error al abrir el archivo 'm.txt'.\n");
	else
		printf("Archivo 'm.txt' abierto.\n");
	c = fgetc (mensaje);
	while (c != EOF)												//Mientras no sea el final del archivo
	{
		if (c != 32 && c != '\n')									//Si es salto de linea o espacio, se lo quitamos
		{
			if ((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))	//Si es numero o mayuscula, terminamos el programa
			{
				printf("Error, el archivo a cifrar debe contener unicamente letras minusculas.\n");
				exit (0);
			}else
				msj [i ++] = c;										//Guardamos las letras minusculas en el arreglo
		}
		c = fgetc (mensaje);
	}
	msj [i] = '\0';													//Marcamos el final del arreglo para no imprimir basura
	return msj;														//Regresamos el archivo en un arreglo de caracteres
}


void descifrar (int alfa, int beta)
{
	//
}


/*
char c;
	for (i = 0; i < TAM_ALFABETO; i ++)
	{
		c = 'a' + i;
		printf("Letra %d: %c\n", i, c);
	}
*/