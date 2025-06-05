#include "StringUtils.h"

namespace Utils {
    void replaceAll(std::string& str, const std::string& from, const std::string& to)
    {
        if(from.empty())
            return;
        size_t start_pos = 0;
        while((start_pos = str.find(from, start_pos)) != std::string::npos) {
            str.replace(start_pos, from.length(), to);
            start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
        }
    }

    std::string escapeHtml(const std::string& input)
    {
        std::string result = input;
        // Order matters here: & must be replaced first to avoid replacing parts of other entities
        replaceAll(result, "&", "&amp;");
        replaceAll(result, "<", "&lt;");
        replaceAll(result, ">", "&gt;");
        replaceAll(result, "\"", "&quot;");
        return result;
    }

    char getDelimiter(const Rml::String strDelimiter) {
    if (strDelimiter.length() > 1 && strDelimiter[0] == '\\') 
    {
        switch (strDelimiter[1]) 
        {
            case 't':
                return '\t';
                break;
            case 'n':
                return '\n';
                break;
            case 'r':
                return '\r';
                break;
            case '\\':
                return '\\';
                break;
            default:
                return strDelimiter[1];
                break;
        }
    }
    else 
    {
        return strDelimiter[0];
    }
}
}
