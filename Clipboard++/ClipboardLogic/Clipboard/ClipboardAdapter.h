#ifndef CLIPBOARD_ADAPTER_H
#define CLIPBOARD_ADAPTER_H

#include <Clipboard/ClipboardInterface.h>
#include <QClipboard>
#include <QObject>

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
    void setKeyShortCutPaste(std::vector<Rml::Input::KeyIdentifier> newShortCut) override;
    void setKeyShortCutCopy(std::vector<Rml::Input::KeyIdentifier> newShortCut) override;

private:
    QClipboard* m_clipboard;
    KeyShortCut* m_keyShortCutPaste;
    KeyShortCut* m_keyShortCutCopy;
};

#endif