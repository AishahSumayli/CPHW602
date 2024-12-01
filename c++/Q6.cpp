
/*
Write a c++ script that defines and uses the following functions:

1. is_even(n): A function that takes an integer n and returns True if the number is even, and False otherwise.

2. main(): A function that prompts the user to enter an integer and then:

A. Checks if the number is even using is_even(n) and prints "The number is even." if the function returns True.
B. If the function returns False, print "The number is odd."

Call the main() function to run the script.
*/




bool is_even(int number) { 
  return number % 2 == 0;

}
void Q6() {
    int number;

    cout << "Enter an integer number: ";
    cin >> number;

   
    if (is_even(number)) {
        cout << "The number is even." << endl;
    } else {
        cout << "The number is odd." << endl;
    }
}
