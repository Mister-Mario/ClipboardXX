#include <RmlUi/Core.h>
#include <RmlUi/Debugger.h>
#include <RmlUi_Backend.h>
#include <RmlUi_Renderer_GL3.h>
#include <EventListenerInstancer.h>
#include <ElementFileManager.h>
#include <ElementClipboard.h>
#include <ElementShortCuts.h>
#include <Shell.h>
#include <iostream>
#include <QApplication>
#include <QClipboard>
#include <QScreen>
#include <QLocale>
#include "QClipboard/ClipboardInterface.h"
#include "QClipboard/ClipboardAdapter.h"
#include "QClipboard/MemoryCells/MemoryCellManager.h"
#include "QClipboard/HotKeyListener/HotKeyListener.h"
#include "QClipboard/KeyShortCuts/KeyShortCutManager.h"
#include "Utils/TranslationManager.h"
#include <QSystemTrayIcon>
#include <QMenu>
#include <QIcon>
#include <thread>
#include <atomic> 
#ifdef _WIN32
#include <windows.h>
HWND lastWindow = NULL;
#endif

Rml::Context* context = nullptr;
bool isWindowOpened = false;
bool running = true;

void captureHWND() {
	#ifdef _WIN32
	if(!isWindowOpened)
		lastWindow = GetForegroundWindow();
    #endif
}

void showShortcuts(Rml::ElementDocument* shortcuts) {
	if(!isWindowOpened) {
		shortcuts->Show();
		Backend::ModifyWindowSize(context, 1200, 500);
		Backend::SetBorder(false);
		Backend::ShowWindow();
		isWindowOpened = true;
	}
	else {
		Backend::ShowWindow();
	}
}

void quit() {
	running = false;
}

 #if defined RMLUI_PLATFORM_WIN32
	 #include <RmlUi_Include_Windows.h>
 int APIENTRY WinMain(HINSTANCE /*instance_handle*/, HINSTANCE /*previous_instance_handle*/, char* /*command_line*/, int /*command_show*/)
 #else
 int main(int /*argc*/, char** /*argv*/)
 #endif
 {
	std::thread listener(HotkeyListenerThread);
    listener.detach();

	int argc = 0;
	QApplication app(argc, nullptr);
	QApplication::setQuitOnLastWindowClosed(false);
	QClipboard *qClipboard = QApplication::clipboard();

	KeyShortCutManager::Instance();
	MemoryCellManager::Instance()->initialize(new ClipboardAdapter(qClipboard, KeyShortCutManager::Instance()->GetPasteShortCut(0), KeyShortCutManager::Instance()->GetCopyShortCut(0)), 21);
	ShortCutsViewModel::Instance()->updateList("");

	QLocale default_locale = QLocale::system();
    QString locale_name = default_locale.name(); // "es_ES"
	TranslationManager* translator = TranslationManager::Instance(); 
    translator->loadLanguage(locale_name.toStdString());

	// Get primary screen dimensions
	QScreen* screen = QApplication::primaryScreen();
	QRect screenGeometry = screen->geometry();
	int maxWindowWidth = 1920 * (2-0.95);
	int maxWindowHeight = 1080 * (2-0.875);
	int window_width = screenGeometry.width() <= maxWindowWidth ? screenGeometry.width() * 0.95 : 1920;
	int window_height = screenGeometry.height() <= maxWindowHeight ? screenGeometry.height() * 0.875 : 1080;

	QIcon icon("assets/icons/Icono.png");
    QSystemTrayIcon trayIcon(icon);
    trayIcon.setToolTip("Mi App (RmlUI + Hotkey)");
    QMenu menu;
    QAction *showAction = menu.addAction("Mostrar");
    menu.addSeparator();
    QAction *quitAction = menu.addAction("Salir");
    trayIcon.setContextMenu(&menu);
    trayIcon.show(); 

	// Initializes the shell which provides common functionality used by the included samples.
	if (!Shell::Initialize()){
		std::cout << "Falla la Shell";
		return -1;
	}

	// Constructs the system and render interfaces, creates a window, and attaches the renderer.
	if (!Backend::Initialize("Clipboard++", window_width, window_height, true))
	{
		std::cout << "Falla el Backend";
		Shell::Shutdown();
		return -1;
	}

	// Install the custom interfaces constructed by the backend before initializing RmlUi.
	Rml::SetSystemInterface(Backend::GetSystemInterface());
	Rml::SetRenderInterface(Backend::GetRenderInterface());



	// RmlUi initialisation.
	Rml::Initialise();

	// Create the main RmlUi context.
	context = Rml::CreateContext("main", Rml::Vector2i(window_width, window_height));
	if (!context)
	{
		std::cout << "Falla el context";
		Rml::Shutdown();
		Backend::Shutdown();
		Shell::Shutdown();
		return -1;
	}

	Rml::Debugger::Initialise(context);
	Shell::LoadFonts();

	Rml::ElementInstancerGeneric<ElementClipboard> element_clipboard_instancer;
	Rml::Factory::RegisterElementInstancer("app", &element_clipboard_instancer);

	Rml::ElementInstancerGeneric<ElementFileManager> element_file_instancer;
	Rml::Factory::RegisterElementInstancer("fileImport", &element_file_instancer);
	Rml::Factory::RegisterElementInstancer("fileExport", &element_file_instancer);

	Rml::ElementInstancerGeneric<ElementShortcuts> element_shortcuts_instancer;
	Rml::Factory::RegisterElementInstancer("shortcuts", &element_shortcuts_instancer);

	EventListenerInstancer event_listener_instancer;
	Rml::Factory::RegisterEventListenerInstancer(&event_listener_instancer);

	Rml::ElementDocument* main = context->LoadDocument("assets/main.rml");
	Rml::ElementDocument* fileImport = context->LoadDocument("assets/fileImport.rml");
	Rml::ElementDocument* fileExport = context->LoadDocument("assets/fileExport.rml");
	Rml::ElementDocument* shortcutsMenu = context->LoadDocument("assets/shortcutsMenu.rml"); 
	Rml::ElementDocument* edit = context->LoadDocument("assets/edit.rml"); 
	if (!main || !fileImport || !fileExport || !shortcutsMenu || !edit){
		Rml::Shutdown();
		Backend::Shutdown();
		Shell::Shutdown();
		return -1;
	}

	QObject::connect(showAction, &QAction::triggered, [shortcutsMenu]() {
		showShortcuts(shortcutsMenu);
	});
    QObject::connect(quitAction, &QAction::triggered, &quit);

	main->Show();
	isWindowOpened= true;
	running = true;
	while (running)
	{
		QApplication::processEvents();

		if(isWindowOpened && Backend::IsWindowShown()) {		
			isWindowOpened = Backend::ProcessEvents(context, &Shell::ProcessKeyDownShortcuts, true);
			context->Update();
			Backend::BeginFrame();
			context->Render();
			Backend::PresentFrame();
			if(!isWindowOpened) {
				main->Hide();
				fileImport->Hide();
				fileExport->Hide();
				edit->Hide();
				Backend::HideWindow();
			}
		}
		
		if (g_hotkeyPressed.load()) {
            g_hotkeyPressed.store(false);
			captureHWND();
			showShortcuts(shortcutsMenu);
        }
	}

	// Shutdown RmlUi.
	Rml::Shutdown();
	Backend::Shutdown();
	Shell::Shutdown();
	trayIcon.hide();

	return 0;
 }