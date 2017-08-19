#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM_ALFABETO 26
#include "funciones.h"

void cifrar (int alfa, int beta)
{
	int i, valor, * valores;
	char * mensaje, * mensajeCifrado;
	mensaje = leerMensaje ();										//Recibimos el mensaje a cifrar y lo guardamos en un arreglo
	printf("\nMensaje: %s\n", mensaje);								//Imprimimos el arreglo para saber que llego correctamente
	valores = (int *) malloc (sizeof (int) * strlen (mensaje));
	for (i = 0; i < strlen (mensaje); i ++)
	{
		valor = obtenerValorLetra (mensaje [i]);					//Obtenemos el valor numerico de cada letra del mensaje
		valor *= alfa;												//Multiplicamos por alfa
		valor += beta;												//Le sumamos beta
		valor %= TAM_ALFABETO;										//Sacamos el valor modulo el tamaño del alfabeto
		valores [i] = valor;										//Guardamos ese valor en un arreglo
	}
	valores [i] = '\0';												//Le ponemos el fin del arreglo para no tener basura
	mensajeCifrado = obtenerMsjCifrado (valores, mensaje);			//Obtenemos el mensaje cifrado
	//escribirTextoCifrado (mensajeCifrado);							//Escribimos en el archivo el mensaje cifrado
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
	fclose (mensaje);												//Cerramos el archivo despues de leerlo
	msj [i] = '\0';													//Marcamos el final del arreglo para no imprimir basura
	return msj;														//Regresamos el archivo en un arreglo de caracteres
}

int obtenerValorLetra (char letra)
{
	int i;
	char c;
	if (letra >= 'A' && letra <= 'Z')
		letra += 32;												//Si es una mayuscula, la convertimos en minuscula para obtener valor
	for (i = 0; i < TAM_ALFABETO; i ++)
	{
		c = 'a' + i;												//Recorremos todo el alfabeto
		if (c == letra)												//Si ya llegamos a la letra buscada, rompemos el ciclo
			break;
	}
	return i;														//Regresamos el valor de la letra siendo la a = 0, b = 1, ... z = 25
}

char * obtenerMsjCifrado (int * valores, char * mensaje)
{
	int i;
	char c, * mensajeCifrado = (char *) malloc (sizeof (char));		//Para guardar el mensaje cifrado
	for (i = 0; i < strlen (mensaje); i ++)
	{
		c = 'A' + valores [i];										//A la letra 'A' le sumamos el valor de la letra nueva
		mensajeCifrado [i] = c;
	}
	mensajeCifrado [i] = '\0';
	return mensajeCifrado;
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