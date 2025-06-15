#include "ClipboardXX.h"

#include <RmlUi/Debugger.h>
#include <RmlUi_Backend.h>
#include <Shell.h>
#include <QScreen>
#include <QLocale>
#include "QClipboard/ClipboardAdapter.h"
#include "QClipboard/MemoryCells/MemoryCellManager.h"
#include "QClipboard/HotKeyListener/HotKeyListener.h"
#include "QClipboard/KeyShortCuts/KeyShortCutManager.h"
#include "Utils/TranslationManager.h"
#include "ClipboardListener.h"


// Global variables used across the application
extern std::atomic<bool> g_hotkeyPressed;
Rml::Context* contextClipboardXX = nullptr;
HWND lastWindowClipboardXX = NULL;

/**
 * @brief Constructor for the ClipboardXX class.
 * @details Initializes the QApplication.
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 */
ClipboardXX::ClipboardXX(int argc, char* argv[]) {
    m_app = std::make_unique<QApplication>(argc, argv);
}

/**
 * @brief Destructor for the ClipboardXX class.
 * @details Calls the shutdown method to release all resources.
 */
ClipboardXX::~ClipboardXX() {
    shutdown();
}

/**
 * @brief Starts the main execution of the application.
 * @details First, it initializes the components and, if successful, enters the main loop.
 * @return int Returns 0 on successful execution, -1 if there was an initialization error.
 */
int ClipboardXX::Run() {
    if (!initialize()) {
        shutdown();
        return -1;
    }

    mainLoop();
    return 0;
}

/**
 * @brief Initializes all application subsystems.
 * @details Configures the hotkey listener, Qt clipboard, memory cell and shortcut managers, 
 * the translation system, the system tray icon, and the graphics backend with RmlUi.
 * @return bool Returns true if initialization was successful, false otherwise.
 */
bool ClipboardXX::initialize() {
    m_hotkeyListenerThread = std::thread(HotkeyListenerThread);
    m_hotkeyListenerThread.detach();

    QApplication::setQuitOnLastWindowClosed(false);
    QClipboard* qClipboard = QApplication::clipboard();
    ClipboardListener::Instance()->Initialize(qClipboard);
    KeyShortCutManager::Instance();
    MemoryCellManager::Instance()->initialize(new ClipboardAdapter(qClipboard, KeyShortCutManager::Instance()->GetPasteShortCut(0), KeyShortCutManager::Instance()->GetCopyShortCut(0)), 21);
    ShortCutsViewModel::Instance()->updateList("");

    QLocale default_locale = QLocale::system();
    QString locale_name = default_locale.name();
    TranslationManager* translator = TranslationManager::Instance();
    translator->loadLanguage(locale_name.toStdString());

    QIcon icon("assets/icons/Icono.png");
    m_trayIcon = new QSystemTrayIcon(icon, m_app.get());
    m_trayIcon->setToolTip(QString::fromStdString(translator->getString("title")));
    

    auto* menu = new QMenu();
    QAction* showAction = menu->addAction(QString::fromStdString(translator->getString("tray.show")));
    menu->addSeparator();
    QAction* quitAction = menu->addAction(QString::fromStdString(translator->getString("tray.quit")));
    m_trayIcon->setContextMenu(menu);
    m_trayIcon->show();

    if (!Shell::Initialize()) return false;
    if (!Backend::Initialize(translator->getString("title").c_str(), 100, 100, false)) return false;

    Rml::SetSystemInterface(Backend::GetSystemInterface());
    Rml::SetRenderInterface(Backend::GetRenderInterface());
    Rml::Initialise();

    contextClipboardXX = Rml::CreateContext("main", Rml::Vector2i(0, 0));
    if (!contextClipboardXX) return false;

    contextClipboardXX->SetDensityIndependentPixelRatio(Backend::GetDPIScale());
    Backend::MaximizeWindow();

    Shell::LoadFonts();
    
    // Register Instancers for custom RmlUi elements
    Rml::Factory::RegisterElementInstancer("app", &element_clipboard_instancer);
    Rml::Factory::RegisterElementInstancer("fileImport", &element_file_instancer);
    Rml::Factory::RegisterElementInstancer("fileExport", &element_file_instancer);
    Rml::Factory::RegisterElementInstancer("shortcuts", &element_shortcuts_instancer);
    Rml::Factory::RegisterElementInstancer("edit", &element_edit_instancer);

    Rml::Factory::RegisterEventListenerInstancer(&event_listener_instancer);
    
    // Load RML documents for the user interface
    m_doc_main = contextClipboardXX->LoadDocument("assets/main.rml");
    m_doc_fileImport = contextClipboardXX->LoadDocument("assets/fileImport.rml");
    m_doc_fileExport = contextClipboardXX->LoadDocument("assets/fileExport.rml");
    m_doc_shortcutsMenu = contextClipboardXX->LoadDocument("assets/shortcutsMenu.rml");
    m_doc_edit = contextClipboardXX->LoadDocument("assets/edit.rml");

    if (!m_doc_main || !m_doc_fileImport || !m_doc_fileExport || !m_doc_shortcutsMenu || !m_doc_edit) return false;

    // Connect system tray signals to slots
    QObject::connect(showAction, &QAction::triggered, this, &ClipboardXX::showShortcuts);
    QObject::connect(quitAction, &QAction::triggered, this, &ClipboardXX::quit);
    
    m_doc_main->Show();
    m_isWindowOpened = true;

    return true;
}

/**
 * @brief The main loop of the application.
 * @details Processes application events (Qt and RmlUi) and handles rendering logic 
 * and response to global keyboard shortcuts.
 */
void ClipboardXX::mainLoop() {
    m_running = true;
    while (m_running) {
        m_app->processEvents();

        if (m_isWindowOpened && Backend::IsWindowShown()) {
            m_isWindowOpened = Backend::ProcessEvents(contextClipboardXX, &Shell::ProcessKeyDownShortcuts, false);
            contextClipboardXX->Update();
            Backend::BeginFrame();
            contextClipboardXX->Render();
            Backend::PresentFrame();
            if (!m_isWindowOpened) {
                hideAllDocuments();
                Backend::HideWindow();
            }
        }
        
        if (g_hotkeyPressed.load()) {
            g_hotkeyPressed.store(false);
            captureHWND();
            showShortcuts();
        }
    }
}

/**
 * @brief Releases all resources used by the application.
 * @details Closes all RML documents, shuts down RmlUi, the backend, and the shell,
 * and hides the system tray icon.
 */
void ClipboardXX::shutdown() {
    if (m_doc_main) m_doc_main->Close();
    if (m_doc_fileImport) m_doc_fileImport->Close();
    if (m_doc_fileExport) m_doc_fileExport->Close();
    if (m_doc_shortcutsMenu) m_doc_shortcutsMenu->Close();
    if (m_doc_edit) m_doc_edit->Close();

    Rml::Shutdown();
    Backend::Shutdown();
    Shell::Shutdown();
    
    if(m_trayIcon) m_trayIcon->hide();
}

/**
 * @brief Captures the HWND (window handle) of the foreground window.
 * @details Only executes on Windows. It saves the handle of the window that was active 
 * before the clipboard application was shown.
 * @note This is useful for returning focus to the original window afterwards.
 */
void ClipboardXX::captureHWND() {
#ifdef _WIN32
    if (!Backend::IsWindowShown()) {
        lastWindowClipboardXX = GetForegroundWindow();
    }
#endif
}

/**
 * @brief Hides all RML documents loaded in the current context.
 */
void ClipboardXX::hideAllDocuments() {
    if (!contextClipboardXX) return;
    for (int i = 0; i < contextClipboardXX->GetNumDocuments(); ++i) {
        if(auto doc = contextClipboardXX->GetDocument(i)) doc->Hide();
    }
}

/**
 * @brief Displays the main window with the shortcuts menu.
 * @details If the window is not open, it creates it, adjusts its size, and shows it. 
 * If it's already open, it simply ensures the shortcuts document is visible.
 */
void ClipboardXX::showShortcuts() {
    if (!m_isWindowOpened) {
        m_doc_shortcutsMenu->Show();
        Backend::ModifyWindowSize(950/16.0f, 350/16.0f);
        Backend::SetBorder(false);
        Backend::ShowWindow();
        m_isWindowOpened = true;
    } else {
        hideAllDocuments();
        m_doc_shortcutsMenu->Show();
        Backend::ModifyWindowSize(950/16.0f, 350/16.0f);
        Backend::SetBorder(false);
        Backend::ShowWindow();
    }
}

/**
 * @brief Signals the end of the application's execution.
 * @details Sets the main loop's control variable to false to terminate it.
 */
void ClipboardXX::quit() {
    m_running = false;
}
