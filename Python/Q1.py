'''

Q1:

Write a Python script that performs the following tasks:
The marks obtained by a student in 3 different subjects are input by the user. Your
program should calculate the average of subjects and display the grade. The student gets a
grade as per the following rules:
Average Grade
90-100 A
80-89 B
70-79 C
60-69 D
0-59 F
'''
subject1 = int(input("Enter marks obtained in subject1:"))

subject2 = int(input("Enter marks obtained in subject2:"))

subject3 = int(input("Enter marks obtained in subject3:"))

average = ( subject1 + subject2 + subject3 )/3
print("Average marks:",average)

if average  >=90:
  print("Grade: A")
elif average  >=80:
  print("Grade: B")
elif average  >=70:
  print("Grade: C")
elif average  >=60:
  print("Grade: D")
else:
  print("Grade: F")