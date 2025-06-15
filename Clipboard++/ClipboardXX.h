#ifndef CLIPBOARDXX_H
#define CLIPBOARDXX_H

#include <RmlUi/Core.h>
#include <QApplication>
#include <QSystemTrayIcon>
#include <QMenu>
#include <thread>
#include <atomic>
#include <memory>
#include <QObject>
#include <EventListenerInstancer.h>
#include <ElementFileManager.h>
#include <ElementClipboard.h>
#include <ElementShortCuts.h>
#include <ElementEdit.h>
#ifdef _WIN32
#include <windows.h>
#endif

class QClipboard;
extern Rml::Context* contextClipboardXX;
#ifdef _WIN32
extern HWND lastWindowClipboardXX;
#endif
class ClipboardXX : public QObject {
    Q_OBJECT
public:
    ClipboardXX(int argc, char* argv[]);
    ~ClipboardXX();
    int Run();
private:
    bool initialize();
    void mainLoop();
    void shutdown();

    void captureHWND();
    void hideAllDocuments();
    void showShortcuts();
    void quit();

    std::unique_ptr<QApplication> m_app;
    QSystemTrayIcon* m_trayIcon = nullptr;
    

    Rml::ElementDocument* m_doc_main = nullptr;
    Rml::ElementDocument* m_doc_fileImport = nullptr;
    Rml::ElementDocument* m_doc_fileExport = nullptr;
    Rml::ElementDocument* m_doc_shortcutsMenu = nullptr;
    Rml::ElementDocument* m_doc_edit = nullptr;

    Rml::ElementInstancerGeneric<ElementClipboard> element_clipboard_instancer;
	Rml::ElementInstancerGeneric<ElementFileManager> element_file_instancer;
	Rml::ElementInstancerGeneric<ElementShortcuts> element_shortcuts_instancer;
	Rml::ElementInstancerGeneric<ElementEdit> element_edit_instancer;
	EventListenerInstancer event_listener_instancer;

    bool m_running = true;
    bool m_isWindowOpened = false;

    std::thread m_hotkeyListenerThread;

};

#endif