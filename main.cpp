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

// mutex for log file
mutex logMutex;

// mutex for user's threads
mutex usersThreadsMutex;

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
void send_message(const string& message);

void clrscr();

int main() {
    {
        ofstream logFile("thread_monitor.log", ios::trunc);
        logFile << "=== Thread Monitor Started ===" << endl;
        logFile.close();
    }

    int userChoice;
    int userThreads = checkUsersThreads();
    string checkThreads = "You have left " + to_string(userThreads) + " threads.";
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
                if (userThreads > 0) {
                    send_message("Thread 1 has started: creating file.");
                    {
                        lock_guard<mutex> lock(usersThreadsMutex);
                        userThreads--;
                    }
                    send_message("Available threads: " + to_string(userThreads));

                    thread createThread([&]() {
                        createFile();
                        {
                            lock_guard<mutex> lock(usersThreadsMutex);
                            userThreads++;
                        }
                    });

                    send_message("Thread 1 is waiting.");
                    createThread.join();
                    send_message("Thread 1 has finished: file created.");
                    send_message("Available threads: " + to_string(userThreads));
                } else {
                    send_message("No available threads left!");
                }
                break;
            }
            case 2: {
                if (userThreads > 0) {
                    send_message("Thread 2 has started: deleting file.");
                    {
                        lock_guard<mutex> lock(usersThreadsMutex);
                        userThreads--;
                    }
                    send_message("Available threads: " + to_string(userThreads));

                    thread deleteThread([&]() {
                        deleteFile();
                        {
                            lock_guard<mutex> lock(usersThreadsMutex);
                            userThreads++;
                        }
                    });

                    send_message("Thread 2 is waiting.");
                    deleteThread.join();
                    send_message("Thread 2 has finished: file deleted.");
                    send_message("Available threads: " + to_string(userThreads));
                } else {
                    send_message("No available threads left!");
                }
                break;
            }
            case 3: {
                if (userThreads > 0) {
                    send_message("Thread 3 has started: searching in file.");
                    {
                        lock_guard<mutex> lock(usersThreadsMutex);
                        userThreads--;
                    }
                    send_message("Available threads: " + to_string(userThreads));

                    thread searchThread([&]() {
                        searchInFile();
                        {
                            lock_guard<mutex> lock(usersThreadsMutex);
                            userThreads++;
                        }
                    });

                    send_message("Thread 3 is waiting.");
                    searchThread.join();
                    send_message("Thread 3 has finished: search completed.");
                    send_message("Available threads: " + to_string(userThreads));
                } else {
                    send_message("No available threads left!");
                }
                break;
            }
            case 4: {
                if (userThreads > 0) {
                    send_message("Thread 4 has started: reading file.");
                    {
                        lock_guard<mutex> lock(usersThreadsMutex);
                        userThreads--;
                    }
                    send_message("Available threads: " + to_string(userThreads));

                    thread readThread([&]() {
                        readFile();
                        {
                            lock_guard<mutex> lock(usersThreadsMutex);
                            userThreads++;
                        }
                    });

                    send_message("Thread 4 is waiting.");
                    readThread.join();
                    send_message("Thread 4 has finished: file read.");
                    send_message("Available threads: " + to_string(userThreads));
                } else {
                    send_message("No available threads left!");
                }
                break;
            }
            case 5: {
                if (userThreads > 0) {
                    send_message("Thread 5 has started: incrementing variable.");
                    {
                        lock_guard<mutex> lock(usersThreadsMutex);
                        userThreads--;
                    }
                    send_message("Available threads: " + to_string(userThreads));

                    thread incrementThread([&]() {
                        incrementVariable();
                        {
                            lock_guard<mutex> lock(usersThreadsMutex);
                            userThreads++;
                        }
                    });

                    send_message("Thread 5 is waiting.");
                    incrementThread.join();
                    send_message("Thread 5 has finished: variable incremented.");
                    send_message("Available threads: " + to_string(userThreads));
                } else {
                    send_message("No available threads left!");
                }
                break;
            }
            case 6: {
                if (userThreads > 0) {
                    send_message("Thread 6 has started: decrementing variable.");
                    {
                        lock_guard<mutex> lock(usersThreadsMutex);
                        userThreads--;
                    }
                    send_message("Available threads: " + to_string(userThreads));

                    thread decrementThread([&]() {
                        decrementVariable();
                        {
                            lock_guard<mutex> lock(usersThreadsMutex);
                            userThreads++;
                        }
                    });

                    send_message("Thread 6 is waiting.");
                    decrementThread.join();
                    send_message("Thread 6 has finished: variable decremented.");
                    send_message("Available threads: " + to_string(userThreads));
                } else {
                    send_message("No available threads left!");
                }
                break;
            }
            case 7: {
                if (userThreads > 0) {
                    send_message("Thread 7 has started: printing variable.");
                    {
                        lock_guard<mutex> lock(usersThreadsMutex);
                        userThreads--;
                    }
                    send_message("Available threads: " + to_string(userThreads));

                    thread printVariableThread([&]() {
                        printVariable();
                        {
                            lock_guard<mutex> lock(usersThreadsMutex);
                            userThreads++;
                        }
                    });

                    send_message("Thread 7 is waiting.");
                    printVariableThread.join();
                    send_message("Thread 7 has finished: variable printed.");
                    send_message("Available threads: " + to_string(userThreads));
                } else {
                    send_message("No available threads left!");
                }
                break;
            }
            case 8: {
                if (userThreads > 0) {
                    send_message("Thread 8 has started: multiplying variable.");
                    {
                        lock_guard<mutex> lock(usersThreadsMutex);
                        userThreads--;
                    }
                    send_message("Available threads: " + to_string(userThreads));

                    thread multiplyThread([&]() {
                        multiplyVariable();
                        {
                            lock_guard<mutex> lock(usersThreadsMutex);
                            userThreads++;
                        }
                    });

                    send_message("Thread 8 is waiting.");
                    multiplyThread.join();
                    send_message("Thread 8 has finished: variable multiplied.");
                    send_message("Available threads: " + to_string(userThreads));
                } else {
                    send_message("No available threads left!");
                }
                break;
            }
            case 9: {
                send_message("Program is exiting...");
                lock_guard<mutex> lock(ioMutex);
                cout << "Program is exiting...\n";
                break;
            }
            default: {
                send_message("Invalid choice entered.");
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
    system("cls");
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
    system("cls");
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
        } else {
            lock_guard<mutex> ioLock(ioMutex);
            cout << "Failed to open file: " << fullPath << endl;
        }
    } else {
        lock_guard<mutex> ioLock(ioMutex);
        cout << "File not found: " << fullPath << endl;
    }
}


void deleteFile() {
    system("cls");
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
    system("cls");
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
    system("cls");
    lock_guard<mutex> varLock(variableMutex);
    variable++;
    lock_guard<mutex> ioLock(ioMutex);
    cout << "Variable incremented successfully!" << endl;
}

void decrementVariable() {
    system("cls");
    lock_guard<mutex> varLock(variableMutex);
    if (variable == 0) {
        lock_guard<mutex> ioLock(ioMutex);
        cout << "We can't decrement variable! It is 0 already!" << endl;
    } else {
        variable--;
        lock_guard<mutex> ioLock(ioMutex);
        cout << "Variable decremented successfully!" << endl;
    }
}

void printVariable() {
    system("cls");
    lock_guard<mutex> varLock(variableMutex);
    lock_guard<mutex> ioLock(ioMutex);
    cout << "Current value of variable: " << variable << endl;
}

void multiplyVariable() {
    system("cls");
    lock_guard<mutex> varLock(variableMutex);
    variable *= 2;
    lock_guard<mutex> ioLock(ioMutex);
    cout << "Variable multiplied successfully!" << endl;
}

void send_message(const string& message) {
    lock_guard<mutex> logLock(logMutex);
    ofstream logFile("thread_monitor.log", ios::app);

    // Get current time
    auto now = chrono::system_clock::now();
    time_t current_time = chrono::system_clock::to_time_t(now);

    // Format: [HH:MM:SS] Message
    char time_str[26];
    ctime_s(time_str, sizeof time_str, &current_time);
    time_str[24] = '\0';  // Remove newline

    logFile << "[" << time_str << "] " << message << endl;
    logFile.close();
}