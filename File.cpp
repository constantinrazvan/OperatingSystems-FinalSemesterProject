
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