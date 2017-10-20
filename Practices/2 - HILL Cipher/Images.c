#include <stdio.h>
#include <stdlib.h>
#include "Functions.c"

////////////////////////////////////////////////////////////////////////////////////////
////									Images.c 									////
////																				////
////																				////
//// HILL Cipher, es un cifrador por bloques, que puede servir tanto para mensajes 	////
//// de texto como imágenes, en este caso, se implementa para cifrar imágenes BMP 	////
//// pixel a pixel, con 6 distintos modos de operación, para cada uno de estos, 	////
//// existe una llave de cifrado Ek y una de descifrado Dk.							////
//// Para ejecutar, escribir el nombre del ejecutable seguido de la imagen a cifrar ////
//// o descifrar y por último el nombre de la imagen que se obtendrá a la salida.	////
////																				////
////																				////
//// Autor: Romero Gamarra Joel Mauricio											////
////////////////////////////////////////////////////////////////////////////////////////

int main (int argc, char* argv[])
{	
	FILE * original, * encrypted;
	bmp image;
	int i, option;
	char * encryptedImage = (char *) malloc (sizeof (char));
	char * originalImage = (char *) malloc (sizeof (char));
	system ("cls");
	if (argc < 3)
	{
		printf("Error, missing arguments.\nExample: %s Image.bmp EncryptedImage.bmp\n\n", argv [0]);
		exit (0);
	}else
	{
		originalImage = (char *) argv [1];
		encryptedImage = (char *) argv [2];
	}
	printf("\n\n%cDo you want to encryp or decrypt?\n\n1.Encrypt\t2.Decrypt\n\n", 168);
	scanf ("%d", &option);

	//We open each file in binary mode
	original = open_file (originalImage, encryptedImage, 1);
	encrypted = open_file (originalImage, encryptedImage, 2);

	//We read and write the head of the file
	read_head (original, encrypted, &image);
	if (option == 1)
		operation_mode (original, encrypted, &image, 'e');
	else if (option == 2)
		operation_mode (original, encrypted, &image, 'd');
	exit (0);
}
