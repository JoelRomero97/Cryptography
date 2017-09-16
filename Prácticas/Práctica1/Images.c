#include <stdio.h>
#include <stdlib.h>
#include "Functions.c"

int main (int argc, char* argv[])
{	
	FILE * original, * encrypted;
	bmp image;
	int i, option;
	char * encryptedImage = (char *) malloc (sizeof (char));
	char * originalImage = (char *) malloc (sizeof (char));
	system ("cls");
	if (argc < 3)
		printf("Error, missing arguments.\nExample: %s Image.bmp EncryptedImage.bmp\n\n", argv [0]);
	else
	{
		originalImage = (char *) argv [1];
		encryptedImage = (char *) argv [2];
	}
	printf("%cDo you want to encryp or decrypt?\n\n1.Encrypt\t2.Decrypt\n\n", 168);
	scanf ("%d", &option);

	//We open each file in binary mode
	original = open_file (originalImage, encryptedImage, 1);
	encrypted = open_file (originalImage, encryptedImage, 2);

	//We read and write the head of the file
	read_head (original, encrypted, &image);
	if (option == 1)
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
		hill (original, encrypted, &image, 'e');
	else if (option == 2)
		hill (original, encrypted, &image, 'd');
=======
		operation_mode (original, encrypted, &image, 'e');
		//hill (original, encrypted, &image, 'e');
	else if (option == 2)
		operation_mode (original, encrypted, &image, 'd');
		//hill (original, encrypted, &image, 'd');
>>>>>>> NuevaPractica
=======
		hill (original, encrypted, &image, 'e');
	else if (option == 2)
		hill (original, encrypted, &image, 'd');
>>>>>>> NuevaPractica
=======
		operation_mode (original, encrypted, &image, 'e');
	else if (option == 2)
		operation_mode (original, encrypted, &image, 'd');
>>>>>>> NuevaPractica
	exit (0);
}
