'''
Write a Python script that performs the following tasks:

1. Create Data:

Create a list of strings: ["apple", "banana", "cherry"].

2. Save Data:

Write a function named save_to_file(data, filename) that takes a list of strings and a filename as input and writes each string to a new line in a text file with the given filename.

3. Main Script:

Use the save_to_file(data, "fruits.txt") function to save the list of strings to a text file named "fruits.txt".
Ensure that the script creates the file and writes the strings correctly.

'''

data = ["apple", "banana", "cherry"]
'''
def save_to_file(data, filename):
    with open(filename,"w") as file:
        for item in data:
            file.write(item + '\n')

save_to_file(data, "fruits.txt")
'''
def save_to_file(data, filename):
    file = open(filename,"w")
    for line in data:
        file.write(line + '\n')
    file.close()
save_to_file(data, "fruits.txt")
