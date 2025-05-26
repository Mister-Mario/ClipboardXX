#include <gtest/gtest.h>
#include "TranslationManager.h"
#include <fstream>


class TranslationManagerTest : public ::testing::Test {
protected:

    void SetUp() override {
        translator->loadLanguage("es_ES");
    }

    TranslationManager* translator = TranslationManager::Instance();
};



TEST_F(TranslationManagerTest, GetReturnsValueForExistingKey) 
{
    const std::string key = "list.clipboard";
    const std::string expected_value = "Portapapeles";

    const std::string result = translator->getString(key);

    EXPECT_EQ(result, expected_value);
}

TEST_F(TranslationManagerTest, GetReturnsKeyItselfForNonExistentKey)
{
    const std::string non_existent_key = "this_key_does_not_exist";
    const std::string expected_value = "";

    const std::string result = translator->getString(non_existent_key);

    EXPECT_EQ(result, expected_value);
}