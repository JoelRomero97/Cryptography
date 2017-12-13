import os
from Crypto.Hash import SHA
from Crypto.PublicKey import RSA

########################################################################################
####                                 Signature.py                                   ####
####                                                                                ####
####                                                                                ####
#### Implementation of digital signature using SHA - 1 and RSA for text files.		####
#### Modify: Message.txt                                                            ####
####                                                                                ####
#### Author: Romero Gamarra Joel Mauricio                                           ####
########################################################################################

def main ():
    os.system ("cls")
    
    #Menu to the user
    original = input ("\nIntroduce the name of input file: ")

    #Generation of new keys
    key = RSA.generate (2048)
    key_file = open ('Alice_Key.pem', 'w')
    key_file.write (str (key.exportKey ('PEM'), 'utf-8'))
    print ('Llave: ' + str (key.exportKey ('PEM'), 'utf-8'))
    key_file.close ()

    #Calling the selected option
    #digesto (original, encrypted)

#Electronic Codebook
def digesto (original, encrypted):

    #Creating a new Hash object (SHA 1)
    dig = SHA.new ()

    #Opening both files
    original_file = open (original, "rb")
    encrypted_file = open (encrypted, "wb")

    #Reading all the massage as a string of bytes
    data = original_file.read ()

    #Digest of the message
    dig.update (data)

    #Converting from _SHA1 to bytes
    data = bytes (dig.hexdigest (), 'utf-8')

    #Writing bytes on binary file
    encrypted_file.write (data)

    original_file.close ()
    encrypted_file.close ()

#Main function
main ()