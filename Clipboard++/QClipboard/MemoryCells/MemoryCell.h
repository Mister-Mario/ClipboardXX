#ifndef MEMORY_CELL_H
#define MEMORY_CELL_H

#include <ClipboardInterface.h>
#include <QClipboard>


class MemoryCell : public ClipboardInterface {
public:
    explicit MemoryCell(std::string name, KeyShortCut* keyShortCutPaste, KeyShortCut* m_keyShortCutCopy);
    virtual ~MemoryCell() = default;
    
    void setText(const std::string& text) override;
    std::string text() const override;
    std::string name() const override;
    void clear() override;
    KeyShortCut* getKeyShortCutPaste() override;
    KeyShortCut* getKeyShortCutCopy() override;
    void setKeyShortCutPaste(std::vector<Rml::Input::KeyIdentifier> newShortCut) override;
    void setKeyShortCutCopy(std::vector<Rml::Input::KeyIdentifier> newShortCut) override;

private:
    std::string m_text;
    std::string m_name;
    KeyShortCut* m_keyShortCutPaste;
    KeyShortCut* m_keyShortCutCopy;
};

#endif