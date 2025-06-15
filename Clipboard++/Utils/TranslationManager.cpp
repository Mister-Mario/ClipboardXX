#include "TranslationManager.h"
#include <fstream>
#include "nlohmann/json.hpp"
#include <RmlUi/Core/Log.h>

using json = nlohmann::json;

// Initialize the static singleton instance to nullptr.
TranslationManager* TranslationManager::m_instance = nullptr;

/**
 * @brief Private constructor for the TranslationManager to enforce the singleton pattern.
 */
TranslationManager::TranslationManager(){}

/**
 * @brief Provides access to the singleton instance of the TranslationManager.
 * @return TranslationManager* A pointer to the singleton instance.
 */
TranslationManager* TranslationManager::Instance() {
    if(m_instance == nullptr) {
        m_instance = new TranslationManager();
    }
    return m_instance;
}

/**
 * @brief Loads a language translation file.
 * @details This function attempts to load a JSON file corresponding to the provided language code.
 * If the specific language file is not found, it falls back to a default (en_US.json). It then
 * parses the JSON and flattens its structure into a key-value map (e.g., "header.title").
 * @param code The language code to load (e.g., "en_US", "es_ES").
 * @return bool True if a language file was successfully loaded and parsed, false otherwise.
 */
bool TranslationManager::loadLanguage(const std::string& code) {
    std::string path_to_load = "assets/translations/" + code + ".json";

    // Check if the requested language file exists. If not, prepare to load the default.
    std::ifstream test_file(path_to_load);
    if (!test_file.is_open()) {
        Rml::Log::Message(Rml::Log::LT_WARNING, "Translation file not found for '%s'. Falling back to default.", code.c_str());
        path_to_load = "assets/translations/en_US.json";
    }

    std::ifstream file_stream(path_to_load);
    if (!file_stream.is_open()) {
        Rml::Log::Message(Rml::Log::LT_ERROR, "Could not open fallback translation file: %s", path_to_load.c_str());
        return false;
    }

    // Parse the JSON data from the file.
    json data;
    try {
        data = json::parse(file_stream);
    } catch (json::parse_error& e) {
        Rml::Log::Message(Rml::Log::LT_ERROR, "Cannot parse file: %s\n", e.what());
        return false;
    }
    
    // Clear any previously loaded translations.
    m_strings.clear();

    // Define a recursive lambda to flatten the JSON structure.
    // This turns { "header": { "title": "..." } } into "header.title" -> "...".
    std::function<void(const json&, const std::string&)> flattenJson = 
        [&](const json& jsonObj, const std::string& parentKey) {
        for (auto& [key, value] : jsonObj.items()) {
            std::string currentKey = parentKey.empty() ? key : parentKey + "." + key;

            if (value.is_object()) {
                flattenJson(value, currentKey);
            } else if (value.is_string()) {
                m_strings[currentKey] = value.get<std::string>();
            }
        }
    };
    
    // Start the recursive flattening from the top level of the JSON.
    flattenJson(data, "");

    Rml::Log::Message(Rml::Log::LT_INFO, "Loaded %zu strings from %s\n", m_strings.size(), code.c_str());
    return true;
}

/**
 * @brief Retrieves a translated string by its key.
 * @param key The key of the string to retrieve (e.g., "header.title").
 * @return const std::string& The translated string if found; otherwise, a reference to an empty string.
 */
const std::string& TranslationManager::getString(const std::string& key) const {
    auto it = m_strings.find(key);
    if (it != m_strings.end()) {
        return it->second; // If found, return the translated text.
    }

    return m_empty_string; // Return empty string if the key is not found.
}
