#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>
#include <RmlUi/Core/Types.h>
#include <RmlUi/Core/Input.h>

namespace StringUtils {
    void replaceAll(std::string& str, const std::string& from, const std::string& to);
    std::string escapeHtml(const std::string& input);
    char getDelimiter(const Rml::String strDelimiter);
    std::string getStringFronEnum(Rml::Input::KeyIdentifier enumValue);
    Rml::Input::KeyIdentifier getEnumFronString(std::string string);
}

#endif