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
        manager->initialize(mock_adapter, 9);
    }

    void TearDown() override {
        manager->cleanup();
    }
};

TEST_F(MemoryCellManagerTest, InitializationCreatesCorrectNumberOfCells) {
    ASSERT_EQ(manager->getMemoryCellCount(), 9);
    ASSERT_EQ(manager->getMemoryCell(0), mock_adapter);
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