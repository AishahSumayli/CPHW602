
/*
Write a Python script that performs the following tasks:

1. Create Data:

Create a list of strings: ["apple", "banana", "cherry"].

2. Save Data:

Write a function named save_to_file(data, filename) that takes a list of strings and a filename as input and writes each string to a new line in a text file with the given filename.

3. Main Script:

Use the save_to_file(data, "fruits.txt") function to save the list of strings to a text file named "fruits.txt".
Ensure that the script creates the file and writes the strings correctly.
*/

void save_to_file(const vector<string>& data, const string& filename) {
    ofstream file(filename); 
    if (file.is_open()) {
        for (const string& item : data) {
            file << item << '\n'; 
        }
        file.close(); 
        cout << "Data has been saved to " << filename << "." << endl;
    } else {
        cerr << "Error: Could not open the file " << filename << endl;
    }
}

void Q7() {
    
    vector<string> data = {"apple", "banana", "cherry"};

    
    save_to_file(data, "fruits.txt");


}
