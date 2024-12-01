/*
Q1:

Write a c++ script that performs the following tasks:
The marks obtained by a student in 3 different subjects are input by the user. Your
program should calculate the average of subjects and display the grade. The student gets a
grade as per the following rules:
Average Grade
90-100 A
80-89 B
70-79 C
60-69 D
0-59 F
*/

void Q1(){
    float subject1, subject2, subject3;
    std::cout << "Enter marks obtained in subject1: ";
    std::cin >> subject1;
    
    std::cout << "Enter marks obtained in subject2: ";
    std::cin >> subject2;
    
    std::cout << "Enter marks obtained in subject3: ";
    std::cin >> subject3;

    float average = (subject1 + subject2 + subject3) / 3.0;
    std::cout << "Average marks: " << average << endl;
    
    if (average >= 90 && average <= 100) {
        std::cout << "Grade: A" << endl;
    } else if (average >= 80 && average < 90) {
        std::cout << "Grade: B" << endl;
    } else if (average >= 70 && average < 80) {
        std::cout << "Grade: C" << endl;
    } else if (average >= 60 && average < 70) {
        std::cout << "Grade: D" << endl;
    }
    else if (average >= 0 && average < 60) {
        std::cout << "Grade: F" << endl;
    } else {
        std::cout << "Invalid marks" << endl;
    }
    
}
