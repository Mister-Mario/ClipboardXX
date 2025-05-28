#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>
#include <vector>

std::string openFile();
std::vector<std::string> readFile(const char* filePath, char delimiter);

#endif