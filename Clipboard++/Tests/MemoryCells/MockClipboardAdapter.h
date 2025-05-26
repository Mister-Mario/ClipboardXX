#ifndef MOCK_CLIPBOARD_ADAPTER_H
#define MOCK_CLIPBOARD_ADAPTER_H

#include <gmock/gmock.h>
#include "ClipboardAdapter.h"

class MockClipboardAdapter : public ClipboardAdapter {
public:
    MockClipboardAdapter() : ClipboardAdapter(nullptr) {}
    MOCK_METHOD(void, setText, (const std::string& text), (override));
    MOCK_METHOD(std::string, text, (), (const, override));
    MOCK_METHOD(std::string, name, (), (const, override));
    MOCK_METHOD(void, clear, (), (override));
};

#endif