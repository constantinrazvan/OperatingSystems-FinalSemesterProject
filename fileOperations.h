#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H

#include <string>

// Function prototypes
bool checkFileForExistence(const std::string& filePath);
void createFile(const std::string& filePath);
void readFile(const std::string& filePath);
void writeToFile(const std::string& filePath, const std::string& content);
void deleteFile(const std::string& filePath);

#endif // FILEOPERATIONS_H
