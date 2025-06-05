#include "ExpandEvent.h"
#include "../EventManager.h"
#include <RmlUi_Backend.h>
#include <QGuiApplication>
#include <QScreen>

extern Rml::Context* context;

ExpandEvent::ExpandEvent(){
    QScreen* screen = QGuiApplication::primaryScreen();
	QRect screenGeometry = screen->geometry();
	int maxWindowWidth = 1920 * (2-0.95);
	int maxWindowHeight = 1080 * (2-0.875);
	window_width = screenGeometry.width() <= maxWindowWidth ? screenGeometry.width() * 0.95 : 1920;
	window_height = screenGeometry.height() <= maxWindowHeight ? screenGeometry.height() * 0.875 : 1080;
}

void ExpandEvent::handle(Rml::Event& event, Rml::StringList values) {
	Backend::SetBorder(true);
    Backend::MaximizeWindow(context);
    EventManager::ChangeDocument("main_window", "shortcuts_menu");
}