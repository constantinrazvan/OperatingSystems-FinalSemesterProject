class FileClass {
public:
    FileClass() { }

    string getFilename() const {
        return filename;
    }

    bool checkFileForExistence(const string& filePath) {
        ifstream file(filePath);
        return file.good();
    }

    // create a new file if it doesn't exist
    void createFile(const string& filePath, string* filename) {
        if (!checkFileForExistence(filePath)) {
            ofstream newFile(*filename); 
            if (newFile) {
                cout << "File created: " << *filename << endl;
            } else {
                cout << "Error creating file: " << *filename << endl;
            }
            newFile.close();
        } else {
            cout << "File already exists: " << filePath << endl;
        }
    }

    // Read and display the content of a file
    void readFile(const string& filePath, const string& filename) {
        string fullPath = filePath + filename; 

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

    // Delete a file
    void deleteFile(const string& filePath) {

        string filename; 
        cout << "Enter the name of the file you want to delete from this path: ";
        cin >> filename;
        
        if (remove(filename) == 0) {
            cout << "File deleted: " << filename << endl;
        } else {
            cout << "Error deleting file: " << filename << endl;
        }
    }

    // Search for a specific content in the file
    void searchInFile(const string& filePath, const string& searchContent) {
        ifstream file(filePath);
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
            cout << "Error opening file: " << filePath << endl;
        }
    }
};