#include "FileManager.h"
#include "TranslationManager.h"
#include <tinyfiledialogs.h>
#include <fstream>                   
#include <iostream>

std::string openFile() {
    char const * filterPatterns[2] = { "*.txt", "*.csv" };

    TranslationManager* translator = TranslationManager::Instance(); 

    char const * filePath = tinyfd_openFileDialog(
        translator->getString("fileDialog.title").c_str(), 
        "",                      
        2,                       
        filterPatterns,          
        "*.txt, *.csv",    
        0                       
    );

    

    if (filePath) {
        std::string strFilePath(filePath);
        if (strFilePath.ends_with(".txt") || strFilePath.ends_with(".csv")) {
            std::cout << "File selected: " << filePath << std::endl;
            return strFilePath;
        }
        else {
            std::cout << "Wrong extension: " << filePath << std::endl;
        }
    } else {
        std::cout << "File selection canceled" << std::endl;
    }

    return "";
}

void readFile(const char* filePath) {
    std::ifstream fileStream(filePath);
    if (!fileStream.is_open()) {
        std::cerr << "Cannot open file" << std::endl;
        return;
    }

    std::string line;
    int lineNumber = 1;
    while (std::getline(fileStream, line)) {
        std::cout << "Line " << lineNumber++ << ": " << line << std::endl;
    }
}