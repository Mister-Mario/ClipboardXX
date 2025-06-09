#ifndef CLIPBOARD_ADAPTER_H
#define CLIPBOARD_ADAPTER_H

#include <ClipboardInterface.h>
#include <QClipboard>

class ClipboardAdapter : public ClipboardInterface {
public:
    explicit ClipboardAdapter(QClipboard* clipboard, KeyShortCut* keyShortCutPaste, KeyShortCut* m_keyShortCutCopy);
    virtual ~ClipboardAdapter() = default;
    
    void setText(const std::string& text) override;
    std::string text() const override;
    std::string name() const override;
    void clear() override;
    KeyShortCut* getKeyShortCutPaste() override;
    KeyShortCut* getKeyShortCutCopy() override;
    
private:
    QClipboard* m_clipboard;
    KeyShortCut* m_keyShortCutPaste;
    KeyShortCut* m_keyShortCutCopy;
};

#endif