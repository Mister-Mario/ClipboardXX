#ifndef MOCK_FILE_MANAGER_H
#define MOCK_FILE_MANAGER_H

#include <gmock/gmock.h>
#include "IFileManager.h"


class MockFileManager : public IFileManager {
public:
    MOCK_METHOD(std::string, getLastFile, (), (const, override));
    MOCK_METHOD(std::string, searchImportFile, (const char* title), (override));
    MOCK_METHOD(std::string, searchExportFile, (const char* title), (override));
    MOCK_METHOD(std::vector<std::string>, readFile, (const char* filePath, char delimiter, bool showDialog), (override));
    MOCK_METHOD(void, exportFile, (const char* filePath, char delimiter, std::vector<std::string> content, bool showDialog), (override));
    MOCK_METHOD(void, showErrorDialog, (const char* message), (override));
    MOCK_METHOD(void, showGoodDialog, (const char* message), (override));
};

#endif