#include <stdio.h>
#include <stdlib.h>
#include "Functions.c"

////////////////////////////////////////////////////////////////////////////////////////
////									Images.c 									////
////																				////
////																				////
//// HILL Cipher, is a block cipher that can encrypt/decrypt plaintext messages, 	////
//// images, etc. In this case, I implemented for encrypting and decrypting BMP 	////
//// images pixel by pixel with 5 different modes of operation, for each one, 		////
//// exists a ciphering key Ek and a deciphering key DK.							////
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
