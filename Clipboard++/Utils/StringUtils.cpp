#include "StringUtils.h"
#include <magic_enum/magic_enum.hpp>

// Specialization for magic_enum to define the valid range for the Rml::Input::KeyIdentifier enum.
namespace magic_enum::customize {
template <>
struct enum_range<Rml::Input::KeyIdentifier> {
    static constexpr int min = 0;
    static constexpr int max = 255; 
};
}


namespace StringUtils {
    /**
     * @brief Replaces all occurrences of a substring within a string.
     * @param str The string to modify.
     * @param from The substring to be replaced.
     * @param to The string to insert in place of the 'from' substring.
     */
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

    /**
     * @brief Escapes special HTML characters in a string.
     * @param input The raw string to escape.
     * @return std::string The HTML-escaped string.
     */
    std::string escapeHtml(const std::string& input)
    {
        std::string result = input;
        // Order matters here: & must be replaced first to avoid replacing parts of other entities
        replaceAll(result, "&", "&amp;");
        replaceAll(result, "<", "&lt;");
        replaceAll(result, ">", "&gt;");
        replaceAll(result, "\"", "&quot;");
        replaceAll(result, "{", "&#123;");
        replaceAll(result, "}", "&#125;");
        
        return result;
    }

    /**
     * @brief Interprets a string to get a single character delimiter.
     * @details Handles common escape sequences like \t, \n, \r, and \\.
     * If no escape sequence is found, it returns the first character of the string.
     * @param strDelimiter The string representation of the delimiter.
     * @return char The resulting character delimiter.
     */
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

    /**
     * @brief Converts a KeyIdentifier enum value to its string name.
     * @param enumValue The enum value to convert.
     * @return std::string The string representation of the enum (e.g., "KI_LCONTROL").
     */
    std::string getStringFronEnum(Rml::Input::KeyIdentifier enumValue) {
        return std::string(magic_enum::enum_name(enumValue));
    }

    /**
     * @brief Converts a string name back to a KeyIdentifier enum value.
     * @param string The string to convert (e.g., "KI_LCONTROL").
     * @return Rml::Input::KeyIdentifier The corresponding enum value, or KI_UNKNOWN if not found.
     */
    Rml::Input::KeyIdentifier getEnumFronString(std::string string) {
        auto tecla_opcional = magic_enum::enum_cast<Rml::Input::KeyIdentifier>(string);
        if (tecla_opcional.has_value()) {
            return tecla_opcional.value();
        }
        return Rml::Input::KI_UNKNOWN;
    }
}
