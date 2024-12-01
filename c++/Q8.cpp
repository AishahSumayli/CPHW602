/*
Write a Python script that performs the following tasks:

1. Read Data:

Write a function named read_from_file(filename) that takes a filename as input and reads the contents of the file. The function should return a list of strings, where each string represents a line from the file.

2. Main Script:

A. Use the read_from_file("fruits.txt") function to read the contents of a file named "fruits.txt", which contains a list of fruits, each on a new line.
B. Print each fruit to the console.
Make sure the script correctly reads and prints the contents of the "fruits.txt" file
*/


vector<string> read_from_file(const string& filename) {
    vector<string> data;
    ifstream file(filename); 
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
	  data.push_back(line);
        }
        file.close(); 
    } else {
        cerr << "Error: Could not open the file " << filename << endl;
    }
    return data;
}

void Q8 () {
    
    vector<string> fruits = read_from_file("fruits.txt");

    for (const string& fruit : fruits) {
        cout << fruit << endl;
    }

 
}
