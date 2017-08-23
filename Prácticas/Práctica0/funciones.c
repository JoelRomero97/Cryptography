#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM_ALFABETO 26
#include "funciones.h"

int i, valor;

//FUNCIONES DE CIFRADO AFFINE
void cifrar (int alfa, int beta)
{
	char * mensaje, * mensajeCifrado = (char *) malloc (sizeof (char));
	validarNumeros (alfa, beta);
	mensaje = leerMensaje ();										//Recibimos el mensaje a cifrar y lo guardamos en un arreglo
	printf("\nMesage to encrypt: %s\n\n", mensaje);					//Imprimimos el arreglo para saber que llego correctamente
	for (i = 0; i < strlen (mensaje); i ++)
	{
		valor = mensaje [i] - 97; 
		valor *= alfa;												//Multiplicamos por alfa
		valor += beta;												//Le sumamos beta
		valor %= TAM_ALFABETO;										//Sacamos el valor modulo el tamaño del alfabeto
		mensajeCifrado [i] = valor + 65;							//Guardamos ese valor en un arreglo
	}
	mensajeCifrado [i] = '\0';										//Le ponemos el fin del arreglo para no tener basura
	escribirTextoCifrado (mensajeCifrado);							//Escribimos en el archivo el mensaje cifrado
}

char * leerMensaje ()
{
	FILE * mensaje;													//Para leer el archivo a cifrar
	char c, * msj = (char *) malloc (sizeof (char));				//Para guardar el mensaje y leer el archivo
	i = 0;															//Indice para guardar el mensaje
	mensaje = fopen ("m.txt", "r");									//Abrimos el archivo 'm.txt' en modo lectura
	if (mensaje == NULL)
		printf("Error while opening file: 'm.txt'.\n");
	else
		printf("File 'm.txt' opened correctly.\n");
	c = fgetc (mensaje);
	while (c != EOF)												//Mientras no sea el final del archivo
	{
		if (c != 32 && c != '\n')									//Si es salto de linea o espacio, se lo quitamos
		{
			if ((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))	//Si es numero o mayuscula, terminamos el programa
			{
				printf("Error, the file to encrypt has to has small letters only.\n");
				exit (0);
			}else if ((c >= 'a' && c <= 'z'))
				msj [i ++] = c;										//Guardamos las letras minusculas en el arreglo
			else
			{
				printf("Error, the file to encrypt has to has small letters only.\n");
			}
		}
		c = fgetc (mensaje);
	}
	fclose (mensaje);												//Cerramos el archivo despues de leerlo
	msj [i] = '\0';													//Marcamos el final del arreglo para no imprimir basura
	return msj;														//Regresamos el archivo en un arreglo de caracteres
}

void escribirTextoCifrado (char * mensajeCifrado)
{
	FILE * textoCifrado;
	textoCifrado = fopen ("c.txt", "w");							//Creamos/Sobreescribimos el archivo 'c.txt' para escritura
	if (textoCifrado == NULL)
		printf("Error while creating file: 'c.txt'\n");
	fprintf(textoCifrado, "%s", mensajeCifrado);					//Escribimos la cadena correspondiente al mensaje cifrado
	printf("File encrypted succesfully.\n\n\n");
	fclose (textoCifrado);											//Cerramos el archivo
}

//FUNCIONES DE DESCIFRADO AFFINE
void descifrar (int alfa, int beta)
{
	char * mensajeCifrado, * mensajeDescifrado = (char *) malloc (sizeof (char));
	validarNumeros (alfa, beta);
	int inverso;
	inverso = inversoMultiplicativo (alfa);
	printf("El inverso de %d es %d\n", alfa, inverso);
	mensajeCifrado = leerMensajeCifrado ();							//Recibimos el mensaje a descifrar y lo guardamos en un arreglo
	printf("\nMessage to decrypt: %s\n\n", mensajeCifrado);			//Imprimimos el arreglo para saber que llego correctamente
	for (i = 0; i < strlen (mensajeCifrado); i ++)
	{
		valor = mensajeCifrado [i] - 65;							//Obtenemos el valor numerico de cada letra del mensaje
		valor *= inverso;											//Encontramos el inverso multiplicativo de alfa
		valor += (TAM_ALFABETO - beta) * inverso;					//Encontramos el inverso aditivo de beta
		valor %= TAM_ALFABETO;										//Sacamos el valor modulo el tamaño del alfabeto
		mensajeDescifrado [i] = valor + 97;							//Guardamos ese valor en un arreglo
	}
	mensajeDescifrado [i] = '\0';									//Le ponemos el fin del arreglo para no tener basura
	printf("\nDecrypted message:'%s'\n\n\n", mensajeDescifrado);
}

char * leerMensajeCifrado ()
{
	FILE * mensaje;													//Para leer el archivo a descifrar
	char c, * msj = (char *) malloc (sizeof (char));				//Para guardar el mensaje y leer el archivo
	i = 0;															//Indice para guardar el mensaje
	mensaje = fopen ("c.txt", "r");									//Abrimos el archivo 'c.txt' en modo lectura
	if (mensaje == NULL)
		printf("Error while opening file: 'c.txt'.\n");
	else
		printf("File 'c.txt' opened correctly.\n");
	c = fgetc (mensaje);
	while (c != EOF)												//Mientras no sea el final del archivo
	{
		if (c != 32 && c != '\n')									//Si es salto de linea o espacio, se lo quitamos
		{
			if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'))	//Si es numero o minuscula, terminamos el programa
			{
				printf("Error, the file to decrypt has been modified.\n");
				exit (0);
			}else if ((c >= 'A' && c <= 'Z'))
				msj [i ++] = c;										//Guardamos las letras mayusculas en el arreglo
			else
			{
				printf("Error, the file to decrypt has been modified.\n");
				exit (0);
			}
		}
		c = fgetc (mensaje);
	}
	fclose (mensaje);												//Cerramos el archivo despues de leerlo
	msj [i] = '\0';													//Marcamos el final del arreglo para no imprimir basura
	return msj;														//Regresamos el archivo en un arreglo de caracteres
}

int inversoMultiplicativo (int alfa)
{
	int j, flag = 0;
	for (i = 1; i < TAM_ALFABETO; i ++)
		for (j = 1; j < TAM_ALFABETO; j ++)
		{
			if (((TAM_ALFABETO * i) + 1) == (alfa * j) )
				return j;
		}
	//return j;
}

//FUNCIONES COMPARTIDAS DE CIFRADO/DESCIFRADO AFFINE
void menu ()
{
	int opcion, alfa, beta;
	system ("cls");
	printf("\n\n%cWould you like to encrypt or decrypt?\n\n", 168);
	printf("1. Encrypt\n2. Decrypt\n\n");
	scanf ("%d", &opcion);
	printf("\n\nAlfa's value: ");
	scanf ("%d", &alfa);
	printf("\nBeta's value: ");
	scanf ("%d", &beta);
	if (opcion == 1)
		cifrar (alfa, beta);
	else if (opcion == 2)
		descifrar (alfa, beta);
	else
		menu ();
}

void validarNumeros (int alfa, int beta)
{
	if (alfa == 1)
	{
		if (beta == TAM_ALFABETO)
		{
			printf("Error, the text won't encrypt/decrypt correctly due to alfa's and beta's values.\n\nAlfa: %d \t Beta: %d.\n\n", alfa, beta);
			menu ();
		}
	}else if (alfa <= 0)
	{
		printf("Error, alfa's value must be between 1 and alphabet's size.\n");
		menu ();
	}
	if (beta <= 0 || beta > TAM_ALFABETO)
	{
		printf("Error, beta's value must be between 1 and alphabet's size.\n");
		menu ();
	}
	if (mcd (alfa, TAM_ALFABETO) != 1)
	{
		printf("Error, the text won't encrypt/decrypt correctly due to alfa's value.\n");
		menu ();
	}
}

int mcd (int alfa, int alfabeto)
{
	int temp;
	while (alfa > 0)
	{
         temp = alfa;
         alfa = alfabeto % alfa;
         alfabeto = temp;
     }
     return alfabeto;
}