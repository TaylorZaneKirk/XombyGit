##############################################################################
#                    Project Name: Quadratic Functions
#                           Name: Taylor Kirk
#                    Data Structures Date: 03/23/2015
##############################################################################
#        This program serves to be a 'fraction tutor.' Using a custom fraction
#     this program can add, subtract, multiply, divide, and print fractions.
#     When this program is started it generates four fractions: 2 sets of 2
#     fractions being summed. The user is then asked to give the correct
#     response for just one of the sets. After the correct answer is given,
#     or after the user has answered incorrectly 3 total times, the answer is
#     shown, and the program moves on the other problems.
##############################################################################

from random import randint #useful for generating integers to be used for
                           #dynamic fraction generation

#The below function is passed two parameters which will be used to
#determine the GCD of two numbers.
def GreatestCommonDenominator(Numerator, Denominator):
    while Denominator != Numerator:
        if Denominator < Numerator:
            Numerator = Numerator - Denominator
        else:
            Denominator = Denominator - Numerator
    return Numerator

#The Fraction class below is passed two parameters, which will be used
#to construct a proper fraction. Once the fraction is formed, it is returned
#to the caller for use.            
class Fraction:
    #Constructor
    def __init__(self, Numerator, Denominator):
        self.Numerator = Numerator / GreatestCommonDenominator(Numerator, 
                                                            Denominator)
        self.Denominator = Denominator / GreatestCommonDenominator(Numerator, 
                                                            Denominator)
        if self.Denominator == 0:
            raise ZeroDivisionError #Prevents user from passing 0
    
    #Overloaded string operator    
    def __str__(self):
        if type(self) is tuple:
            if self.Numerator < 0:
                return '%s/%s' %(self.Denominator, -1*self.Numerator)
            else:
                return '%s/%s' %(self.Denominator, self.Numerator)
        elif self.Denominator == 1:
            return str(self.Numerator)
        else:
            return '%s/%s' %(self.Numerator, self.Denominator)
    
    #Overloaded addition operator. Will prevent floats from being passed
    #also will automatically convert single integers into fractions
    def __add__(self, Right):
        if type(Right) == int:
            Right = Fraction(Right, 1)
        if type(Right) == float:
            return NotImplemented
        NewNumerator = (self.Numerator*Right.Denominator + 
            self.Denominator*Right.Numerator)
        NewDenominator = (self.Denominator*Right.Denominator)
        return Fraction(NewNumerator, NewDenominator)
     
    #Overloaded subtraction operator. Will prevent floats from being passed
    #also will automatically convert single integers into fractions 
    def __sub__(self, Right):
        if type(Right) == int:
            Right = Fraction(Right, 1)
        if type(Right) == float:
            return NotImplemented
        NewNumerator = (self.Numerator*Right.Denominator - 
            self.Denominator*Right.Numerator)
        NewDenominator = (self.Denominator*Right.Denominator)
        return Fraction(NewNumerator, NewDenominator)
     
    #Overloaded multiplication operator. Will prevent floats from being passed
    #also will automatically convert single integers into fractions 
    def __mul__(self, Right):
        if type(Right) == int:
            Right = Fraction(Right, 1)
        if type(Right) == float:
            return NotImplemented
        NewNumerator = (self.Numerator*Right.Numerator)
        NewDenominator = (self.Denominator*Right.Denominator)
        return Fraction(NewNumerator, NewDenominator)
    
    #Overloaded division operator. Will prevent floats from being passed
    #also will automatically convert single integers into fractions    
    def __div__(self, Right):
        if type(Right) == int:
            Right = Fraction(Right, 1)
        if type(Right) == float:
            return NotImplemented
        NewNumerator = (self.Numerator*Right.Denominator)
        NewDenominator = (self.Denominator*Right.Numerator)
        return Fraction(NewNumerator, NewDenominator)
    
    #Overloaded comparison operator    
    def __cmp__(self, Other):
        if self.Numerator == Other.Numerator:
            if self.Denominator == Other.Denominator:
                return 0
        else:
            return 1
        
##############################################################################
#                        Main Program Body
##############################################################################
print("Hello & welcome to the Fraction Tutor!")
print("You will be asked to solve ONE of the two fractions below.")
print("If you answer incorrectly three consecutive times the answer")
print("will be shown and the next question given.\n")

NumAttempts = 0; #Tracks the number of times a user has submitted an answer

#The beow group of four statements generates four total fractions from
#randomly selected integers (using only 1-9)
FirstFraction = Fraction(randint(1,9), randint(1,9))
SecondFraction = Fraction(randint(1,9), randint(1,9))
ThirdFraction = Fraction(randint(1,9), randint(1,9))
FourthFraction = Fraction(randint(1,9), randint(1,9))

print "First Challenge: %s + %s OR %s + %s" %(FirstFraction, SecondFraction,
                                              ThirdFraction, FourthFraction)

#Addition questions
while NumAttempts < 3:
    FirstAnswer = FirstFraction + SecondFraction
    SecondAnswer = ThirdFraction + FourthFraction
    
    try:
        First = int(raw_input("Numerator: "))
    except ValueError:
        print "Not a number."
    try:
        Second = int(raw_input("Denominator: "))
    except ValueError:
        print "Not a number."
    UserAnswer = Fraction(First, Second)
    
    if UserAnswer in (FirstAnswer, SecondAnswer):
        print "Correct!"
        NumAttempts = 3
    else:
        NumAttempts = NumAttempts + 1
        
    if NumAttempts == 3:
        print "First Answer: %s, Second Answer: %s" %(FirstAnswer,
                                                      SecondAnswer)

NumAttempts = 0; #After addition set, return NumAttempts to zero for next

FirstFraction = Fraction(randint(1,9), randint(1,9))
SecondFraction = Fraction(randint(1,9), randint(1,9))
ThirdFraction = Fraction(randint(1,9), randint(1,9))
FourthFraction = Fraction(randint(1,9), randint(1,9))

print "Second Challenge: %s - %s OR %s - %s" %(FirstFraction, SecondFraction,
                                              ThirdFraction, FourthFraction)
#Subtraction questions
while NumAttempts < 3:
    FirstAnswer = FirstFraction - SecondFraction
    SecondAnswer = ThirdFraction - FourthFraction
    
    try:
        First = int(raw_input("Numerator: "))
    except ValueError:
        print "Not a number."
    try:
        Second = int(raw_input("Denominator: "))
    except ValueError:
        print "Not a number."
    UserAnswer = Fraction(First, Second)
    
    if UserAnswer in (FirstAnswer, SecondAnswer):
        print "Correct!"
        NumAttempts = 3
    else:
        NumAttempts = NumAttempts + 1
        
    if NumAttempts == 3:
        print "First Answer: %s, Second Answer: %s" %(FirstAnswer,
                                                      SecondAnswer)   

NumAttempts = 0;

FirstFraction = Fraction(randint(1,9), randint(1,9))
SecondFraction = Fraction(randint(1,9), randint(1,9))
ThirdFraction = Fraction(randint(1,9), randint(1,9))
FourthFraction = Fraction(randint(1,9), randint(1,9))

print "Third Challenge: %s * %s OR %s * %s" %(FirstFraction, SecondFraction,
                                              ThirdFraction, FourthFraction)
#Multiplication questions
while NumAttempts < 3:
    FirstAnswer = FirstFraction * SecondFraction
    SecondAnswer = ThirdFraction * FourthFraction
    
    try:
        First = int(raw_input("Numerator: "))
    except ValueError:
        print "Not a number."
    try:
        Second = int(raw_input("Denominator: "))
    except ValueError:
        print "Not a number."
    UserAnswer = Fraction(First, Second)
    
    if UserAnswer in (FirstAnswer, SecondAnswer):
        print "Correct!"
        NumAttempts = 3
    else:
        NumAttempts = NumAttempts + 1
        
    if NumAttempts == 3:
        print "First Answer: %s, Second Answer: %s" %(FirstAnswer,
                                                      SecondAnswer)

NumAttempts = 0;

FirstFraction = Fraction(randint(1,9), randint(1,9))
SecondFraction = Fraction(randint(1,9), randint(1,9))
ThirdFraction = Fraction(randint(1,9), randint(1,9))
FourthFraction = Fraction(randint(1,9), randint(1,9))

print "Fourth Challenge: %s / %s OR %s / %s" %(FirstFraction, SecondFraction,
                                              ThirdFraction, FourthFraction)
#Division question
while NumAttempts < 3:
    FirstAnswer = FirstFraction / SecondFraction
    SecondAnswer = ThirdFraction / FourthFraction
    
    try:
        First = int(raw_input("Numerator: "))
    except ValueError:
        print "Not a number."
    try:
        Second = int(raw_input("Denominator: "))
    except ValueError:
        print "Not a number."
    UserAnswer = Fraction(First, Second)
    
    if UserAnswer in (FirstAnswer, SecondAnswer):
        print "Correct!"
        NumAttempts = 3
    else:
        NumAttempts = NumAttempts + 1
        
    if NumAttempts == 3:
        print "First Answer: %s, Second Answer: %s" %(FirstAnswer,
                                                      SecondAnswer)

print "Tutor complete..."