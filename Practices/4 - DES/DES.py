import os
from Crypto.Cipher import DES

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

    #Asking for the key to the user (8 bytes)
    key = bytes (input ('Introduce the key: '), 'utf-8')

    #Creating a new DES cipher
    cipher = DES.new (key, DES.MODE_ECB)

    #Opening both files
    original_file = open (original, "rb")
    encrypted_file = open (ciphered, "wb")

    #We copy the entire head of the image
    data = original_file.read (54)
    encrypted_file.write (data)

    #Obtaining the size of the image
    original_file.seek (34)
    size = int.from_bytes (original_file.read (4), byteorder = 'little')
    print ("\nTamaño de imagen: ", size)

    #We move to the start of the real image to encrypt it
    original_file.seek (54)

    #Loop for reading the image
    i = 0
    
    #Cifrar
    if option == 1:
        while (i < size):
            #Reading 8 bytes to encrypt it using DES cipher
            pixels = original_file.read (8)

            #Encrypting 8 bytes readed
            encrypted_pixels = cipher.encrypt (pixels)

            #Writing encrypted pixels
            encrypted_file.write (encrypted_pixels)

            #Updating the counter
            i = i + 8

    #Descifrar
    elif option == 2:
        while (i < size):
            #Reading 8 bytes to decrypt it using DES cipher
            pixels = original_file.read (8)

            #Encrypting 8 bytes readed
            encrypted_pixels = cipher.decrypt (pixels)

            #Writing decrypted pixels
            encrypted_file.write (encrypted_pixels)

            #Updating the counter
            i = i + 8

    original_file.close ()
    encrypted_file.close ()
        


def CBC(original,ciphered,option):
    print ("DES in CBC mode\n")
    IV = "9999"
    cipher = DES.new('12345678',DES.MODE_CBC,IV)

    #Cifrar
    if option == 1:
        file = open(original,"rb")
        data = file.read()
        file.close()
        cipher.encrypt(data)
        ciphered = open(ciphered,"wb")
        ciphered.write(data)
        ciphered.close()

    #Descifrar
    elif option == 2:
        file = open(original,"rb")
        data = file.read()
        file.close()
        cipher.decrypt(data)
        ciphered = open(ciphered,"wb")
        ciphered.write(data)
        ciphered.close()
        

def CFB(original,ciphered,option):
    print ("DES in CBF mode")
    IV = "9999"
    cipher = DES.new('12345678',DES.MODE_CFB,IV)
    if option == 1:
        file = open(original,"rb")
        data = file.read()
        file.close()
        cipher.encrypt(data)
        ciphered = open(ciphered,"wb")
        ciphered.write(data)
        ciphered.close()
    elif option == 2:
        file = open(original,"rb")
        data = file.read()
        file.close()
        cipher.decrypt(data)
        ciphered = open(ciphered,"wb")
        ciphered.write(data)
        ciphered.close()


def OFB(original,ciphered,option):
    print ("DES in OFB mode")
    IV = "9999"
    cipher = DES.new('12345678',DES.MODE_OFB,IV)
    if option == 1:
        file = open(original,"rb")
        data = file.read()
        file.close()
        cipher.encrypt(data)
        ciphered = open(ciphered,"wb")
        ciphered.write(data)
        ciphered.close()
    elif option == 2:
        file = open(original,"rb")
        data = file.read()
        file.close()
        cipher.decrypt(data)
        ciphered = open(ciphered,"wb")
        ciphered.write(data)
        ciphered.close()

def CTR(original,ciphered,option):
    print ("DES in CTR mode")
    cipher = DES.new('12345678',DES.MODE_CTR)
    if option == 1:
        file = open(original,"rb")
        data = file.read()
        file.close()
        cipher.encrypt(data)
        ciphered = open(ciphered,"wb")
        ciphered.write(data)
        ciphered.close()
    elif option == 2:
        file = open(original,"rb")
        data = file.read()
        file.close()
        cipher.decrypt(data)
        ciphered = open(ciphered,"wb")
        ciphered.write(data)
        ciphered.close()

main()