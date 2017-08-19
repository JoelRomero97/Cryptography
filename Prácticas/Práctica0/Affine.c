#include <stdio.h>
#include <stdlib.h>
#include "funciones.c"

////////////////////////////////////////////////////////////////////////////////////////
////								Affine.c 										////
////																				////
////																				////
//// Cifrador Affine, que recibe el parametro alfa y beta del usuario, mientras 	////
//// lee un archivo que contiene el mensaje a cifrar y genera uno nuevo que será el	////
//// texto cifrado, de tal forma que cuando se inicie, se puede escoger la opción	////
//// de cifrar o descifrar el mensaje.												////
//// Modificar archivo "m.txt".														////
////																				////
////																				////
//// Autor: Romero Gamarra Joel Mauricio											////
////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char const *argv[])
{
	int opcion, alfa, beta;
	system ("cls");
	printf("\n\n%cDesea cifrar o descifrar?\n\n", 168);
	printf("1. Cifrar\n2. Descifrar\n\n");
	scanf ("%d", &opcion);
	printf("\nIngrese el valor de alfa: ");
	scanf ("%d", &alfa);
	printf("Ingrese el valor de beta: ");
	scanf ("%d", &beta);
	if (opcion == 1)
		cifrar (alfa, beta);
	else if (opcion == 2)
		descifrar (alfa, beta);
	else
		printf("Opci%cn invalida.\n\n", 162);
	return 0;
}