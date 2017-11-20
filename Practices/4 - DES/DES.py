import os
from Crypto.Cipher import DES
from PIL import Image
import numpy as np
import matplotlib.pyplot as plt

def main():
    os.system ("cls")
    
    #Definimos las funciones de los modos de operacion
    modos_operacion = {1: des_ecb, 2: des_cbc, 3: des_cfb, 4: des_ofb, 5: des_ctr}
    
    #Menu para el usuario
    original = input ("\nEnter the name of the original image: ")
    cipher = input ("\nEnter the name of the encrypted image: ")
    option = int (input ("\nSelect an option\n\n1.Enrypt\n2.Decrypt\n\n"))
    mode = int (input ("\n\nWhich mode of operation do you want?\n\n1.ECB\n2.CBC\n3.CFB\n4.OFB\n5.CTR\n\n"))

    #Llamamos a la función seleccionada
    modos_operacion [mode] (original, cipher, option)

def des_ecb (original,ciphered,option):
    print ("DES in ECB mode\n")
    cipher = DES.new ('12345678', DES.MODE_ECB)
    
    #Cifrar
    if option == 1:
        file = open (original, "rb")
        data = file.read ()
        file.close ()
        ciphered = open (ciphered, "wb")
        ciphered.write (data)

    #Descifrar
    elif option == 2:
        file = open(original,"rb")
        data = file.read()
        file.close()
        cipher.decrypt(data)
        ciphered = open(ciphered,"wb")
        ciphered.write(data)
        ciphered.close()
        


def des_cbc(original,ciphered,option):
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
        

def des_cfb(original,ciphered,option):
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


def des_ofb(original,ciphered,option):
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

def des_ctr(original,ciphered,option):
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