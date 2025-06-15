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
#include "ElementEdit.h"
#include "ClipboardListener.h"
#ifdef _WIN32
#include <windows.h>
#endif
#include "GlobalFunctions.h"
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
	ClipboardListener::Instance()->Initialize(qClipboard);
	KeyShortCutManager::Instance();
	MemoryCellManager::Instance()->initialize(new ClipboardAdapter(qClipboard, KeyShortCutManager::Instance()->GetPasteShortCut(0), KeyShortCutManager::Instance()->GetCopyShortCut(0)), 21);
	ShortCutsViewModel::Instance()->updateList("");

	QLocale default_locale = QLocale::system();
    QString locale_name = default_locale.name(); // "es_ES"
	TranslationManager* translator = TranslationManager::Instance(); 
    translator->loadLanguage(locale_name.toStdString());

	QIcon icon("assets/icons/Icono.png");
    QSystemTrayIcon trayIcon(icon);
    trayIcon.setToolTip(QString::fromStdString((translator->getString("title"))));
    QMenu menu;
    QAction *showAction = menu.addAction(QString::fromStdString((translator->getString("tray.show"))));
    menu.addSeparator();
    QAction *quitAction = menu.addAction(QString::fromStdString((translator->getString("tray.quit"))));
    trayIcon.setContextMenu(&menu);
    trayIcon.show(); 

	// Initializes the shell which provides common functionality used by the included samples.
	if (!Shell::Initialize()){
		std::cout << "Falla la Shell";
		return -1;
	}

	// Constructs the system and render interfaces, creates a window, and attaches the renderer.
	if (!Backend::Initialize(translator->getString("title").c_str(), 100, 100, false))
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
	GlobalFunctions::context = Rml::CreateContext("main", Rml::Vector2i(0, 0));
	if (!GlobalFunctions::context)
	{
		Rml::Shutdown();
		Backend::Shutdown();
		Shell::Shutdown();
		return -1;
	}
	GlobalFunctions::context->SetDensityIndependentPixelRatio(Backend::GetDPIScale());

	Backend::MaximizeWindow(GlobalFunctions::context);

	//Rml::Debugger::Initialise(GlobalFunctions::context);
	Shell::LoadFonts();

	Rml::ElementInstancerGeneric<ElementClipboard> element_clipboard_instancer;
	Rml::Factory::RegisterElementInstancer("app", &element_clipboard_instancer);

	Rml::ElementInstancerGeneric<ElementFileManager> element_file_instancer;
	Rml::Factory::RegisterElementInstancer("fileImport", &element_file_instancer);
	Rml::Factory::RegisterElementInstancer("fileExport", &element_file_instancer);

	Rml::ElementInstancerGeneric<ElementShortcuts> element_shortcuts_instancer;
	Rml::Factory::RegisterElementInstancer("shortcuts", &element_shortcuts_instancer);

	Rml::ElementInstancerGeneric<ElementEdit> element_edit_instancer;
	Rml::Factory::RegisterElementInstancer("edit", &element_edit_instancer);

	EventListenerInstancer event_listener_instancer;
	Rml::Factory::RegisterEventListenerInstancer(&event_listener_instancer);

	Rml::ElementDocument* main = GlobalFunctions::context->LoadDocument("assets/main.rml");
	Rml::ElementDocument* fileImport = GlobalFunctions::context->LoadDocument("assets/fileImport.rml");
	Rml::ElementDocument* fileExport = GlobalFunctions::context->LoadDocument("assets/fileExport.rml");
	Rml::ElementDocument* shortcutsMenu = GlobalFunctions::context->LoadDocument("assets/shortcutsMenu.rml"); 
	Rml::ElementDocument* edit = GlobalFunctions::context->LoadDocument("assets/edit.rml"); 
	if (!main || !fileImport || !fileExport || !shortcutsMenu || !edit){
		if (main) main->Close();
		if (fileImport) fileImport->Close();
		if (fileExport) fileExport->Close();
		if (shortcutsMenu) shortcutsMenu->Close();
		if (edit) edit->Close();
		Rml::Shutdown();
		Backend::Shutdown();
		Shell::Shutdown();
		return -1;
	}

	QObject::connect(showAction, &QAction::triggered, [shortcutsMenu]() {
		GlobalFunctions::showShortcuts(shortcutsMenu);
	});
    QObject::connect(quitAction, &QAction::triggered, &GlobalFunctions::quit);

	main->Show();
	GlobalFunctions::isWindowOpened= true;
	GlobalFunctions::running = true;

	while (GlobalFunctions::running)
	{
		QApplication::processEvents();

		if(GlobalFunctions::isWindowOpened && Backend::IsWindowShown()) {
			GlobalFunctions::isWindowOpened = Backend::ProcessEvents(GlobalFunctions::context, &Shell::ProcessKeyDownShortcuts, false);
			GlobalFunctions::context->Update();
			Backend::BeginFrame();
			GlobalFunctions::context->Render();
			Backend::PresentFrame();
			if(!GlobalFunctions::isWindowOpened) {
				GlobalFunctions::hideAllDocuments();
				Backend::HideWindow();
			}
		}
		
		if (g_hotkeyPressed.load()) {
            g_hotkeyPressed.store(false);
			GlobalFunctions::captureHWND();
			GlobalFunctions::showShortcuts(shortcutsMenu);
		}
	}

	if (main) main->Close();
    if (fileImport) fileImport->Close();
    if (fileExport) fileExport->Close();
    if (shortcutsMenu) shortcutsMenu->Close();
    if (edit) edit->Close();

	// Shutdown RmlUi.
	Rml::Shutdown();
	Backend::Shutdown();
	Shell::Shutdown();
	trayIcon.hide();

	return 0;
 }