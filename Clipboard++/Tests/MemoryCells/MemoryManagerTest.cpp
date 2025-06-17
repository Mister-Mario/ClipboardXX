#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "MemoryCells/MemoryCellManager.h"
#include "MockClipboardAdapter.h"

class MemoryCellManagerTest : public ::testing::Test {
protected:
    MemoryCellManager* manager;
    MockClipboardAdapter* mock_adapter;

    void SetUp() override {
        manager = MemoryCellManager::Instance();
        mock_adapter = new MockClipboardAdapter();
        manager->initialize(mock_adapter, 5);
    }

    void TearDown() override {
        manager->cleanup();
    }
};

TEST_F(MemoryCellManagerTest, InitializationCreatesCorrectNumberOfCells) {
    ASSERT_EQ(manager->getMemoryCellCount(), 5);
    ASSERT_EQ(manager->getMemoryCell(0), mock_adapter);
    ASSERT_NE(manager->getMemoryCell(4), nullptr);
    ASSERT_EQ(manager->getMemoryCell(5), nullptr);
}

TEST_F(MemoryCellManagerTest, CellSelectionWorksCorrectly) {
    const size_t target_index = 3;
    manager->setSelectedCell(target_index);
    ASSERT_EQ(manager->getSelectedCell(), manager->getMemoryCell(target_index));

    EXPECT_CALL(*mock_adapter, name())
        .WillOnce(::testing::Return("RealClipboard"));

    manager->setSelectedCell(0);
    std::string cell_name = manager->getSelectedCell()->name();
    EXPECT_EQ(cell_name, "RealClipboard");
}

TEST_F(MemoryCellManagerTest, AddMemoryCell) {
    size_t initial_count = manager->getMemoryCellCount();
    size_t new_index = manager->addMemoryCell();
    
    ASSERT_EQ(new_index, initial_count);
    ASSERT_EQ(manager->getMemoryCellCount(), initial_count + 1);
    ASSERT_NE(manager->getMemoryCell(new_index), nullptr);
}

TEST_F(MemoryCellManagerTest, LoadAndGetContents) {
    std::vector<std::string> new_contents = {"zero", "one"};
    manager->loadCells(new_contents);
    
    EXPECT_CALL(*mock_adapter, text()).WillOnce(::testing::Return("zero"));
    ASSERT_EQ(manager->getMemoryCell(1)->text(), "one");
    
    std::vector<std::string> retrieved_contents = manager->getContents();

    EXPECT_EQ(retrieved_contents[0], "zero");
    EXPECT_EQ(retrieved_contents[1], "one");
}

TEST_F(MemoryCellManagerTest, MoveContentsOneDown) {
    std::vector<std::string> new_contents = {"1", "2", "3", "4", "5"};
    manager->loadCells(new_contents);

    //Simulates a copy by the user
    EXPECT_CALL(*mock_adapter, text()).WillRepeatedly(::testing::Return("hola"));
    manager->moveContentsOneDown();

    std::vector<std::string> retrieved_contents = manager->getContents();

    EXPECT_EQ(retrieved_contents[0], "hola");
    EXPECT_EQ(retrieved_contents[1], "hola");
    EXPECT_EQ(retrieved_contents[4], "4");
}