#ifndef I_FILE_MANAGER_H
#define I_FILE_MANAGER_H

#include <string>
#include <vector>

class IFileManager {
public:
    virtual ~IFileManager() = default;

    virtual std::string getLastFile() const = 0;
    virtual std::string searchImportFile(const char* title) = 0;
    virtual std::string searchExportFile(const char* title) = 0;
    virtual std::vector<std::string> readFile(const char* filePath, char delimiter, bool showDialog) = 0;
    virtual void exportFile(const char* filePath, char delimiter, std::vector<std::string> content, bool showDialog) = 0;
    virtual void showErrorDialog(const char* message) = 0;
    virtual void showGoodDialog(const char* message) = 0;
};

#endif