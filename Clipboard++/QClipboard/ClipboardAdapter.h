#ifndef CLIPBOARD_ADAPTER_H
#define CLIPBOARD_ADAPTER_H

#include <ClipboardInterface.h>
#include <QClipboard>

class ClipboardAdapter : public ClipboardInterface {
public:
    explicit ClipboardAdapter(QClipboard* clipboard);
    virtual ~ClipboardAdapter() = default;
    
    void setText(const std::string& text) override;
    std::string text() const override;
    void clear() override;
    
private:
    QClipboard* m_clipboard;
};

#endif