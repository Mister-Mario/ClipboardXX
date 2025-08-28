#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>
#include <vector>
#include "TranslationManager.h"
#include "IFileManager.h"

class FileManager : public IFileManager {
    public:
        static FileManager* Instance();
        virtual ~FileManager() = default;

        std::string getLastFile() const override;
        std::string searchImportFile(const char* title) override;
        std::string searchExportFile(const char* title) override;
        std::vector<std::string> readFile(const char* filePath, char delimiter, bool showDialog = true) override;
        void exportFile(const char* filePath, char delimiter, std::vector<std::string> content, bool showDialog = true) override;
        void showErrorDialog(const char* message) override;
        void showGoodDialog(const char* message) override;
    protected:
        FileManager();
    private:
        static FileManager* m_instance;
        std::string m_lastFile = "";  
        static TranslationManager* translator;
};

#endif