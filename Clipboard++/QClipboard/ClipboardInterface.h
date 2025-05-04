#ifndef CLIPBOARD_INTERFACE_H
#define CLIPBOARD_INTERFACE_H

#include <string>

class ClipboardInterface {
public:
    virtual ~ClipboardInterface() = default;
    virtual void setText(const std::string& text) = 0;
    virtual std::string text() const = 0;
    virtual std::string name() const = 0;
    virtual void clear() = 0;
    // Add other methods you need to test
};

#endif