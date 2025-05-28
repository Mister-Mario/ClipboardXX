#include <RmlUi/Core.h>
#include <RmlUi/Debugger.h>
#include <RmlUi_Backend.h>
#include <EventListenerInstancer.h>
#include <ElementFileManager.h>
#include <ElementClipboard.h>
#include <Shell.h>
#include <iostream>
#include <QGuiApplication>
#include <QClipboard>
#include <QGuiApplication>
#include <QScreen>
#include <QLocale>
#include "QClipboard/ClipboardInterface.h"
#include "QClipboard/ClipboardAdapter.h"
#include "QClipboard/MemoryCells/MemoryCellManager.h"
#include "Utils/TranslationManager.h"

Rml::Context* context = nullptr;

 #if defined RMLUI_PLATFORM_WIN32
	 #include <RmlUi_Include_Windows.h>
 int APIENTRY WinMain(HINSTANCE /*instance_handle*/, HINSTANCE /*previous_instance_handle*/, char* /*command_line*/, int /*command_show*/)
 #else
 int main(int /*argc*/, char** /*argv*/)
 #endif
 {
	int argc = 0;
	QGuiApplication app(argc, nullptr);
	QClipboard *qClipboard = QGuiApplication::clipboard();
	MemoryCellManager* memoryCellManager = MemoryCellManager::Instance();
	memoryCellManager->initialize(new ClipboardAdapter(qClipboard), 21);

	QLocale default_locale = QLocale::system();
    QString locale_name = default_locale.name(); // "es_ES"
	TranslationManager* translator = TranslationManager::Instance(); 
    translator->loadLanguage(locale_name.toStdString());

	// Get primary screen dimensions
	QScreen* screen = QGuiApplication::primaryScreen();
	QRect screenGeometry = screen->geometry();
	int maxWindowWidth = 1920 * (2-0.95);
	int maxWindowHeight = 1080 * (2-0.875);
	int window_width = screenGeometry.width() <= maxWindowWidth ? screenGeometry.width() * 0.95 : 1920;
	int window_height = screenGeometry.height() <= maxWindowHeight ? screenGeometry.height() * 0.875 : 1080;

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

	EventListenerInstancer event_listener_instancer;
	Rml::Factory::RegisterEventListenerInstancer(&event_listener_instancer);

	Rml::ElementDocument* main = context->LoadDocument("assets/main.rml");
	Rml::ElementDocument* fileSelector = context->LoadDocument("assets/file.rml");
	if (!main || !fileSelector){
		Rml::Shutdown();
		Backend::Shutdown();
		Shell::Shutdown();
		return -1;
	}
	
	fileSelector->Show();

	bool running = true;
	while (running)
	{

		running = Backend::ProcessEvents(context, &Shell::ProcessKeyDownShortcuts, true);
		
		context->Update();

		Backend::BeginFrame();
		context->Render();
		Backend::PresentFrame();
	}

	// Shutdown RmlUi.
	main->Close();
	fileSelector->Close();
	Rml::Shutdown();
	Backend::Shutdown();
	Shell::Shutdown();

	return 0;
 }