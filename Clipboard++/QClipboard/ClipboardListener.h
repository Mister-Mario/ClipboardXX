#ifndef CLIPBOARD_LISTENER_H
#define CLIPBOARD_LISTENER_H

#include <QObject>
#include <QClipboard>
#include <queue>
#include <functional>

class ClipboardListener : public QObject
{
    Q_OBJECT

public:
    static ClipboardListener* Instance();
    void Initialize(QClipboard* clipboard);
    void AddCallback(const std::function<void(const std::string&)>& callback);
protected:
    ClipboardListener();
private slots:
    void OnSystemClipboardChanged();

private:
    QClipboard* m_clipboard;
    std::queue<std::function<void(const std::string&)>> m_actionQueue;
};

#endif