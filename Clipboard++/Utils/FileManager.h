#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>
#include <vector>
#include "TranslationManager.h"

class FileManager {
    public:
        static FileManager* Instance();
        std::string getLastFile() const;
        std::string searchImportFile(const char* title);
        std::string searchExportFile(const char* title);
        std::vector<std::string> readFile(const char* filePath, char delimiter);
        void exportFile(const char* filePath, char delimiter, std::vector<std::string> content);
        void showErrorDialog(const char* message);
        void showGoodDialog(const char* message);
    protected:
        FileManager();
    private:
        static FileManager* m_instance;
        std::string m_lastFile = "";  
        static TranslationManager* translator;
};

#endif