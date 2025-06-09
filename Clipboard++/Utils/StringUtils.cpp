#include "StringUtils.h"
#include <magic_enum/magic_enum.hpp>
namespace magic_enum::customize {
template <>
struct enum_range<Rml::Input::KeyIdentifier> {
    static constexpr int min = 0;
    static constexpr int max = 255; 
};
}


namespace StringUtils {
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

    std::string getStringFronEnum(Rml::Input::KeyIdentifier enumValue) {
        return std::string(magic_enum::enum_name(enumValue));
    }

    Rml::Input::KeyIdentifier getEnumFronString(std::string string) {
        auto tecla_opcional = magic_enum::enum_cast<Rml::Input::KeyIdentifier>(string);
        if (tecla_opcional.has_value()) {
            return tecla_opcional.value();
        }
        return Rml::Input::KI_UNKNOWN;
    }
}






