#ifndef CLIPBOARD_INTERFACE_H
#define CLIPBOARD_INTERFACE_H

#include <string>
#include <KeyShortCuts/KeyShortCut.h>
class ClipboardInterface {
public:
    virtual ~ClipboardInterface() = default;
    virtual void setText(const std::string& text) = 0;
    virtual std::string text() const = 0;
    virtual std::string name() const = 0;
    virtual void clear() = 0;
    virtual KeyShortCut* getKeyShortCutPaste() = 0;
    virtual KeyShortCut* getKeyShortCutCopy() = 0;
};

#endif