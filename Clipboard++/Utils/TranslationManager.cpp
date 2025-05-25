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

bool TranslationManager::loadLanguage(const std::string& json_path) {
    std::ifstream file_stream(json_path);
    if (!file_stream.is_open()) {
        Rml::Log::Message(Rml::Log::LT_ERROR, "Cannot open translation file: %s\n", json_path.c_str());
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

    Rml::Log::Message(Rml::Log::LT_INFO, "Loaded %zu from %s\n", m_strings.size(), json_path.c_str());
    return true;
}

const std::string& TranslationManager::getString(const std::string& key) const {
    auto it = m_strings.find(key);
    if (it != m_strings.end()) {
        return it->second; //If found returns the translated text
    }

    return m_empty_string; //Returns empty
}