###############################################
# Name: Taylor Kirk
# Class: CMPS XXXX Cryptography
# Date: 13 July 2015
# Program 1 - Playfair Cipher
###############################################

import re

###############################################
# Class Name: playFair
###############################################
# Requires no parameters
# Purpose: This class creates an instance that
#       can be manipulated like a Playfair cipher
###############################################
class playFair:
    def __init__(self):
       self.square = self.generateSquare('')
       
###############################################
# Generate alphabet (From class code)
###############################################
    def generateAlphabet(self):
        alphabet = ""
    
        for i in range(0,26):
            alphabet = alphabet + chr(i+65)
        
        return alphabet
    
###############################################
#  Clean String (From class code)
###############################################       
    def cleanString(self, string, options = {'up':1,'reNonAlphaNum':1,'reSpaces':'_','spLetters':'X'}):
        if 'up' in options:
            string = string.upper()
            
        if 'spLetters' in options:
            string = re.sub(r'([ABCDEFGHIJKLMNOPQRSTUVWXYZ])\1', r'\1X\1', string)
        
        if 'reSpaces' in options:
            space = options['reSpaces']
            string = re.sub(r'[\s]', space, string)
        
        if 'reNonAlphaNum' in options:
            string = re.sub(r'[^\w]', '', string)
        
        if 'reDupes' in options:
            string = ''.join(sorted(set(string), key=string.index))
        
        return string
        
################################################
# generateSquare
################################################
# Purpose: Prepares a grid to be used for digraphs
#   This also removes J's found in the key
#   As well as formats the key into an acceptable
#   form.
################################################
    def generateSquare(self, keyword):
        square = ''
        alpha = self.generateAlphabet()
        alpha = alpha.replace("J", "")
        keyword = self.cleanString(keyword,{'up':1,'reSpaces':'','reNonAlphaNum':1,'reDupes':1})

        for letter in keyword:
            if letter not in square and letter in alpha:
                square += letter
        
        for letter in alpha:
            if letter not in square:
                square += letter
        
        return square

###############################################
# generateDigraphs()
###############################################
# Format message in digraph-form
# ex: AB CD WX YZ
# If a double letter or odd length is encountered
# append 'X'
###############################################
    def generateDigraphs(self, message):
        digraphs = []
        count = 0
        
        while count < len(message):
            digraph = ''
            if count + 1 == len(message):
                digraph = message[count] + 'X'
                digraphs.append(digraph)
                break
            elif message[count] != message[count + 1]:
                digraph = message[count] + message[count + 1]
                digraphs.append(digraph)
                count = count + 2
            else:
                digraph = message[count] + 'X'
                digraphs.append(digraph)
                count = count + 1
        
        return digraphs
    
###############################################
# encryptDigraphs()
###############################################
    def encryptDigraphs(self, message):
        
        firstChar = message[0]
        secondChar = message[1]
        
        firstCharPos = self.square.find(firstChar)
        secondCharPos = self.square.find(secondChar)
        
        firstXY = (firstCharPos % 5, firstCharPos / 5)
        secondXY = (secondCharPos % 5, secondCharPos / 5)
        
        #Perform Slide switch
        if firstXY[0] == secondXY[0]:
            firstEncrypt = self.square[(((firstXY[1] + 1) % 5) * 5) + firstXY[0]]
            secondEncrypt = self.square[(((secondXY[1] + 1) % 5) * 5) + secondXY[0]]
        
        #Perform Fall switch
        elif firstXY[1] == secondXY[1]:
            firstEncrypt = self.square[(firstXY[1] * 5) + ((firstXY[0] + 1) % 5)]
            secondEncrypt = self.square[(secondXY[1] * 5) + ((secondXY[0] + 1) % 5)]
        
        #Perform Cross switch
        else:
            firstEncrypt = self.square[(firstXY[1] * 5) + secondXY[0]]
            secondEncrypt = self.square[(secondXY[1] * 5) + firstXY[0]]
         
        return firstEncrypt+secondEncrypt
        
###############################################
# decryptDigraphs()
###############################################
    def decryptDigraphs(self, message):
        
        firstEncrypt = message[0]
        secondEncrypt = message[1]
        
        firstEncPos = self.square.find(firstEncrypt)
        secondEncPos = self.square.find(secondEncrypt)
        
        firstXY = (firstEncPos % 5, firstEncPos / 5)
        secondXY = (secondEncPos % 5, secondEncPos / 5)
        
        #Perform Slide switch
        if firstXY[0] == secondXY[0]:
            firstLetter = self.square[(((firstXY[1] - 1) % 5) * 5) + firstXY[0]]
            secondLetter = self.square[(((secondXY[1] - 1) % 5) * 5) + secondXY[0]]
        
        #Perform Fall switch
        elif firstXY[1] == secondXY[1]:
            firstLetter = self.square[(firstXY[1] * 5) + ((firstXY[0] - 1) % 5)]
            secondLetter = self.square[(secondXY[1] * 5) + ((secondXY[0] - 1) % 5)]
        
        #Perform Cross Switch    
        else:
            firstLetter = self.square[(firstXY[1] * 5) + secondXY[0]]
            secondLetter = self.square[(secondXY[1] * 5) + firstXY[0]]
         
        return firstLetter+secondLetter

###############################################
# Encrypt
###############################################
    def encrypt(self, message):
        message = message.replace(' ', 'X')
        message = self.cleanString(message)
        digraphs = self.generateDigraphs(message)
        encryptDigraphs= []
        
        for digraph in digraphs:
            encryptDigraphs.append(self.encryptDigraphs(digraph))
        
        return ''.join(encryptDigraphs)
        
###############################################
# Decrypt
###############################################
    def decrypt(self, message):
        message = self.cleanString(message)
        digraphs = self.generateDigraphs(message)
        decryptDigraphs= []
        
        for digraph in digraphs:
            decryptDigraphs.append(self.decryptDigraphs(digraph))
        
        return ''.join(decryptDigraphs)

###############################################
# Set Keyword
###############################################
# Generates a PlayFair grid using the keyword
# as the seed for generation
###############################################
    def setKeyword(self, keyword):
        self.square = self.generateSquare(keyword)
        
###############################################
###############################################
###############################################
# Initial Menu for options (Encrypt, Decrypt, or quit)
###############################################
print("Playfair Encryption Tool: P.E.T")
print("Written by: Taylor Kirk")
print("********************************")
print("1. Encrypt\n2. Decrypt\n3. Quit")
print("********************************")

##############################################
# Recieve input from user to determine
# what function to run.
# If Choice == 1, then Encrypt,
# If Choice == 2, then Decrypt,
# If Choice == 3, then Quit
#############################################
Choice = input("Please select a numerical option from above: ")
if Choice == 3:
    raise SystemExit

opString = raw_input("Please enter a message: ")
keyword = raw_input("Please enter a keyword: ")

theMatrix = playFair()
theMatrix.setKeyword(keyword)

if Choice == 1:
    print("Your encrypted message is: ")
    print(theMatrix.encrypt(opString))

if Choice == 2:
    print("Your decrypted message is: ")
    print(theMatrix.decrypt(opString))