#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>


#include "KeyShortCuts/KeyShortCutManager.h"
#include "../Mocks/MockFileManager.h"

class KeyShortCutManagerTest : public ::testing::Test {
protected:
    MockFileManager mockFileManager;
    KeyShortCutManager* keyShortCutManager;

    void SetUp() override {
        keyShortCutManager = KeyShortCutManager::Instance();
    }
};

TEST_F(KeyShortCutManagerTest, InitializesWithDefaultAndFileShortcuts) {
    std::vector<std::string> fake_user_shortcuts = {"KI_LSHIFT+KI_A", "KI_LSHIFT+KI_B"};
    std::vector<std::string> fake_base_shortcuts = {"KI_LALT+KI_A", "KI_LALT+KI_B"};

    //StrEq is used so GTest checks that the same string content is used on readFile
    EXPECT_CALL(mockFileManager, readFile(::testing::StrEq("assets/conf/shortCuts.csv"), ';', false))
        .WillOnce(::testing::Return(fake_user_shortcuts));
    
    EXPECT_CALL(mockFileManager, readFile(::testing::StrEq("assets/conf/shortCutsBase.csv"), ';', false))
        .WillOnce(::testing::Return(fake_base_shortcuts));
    
    keyShortCutManager->Initialize(&mockFileManager);


    KeyShortCut* copy_shortcut_base = keyShortCutManager->GetCopyShortCut(0);
    ASSERT_NE(copy_shortcut_base, nullptr);
    EXPECT_EQ(copy_shortcut_base->getEvent(), "!copy 0");

    KeyShortCut* copy_shortcut_file = keyShortCutManager->GetCopyShortCut(1);
    ASSERT_NE(copy_shortcut_file, nullptr);
    EXPECT_EQ(copy_shortcut_file->getEvent(), "copy 1");

    KeyShortCut* paste_shortcut_base = keyShortCutManager->GetPasteShortCut(0);
    ASSERT_NE(paste_shortcut_base, nullptr);
    EXPECT_EQ(paste_shortcut_base->getEvent(), "!paste 0");

    KeyShortCut* paste_shortcut_file = keyShortCutManager->GetPasteShortCut(1);
    ASSERT_NE(paste_shortcut_file, nullptr);
    EXPECT_EQ(paste_shortcut_file->getEvent(), "paste 1");
    
    auto keys = copy_shortcut_file->getShortCut();
    ASSERT_EQ(keys.size(), 2);
    EXPECT_EQ(keys[0], Rml::Input::KI_LSHIFT);
    EXPECT_EQ(keys[1], Rml::Input::KI_A);
}

TEST_F(KeyShortCutManagerTest, CompletesSuccessfulUniqueSequence) {
    std::vector<std::string> fake_user_shortcuts = {};
    std::vector<std::string> fake_base_shortcuts = {};

    EXPECT_CALL(mockFileManager, readFile(::testing::StrEq("assets/conf/shortCuts.csv"), ';', false))
        .WillOnce(::testing::Return(fake_user_shortcuts));
    
    EXPECT_CALL(mockFileManager, readFile(::testing::StrEq("assets/conf/shortCutsBase.csv"), ';', false))
        .WillOnce(::testing::Return(fake_base_shortcuts));
    
    keyShortCutManager->Initialize(&mockFileManager);
    
    KeyShortCut* result = nullptr;
    result = keyShortCutManager->FilterShortCuts(Rml::Input::KI_LCONTROL);
    ASSERT_EQ(result, nullptr);

    result = keyShortCutManager->FilterShortCuts(Rml::Input::KI_C);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getEvent(), "!copy 0");
}

TEST_F(KeyShortCutManagerTest, CompletesAfterBadKey) {
    std::vector<std::string> fake_user_shortcuts = {"KI_LSHIFT+KI_A", "KI_LSHIFT+KI_B"};
    std::vector<std::string> fake_base_shortcuts = {"KI_LSHIFT+KI_A", "KI_LSHIFT+KI_B"};

    EXPECT_CALL(mockFileManager, readFile(::testing::StrEq("assets/conf/shortCuts.csv"), ';', false))
        .WillOnce(::testing::Return(fake_user_shortcuts));
    
    EXPECT_CALL(mockFileManager, readFile(::testing::StrEq("assets/conf/shortCutsBase.csv"), ';', false))
        .WillOnce(::testing::Return(fake_base_shortcuts));
    
    keyShortCutManager->Initialize(&mockFileManager);
    
    KeyShortCut* result = nullptr;
    result = keyShortCutManager->FilterShortCuts(Rml::Input::KI_LCONTROL);
    ASSERT_EQ(result, nullptr);

    result = keyShortCutManager->FilterShortCuts(Rml::Input::KI_A);
    ASSERT_EQ(result, nullptr);

    result = keyShortCutManager->FilterShortCuts(Rml::Input::KI_LSHIFT);
    ASSERT_EQ(result, nullptr);

    result = keyShortCutManager->FilterShortCuts(Rml::Input::KI_A);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getEvent(), "copy 1");
}

TEST_F(KeyShortCutManagerTest, CompletesAfterWaitingForLastKey) {
    std::vector<std::string> fake_user_shortcuts = {"KI_LSHIFT+KI_A+KI_B", "KI_LSHIFT+KI_B"};
    std::vector<std::string> fake_base_shortcuts = {"KI_LSHIFT+KI_A+KI_B", "KI_LSHIFT+KI_B"};

    EXPECT_CALL(mockFileManager, readFile(::testing::StrEq("assets/conf/shortCuts.csv"), ';', false))
        .WillOnce(::testing::Return(fake_user_shortcuts));
    
    EXPECT_CALL(mockFileManager, readFile(::testing::StrEq("assets/conf/shortCutsBase.csv"), ';', false))
        .WillOnce(::testing::Return(fake_base_shortcuts));
    
    keyShortCutManager->Initialize(&mockFileManager);
    
    KeyShortCut* result = nullptr;
    result = keyShortCutManager->FilterShortCuts(Rml::Input::KI_LSHIFT);
    ASSERT_EQ(result, nullptr);

    
    result = keyShortCutManager->FilterShortCuts(Rml::Input::KI_A);
    ASSERT_EQ(result, nullptr);

    result = keyShortCutManager->FilterShortCuts(Rml::Input::KI_B);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getEvent(), "copy 1");
}

TEST_F(KeyShortCutManagerTest, FilterDoesntModifyShortCutsList) {
    std::vector<std::string> fake_user_shortcuts = {"KI_LSHIFT+KI_A", "KI_LSHIFT+KI_B"};
    std::vector<std::string> fake_base_shortcuts = {"KI_LALT+KI_A", "KI_LALT+KI_B"};

    //StrEq is used so GTest checks that the same string content is used on readFile
    EXPECT_CALL(mockFileManager, readFile(::testing::StrEq("assets/conf/shortCuts.csv"), ';', false))
        .WillOnce(::testing::Return(fake_user_shortcuts));
    
    EXPECT_CALL(mockFileManager, readFile(::testing::StrEq("assets/conf/shortCutsBase.csv"), ';', false))
        .WillOnce(::testing::Return(fake_base_shortcuts));
    
    keyShortCutManager->Initialize(&mockFileManager);

    KeyShortCut* copy_shortcut_base = keyShortCutManager->GetCopyShortCut(0);
    ASSERT_NE(copy_shortcut_base, nullptr);
    EXPECT_EQ(copy_shortcut_base->getEvent(), "!copy 0");

    KeyShortCut* copy_shortcut_file = keyShortCutManager->GetCopyShortCut(1);
    ASSERT_NE(copy_shortcut_file, nullptr);
    EXPECT_EQ(copy_shortcut_file->getEvent(), "copy 1");

    KeyShortCut* paste_shortcut_base = keyShortCutManager->GetPasteShortCut(0);
    ASSERT_NE(paste_shortcut_base, nullptr);
    EXPECT_EQ(paste_shortcut_base->getEvent(), "!paste 0");

    KeyShortCut* paste_shortcut_file = keyShortCutManager->GetPasteShortCut(1);
    ASSERT_NE(paste_shortcut_file, nullptr);
    EXPECT_EQ(paste_shortcut_file->getEvent(), "paste 1");

    
    KeyShortCut* result = nullptr;
    result = keyShortCutManager->FilterShortCuts(Rml::Input::KI_LSHIFT);
    ASSERT_EQ(result, nullptr);


    KeyShortCut* copy_shortcut_base = keyShortCutManager->GetCopyShortCut(0);
    ASSERT_NE(copy_shortcut_base, nullptr);
    EXPECT_EQ(copy_shortcut_base->getEvent(), "!copy 0");

    KeyShortCut* copy_shortcut_file = keyShortCutManager->GetCopyShortCut(1);
    ASSERT_NE(copy_shortcut_file, nullptr);
    EXPECT_EQ(copy_shortcut_file->getEvent(), "copy 1");

    KeyShortCut* paste_shortcut_base = keyShortCutManager->GetPasteShortCut(0);
    ASSERT_NE(paste_shortcut_base, nullptr);
    EXPECT_EQ(paste_shortcut_base->getEvent(), "!paste 0");

    KeyShortCut* paste_shortcut_file = keyShortCutManager->GetPasteShortCut(1);
    ASSERT_NE(paste_shortcut_file, nullptr);
    EXPECT_EQ(paste_shortcut_file->getEvent(), "paste 1");
}
