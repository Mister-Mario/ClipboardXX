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
#include <EventListenerInstancer.h>
#include <ElementClipboard.h>
#include <Shell.h>
#include <iostream>
#include <QGuiApplication>
#include <QClipboard>
#include <QGuiApplication>
#include <QScreen>
#include "QClipboard/ClipboardInterface.h"
#include "QClipboard/ClipboardAdapter.h"
#include "QClipboard/MemoryCells/MemoryCellManager.h"

void HandleFormSubmit(Rml::Event& event, void* /*user_data*/) {
    Rml::Element* target = event.GetCurrentElement();
    if (Rml::ElementForm* form = rmlui_dynamic_cast<Rml::ElementForm*>(target)) {
        Rml::String username = form->GetElementById("username")->GetAttribute<Rml::String>("value", "");
        std::cout << "Submitted username: " << username << std::endl;
    }
    event.StopPropagation();
}

Rml::Context* context = nullptr;
MemoryCellManager* memoryCellManager = nullptr;

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
	memoryCellManager = MemoryCellManager::Instance();
	memoryCellManager->initialize(new ClipboardAdapter(qClipboard), 2);

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

	// Register Invader's custom element and decorator instancers.
	Rml::ElementInstancerGeneric<ElementClipboard> element_instancer;
	Rml::Factory::RegisterElementInstancer("app", &element_instancer);

	// Initialise the event listener instancer and handlers.
	EventListenerInstancer event_listener_instancer;
	Rml::Factory::RegisterEventListenerInstancer(&event_listener_instancer);

	//EventManager::RegisterEventHandler("start_game", Rml::MakeUnique<EventHandlerStartGame>());

	Rml::ElementDocument* document = context->LoadDocument("assets/main.rml");
	if (!document){
		Rml::Shutdown();
		Backend::Shutdown();
		Shell::Shutdown();
		return -1;
	}
	
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