#ifndef STRING_UTILS_H
#define STRING_UTILS_H
#include <string>

namespace Utils {
    void replaceAll(std::string& str, const std::string& from, const std::string& to);
    std::string escapeHtml(const std::string& input);
}

#endif