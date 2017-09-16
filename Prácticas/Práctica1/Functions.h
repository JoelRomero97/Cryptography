//Estructura para almacenar la cabecera de la imagen BMP y un apuntador a la matriz de pixeles
typedef struct BMP
{
	char type [2];															//(2 Bytes)	It contains the characters 'BM'
	int file_size;															//(4 Bytes) It contains the size of the entire file
	int reserved;															//(4 Bytes) It contains reserved bytes
	int offset;																//(4 Bytes) It contains the offset from the beginning

	//BMP Information
	int bitmap_size;														//(4 Bytes) It contains the size of the bitmap
	int width;																//(4 Bytes) Width (Horizontal pixels)
	int height;																//(4 Bytes) Height (Vertical pixels)
	short no_planes;														//(2 Bytes) Number of planes of the image
	short bits_per_pixel;													//(2 Bytes) Quantity of bits per pixel
	int compression;														//(4 Bytes) It contains 0 if it's not compressed
	int image_size;															//(4 Bytes) It contains the size of the image
	int horizontal_res;														//(4 Bytes) It contains the horizontal resolution
	int vertical_res;														//(4 Bytes) It contains the vertical resolution
	int no_colors;															//(4 Bytes) It contains the number of colors 
	int important_colors;													//(4 Bytes) It contains the number of important colors
}bmp;

typedef struct llave
{
	unsigned char Ek [3][3];
	unsigned char Dk [3][3];
}llave;

llave key =														//We initialize the two matrixes of the struct
	{
		{
			{1, 2, 3},
			{4, 5, 6},
			{11, 9, 8}
		},
		{
			{90, 167, 1},
			{74, 179, 254},
			{177, 81, 1}
		}
	};

<<<<<<< HEAD
<<<<<<< HEAD
FILE * open_file (char * original, char * encrypted, int tipo);				//Function to open each file
void read_head (FILE * original, FILE * encrypted, bmp * image);			//Function to read the head of the BMP image
<<<<<<< HEAD
void hill (FILE * original, FILE * encrypted, bmp * image, char option);	//Función para crear una imagen BMP
=======
FILE * open_file (char * original, char * encrypted, int type);
void read_head (FILE * original, FILE * encrypted, bmp * image);
int selected_mode ();
void operation_mode (FILE * original, FILE * encrypted, bmp * image, char option);
void ECB (FILE * original, FILE * encrypted, bmp * image, char option);
void CBC (FILE * original, FILE * encrypted, bmp * image, char option);
void CFB (FILE * original, FILE * encrypted, bmp * image, char option);
void OFB (FILE * original, FILE * encrypted, bmp * image, char option);
void CTR (FILE * original, FILE * encrypted, bmp * image, char option);
void hill (unsigned char * BGR, char option, unsigned char * pixel);
>>>>>>> NuevaPractica
=======
FILE * open_file (char * original, char * encrypted, int tipo);				//Function to open each file
void read_head (FILE * original, FILE * encrypted, bmp * image);			//Function to read the head of the BMP image
void hill (FILE * original, FILE * encrypted, bmp * image, char option);	//Función para crear una imagen BMP
>>>>>>> NuevaPractica
=======
void hill (unsigned char * BGR, unsigned char * pixel, char option);	//Función para crear una imagen BMP
void operation_mode (FILE * original, FILE * encrypted, bmp * image, char option);
>>>>>>> NuevaPractica
