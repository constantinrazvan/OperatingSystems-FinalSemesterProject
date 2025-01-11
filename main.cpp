#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <unistd.h>
#include <filesystem>

using namespace std;

int THREADS = 0; // number of threads
int variable = 0; // the pre-inited variable for user to work with

void checkAndAssignThreads() {
    unsigned int threads = thread::hardware_concurrency();
    THREADS = (int)threads;
    cout << "Number of threads: " << THREADS << endl;
}

// Function to check if a file exists
bool checkFileForExistence(const string& fullPath) {
    ifstream file(fullPath);
    return file.good();
}

// Function to create a new file
void createFile(string& path, string& filename) {
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
void deleteFile(string& fullPath, string& filename) {
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
void searchInFile(string& fullPath, string& filename, string& searchContent) {
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
void readFile(string& path, string& filename) {
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

void incrementVariable(int& variable) {
    variable += 1;
}

void decrementVariable(int& variable) {
    if (variable <= 0) {
        cout << "[ERROR] Cannot decrement below 0" << endl;
    } else {
        variable--;
    }
}

void printVariable(int& variable) {
    cout << "[INFO] Variable value: " << variable << endl;
}

void multiplyVariable(int& variable) {
    variable *= 2;
}

// Function to get the number of available threads
void checkAndAssignThreads() {
    unsigned int threads = std::thread::hardware_concurrency();
    THREADS = (int)threads;
    std::cout << "Number of threads: " << THREADS << std::endl;
}

// Menu for checking usability of the program
void checkUsability() {
    system("cls");
    checkAndAssignThreads();
    std::cout << "\nWhat would you like to do?\n";
    std::cout << "1. Modify variable" << std::endl;
    std::cout << "2. Modify file" << std::endl;
    std::cout << "3. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

// Menu for variable operations
void showMenuForVariable() {
    int varChoice;
    do {
        std::cout << "\nVariable Menu:\n";
        std::cout << "1. Increment variable by 1\n";
        std::cout << "2. Decrement variable by 1\n";
        std::cout << "3. Print variable\n";
        std::cout << "4. Multiply variable by 2\n";
        std::cout << "5. Go back to main menu\n";
        std::cout << "Enter your choice: ";
        std::cin >> varChoice;

        switch (varChoice) {
            case 1:
                system("cls");
                incrementVariable(variable);
                std::cout << "[INFO] Variable incremented. Current value: " << variable << std::endl;
                break;
            case 2:
                system("cls");

                if (variable <= 0) {
                    cout << "[ERROR] Cannot decrement below 0" << endl;
                } else {
                    variable--;
                    std::cout << "[INFO] Variable decremented. Current value: " << variable << std::endl;
                }

                break;
            case 3:
                system("cls");
                printVariable(variable);
                break;
            case 4:
                system("cls");
                multiplyVariable(variable);
                std::cout << "[INFO] Variable multiplied. Current value: " << variable << std::endl;

                break;
            case 5:
                system("cls");
                checkUsability();
                break;
            default:
                std::cout << "Invalid choice, please try again." << std::endl;
        }
    } while (varChoice != 5);
}

void showMenuForFile() {
    int fileChoice;
    std::string filePath;

    std::cout << "Before diving into file operations, please provide the path to the file." << std::endl;
    std::cout << "Enter the path to the file: ";
    std::cin >> filePath;

    std::string filename = "";
    std::string searchContent = "";

    if (filePath.empty()) {
        std::cout << "Invalid file path. Please try again." << std::endl;
    } else {
        std::string newFilePath = filePath + "\\"; // Set full path

        do {
            std::cout << "Your current path is: " << newFilePath << std::endl;
            std::cout << "\nFile Menu:\n";
            std::cout << "1. Create a new file in path\n";
            std::cout << "2. Remove file in path\n";
            std::cout << "3. Search in file\n";
            std::cout << "4. Print file contents\n";
            std::cout << "5. Change Path\n";
            std::cout << "6. Go back to main menu\n";
            std::cout << "Enter your choice: ";
            std::cin >> fileChoice;

            switch (fileChoice) {
                case 1:
                    system("cls");
                    // Get the filename from the user
                    std::cout << "Enter the filename to create: ";
                    std::cin >> filename;
                    createFile(newFilePath, filename);
                    break;
                case 2:
                    system("cls");
                    // Get the filename to delete
                    std::cout << "Enter the filename to delete: ";
                    std::cin >> filename;
                    deleteFile(newFilePath, filename);
                    break;
                case 3:
                    system("cls");
                    // Get search content and filename
                    std::cout << "Enter the filename to search: ";
                    std::cin >> filename;
                    std::cout << "Enter search content: ";
                    std::cin.ignore();  // To handle any leftover newline character
                    std::getline(std::cin, searchContent);
                    searchInFile(newFilePath, filename, searchContent);
                    break;
                case 4:
                    system("cls");
                    // Get the filename to read
                    std::cout << "Enter the filename to read: ";
                    std::cin >> filename;
                    readFile(newFilePath, filename);
                    break;
                case 5:
                    system("cls");
                    std::cout << "Enter new path: ";
                    std::cin >> filePath;
                    newFilePath = filePath + "\\"; // Update path
                    break;
                case 6:
                    system("cls");
                    checkUsability();
                    break;
                default:
                    std::cout << "Invalid choice, please try again." << std::endl;
            }
        } while (fileChoice != 6);
    }
}

int main() {
    // Main menu loop
    checkUsability();

    int mainChoice;
    do {
        std::cin >> mainChoice;

        switch (mainChoice) {
            case 1:
                system("cls");
                showMenuForVariable();
                break;
            case 2:
                system("cls");
                showMenuForFile();
                break;
            case 3:
                std::cout << "Exiting program..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice, please try again." << std::endl;
        }
    } while (mainChoice != 3);

    return 0;
}