#include "TranslationManager.h"
#include <fstream>
#include "nlohmann/json.hpp"
#include <RmlUi/Core/Log.h>

using json = nlohmann::json;

TranslationManager* TranslationManager::m_instance = nullptr;

TranslationManager::TranslationManager(){}

TranslationManager* TranslationManager::Instance() {
    if(m_instance == nullptr) {
        m_instance = new TranslationManager();
    }
    return m_instance;
}

bool TranslationManager::loadLanguage(const std::string& code) {
    std::string path_to_load = "assets/translations/" + code + ".json";

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

    // Parsear el JSON
    json data;
    try {
        data = json::parse(file_stream);
    } catch (json::parse_error& e) {
        Rml::Log::Message(Rml::Log::LT_ERROR, "Cannot parse file: %s\n", e.what());
        return false;
    }
    
    //Clean the map
    m_strings.clear();

    //Define a recursive function to transform header{ import ...} to header.import
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
    //Start the recursive from the top
    flattenJson(data, "");

    Rml::Log::Message(Rml::Log::LT_INFO, "Loaded %zu from %s\n", m_strings.size(), code.c_str());
    return true;
}

const std::string& TranslationManager::getString(const std::string& key) const {
    auto it = m_strings.find(key);
    if (it != m_strings.end()) {
        return it->second; //If found returns the translated text
    }

    return m_empty_string; //Returns empty
}