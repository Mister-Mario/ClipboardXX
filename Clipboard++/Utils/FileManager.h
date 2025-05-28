#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>
#include <vector>

class FileManager {
    public:
        static FileManager* Instance();
        std::string getLastFile() const;
        std::string openFile();
        std::vector<std::string> readFile(const char* filePath, char delimiter);
    protected:
        FileManager();
    private:
        static FileManager* m_instance;
        std::string m_lastFile = "";  
};

#endif