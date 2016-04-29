# -*- coding: utf-8 -*-
"""
Created on Tue Jul 07 15:06:24 2015

@author: Taylor
"""

#Some kind of matrix for vegenere
#2D-matrix for the substitution ciphers
#using number '26' due to 26 letters in alphabet
vigenere = [[0 for i in range(26)] for i in range(26)]
row = 0
col= 0

#Loop through matrix and populate it with applicable
#alphabetical pattern
for i in range(26*26):
    vigenere[row][col] = chr(((col+row)%26)+65)
    col = col + 1
    if col >= 26:
        col = 0
        row = row + 1

def encrypt(v,k,m,ki,mi):
    row = ord(m[mi]) - 65
    col = ord(k[ki]) - 65
    return v[row][col]

#HOMEWORK: GET DECRYPT FUNCTION WORKING
#Accepts same parameters as encrypt() function
#Using the ki (The key index) the function derives
#the row number being used from the key value
#Loop through all the columns of row (WhichRow) in
#matrix v. Once there is a match of the ciphertext
#character being looked for, and the contents of the
#cell v[whichRow][i], then the function sets decryptChar
# to be the character representation of whatever letter
# the found column number (i) is.
def decrypt(v,k,em,ki,emi):
    whichRow = ord(k[ki]) - 65
    for i in range(26):
        if v[whichRow][i] == em[emi]:
            decryptChar = chr(i + 65)
            return(decryptChar)


#print matrix
def printMatrix(v):
    i = 0
    j = 0
    k = 0
    line = ""
    
    for i in range(26*26):
        line = line + v[j][k]
        j = j + 1
        if j >=26:
            print(line)
            line = ""
            j = 0
            k = k + 1

#Define key
#Convert key to uppercase
#remove all spaces
key = "THISistheKEYWORD"
key = key.upper()
key = key.replace(" ","")
print(key)

message = "THIS IS THE MESSAGE"
message = message.upper()

#printMatrix(vigenere)
#print(encrypt(vigenere,key,message,0,0))

ciphertext = ""
decrypttext = ""

#ERROR NOTE: APPENDING '% 26' TO THE END OF mi = i
#RESULTS IN AN ERROR. REASON UNKNOWN
for i in range(len(message)):
    mi = i
    ki = i % len(key)
    if ord(message[i]) != 32:
        ciphertext = ciphertext + encrypt(vigenere,key,message,ki,mi)
    else:
        ciphertext = ciphertext + " "

print(message)    
print(ciphertext)

for i in range(len(ciphertext)):
    emi = i
    ki = i % len(key)
    if ord(ciphertext[i]) != 32:
        decrypttext = decrypttext + decrypt(vigenere,key,ciphertext,ki,emi)
    else:
        decrypttext = decrypttext + " "

print(decrypttext)