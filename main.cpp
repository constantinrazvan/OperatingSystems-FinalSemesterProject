#include <iostream>
#include <fstream>
#include <string>
#include <thread> 
#include <atomic>

using namespace std;

int THREADS; // number of threads

int variable = 0; // the pre-inited variable

// Check user's threads supported by CPU
void checkAndAssignThreads() {
    unsigned int threads = thread::hardware_concurrency();
    THREADS = threads;

    std::cout << "Number of threads: " << THREADS << std::endl;
}   

// Check why he wants to use the program. What is he gonna do?
void checkUsability() {
    cout << "What would you like to do?\n";
    cout << "1. Modify variable" << endl;
    cout << "2. Modify file" << endl;
}

// Show menu for variable usability
void showMenuForVariable() {
    cout << "Menu:\n";
    cout << "1. Increment variable with 1\n";
    cout << "2. Decrement variable with 1\n";
    cout << "3. Increment variable with user input\n";
    cout << "4. Decrement variable with user input\n";
    cout << "5. Print variable\n";
    cout << "6. Go back to choose usability\n";
    cout << "7. Exit\n";
}

//Show menu for file usability
void showMenuForFile() {
    cout << "Menu:\n";
    cout << "1. Add text\n";
    cout << "2. Remove file\n";
    cout << "3. Search in file\n";
    cout << "4. Print file contents\n";
    cout << "5. Go back to choose usability\n";
    cout << "6. Exit\n";
}


int main() {
    checkAndAssignThreads();
    int choice = 0;
    return 0;
}
