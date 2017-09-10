//Estructura para almacenar la cabecera de la imagen BMP y un apuntador a la matriz de pixeles
typedef struct BMP
{
	char type [2];														//(2 Bytes)	It contains the characters 'BM'
	int file_size;														//(4 Bytes) It contains the size of the entire file
	int reserved;														//(4 Bytes) It contains reserved bytes
	int offset;															//(4 Bytes) It contains the offset from the beginning

	//BMP Information
	int bitmap_size;													//(4 Bytes) It contains the size of the bitmap
	int width;															//(4 Bytes) Width (Horizontal pixels)
	int height;															//(4 Bytes) Height (Vertical pixels)
	short no_planes;													//(2 Bytes) Number of planes of the image
	short bits_per_pixel;												//(2 Bytes) Quantity of bits per pixel
	int compression;													//(4 Bytes) It contains 0 if it's not compressed
	int image_size;														//(4 Bytes) It contains the size of the image
	int horizontal_res;													//(4 Bytes) It contains the horizontal resolution
	int vertical_res;													//(4 Bytes) It contains the vertical resolution
	int no_colors;														//(4 Bytes) It contains the number of colors 
	int important_colors;												//(4 Bytes) It contains the number of important colors
}bmp;

FILE * open_file (char * original, char * encrypted, int tipo);			//Function to open each file
void read_head (FILE * original, FILE * encrypted, bmp * image);		//Function to read the head of the BMP image
void encrypt_image (FILE * original, FILE * encrypted, bmp * image);	//Función para crear una imagen BMP
