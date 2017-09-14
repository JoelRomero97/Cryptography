//Encryption functions
void encrypt (int alpha, int beta);
char * readMessage ();
void writeCiphertext (char * ciphertext);

//Decryption functions
void decrypt (int alpha, int beta);
char * readCiphertext ();
int multiplicativeInverse (int alpha);

//Shared encryption/decryption functions
void menu ();
void validateNumbers (int alpha, int beta);
int gcd (int alpha, int alphabet);
int alg_euc_ext(int n1,int n2);