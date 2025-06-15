#include "FileManager.h"
#include <tinyfiledialogs.h>
#include <fstream>              
#include <iostream>
#include "TranslationManager.h"

// Initialize static members.
FileManager* FileManager::m_instance = nullptr;
TranslationManager* FileManager::translator = TranslationManager::Instance();

/**
 * @brief Private constructor for the FileManager to enforce the singleton pattern.
 */
FileManager::FileManager(){}

/**
 * @brief Provides access to the singleton instance of the FileManager.
 * @return FileManager* A pointer to the singleton instance.
 */
FileManager* FileManager::Instance() {
    if(m_instance == nullptr) {
        m_instance = new FileManager();
    }
    return m_instance;
}

/**
 * @brief Gets the path of the last file that was successfully opened or saved.
 * @return std::string The full path to the last used file.
 */
std::string FileManager::getLastFile() const{
    return m_lastFile;
}

/**
 * @brief Opens a system dialog for the user to select a file for import.
 * @param title The title to display on the file dialog window.
 * @return std::string The path of the selected file, or an empty string if canceled or invalid.
 */
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

/**
 * @brief Reads the contents of a file, splitting it by a delimiter.
 * @param filePath The path to the file to read.
 * @param delimiter The character to use for splitting the content.
 * @param showDialog Whether to show a success/error message box after the operation.
 * @return std::vector<std::string> A vector of strings, each being a segment from the file.
 */
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

/**
 * @brief Opens a system "save as" dialog for the user to specify a file for export.
 * @param title The title to display on the file dialog window.
 * @return std::string The path of the chosen file, or an empty string if canceled or invalid.
 */
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

/**
 * @brief Writes a vector of strings to a file, separating them with a delimiter.
 * @param filePath The path to the file to write to.
 * @param delimiter The character to insert between each string.
 * @param content The vector of strings to write.
 * @param showDialog Whether to show a success/error message box after the operation.
 */
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

/**
 * @brief Displays a standard error message box.
 * @param message The error message to display.
 */
void FileManager::showErrorDialog(const char* message) {
    tinyfd_messageBox(NULL, message, "ok", "error", 1); 
}

/**
 * @brief Displays a standard informational message box.
 * @param message The message to display.
 */
void FileManager::showGoodDialog(const char* message){    
    tinyfd_messageBox(NULL, message, "ok", "info", 1);
}
