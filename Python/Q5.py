'''
Write a Python script that takes an integer input from the user and checks the following conditions:

1. If the number is positive and even, print "The number is positive and even."
2. If the number is positive and odd, print "The number is positive and odd."
3. If the number is zero, print "The number is zero."
4. If the number is negative and even, print "The number is negative and even."
5. If the number is negative and odd, print "The number is negative and odd."

Ensure that your script correctly handles each condition using if, elif, and else statements.

'''
number = int(input("Enter integer number"))

if number > 0 and number %2 == 0:
    print("The number is positive and even.")
elif  number > 0 and number %2 == 1:
    print("The number is positive and odd.")

elif number < 0 and number %2 == 0:
    print("The number is negative and even.")
elif  number < 0 and number %2 == 1:
    print("The number is negative and odd.")
else:
    print("The number is zero.")
