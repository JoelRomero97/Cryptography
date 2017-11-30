import os
from Crypto.Hash import SHA

def main ():
    os.system ("cls")
    
    #Menu to the user
    original = input ("\nIntroduce the name of input file (original): ")
    encrypted = input ("\nIntroduce the name of output file (encrypted): ")

    #Calling the selected option
    digesto (original, encrypted)

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