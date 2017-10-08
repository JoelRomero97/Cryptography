#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Functions.h"

int i, j;														//Global variables for loops
unsigned char BGR [3], pixel [3], x;							//Arrays for reading and writing bmp images

FILE * open_file (char * original, char * encrypted, int tipo)
{
	FILE * pt1, * pt2;
	//We open the file in binary mode to read
	pt1 = fopen (original, "rb");
	if (pt1 == NULL)
	{
		printf("Error while opening file: '%s'.\n", original);
		exit(0);
	}
	
	//We open the file in binary mode to write
	pt2 = fopen (encrypted, "wb");
	if (pt2 == NULL)
	{
		printf("Error while creating file: '%s'.\n", encrypted);
		exit(1);
	}
	if (tipo == 1)
	{
		printf("File '%s' opened correctly.\n", original);
		return pt1;
	}
	else
	{
		printf("File '%s' created correctly.\n", encrypted);
		return pt2;
	}
}

void read_head (FILE * original, FILE * encrypted, bmp * image)
{
	//Type (must be 'BM')
	fread (&image -> type, sizeof (char), 2, original);
	fwrite (&image -> type, sizeof (char), 2, encrypted);

	//Size of the file
	fread (&image -> file_size, sizeof (int), 1, original);
	fwrite (&image -> file_size, sizeof (int), 1, encrypted);

	//Reserved bytes
	fread (&image -> reserved, sizeof (int), 1, original);
	fwrite (&image -> reserved, sizeof (int), 1, encrypted);

	//Offset
	fread (&image -> offset, sizeof (int), 1, original);
	fwrite (&image -> offset, sizeof (int), 1, encrypted);

	//Size of the bitmap
	fread (&image -> bitmap_size, sizeof (int), 1, original);
	fwrite (&image -> bitmap_size, sizeof (int), 1, encrypted);

	//Width
	fread (&image -> width, sizeof (int), 1, original);
	fwrite (&image -> width, sizeof (int), 1, encrypted);

	//Height
	fread (&image -> height, sizeof (int), 1, original);
	fwrite (&image -> height, sizeof (int), 1, encrypted);

	//Number of planes
	fread (&image -> no_planes, sizeof (short),1, original);
	fwrite (&image -> no_planes, sizeof (short),1, encrypted);

	//Bits per pixel
	fread (&image -> bits_per_pixel, sizeof (short),1, original);
	fwrite (&image -> bits_per_pixel, sizeof (short),1, encrypted);

	//Type of compression (must be 0)
	fread (&image -> compression, sizeof (int), 1, original);
	fwrite (&image -> compression, sizeof (int), 1, encrypted);

	//Size of the image
	fread (&image -> image_size, sizeof (int), 1, original);
	fwrite (&image -> image_size, sizeof (int), 1, encrypted);

	//Horizontal resolution
	fread (&image -> horizontal_res, sizeof (int), 1, original);
	fwrite (&image -> horizontal_res, sizeof (int), 1, encrypted);

	//Vertical resolution
	fread (&image -> vertical_res, sizeof (int), 1, original);
	fwrite (&image -> vertical_res, sizeof (int), 1, encrypted);

	//Number of colors
	fread (&image -> no_colors, sizeof (int), 1, original);
	fwrite (&image -> no_colors, sizeof (int), 1, encrypted);

	//Number of important colors
	fread (&image -> important_colors, sizeof (int), 1, original);
	fwrite (&image -> important_colors, sizeof (int), 1, encrypted);

	//We check if the selected file is a bitmap
	if (image -> type [0] != 'B' || image -> type [1] != 'M')	
	{
		printf ("The image must be a bitmap.\n"); 
		exit (1);
	}
	if (image -> bits_per_pixel != 24) 
	{
		printf ("The image must be 24-bits.\n"); 
		exit (1);
	}
}

void operation_mode (FILE * original, FILE * encrypted, bmp * image, char option)
{
	int selected_mode = 3;
	printf("\n\n%cWhich mode of operation do you want to use?\n\n", 168);
	printf("1. Electronic Codebook (ECB).\n");
	printf("2. Cipher Block Chaining (CBC)\n");
	printf("3. Cipher Feedback (CFB)\n");
	printf("4. Output Feedback (OFB)\n");
	printf("5. Counter (CTR)\n\n");
	scanf ("%d", &selected_mode);
	system ("cls");
	print_head (image);
	if (selected_mode == 1)
		ECB (original, encrypted, image, option);
	else if (selected_mode == 2)
		CBC (original, encrypted, image, option);
	else if (selected_mode == 3)
		CFB (original, encrypted, image, option);
	else if (selected_mode == 4)
		OFB (original, encrypted, image, option);
	else
		CTR (original, encrypted, image, option);
}

void print_head (bmp * image)
{
	printf ("\n\nType: %s\n", image -> type);
	printf ("Size of the file: %d\n", image -> file_size);
	printf ("Reserved: %d\n", image -> reserved);
	printf ("Offset: %d\n", image -> offset);
	printf ("Size of bitmap: %d\n", image -> bitmap_size);
	printf ("Width: %d\n", image -> width);
	printf ("Height: %d\n", image -> height);
	printf ("Number of planes: %d\n", image -> no_planes);
	printf ("Bits per pixel: %d\n", image -> bits_per_pixel);
	printf ("compression: %d\n", image -> compression);
	printf ("Size of image: %d\n", image -> image_size);
	printf ("Horizontal resolution: %d\n", image -> horizontal_res);
	printf ("Vertical resolution: %d\n", image -> vertical_res);
	printf ("Number of colors: %d\n", image -> no_colors);
	printf ("Number of important colors: %d\n", image -> important_colors);
}

char * message (char option)
{
	if (option == 'e')
		return "encrypted";
	else
		return "decrypted";
}

void ECB (FILE * original, FILE * encrypted, bmp * image, char option)
{
	for (i = 0; i < (image -> image_size); i ++)
	{
		fread (&BGR, sizeof (char), 3, original);
		/*
		//DESCOMENTAR ESTA PARTE PARA QUE QUEDE EXACTAMENTE IGUAL QUE EN EL CUADERNO YA QUE LOS COLORES DE PIXELES LLEGAN B,G,R Y NO R,G,B
		x = BGR [0];
		BGR [0] = BGR [2];
		BGR [2] = x;
		*/
		hill ((unsigned char * ) BGR, (unsigned char * ) pixel, option);
		fwrite (&pixel, sizeof (char), 3, encrypted);
		memset (pixel, 0, 3);
	}
	printf ("\n\n\nThe image was %s correctly.\n\n", message (option));
}

void CBC (FILE * original, FILE * encrypted, bmp * image, char option)
{
	unsigned char aux [3];
	printf ("\n\nIntroduce the initialization vector separated by spaces:\t");
	scanf ("%u %u %u", &pixel [0], &pixel [1], &pixel [2]);
	if (option == 'e')
	{
		for (i = 0; i < (image -> image_size); i ++)
		{
			fread (&BGR, sizeof (char), 3, original);
			/*
			//DESCOMENTAR ESTA PARTE PARA QUE QUEDE EXACTAMENTE IGUAL QUE EN EL CUADERNO YA QUE LOS COLORES DE PIXELES LLEGAN B,G,R Y NO R,G,B
			x = BGR [0];
			BGR [0] = BGR [2];
			BGR [2] = x;
			*/
			for (j = 0; j < 3; j ++)
				BGR [j] = (pixel [j] ^ BGR [j]);								//We realize XOR between pixel and BGR from Image
			hill ((unsigned char * ) BGR, (unsigned char * ) pixel, option);
			fwrite (&pixel, sizeof (char), 3, encrypted);
		}
	}else
	{
		for (i = 0; i < (image -> image_size); i ++)
		{
			fread (&BGR, sizeof (char), 3, original);
			/*
			//DESCOMENTAR ESTA PARTE PARA QUE QUEDE EXACTAMENTE IGUAL QUE EN EL CUADERNO YA QUE LOS COLORES DE PIXELES LLEGAN B,G,R Y NO R,G,B
			x = BGR [0];
			BGR [0] = BGR [2];
			BGR [2] = x;
			*/
			hill ((unsigned char * ) BGR, (unsigned char * ) aux, option);
			for (j = 0; j < 3; j ++)
				pixel [j] = (pixel [j] ^ aux [j]);								//We realize XOR between pixel and BGR from Image
			fwrite (&pixel, sizeof (char), 3, encrypted);
			for (j = 0; j < 3; j ++)
				pixel [j] = BGR [j];
		}
	}
	printf ("\n\n\nThe image was %s correctly.\n\n", message (option));
}

void CFB (FILE * original, FILE * encrypted, bmp * image, char option)
{
	unsigned char aux [3];
	if (option == 'e')
	{
		printf ("\n\nIntroduce the initialization vector separated by spaces:\t");
		scanf ("%u %u %u", &pixel [0], &pixel [1], &pixel [2]);
		for (i = 0; i < (image -> image_size); i ++)
		{
			fread (&BGR, sizeof (char), 3, original);
			/*
			//DESCOMENTAR ESTA PARTE PARA QUE QUEDE EXACTAMENTE IGUAL QUE EN EL CUADERNO YA QUE LOS COLORES DE PIXELES LLEGAN B,G,R Y NO R,G,B
			x = BGR [0];
			BGR [0] = BGR [2];
			BGR [2] = x;
			*/
			hill ((unsigned char * ) pixel, (unsigned char * ) aux, option);
			for (j = 0; j < 3; j ++)
				pixel [j] = (aux [j] ^ BGR [j]);								//We realize XOR between pixel and BGR from Image
			fwrite (&pixel, sizeof (char), 3, encrypted);
		}
	}else
	{
		printf ("\n\nIntroduce the initialization vector separated by spaces:\t");
		scanf ("%u %u %u", &BGR [0], &BGR [1], &BGR [2]);
		for (i = 0; i < (image -> image_size); i ++)
		{
			hill ((unsigned char * ) BGR, (unsigned char * ) aux, 'e');
			fread (&BGR, sizeof (char), 3, original);
			/*
			//DESCOMENTAR ESTA PARTE PARA QUE QUEDE EXACTAMENTE IGUAL QUE EN EL CUADERNO YA QUE LOS COLORES DE PIXELES LLEGAN B,G,R Y NO R,G,B
			x = BGR [0];
			BGR [0] = BGR [2];
			BGR [2] = x;
			*/
			for (j = 0; j < 3; j ++)
				pixel [j] = (aux [j] ^ BGR [j]);								//We realize XOR between pixel and BGR from Image
			fwrite (&pixel, sizeof (char), 3, encrypted);
		}
	}
	printf ("\n\n\nThe image was %s correctly.\n\n", message (option));
}

void OFB (FILE * original, FILE * encrypted, bmp * image, char option)
{
	unsigned char aux [3], aux2 [3];
	printf ("\n\nIntroduce the initialization vector separated by spaces:\t");
	scanf ("%u %u %u", &pixel [0], &pixel [1], &pixel [2]);
	hill ((unsigned char * ) pixel, (unsigned char * ) aux, 'e');
	for (i = 0; i < 3; i ++)
		aux2 [i] = aux [i];
	for (i = 0; i < (image -> image_size); i ++)
	{
		fread (&BGR, sizeof (char), 3, original);
		/*
		//DESCOMENTAR ESTA PARTE PARA QUE QUEDE EXACTAMENTE IGUAL QUE EN EL CUADERNO YA QUE LOS COLORES DE PIXELES LLEGAN B,G,R Y NO R,G,B
		x = BGR [0];
		BGR [0] = BGR [2];
		BGR [2] = x;
		*/
		for (j = 0; j < 3; j ++)
			pixel [j] = (aux2 [j] ^ BGR [j]);								//We realize XOR between pixel and BGR from Image
		fwrite (&pixel, sizeof (char), 3, encrypted);
		hill ((unsigned char * ) aux, (unsigned char * ) aux2, 'e');
	}
	printf ("\n\n\nThe image was %s correctly.\n\n", message (option));
}

void CTR (FILE * original, FILE * encrypted, bmp * image, char option)
{
	//
}

void hill (unsigned char * BGR, unsigned char * pixel, char option)
{
	int i;
	for (i = 0; i < 3; i ++)
	{
		if (option == 'd')				//D from decryption
			pixel [i] = ((BGR [0] * key.Dk [0][i]) + (BGR [1] * key.Dk [1][i]) + (BGR [2] * key.Dk [2][i])) % 256;
		else
			pixel [i] = ((BGR [0] * key.Ek [0][i]) + (BGR [1] * key.Ek [1][i]) + (BGR [2] * key.Ek [2][i])) % 256;
	}
	return;
}
