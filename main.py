import os
import binascii

os.system('sh compilare.sh')
os.system('sh rulare.sh') # hash

def diferente(str1, str2):
	diff = 0
	print(str1)
	print(str2)
	for i in range(len(str1) - 1):
		if str1[i] + str1[i + 1] == str2[i] + str2[i + 1]:
			diff += 1
	return diff

with open('outmd51.txt') as f1:
	with open('outmd52.txt') as f2:
		fisier1 = f1.read()
		fisier2 = f2.read()
		print(diferente(fisier1, fisier2))


with open('outsha1.txt') as f1:
	with open('outsha2.txt') as f2:
		fisier1 = f1.read()
		fisier2 = f2.read()
		print(diferente(fisier1, fisier2))