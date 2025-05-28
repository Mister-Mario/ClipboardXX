#include "FileManager.h"
#include "TranslationManager.h"
#include <tinyfiledialogs.h>
#include <fstream>                   
#include <iostream>

std::string openFile() {
    char const * filterPatterns[3] = { "*.txt", "*.csv", "*.tsv" };

    TranslationManager* translator = TranslationManager::Instance(); 

    char const * filePath = tinyfd_openFileDialog(
        translator->getString("fileDialog.title").c_str(), 
        "",                      
        3,                       
        filterPatterns,          
        "*.txt, *.csv, *.tsv",    
        0                       
    );    

    if (filePath) {
        std::string strFilePath(filePath);
        if (strFilePath.ends_with(".txt") || strFilePath.ends_with(".csv") || strFilePath.ends_with(".tsv")) {
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

std::vector<std::string> readFile(const char* filePath, char delimiter) {
    std::ifstream fileStream(filePath);
    if (!fileStream.is_open()) {
        std::cerr << "Cannot open file" << std::endl;
        return {} ;
    }

    std::vector<std::string> fields;
    std::string field;

    while (std::getline(fileStream, field, delimiter)) {
        fields.push_back(field);
    }

    return fields;
}