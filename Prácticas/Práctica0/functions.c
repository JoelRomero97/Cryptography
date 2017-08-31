#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALPHABET_SIZE 26
#include "functions.h"

int i, value;

//ENCRYPTION FUNCTIONS
void encrypt (int alpha, int beta)
{
	char * message, * ciphertext = (char *) malloc (sizeof (char));
	validateNumbers (alpha, beta);
	message = readMessage ();										//Receiving the message to encrypt and save it in a dinamic array
	printf("\nMesage to encrypt: %s\n\n", message);					//Print the message to know it is correct
	for (i = 0; i < strlen (message); i ++)
	{
		value = message [i] - 97; 
		value *= alpha;												//Multiplying each letter by alpha
		value += beta;												//Adding beta
		value %= ALPHABET_SIZE;										//We get the value module alphabet's size
		ciphertext [i] = value + 65;								//We save each encrypted letter in a dinamic array
	}
	ciphertext [i] = '\0';											//We add null character to avoid trash on the array
	writeCiphertext (ciphertext);									//Finally, we write the message in a file
}

char * readMessage ()
{
	FILE * message;													//Pointer for read the file
	char c, * msgToEncrypt = (char *) malloc (sizeof (char));
	i = 0;
	message = fopen ("m.txt", "r");									//Opening the file in reading mode
	if (message == NULL)
		printf("Error while opening file: 'm.txt'.\n");
	else
		printf("File 'm.txt' opened correctly.\n");
	c = fgetc (message);											//Reading the first character
	while (c != EOF)												//While it's not the end of the file
	{
		if (c != 32 && c != '\n')									//If is a space or a line break, we don't add it
		{
			if ((c >= 'a' && c <= 'z'))
				msgToEncrypt [i ++] = c;							//We save small letters on our dinamic array
			else
			{														//If it's another character, we end the program
				printf("Error, the file to encrypt has to has small letters only.\n");
				exit (0);
			}
		}
		c = fgetc (message);										//Reading the next character
	}
	msgToEncrypt [i] = '\0';										//We add null character to avoid trash on the array
	fclose (message);												//We close the file after reading it
	return msgToEncrypt;											//Return the original message to encrypt from file
}

void writeCiphertext (char * ciphertext)
{
	FILE * encryptedMessage;										//Pointer for writing in the file
	encryptedMessage = fopen ("c.txt", "w");						//Opening the file in writing/overwriting mode
	if (encryptedMessage == NULL)
		printf("Error while creating file: 'c.txt'\n");
	fprintf(encryptedMessage, "%s", ciphertext);					//Writing the encryped message on the file as a string
	printf("File encrypted succesfully.\n\n\n");
	fclose (encryptedMessage);										//We close the file after reading it
}

//DECRYPTION FUNCTIONS
void decrypt (int alpha, int beta)
{
	char * ciphertext, * plainText = (char *) malloc (sizeof (char));
	validateNumbers (alpha, beta);
	int inverse;
	inverse = multiplicativeInverse (alpha);						//Obtain the multiplicative inverse for alpha
	ciphertext = readCiphertext ();									//Receiving the message to decrypt and save it in a dinamic array
	printf("\nMessage to decrypt: %s\n\n", ciphertext);				//Print the message to know it is correct
	for (i = 0; i < strlen (ciphertext); i ++)
	{
		value = ciphertext [i] - 65;
		value *= inverse;											//Multiplying each letter by multiplicative inverse of alpha
		value += (ALPHABET_SIZE - beta) * inverse;					//Adding the aditive inverse of beta
		value %= ALPHABET_SIZE;										//We get the value module alphabet's size
		plainText [i] = value + 97;									//We save each decrypted letter in a dinamic array
	}
	plainText [i] = '\0';											//We add null character to avoid trash on the array
	printf("\nDecrypted message:'%s'\n\n\n", plainText);			//Finally, we show the original message to the user
}

char * readCiphertext ()
{
	FILE * message;													//Pointer for read the file
	char c, * msgToDecrypt = (char *) malloc (sizeof (char));
	i = 0;
	message = fopen ("c.txt", "r");									//Opening the file in reading mode
	if (message == NULL)
		printf("Error while opening file: 'c.txt'.\n");
	else
		printf("File 'c.txt' opened correctly.\n");
	c = fgetc (message);											//Reading the first character
	while (c != EOF)												//While it's not the end of the file
	{
		if (c != 32 && c != '\n')									//If is a space or a line break, we don't add it
		{
			if ((c >= 'A' && c <= 'Z'))
				msgToDecrypt [i ++] = c;							//We save capital letters on our dinamic array
			else
			{														//If it's another character, we end the program
				printf("Error, the file to decrypt has been modified.\n");
				exit (0);
			}
		}
		c = fgetc (message);										//Reading the next character
	}
	msgToDecrypt [i] = '\0';										//We add null character to avoid trash on the array
	fclose (message);												//We close the file after reading it
	return msgToDecrypt;											//Return the encrypted message to decrypt from file
}

int multiplicativeInverse (int alpha)
{
	int j, flag = 0;
	for (i = 1; i < ALPHABET_SIZE; i ++)							//We go through all possible combinations from 1 to alphabet's size
		for (j = 1; j < ALPHABET_SIZE; j ++, j++)					//We discard pair numbers from the search
		{
			if (((ALPHABET_SIZE * i) + 1) == (alpha * j))			//If this operation is correct...
				return j;											//We return the value of j
		}
}

//SHARED ENCRYPTION/DECRYPTION FUNCTIONS
void menu ()
{
	int option, alpha, beta;
	system ("cls");
	printf("\n\n%cWould you like to encrypt or decrypt?\n\n", 168);
	printf("1. Encrypt\n2. Decrypt\n\n");
	scanf ("%d", &option);
	printf("\n\nAlfa's value: ");
	scanf ("%d", &alpha);
	printf("\nBeta's value: ");
	scanf ("%d", &beta);
	if (option == 1)
		encrypt (alpha, beta);										//If option 1, we encrypt the message
	else if (option == 2)
		decrypt (alpha, beta);										//If option 2, we decrypt the message
	else
		menu ();
}

void validateNumbers (int alpha, int beta)
{
	if (alpha == 1)
	{
		if (beta == ALPHABET_SIZE)
		{
			printf("Error, the text won't encrypt/decrypt correctly due to alpha's and beta's values.\n\nAlfa: %d \t Beta: %d.\n\n", alpha, beta);
			menu ();
		}
	}else if (alpha <= 0)											//If alpha's value is less than zero, we return to the menu
	{
		printf("Error, alpha's value must be between 1 and alphabet's size.\n");
		menu ();
	}
	if (beta <= 0 || beta > ALPHABET_SIZE)							//If beta's value is bigger than alphabet size, we return to the menu
	{
		printf("Error, beta's value must be between 1 and alphabet's size.\n");
		menu ();
	}
	if (gcd (alpha, ALPHABET_SIZE) != 1)							//We calculate the greatest common divisor
	{
		printf("Error, the text won't encrypt/decrypt correctly due to alpha's value.\n");
		menu ();
	}
}

int gcd (int alpha, int alphabet)									//Implementation of Euclides algorithm to obtain the greatest common divisor
{
	int temp;
	if (alpha > alphabet)
	{
		temp = alphabet;
		alphabet = alpha;
		alpha = temp;
	}
	if (alpha != 0)												//While alpha's value is bigger than zero
	{
        printf ("%d = (%d * %d) + %d\n", alphabet, alpha, alphabet / alpha, alphabet - (alphabet/alpha) * alpha);
        gcd (alpha, alphabet % alpha);
     }else
     	return alphabet;
}