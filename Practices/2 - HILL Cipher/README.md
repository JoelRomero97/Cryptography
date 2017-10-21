# HILL Cipher

Hill was the first cipher that uses algebraic methods (matrix operations) for encryption and decryption using a mxm matrix for encryption called Ek and the inverse of it for decryption called Dk.
In this case, we use images BMP applying these Modes of Operations:
- Electronic Codebook
- Cipher Block Chaining
- Cipher Feedback
- Output Feedback

# Encryption

Compile the program: gcc Images.c -o Images
Execute the program: Images.exe Original_Image.bmp Encrypted_Image.bmp
Select option 1
Select one mode of operation
If Mode of Operation is not ECB, introduce an Initialization Vector. 

Example: 9 99 11

# Decryption

Compile the program: gcc Images.c -o Images
Execute the program: Images.exe Encrypted_Image.bmp Decrypted_Image.bmp
Select option 2
Select one mode of operation
If Mode of Operation is not ECB, introduce an Initialization Vector. 

Example: 9 99 11


# Author

Joel Mauricio Romero Gamarra
