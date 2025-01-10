#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <unistd.h>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

int THREADS = 0; // number of threads
int variable = 0; // the pre-inited variable for user to work with

// function to get the number of available threads
void checkAndAssignThreads() {
    unsigned int threads = thread::hardware_concurrency();
    THREADS = (int)threads;
    cout << "Number of threads: " << THREADS << endl;
}

// Menu for checking usability of the program
void checkUsability() {
    system("cls");
    checkAndAssignThreads();
    cout << "\nWhat would you like to do?\n";
    cout << "1. Modify variable" << endl;
    cout << "2. Modify file" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: ";
}

// Menu for variable operations
void showMenuForVariable() {
    int varChoice;
    do {
        cout << "\nVariable Menu:\n";
        cout << "1. Increment variable by 1\n";
        cout << "2. Decrement variable by 1\n";
        cout << "3. Print variable\n";
        cout << "4. Multiply variable by 2\n";
        cout << "5. Go back to main menu\n";
        cout << "Enter your choice: ";
        cin >> varChoice;

        switch (varChoice) {
            case 1:
                system("cls");
                variable++;
                cout << "[INFO] Variable incremented. Current value: " << variable << endl;
                break;
            case 2:
                system("cls");
                if(variable <= 0 ) {
                    cout << "[ERROR] Cannot decrement below 0" << endl;
                } else {
                    variable--;
                    cout << "[INFO] Variable decremented. Current value: " << variable << endl;
                }
                break;
            case 3:
                system("cls");
                cout << "Current value of variable: " << variable << endl;
                break;
            case 4:
                system("cls");
                variable *= 2;
                cout << "[INFO] Variable multiplied by 2. Current value: " << variable << endl;
                break;
            case 5:
                system("cls");
                checkUsability();
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
        }
    } while (varChoice != 5);  
}

// Function to check if a file exists
bool checkFileForExistence(const string& fullPath) {
    ifstream file(fullPath);
    return file.good();
}

// Function to create a new file
void createFile(const string& path, const string& filename) {
    string fullPath = path + filename;
    if (!checkFileForExistence(fullPath)) {
        ofstream newFile(fullPath); 
        if (newFile) {
            cout << "File created: " << fullPath << endl;
        } else {
            cout << "Error creating file: " << fullPath << endl;
        }
        newFile.close();
    } else {
        cout << "File already exists: " << fullPath << endl;
    }
}

// Function to delete a file
void deleteFile(const string& fullPath, const string& filename) {
    string completePath = fullPath + filename + ".txt"; 

    ifstream file(completePath);
    if (file.good()) {  // checking if the file exists
        file.close();  // close the file before deleting it

        if (remove(completePath.c_str()) == 0) { // deleting the file
            cout << "File deleted: " << completePath << endl;
        } else {
            cout << "Error deleting file: " << completePath << endl;
        }
    } else {
        cout << "File does not exist: " << completePath << endl;
    }
}

// Function to search content in a file
void searchInFile(const string& fullPath, const string& filename, const string& searchContent) {
    string completePath = fullPath + filename + ".txt";  // Concatenate the full path and filename

    ifstream file(completePath);
    string line;
    bool found = false;

    if (file.is_open()) {
        while (getline(file, line)) {
            if (line.find(searchContent) != string::npos) {
                cout << "Found: " << line << endl;
                found = true;
            }
        }
        file.close();

        if (!found) {
            cout << "Search term not found in the file." << endl;
        }
    } else {
        cout << "Error opening file: " << completePath << endl;  // Report error with the full file path
    }
}

// Function to read the content of a file
void readFile(const string& path, const string& filename) {
    string fullPath = path + filename + ".txt";
    ifstream file(fullPath);

    if (file.is_open()) {
        string line;
        cout << "Reading file: " << fullPath << endl;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "Error opening file: " << fullPath << endl;
    }
}

// Menu for file operations
void showMenuForFile() {
    int fileChoice;
    string filePath;

    cout << "Before diving into file operations, please provide the path to the file." << endl;
    cout << "Enter the path to the file: ";
    cin >> filePath;

    if (filePath.empty()) {
        cout << "Invalid file path. Please try again." << endl;
    } else {  
        string newFilePath = filePath + "\\";
        do {
            cout << "Your current path is: " << newFilePath << endl;
            cout << "\nFile Menu:\n";
            cout << "1. Create a new file in path\n";
            cout << "2. Remove file in path\n";
            cout << "3. Search in file\n";
            cout << "4. Print file contents\n";
            cout << "5. Change Path\n";
            cout << "6. Go back to main menu\n";
            cout << "Enter your choice: ";
            cin >> fileChoice;

            switch (fileChoice) {
                case 1: {
                    string fileName; 
                    cout << "Enter the name of the file to create: ";
                    cin >> fileName;
                    fileName = fileName + ".txt";
                    createFile(newFilePath, fileName);
                    break;
                }
                case 2: {
                    string fileName;
                    cout << "Enter the name of the file to delete: ";
                    cin >> fileName;

                    fileName = fileName + ".txt";
                    deleteFile(newFilePath, fileName);
                    break;
                }
                case 3: {
                    string searchContent;
                    string filename; 

                    cout << "Enter the name of the file to search in: ";
                    cin >> filename;

                    cout << "Enter the content to search for: ";
                    cin >> searchContent;
                    searchInFile(newFilePath, filename, searchContent);
                    break;
                }
                case 4: {
                    string fileName;
                    cout << "Enter the name of the file to read: ";
                    cin >> fileName;
                    readFile(newFilePath, fileName);
                    break;
                }
                case 5:
                    cout << "Enter the new path: ";
                    cin >> filePath;
                    newFilePath = filePath + "\\";
                    break;
                case 6:
                    system("cls");
                    checkUsability();
                    break;
                default:
                    cout << "Invalid choice, please try again." << endl;
                    break;
            }
        } while (fileChoice != 6);  
    }
}

int main() {
    int choice;
    do {
        checkUsability();
        cin >> choice;

        switch (choice) {
            case 1:
                showMenuForVariable();
                break;
            case 2:
                showMenuForFile();
                break;
            case 3:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 3);

    return 0;
}
