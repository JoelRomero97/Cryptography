import os
import os.path as path
from Crypto.Hash import SHA
from Crypto.PublicKey import RSA
from Crypto.Cipher import PKCS1_OAEP

def generate_keys (transmitter, receiver):
	private_key = RSA.generate (2048)
	public_key = private_key.publickey ()
	name = transmitter + "_pvt.pem"
	file = open (name, "w")
	file.write (str (private_key.exportKey ('PEM'), 'utf-8'))
	file.close ()
	name = transmitter + "_pub.pem"
	file = open (name, "w")
	file.write (str (public_key.exportKey ('PEM'), 'utf-8'))
	file.close ()
	private_key = RSA.generate (2048)
	public_key = private_key.publickey ()
	name = receiver + "_pvt.pem"
	file = open (name, "w")
	file.write (str (private_key.exportKey ('PEM'), 'utf-8'))
	file.close ()
	name = receiver + "_pub.pem"
	file = open (name, "w")
	file.write (str (public_key.exportKey ('PEM'), 'utf-8'))
	file.close ()

def obtain_private_key (user):
	name = user + "_pvt.pem"
	if path.exists (name):
		file = open (name, "r")
		private_key = RSA.importKey (file.read ())
		file.close ()
		return private_key
	else:
		print ("\nPrivate key of "+ user + " could not be located\n")
		quit ()

def obtain_public_key (user):
	name = user + "_pub.pem"
	if path.exists (name):
		file = open (name, "r")
		public_key = RSA.importKey (file.read ())
		file.close ()
		return public_key
	else:
		print ("\nPublic key of "+ user + " could not be located\n")
		quit ()

def sha_1 (message):
	#Creating a new Hash object (SHA 1)
	dig = SHA.new ()

	#Opening both files
	file = open (message, "rb")

	#Reading all the massage as a string of bytes
	data = file.read ()

	#Counting characters
	caracteres = len (data)

	#Digest of the message
	dig.update (data)

	#Converting from _SHA1 to bytes
	data = bytes (dig.hexdigest (), 'utf-8')

	file.close ()
	
	#Returning message digest
	return data, caracteres

def sign (private_key, digesto):
	cipher = PKCS1_OAEP.new (private_key)
	sign = cipher.encrypt (digesto)
	return sign

def sign_message (message, digital_signature, length, receiver):
	public_key = obtain_public_key (receiver)

def main ():
	os.system ("cls")
	transmitter = input ('¿Who are you? (Write your name)\n\n')
	option = input ('\n¿Do you want to send or receive a message?\nSend (1)\tReceive (2)\n\n')
	if option == '1':
		receiver = input ('\n¿Who do you want to send a message to? (Write his/her name)\n\n')

		#Generation of the keys for transmitter and receiver
		generate_keys (transmitter, receiver)
		message = input ("\nIntroduce the name of the file that contains the message: ")

		#Digest the message
		digesto, length = sha_1 (message)

		#Obtaining private key of the transmitter
		private_key = obtain_private_key (transmitter)

		#Encrypting message digest
		digital_signature = sign (private_key, digesto)

		#Write the new file with the digital signature
		sign_message (message, digital_signature, length, receiver)

	elif option == '2':
		receiver = transmitter;
		private_key = obtain_private_key (receiver)
	else:
		print ("\n\nIncorrect option.\n")
		quit ()

#Main function
main ()
