#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Functions.h"

FILE * open_file (char * original, char * encrypted, int tipo)
{
	FILE * pt1, * pt2;
	pt1 = fopen (original, "rb");
	if (pt1 == NULL)
	{
		printf("Error while opening file: '%s'.\n", original);
		exit(0);
	}
	
	//Abrimos el archivo a escribir en modo binario	
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
	printf ("\n\nType: %s\n", image -> type);

	//Size of the file
	fread (&image -> file_size, sizeof (int), 1, original);
	fwrite (&image -> file_size, sizeof (int), 1, encrypted);
	printf ("Size of the file: %d\n", image -> file_size);

	//Reserved bytes
	fread (&image -> reserved, sizeof (int), 1, original);
	fwrite (&image -> reserved, sizeof (int), 1, encrypted);
	printf ("Reserved: %d\n", image -> reserved);

	//Offset
	fread (&image -> offset, sizeof (int), 1, original);
	fwrite (&image -> offset, sizeof (int), 1, encrypted);
	printf ("Offset: %d\n", image -> offset);

	//Size of the bitmap
	fread (&image -> bitmap_size, sizeof (int), 1, original);
	fwrite (&image -> bitmap_size, sizeof (int), 1, encrypted);
	printf ("Size of bitmap: %d\n", image -> bitmap_size);

	//Width
	fread (&image -> width, sizeof (int), 1, original);
	fwrite (&image -> width, sizeof (int), 1, encrypted);
	printf ("Width: %d\n", image -> width);

	//Height
	fread (&image -> height, sizeof (int), 1, original);
	fwrite (&image -> height, sizeof (int), 1, encrypted);
	printf ("Height: %d\n", image -> height);

	//Number of planes
	fread (&image -> no_planes, sizeof (short),1, original);
	fwrite (&image -> no_planes, sizeof (short),1, encrypted);
	printf("Number of planes: %d\n", image -> no_planes);

	//Bits per pixel
	fread (&image -> bits_per_pixel, sizeof (short),1, original);
	fwrite (&image -> bits_per_pixel, sizeof (short),1, encrypted);
	printf ("Bits per pixel: %d\n", image -> bits_per_pixel);

	//Type of compression (must be 0)
	fread (&image -> compression, sizeof (int), 1, original);
	fwrite (&image -> compression, sizeof (int), 1, encrypted);
	printf ("compression: %d\n", image -> compression);

	//Size of the image
	fread (&image -> image_size, sizeof (int), 1, original);
	fwrite (&image -> image_size, sizeof (int), 1, encrypted);
	printf ("Size of image: %d\n", image -> image_size);

	//Horizontal resolution
	fread (&image -> horizontal_res, sizeof (int), 1, original);
	fwrite (&image -> horizontal_res, sizeof (int), 1, encrypted);
	printf ("Horizontal resolution: %d\n", image -> horizontal_res);

	//Vertical resolution
	fread (&image -> vertical_res, sizeof (int), 1, original);
	fwrite (&image -> vertical_res, sizeof (int), 1, encrypted);
	printf ("Vertical resolution: %d\n", image -> vertical_res);

	//Number of colors
	fread (&image -> no_colors, sizeof (int), 1, original);
	fwrite (&image -> no_colors, sizeof (int), 1, encrypted);
	printf ("Number of colors: %d\n", image -> no_colors);

	//Number of important colors
	fread (&image -> important_colors, sizeof (int), 1, original);
	fwrite (&image -> important_colors, sizeof (int), 1, encrypted);
	printf ("Number of important colors: %d\n", image -> important_colors);

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

void encrypt_image (FILE * original, FILE * encrypted, bmp * image)
{
	int i, j;
	unsigned char key [3][3] = 
	{
		{126, 157, 27},
		{206, 225, 202},
		{171, 139, 27}
	};
	unsigned char red, blue, green, pixel [3];
	for (i = 0; i < (image -> image_size); i ++)
	{
		fread (&red, sizeof (char), 1, original);
		fread (&blue, sizeof (char), 1, original);
		fread (&green, sizeof (char), 1, original);
		for (j = 0; j < 3; j ++)
		{
			pixel [j] = ((red * key [0][j]) + (green * key [1][j]) + (blue * key [2][j]));
		}
		fwrite (&pixel, sizeof (char), 3, encrypted);
	}
	
	//PRUEBA ESCRIBIENDO TODO TAL CUAL
	/*unsigned char x;
	for (i = 0; i < (image -> image_size); i++)
	{
		fread (&x, sizeof (char), 1, original);
		fwrite (&x, sizeof (char), 1, encrypted);
	}*/
	//We close each file
	fclose (original);
	fclose (encrypted);
}
