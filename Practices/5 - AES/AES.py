import os
from Crypto.Cipher import AES
from Crypto.Util import Counter

########################################################################################
####                                    AES.py                                      ####
####                                                                                ####
####                                                                                ####
#### Implementation of Advanced Encryption Standard (AES) for BMP images with 5     ####
#### different modes of operation.                                                  ####
#### Restrictions:                                                                  ####
#### - Image.bmp size must be multiple of 16 (128 bits)                             ####
####                                                                                ####
#### Author: Romero Gamarra Joel Mauricio                                           ####
########################################################################################

def main ():
    os.system ("cls")
    
    #We define the functions (modes of operation) inside a dictionary
    modos_operacion = {1: ECB, 2: CBC, 3: CFB, 4: OFB, 5: CTR}
    
    #Menu to the user
    original = input ("\nEnter the name of the original image: ")
    cipher = input ("\nEnter the name of the encrypted image: ")
    option = int (input ("\nSelect an option\n\n1.Enrypt\n2.Decrypt\n\n"))
    print ("\n\nWhich mode of operation do you want?\n\n")
    print ("1. Electronic Codebook (ECB)")
    print ("2. Cipher Block Chaining (CBC)")
    print ("3. Cipher Feedback (CFB)")
    print ("4. Output Feedback (OFB)")
    print ("5. Counter (CTR)")
    mode = int (input ("\n"))

    #Calling the selected mode of operation
    modos_operacion [mode] (original, cipher, option)


#Electronic Codebook
def ECB (original, ciphered, option):

    #Asking for the key to the user (16 bytes)
    key = bytes (input ('Introduce the key: '), 'utf-8')

    #Creating a new AES cipher
    cipher = AES.new (key, AES.MODE_ECB)

    #Opening both files
    original_file = open (original, "rb")
    encrypted_file = open (ciphered, "wb")

    #We copy the entire head of the image
    data = original_file.read (54)
    encrypted_file.write (data)

    #Obtaining the size of the image
    original_file.seek (34)
    size = int.from_bytes (original_file.read (4), byteorder = 'little')

    #We move to the start of the real image to encrypt it
    original_file.seek (54)

    i = 0
    
    #Encrypt
    if option == 1:
        while (i < size):
            #Reading 16 bytes to encrypt it using AES cipher
            pixels = original_file.read (16)

            #Encrypting 16 bytes readed
            encrypted_pixels = cipher.encrypt (pixels)

            #Writing encrypted pixels
            encrypted_file.write (encrypted_pixels)

            #Updating the counter
            i = i + 16
        print ("\n\n", original, "was encrypted correctly using Electronic Codebook Mode")

    #Decrypt
    elif option == 2:
        while (i < size):
            #Reading 16 bytes to decrypt it using AES cipher
            pixels = original_file.read (16)

            #Encrypting 16 bytes readed
            encrypted_pixels = cipher.decrypt (pixels)

            #Writing decrypted pixels
            encrypted_file.write (encrypted_pixels)

            #Updating the counter
            i = i + 16
        print ("\n\n", original, "was decrypted correctly using Electronic Codebook Mode")

    original_file.close ()
    encrypted_file.close ()


#Cipher Block Chaining
def CBC (original, ciphered, option):
    
    #Asking for the key to the user (16 bytes)
    key = bytes (input ('Introduce the key: '), 'utf-8')

    #Asking for the initialization vector to the user (16 bytes)
    IV = bytes (input ('Introduce the initialization vector: '), 'utf-8')

    #Creating a new AES cipher
    cipher = AES.new (key, AES.MODE_CBC, IV)

    #Opening both files
    original_file = open (original, "rb")
    encrypted_file = open (ciphered, "wb")

    #We copy the entire head of the image
    data = original_file.read (54)
    encrypted_file.write (data)

    #Obtaining the size of the image
    original_file.seek (34)
    size = int.from_bytes (original_file.read (4), byteorder = 'little')

    #We move to the start of the real image to encrypt it
    original_file.seek (54)
    
    i = 0

    #Encrypt
    if option == 1:
        while (i < size):
            #Reading 16 bytes to encrypt it using AES cipher
            pixels = original_file.read (16)

            #Encrypting 16 bytes readed
            encrypted_pixels = cipher.encrypt (pixels)

            #Writing encrypted pixels
            encrypted_file.write (encrypted_pixels)

            #Updating the counter
            i = i + 16
        print ("\n\n", original, "was encrypted correctly using Cipher Block Chaining Mode")

    #Decrypt
    elif option == 2:
        while (i < size):
            #Reading 16 bytes to decrypt it using AES cipher
            pixels = original_file.read (16)

            #Encrypting 16 bytes readed
            encrypted_pixels = cipher.decrypt (pixels)

            #Writing decrypted pixels
            encrypted_file.write (encrypted_pixels)

            #Updating the counter
            i = i + 16
        print ("\n\n", original, "was decrypted correctly using Cipher Block Chaining Mode")

    original_file.close ()
    encrypted_file.close ()


#Cipher Feedback
def CFB (original, ciphered, option):
    
    #Asking for the key to the user (16 bytes)
    key = bytes (input ('Introduce the key: '), 'utf-8')

    #Asking for the initialization vector to the user (16 bytes)
    IV = bytes (input ('Introduce the initialization vector: '), 'utf-8')

    #Creating a new AES cipher
    cipher = AES.new (key, AES.MODE_CFB, IV)

    #Opening both files
    original_file = open (original, "rb")
    encrypted_file = open (ciphered, "wb")

    #We copy the entire head of the image
    data = original_file.read (54)
    encrypted_file.write (data)

    #Obtaining the size of the image
    original_file.seek (34)
    size = int.from_bytes (original_file.read (4), byteorder = 'little')

    #We move to the start of the real image to encrypt it
    original_file.seek (54)
    
    i = 0

    #Encrypt
    if option == 1:
        while (i < size):
            #Reading 16 bytes to encrypt it using AES cipher
            pixels = original_file.read (16)

            #Encrypting 16 bytes readed
            encrypted_pixels = cipher.encrypt (pixels)

            #Writing encrypted pixels
            encrypted_file.write (encrypted_pixels)

            #Updating the counter
            i = i + 16
        print ("\n\n", original, "was encrypted correctly using Cipher Feedback Mode")

    #Decrypt
    elif option == 2:
        while (i < size):
            #Reading 16 bytes to decrypt it using AES cipher
            pixels = original_file.read (16)

            #Encrypting 16 bytes readed
            encrypted_pixels = cipher.decrypt (pixels)

            #Writing decrypted pixels
            encrypted_file.write (encrypted_pixels)

            #Updating the counter
            i = i + 16
        print ("\n\n", original, "was decrypted correctly using Cipher Feedback Mode")

    original_file.close ()
    encrypted_file.close ()


#Output Feedback
def OFB(original,ciphered,option):

    #Asking for the key to the user (16 bytes)
    key = bytes (input ('Introduce the key: '), 'utf-8')

    #Asking for the initialization vector to the user (16 bytes)
    IV = bytes (input ('Introduce the initialization vector: '), 'utf-8')

    #Creating a new AES cipher
    cipher = AES.new (key, AES.MODE_OFB, IV)

    #Opening both files
    original_file = open (original, "rb")
    encrypted_file = open (ciphered, "wb")

    #We copy the entire head of the image
    data = original_file.read (54)
    encrypted_file.write (data)

    #Obtaining the size of the image
    original_file.seek (34)
    size = int.from_bytes (original_file.read (4), byteorder = 'little')

    #We move to the start of the real image to encrypt it
    original_file.seek (54)
    
    i = 0

    #Encrypt
    if option == 1:
        while (i < size):
            #Reading 16 bytes to encrypt it using AES cipher
            pixels = original_file.read (16)

            #Encrypting 16 bytes readed
            encrypted_pixels = cipher.encrypt (pixels)

            #Writing encrypted pixels
            encrypted_file.write (encrypted_pixels)

            #Updating the counter
            i = i + 16
        print ("\n\n", original, "was encrypted correctly using Output Feedback Mode")

    #Decrypt
    elif option == 2:
        while (i < size):
            #Reading 16 bytes to decrypt it using AES cipher
            pixels = original_file.read (16)

            #Encrypting 16 bytes readed
            encrypted_pixels = cipher.decrypt (pixels)

            #Writing decrypted pixels
            encrypted_file.write (encrypted_pixels)

            #Updating the counter
            i = i + 16
        print ("\n\n", original, "was decrypted correctly using Output Feedback Mode")

    original_file.close ()
    encrypted_file.close ()


#Counter
def CTR(original,ciphered,option):

    #Asking for the key to the user (16 bytes)
    key = bytes (input ('Introduce the key: '), 'utf-8')

    #Creating a new AES cipher
    ctr = Counter.new (128)
    cipher = AES.new (key, AES.MODE_CTR, counter = ctr)

    #Opening both files
    original_file = open (original, "rb")
    encrypted_file = open (ciphered, "wb")

    #We copy the entire head of the image
    data = original_file.read (54)
    encrypted_file.write (data)

    #Obtaining the size of the image
    original_file.seek (34)
    size = int.from_bytes (original_file.read (4), byteorder = 'little')

    #We move to the start of the real image to encrypt it
    original_file.seek (54)

    i = 0
    
    #Encrypt
    if option == 1:
        while (i < size):
            #Reading 16 bytes to encrypt it using AES cipher
            pixels = original_file.read (16)

            #Encrypting 16 bytes readed
            encrypted_pixels = cipher.encrypt (pixels)

            #Writing encrypted pixels
            encrypted_file.write (encrypted_pixels)

            #Updating the counter
            i = i + 16
        print ("\n\n", original, "was encrypted correctly using Counter Mode")

    #Decrypt
    elif option == 2:
        while (i < size):
            #Reading 16 bytes to decrypt it using AES cipher
            pixels = original_file.read (16)

            #Encrypting 16 bytes readed
            encrypted_pixels = cipher.decrypt (pixels)

            #Writing decrypted pixels
            encrypted_file.write (encrypted_pixels)

            #Updating the counter
            i = i + 16
        print ("\n\n", original, "was decrypted correctly using Counter Mode")

    original_file.close ()
    encrypted_file.close ()

#Main function
main ()