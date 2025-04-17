#ifndef MEMORY_CELL_H
#define MEMORY_CELL_H

#include <ClipboardInterface.h>
#include <QClipboard>

class MemoryCell : public ClipboardInterface {
public:
    explicit MemoryCell();
    virtual ~MemoryCell() = default;
    
    void setText(const std::string& text) override;
    std::string text() const override;
    void clear() override;

private:
    std::string m_text;
};

#endif