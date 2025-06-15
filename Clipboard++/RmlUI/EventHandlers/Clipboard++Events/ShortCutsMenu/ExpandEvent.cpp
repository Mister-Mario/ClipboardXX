#include "ExpandEvent.h"
#include "../EventManager.h"
#include <RmlUi_Backend.h>
#include <GlobalFunctions.h>

ExpandEvent::ExpandEvent(MemoryCellManager* memoryCellManager, ShortCutsViewModel* shortCutsViewModel) : m_memoryCellManager(memoryCellManager), m_shortCutsViewModel(shortCutsViewModel) {}

void ExpandEvent::handle(Rml::Event* event, Rml::StringList values) {
	if(m_shortCutsViewModel->hasSelectedCell())
		m_memoryCellManager->setSelectedCell(m_shortCutsViewModel->getSelectedCellIndex());
	Backend::SetBorder(true);
    Backend::MaximizeWindow(GlobalFunctions::context);
    EventManager::ChangeDocument("main_window", "shortcuts_menu");
}