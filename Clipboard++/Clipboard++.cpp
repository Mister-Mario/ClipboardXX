/*
 * Copyright (c) 2006 - 2008
 * Wandering Monster Studios Limited
 *
 * Any use of this program is governed by the terms of Wandering Monster
 * Studios Limited's Licence Agreement included with this program, a copy
 * of which can be obtained by contacting Wandering Monster Studios
 * Limited at info@wanderingmonster.co.nz.
 *
 */

 #include <RmlUi/Core.h>
 #include <RmlUi/Debugger.h>
 #include <RmlUi_Backend.h>
 #include <Shell.h>
 #include <iostream>
 #include <QGuiApplication>
 #include <QClipboard>

 #if defined RMLUI_PLATFORM_WIN32
	 #include <RmlUi_Include_Windows.h>
 int APIENTRY WinMain(HINSTANCE /*instance_handle*/, HINSTANCE /*previous_instance_handle*/, char* /*command_line*/, int /*command_show*/)
 #else
 int main(int /*argc*/, char** /*argv*/)
 #endif
 {
	int window_width = 1920;
	int window_height = 1080;

	int argc = 0;
	QGuiApplication app(argc, nullptr);
	QClipboard *clipboard = QGuiApplication::clipboard();
	QString originalText = clipboard->text();
	std::cout << qPrintable(originalText) << "\n";
	clipboard->setText("Hello there");
	originalText = clipboard->text();
	std::cout << qPrintable(originalText) << "\n";
	
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
	Rml::Context* context = Rml::CreateContext("main", Rml::Vector2i(window_width, window_height));
	if (!context)
	{
		std::cout << "Falla el context";
		Rml::Shutdown();
		Backend::Shutdown();
		Shell::Shutdown();
		return -1;
	}

	Rml::Debugger::Initialise(context);
	Rml::Debugger::SetVisible(true);
	Shell::LoadFonts();
	std::cout << "Ha cargado las fonts";

	Rml::ElementDocument* document = context->LoadDocument("assets/hello_world.rml");
	if (!document){
		Rml::Shutdown();
		Backend::Shutdown();
		Shell::Shutdown();
		return -1;
	}
	
	std::cout << "Ha cargado el documento";
	document->Show();


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
	Rml::Shutdown();
	Backend::Shutdown();
	Shell::Shutdown();

	return 0;
 }