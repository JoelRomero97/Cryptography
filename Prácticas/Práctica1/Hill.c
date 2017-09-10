#include <stdio.h>
#include <stdlib.h>
#include "Functions.c"

int main (int argc, char* argv[])
{	
	FILE * original, * encrypted;
	bmp image;
	int i, lectura, escritura;
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

	//We open each file in binary mode
	original = open_file (originalImage, encryptedImage, 1);
	encrypted = open_file (originalImage, encryptedImage, 2);

	//We read and write the head of the file
	read_head (original, encrypted, &image);
	encrypt_image (original, encrypted, &image);
	exit (0);
}
