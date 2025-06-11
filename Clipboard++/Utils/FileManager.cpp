#include "FileManager.h"
#include <tinyfiledialogs.h>
#include <fstream>                   
#include <iostream>

FileManager* FileManager::m_instance = nullptr;
TranslationManager* FileManager::translator = TranslationManager::Instance();

FileManager::FileManager(){}

FileManager* FileManager::Instance() {
    if(m_instance == nullptr) {
        m_instance = new FileManager();
    }
    return m_instance;
}

std::string FileManager::getLastFile() const{
    return m_lastFile;
}

std::string FileManager::searchImportFile(const char* title) {
    char const * filterPatterns[3] = { "*.txt", "*.csv", "*.tsv" };

    char const * filePath = tinyfd_openFileDialog(
        title, 
        "",                      
        3,                       
        filterPatterns,          
        "*.txt, *.csv, *.tsv",    
        0                       
    );    

    if (filePath) {
        std::string strFilePath(filePath);
        if (strFilePath.ends_with(".txt") || strFilePath.ends_with(".csv") || strFilePath.ends_with(".tsv")) {
            m_lastFile = strFilePath;
            return strFilePath;
        }
        else {
            showErrorDialog(translator->getString("file.dialog.message.extension").c_str());
        }
    }

    return "";
}

std::vector<std::string> FileManager::readFile(const char* filePath, char delimiter, bool showDialog) {
    std::ifstream fileStream(filePath);
    if (fileStream.is_open()) {
        std::vector<std::string> fields;
        std::string field;

        while (std::getline(fileStream, field, delimiter)) {
            fields.push_back(field);
        }
        fileStream.close();
        if(showDialog)
            showGoodDialog(translator->getString("file.dialog.message.import.correct").c_str());
        return fields;
    }
    else {
        if(showDialog)
            showErrorDialog(translator->getString("file.dialog.message.import.error").c_str());
        return {} ;
    }

}

std::string FileManager::searchExportFile(const char* title) {
    char const * filterPatterns[3] = { "*.txt", "*.csv", "*.tsv" };

    char const * filePath = tinyfd_saveFileDialog(
        title, 
        m_lastFile.length() == 0 ? "Clipboard++_Export.txt" : m_lastFile.c_str(),                      
        3,                       
        filterPatterns,          
        "*.txt, *.csv, *.tsv" 
    );    

    if (filePath) {
        std::string strFilePath(filePath);
        if (strFilePath.ends_with(".txt") || strFilePath.ends_with(".csv") || strFilePath.ends_with(".tsv")) {
            m_lastFile = strFilePath;
            return strFilePath;
        }
        else {
            showErrorDialog(translator->getString("file.dialog.message.extension").c_str());
        }
    }

    return "";
}

void FileManager::exportFile(const char* filePath, char delimiter, std::vector<std::string> content, bool showDialog) {
    std::ofstream exportFile(filePath);

    if (exportFile.is_open()) {
        for (const std::string& linea : content) {
            exportFile << linea << delimiter;
        }
        exportFile.close();
        if(showDialog)
            showGoodDialog(translator->getString("file.dialog.message.export.correct").c_str());

    } else {
        if(showDialog)
            showErrorDialog(translator->getString("file.dialog.message.export.error").c_str());
    }
}

void FileManager::showErrorDialog(const char* message) {
    tinyfd_messageBox(NULL, message, "ok", "error", 1); 
}
void FileManager::showGoodDialog(const char* message){   
    tinyfd_messageBox(NULL, message, "ok", "info", 1);
}