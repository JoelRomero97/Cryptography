import os
from Crypto.Cipher import DES
from PIL import Image
import numpy as np
import matplotlib.pyplot as plt

def main ():
    os.system ("cls")
    
    #Definimos las funciones de los modos de operacion
    modos_operacion = {1: ECB, 2: CBC, 3: CFB, 4: OFB, 5: CTR}
    
    #Menu para el usuario
    original = input ("\nEnter the name of the original image: ")
    cipher = input ("\nEnter the name of the encrypted image: ")
    option = int (input ("\nSelect an option\n\n1.Enrypt\n2.Decrypt\n\n"))
    print ("\n\nWhich mode of operation do you want?\n\n")
    print ("1. Electronic Codebook (ECB)\n")
    print ("2. Cipher Block Chaining (CBC)\n")
    print ("3. Cipher Feedback (CFB)\n")
    print ("4. Output Feedback (OFB)\n")
    print ("5. Counter (CTR)\n")
    mode = int (input ("\n"))

    #Llamamos a la función seleccionada
    modos_operacion [mode] (original, cipher, option)

#Electronic Codebook
def ECB (original, ciphered, option):
    
    print ("DES in ECB mode\n")

    #Pedimos la llave de 8 bytes al usuario
    key = bytes (input ('Ingresa la llave: '), 'utf-8')
    cipher = DES.new (key, DES.MODE_ECB)

    #Abrimos los archivos correspondientes
    original_file = open (original, "rb")
    encrypted_file = open (ciphered, "wb")
    
    #Cifrar
    if option == 1:
        data = original_file.read ()
        original_file.close ()
        encrypted_file.write (data)

    #Descifrar
    elif option == 2:
        original_file = open(original,"rb")
        data = original_file.read()
        original_file.close()
        cipher.decrypt(data)
        encrypted_file.write(data)
        encrypted_file.close()
        


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