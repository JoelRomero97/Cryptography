#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char const * argv [])
{
	char mensaje [4], revuelto [4], i, j;
	int resultado, residuo;
	char p [32] = {1, 26, 15, 14, 13, 22, 7, 8, 29, 2, 16, 31, 21, 6, 23, 9, 28, 17, 3, 20, 5, 24, 12, 10, 27, 18, 19, 4, 0, 25, 30, 11};
	char p_inversa [32];
	memset (revuelto, '0', 4);
	memset (p_inversa, '0', 32);
	system ("cls");
	printf ("\n\nIngresa una cadena de 4 caracteres: ");
	scanf ("%s", mensaje);
	for (i = 0; i < 32; i ++)
	{
		resultado = (p [i] / 8);
		residuo = (p [i] % 8);
		p_inversa [(p [i])] = i;
		if (mensaje [resultado] & (char)(pow (2, residuo)))
			revuelto [resultado] = (revuelto [resultado] | (1 << residuo));
	}
	printf ("\n\nP");
	for (i = 0, j = 0; i < 32; i ++, j ++)
	{
		if (j % 8 == 0)
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
	printf ("\n\nOriginal:\t\t\tP:\n");
	for (i = 0; i < 4; i ++)
		printf ("\n0x%x\t\t\t\t0x%x", mensaje [i], revuelto [i]);
	printf ("\n\n\nP inversa:\n\n");
	for (i = 0; i < 32; i ++)
	{
		resultado = (p_inversa [i] / 8);
		residuo = (p_inversa [i] % 8);
		if (revuelto [resultado] & (char)(pow (2, residuo)))
			mensaje [resultado] = (mensaje [resultado] | (1 << residuo));
	}
	printf ("\n\nNueva Palabra:\n");
	for (i = 0; i < 4; i ++)
		printf ("\n0x%x", mensaje [i]);
	return 0;
}
