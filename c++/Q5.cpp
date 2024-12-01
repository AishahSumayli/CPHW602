/*
Write a C++ script that takes an integer input from the user and checks the following conditions:

1. If the number is positive and even, print "The number is positive and even."
2. If the number is positive and odd, print "The number is positive and odd."
3. If the number is zero, print "The number is zero."
4. If the number is negative and even, print "The number is negative and even."
5. If the number is negative and odd, print "The number is negative and odd."

Ensure that your script correctly handles each condition using if, elif, and else statements.
*/
void Q5(){
    int number;

    cout << "Enter an integer number: ";
    cin >> number;

    if (number > 0 && number % 2 == 0) {
        cout << "The number is positive and even." << endl;
    } else if (number > 0 && number % 2 == 1) {
        cout << "The number is positive and odd." << endl;
    } else if (number < 0 && number % 2 == 0) {
        cout << "The number is negative and even." << endl;
    } else if (number < 0 && number % 2 == -1) {
        cout << "The number is negative and odd." << endl;
    } else {
        cout << "The number is zero." << endl;
    }
}
