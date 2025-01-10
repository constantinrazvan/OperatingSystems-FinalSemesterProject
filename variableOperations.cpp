#include <iostream>
#include <string>
#include <variableOperations.h>
using namespace std;

incrementVariable(int& variable) {
    variable += 1;
}

decrementVariable(int& variable) {
    variable -= 1;  
}

multiplyVariable(int& variable) {
    variable *= 2;
}

squaringTheNumber(int& variable) {
    variable *= variable;
}