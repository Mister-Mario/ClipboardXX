#ifndef CLIPBOARD_INTERFACE_H
#define CLIPBOARD_INTERFACE_H

#include <QString>

class ClipboardInterface {
public:
    virtual ~ClipboardInterface() = default;
    virtual void setText(const QString& text) = 0;
    virtual QString text() const = 0;
    // Add other methods you need to test
};

#endif