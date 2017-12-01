#include <stdio.h>
#include <stdlib.h>
#include <string.h>

////////////////////////////////////////////////////////////////////////////////////////
////								Permutation.c 									////
////																				////
////																				////
//// This is the first part of Data Encryption Standard (DES) cipher, Initial 		////
//// Permutation, or IP, that mixes bit by bit the message (8 characters). In this 	////
//// case, it must be a 4 - character message because this positions are not the 	////
//// ones that DES uses.															////
////																				////
////																				////
//// Autor: Romero Gamarra Joel Mauricio											////
////////////////////////////////////////////////////////////////////////////////////////

int main (int argc, char const * argv [])
{
	unsigned char mensaje [4], revuelto [4], nuevo [4], i;
	char resultado, residuo;
	unsigned char p [32] = {1, 26, 15, 14, 13, 22, 7, 8,
					29, 2, 16, 31, 21, 6, 23, 9,
					28, 17, 3, 20, 5, 24, 12, 10,
					27, 18, 19, 4, 0, 25, 30, 11};
	unsigned char p_inversa [32];
	memset (revuelto, '0', 4);
	memset (nuevo, '0', 4);
	memset (p_inversa, '0', 32);
	system ("cls");
	printf ("\n\nEnter a 4-character string: ");
	scanf ("%s", mensaje);
	printf ("\n");
	for (i = 0; i < 32; i ++)
	{
		resultado = (p [i] / 8);
		residuo = (p [i] % 8);
		p_inversa [(p [i])] = i;
		if ((mensaje [resultado]) & (1 << residuo))
		{
			resultado = (i / 8);
			residuo = (i % 8);
			revuelto [resultado] = ((revuelto [resultado]) | (1 << residuo));
		}
	}
	printf ("\n\nP");
	for (i = 0; i < 32; i ++)
	{
		if (i % 8 == 0)
			printf ("\n");
		printf ("%d ", p [i]);
	}
	printf ("\n\nP^-1");
	for (i = 0; i < 32; i ++)
	{
		if (i % 8 == 0)
			printf ("\n");
		printf ("%d ", p_inversa [i]);
	}
	for (i = 0; i < 32; i ++)
	{
		resultado = (p_inversa [i] / 8);
		residuo = (p_inversa [i] % 8);
		if ((revuelto [resultado]) & (1 << residuo))
		{
			resultado = (i / 8);
			residuo = (i % 8);
			nuevo [resultado] = ((nuevo [resultado]) | (1 << residuo));
		}
	}
	printf ("\n\nOriginal:\t\t\tP:\t\t\tP^-1:\n");
	for (i = 0; i < 4; i ++)
		printf ("\n0x%x\t\t\t\t0x%x\t\t\t0x%x", mensaje [i], revuelto [i], nuevo [i]);
	return 0;
}
