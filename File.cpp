
class File {
private:
    string filename;

public:
    File() {
        filename = "";
    }

    File(string filename) {
        this->filename = filename;
    }

    void addTextToFile(const string& input) {
        ofstream file(filename, ios::app); 
        try {
            if (file.is_open()) {
                file << input << endl;
                cout << "Text added successfully." << endl;
            } else {
                throw runtime_error("File could not be opened.");
            }
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }

    void searchInFile(const string& input) {
        ifstream file(filename);
        bool found = false;
        string line;
        
        try {
            if (file.is_open()) {
                while (getline(file, line)) {
                    if (line.find(input) != string::npos) {
                        found = true;
                        cout << "Your text is in the file: " << line << endl;
                    }
                }

                if (!found) {
                    cout << "Your text is not in the file." << endl;
                }
            } else {
                throw runtime_error("File could not be opened.");
            }
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }

    void printFile() {
        ifstream file(filename);
        string line;
        
        try {
            if (file.is_open()) {
                while (getline(file, line)) {
                    cout << line << endl;
                }
            } else {
                throw runtime_error("File could not be opened.");
            }
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }

    void deleteFile() {
        try {
            if (remove(filename.c_str()) == 0) {
                cout << "File deleted successfully." << endl;
            } else {
                cout << "File could not be deleted." << endl;
            }
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }

    bool checkFileForExistence(string filePath) {
        ifstream file(filePath);
        return file.good();
    }

    void setFilename(const string& path) {
        filename = path;
    }

    string getFilename() const {
        return filename;
    }
};