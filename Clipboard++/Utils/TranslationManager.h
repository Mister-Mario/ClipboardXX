#ifndef TRANSLATION_MANAGER_H
#define TRANSLATION_MANAGER_H
#include <string>
#include <map>

class TranslationManager {
public:
    static TranslationManager* Instance();
    bool loadLanguage(const std::string& code);
    const std::string& getString(const std::string& key) const;
protected:
    TranslationManager();
private:
    static TranslationManager* m_instance;
    std::map<std::string, std::string> m_strings;
    //Empty string for not found keys
    const std::string m_empty_string = "";
};

#endif