# -*- coding: utf-8 -*-
"""
Created on Mon Nov  2 19:11:34 2015

@author: Taylor Kirk
"""
import string

#Function Name: requestFileName
#Parameters: None
#Purpose: Request file name from user and
#   returns the contents of that file.
def requestFileName():
    fileName = input("Please specify file name: ")
    
    try:
        file = open(fileName, 'r')
    except IOError:
        print('cannot open', fileName)
    else:
        content = file.read()
        file.close()
        
        return content
        
#Function Name: findComplexWords
#Parameters: A list of words from a sentence
#Purpose: Takes a list of words, evaluates each
#   word in that list and strips any punction
#   from the word. Then it counts the number
#   of characters present in the word. If
#   there are more than 8 characters in the
#   word, count that word as complex. Then
#   return the number of complex words in
#   the list of words.
def findComplexWords(wordList):
    numComplex = 0
    
    for word in wordList:
        #set of all punction characters
        exclude = set(string.punctuation)
        word = ''.join(letter for letter in word if letter not in exclude)
        if len(word) > 8:
            numComplex += 1
            
    return numComplex
    
#Function Name: evaluateText
#Parameters: content: String containing the contents
#   of the user-specified file.
#Purpose: Form a list of all the sentences within content
#   evaluate each sentence, as long as the number of words
#   that have been read is less than 100, keep count of the
#   number of sentences read, the number of words per sentence,
#   and the number of complex words that have been found within
#   all the sentences. Form a list of words by splitting the
#   current sentence on each space character. Based on the number
#   of elements within the list of words, increment the word counter
#   by the same number. Once the sample has been evaluated, check the
#   word counter value. If the value is less then 100, determine the
#   sample was not large enough to provide a realistic result.
#   If the word counter is above 100, calculate the average
#   number of words per sentence, calculate the percentage
#   of complex words within the sample, using the values calculate the
#   Gunning Fog Index of the sample.
def evaluateText(content):
    allSentences = content.split('.')
        
    words = 0
    numOfSentences = 0
    complexCount = 0
    
    for sentence in allSentences:
        if words < 100:
            numOfSentences += 1
            wordList = sentence.split(' ')
            words += len(wordList)
            complexCount += findComplexWords(wordList)
            
    if words < 100:
        print("Error: Not enough words in provided sample.")
    else:
        averageWordsPerSentence = words//numOfSentences
        complexPercentage = ((complexCount / words) * 100) // 1
        GFI = ((averageWordsPerSentence + complexPercentage) * 0.4) // 1
        
        printResults(words, numOfSentences, complexCount, 
                     averageWordsPerSentence, complexPercentage, GFI)
    
#Function Name: printResults
#Parameters: integer number of words evaluates, integer number
#   of sentences evaluates, integer number of complex words
#   found in the sample, integer number of the average number
#   of words per sentence, double number of the percentage
#   of complex words in the sample, and double number of
#   the Gunning Fog Index value of the sample.
#Purpose: Print out the results of the evaluation. If the GFI
#   if less than or equal to 12, determine that the sample is generally
#   readable. If the GFI is above 12, determine that the sample
#   is too complex to be considered generally readable.
def printResults(words, sentences, numComplex, average, percent, GFI):    
    print("\nNumber of sentences: ", sentences)
    print("Number of words: ", words)
    print("Number of difficult words: ", numComplex)
    print("Average number of words per sentence: ", average)
    print("Percentage of difficult words: ", percent)
    print("Gunning Fog Index: ", GFI)
    
    if(GFI > 12):
        print("\nConclusion: This sample would not be expected to be",
              "understood by the general public.")
    else:
        print("\nConclusion: This sample is considered readable by the",
              "general public.")
              
#Function Name: main
#Parameters: None
#Purpose: Form a string containing the contents of a
#   user-specified file, then evaluate those contents.
def main():
    content = requestFileName()
    evaluateText(content)
    
    
if __name__ == '__main__':
    main()