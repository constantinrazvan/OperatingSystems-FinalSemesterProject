#include <iostream>
#include <thread>
#include <fstream>
#include <mutex>
#include <cstdlib>
#include <string>

using namespace std;

// mutex for thread-safe I/O
mutex ioMutex;

// mutex for thread-safe file access
mutex fileMutex;

// mutex for variable operations
mutex variableMutex; 

// variable to work with
int variable = 0;  

// Function declarations
int checkUsersThreads();
void createFile();
void deleteFile();
void readFile();
void searchInFile();
bool checkFileExists(const string& filePath);
string getFullPath(const string& folderName);
string ensureTextExtension(const string& filename);
void getUserInput(string& filename, string& filePath);

void incrementVariable();
void decrementVariable();
void printVariable();
void multiplyVariable();

void clrscr();

int main() {
    int userChoice;
    int userThreads = checkUsersThreads();

    do {
        {
            lock_guard<mutex> lock(ioMutex);
            cout << "\nFile Management System\n";
            cout << "The number of available threads on your system is: " << userThreads << "\n";
            cout << "The current variable value is: " << variable << "\n";
            cout << "1. Create File\n";
            cout << "2. Delete File\n";
            cout << "3. Search in File\n";
            cout << "4. Read File\n";
            cout << "5. Increment Variable\n";
            cout << "6. Decrement Variable\n";
            cout << "7. Print Variable\n";
            cout << "8. Multiply Variable\n";
            cout << "9. Exit\n";
            cout << "\nEnter your choice: ";
        }

        cin >> userChoice;

        switch (userChoice) {
            case 1: {
                thread createThread(createFile);
                createThread.join();
                break;
            }
            case 2: {
                thread deleteThread(deleteFile);
                deleteThread.join();
                break;
            }
            case 3: {
                thread searchThread(searchInFile);
                searchThread.join();
                break;
            }
            case 4: {
                thread readThread(readFile);
                readThread.join();
                break;
            }
            case 5: {
                thread incrementThread(incrementVariable);
                incrementThread.join();
                break;
            }
            case 6: {
                thread decrementThread(decrementVariable);
                decrementThread.join();
            }
            case 7: {
                thread printVariableThread(printVariable);
                printVariableThread.join();
                break;
            }
            case 8: {
                thread multiplyThread(multiplyVariable);
                multiplyThread.join();
                break;
            }
            case 9: {
                lock_guard<mutex> lock(ioMutex);
                cout << "Program is exiting...\n";
            }
            default: {
                lock_guard<mutex> lock(ioMutex);
                cout << "Invalid choice, try again.\n";
                break;
            }
        }
    } while (userChoice != 9);

    return 0;
}

void clrscr() {
    cout << "\033[2J\033[1;1H";
}


int checkUsersThreads() {
    return (int)thread::hardware_concurrency();
}

string getFullPath(const string& folderName) {
    const char* userProfile = getenv("USERPROFILE");
    if (userProfile == nullptr) {
        lock_guard<mutex> lock(ioMutex);
        cerr << "Error: Unable to get user profile path!\n";
        return "";
    }
    return string(userProfile) + "\\" + folderName + "\\";
}

void getUserInput(string& filename, string& filePath) {
    {
        lock_guard<mutex> lock(ioMutex);
        cout << "Enter the name of the file: ";
    }
    cin >> filename;

    {
        lock_guard<mutex> lock(ioMutex);
        cout << "Enter the path of the file: ";
    }
    cin >> filePath;
}

bool checkFileExists(const string& filePath) {
    ifstream file(filePath);
    bool exists = file.good();
    file.close();
    return exists;
}

void createFile() {
    system("CLS");
    string filename, filePath;
    getUserInput(filename, filePath);

    string fullPath = getFullPath(filePath) + filename + ".txt";

    lock_guard<mutex> fileLock(fileMutex);
    ofstream file(fullPath);

    lock_guard<mutex> ioLock(ioMutex);
    if (file.is_open()) {
        cout << "File created successfully at: " << fullPath << endl;
        file.close();
    } else {
        cout << "Failed to create file at: " << fullPath << endl;
    }
}

void readFile() {
    system("CLS");
    string filename, filePath;
    getUserInput(filename, filePath);

    string fullPath = getFullPath(filePath) + filename + ".txt";

    if (checkFileExists(fullPath)) {
        lock_guard<mutex> fileLock(fileMutex);
        ifstream file(fullPath);
        if (file.is_open()) {
            string line;
            lock_guard<mutex> ioLock(ioMutex);
            cout << "\nFile contents:\n";
            while (getline(file, line)) {
                cout << line << endl;
            }
            file.close();
        }
    } else {
        lock_guard<mutex> ioLock(ioMutex);
        cout << "File not found: " << fullPath << endl;
    }
}

void deleteFile() {
    system("CLS");
    string filename, filePath;
    getUserInput(filename, filePath);

    string fullPath = getFullPath(filePath) + filename + ".txt";

    if (checkFileExists(fullPath)) {
        lock_guard<mutex> fileLock(fileMutex);
        if (remove(fullPath.c_str()) == 0) {
            lock_guard<mutex> ioLock(ioMutex);
            cout << "File deleted successfully: " << fullPath << endl;
        } else {
            lock_guard<mutex> ioLock(ioMutex);
            cout << "Error deleting file: " << fullPath << endl;
        }
    } else {
        lock_guard<mutex> ioLock(ioMutex);
        cout << "File not found: " << fullPath << endl;
    }
}

void searchInFile() {
    system("CLS");
    string filename, filePath, searchTerm;
    getUserInput(filename, filePath);

    {
        lock_guard<mutex> lock(ioMutex);
        cout << "Enter the search term: ";
    }
    cin >> searchTerm;

    string fullPath = getFullPath(filePath) + filename + ".txt";

    if (checkFileExists(fullPath)) {
        lock_guard<mutex> fileLock(fileMutex);
        ifstream file(fullPath);
        if (file.is_open()) {
            string line;
            bool found = false;
            int lineNumber = 0;

            lock_guard<mutex> ioLock(ioMutex);
            cout << "\nSearch results:\n";
            while (getline(file, line)) {
                lineNumber++;
                if (line.find(searchTerm) != string::npos) {
                    cout << "Line " << lineNumber << ": " << line << endl;
                    found = true;
                }
            }

            if (!found) {
                cout << "Search term '" << searchTerm << "' not found in file." << endl;
            }
            file.close();
        }
    } else {
        lock_guard<mutex> ioLock(ioMutex);
        cout << "File not found: " << fullPath << endl;
    }
}

void incrementVariable() {
    system("CLS");
    lock_guard<mutex> lock(variableMutex);
    variable++;
    lock_guard<mutex> ioLock(ioMutex);
    cout << "[INFO] Variable incremented: " << variable << endl;
}

void decrementVariable() {
    system("CLS");
    lock_guard<mutex> lock(variableMutex);
    variable--;
    lock_guard<mutex> ioLock(ioMutex);
    cout << "[INFO] Variable decremented: " << variable << endl;
}

void printVariable() {
    system("CLS");
    lock_guard<mutex> lock(variableMutex);
    lock_guard<mutex> ioLock(ioMutex);
    cout << "[INFO] Variable value: " << variable << endl;
}

void multiplyVariable() {
    system("CLS");
    lock_guard<mutex> lock(variableMutex);
    variable *= 2;
    lock_guard<mutex> ioLock(ioMutex);
    cout << "[INFO] Variable multiplied: " << variable << endl;
}
