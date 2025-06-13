/*
 * This source file is part of RmlUi, the HTML/CSS Interface Middleware
 *
 * For the latest information, see http://github.com/mikke89/RmlUi
 *
 * Copyright (c) 2008-2010 CodePoint Ltd, Shift Technology Ltd
 * Copyright (c) 2019-2023 The RmlUi Team, and contributors
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include "EventManager.h"
#include <RmlUi/Core/Context.h>
#include <RmlUi/Core/ElementDocument.h>
#include <RmlUi/Core/ElementUtilities.h>
#include "QClipboard/MemoryCells/MemoryCellManager.h"
#include <format>
#include "Utils/StringUtils.h"
#include "Utils/FileManager.h"
#include "Utils/TranslationManager.h"
#include "Utils/TranslationManager.h"
#include "QClipboard/KeyShortCuts/KeyShortCutManager.h"
#include <ShortCutsViewModel.h>
#include <EditViewModel.h>
#include "Clipboard++Events/Main/ClearEvent.h"
#include "Clipboard++Events/Main/InsertEvent.h"
#include "Clipboard++Events/Main/LoadEvent.h"
#include "Clipboard++Events/Main/SlotEvent.h"
#include "Clipboard++Events/Main/HelpEvent.h"
#include "Clipboard++Events/Main/AutoCopyEvent.h"
#include "Clipboard++Events/Import/ImportSearchEvent.h"
#include "Clipboard++Events/Import/ImportEvent.h"
#include "Clipboard++Events/Import/ImportCloseEvent.h"
#include "Clipboard++Events/Import/ImportFileEvent.h"
#include "Clipboard++Events/Export/ExportSearchEvent.h"
#include "Clipboard++Events/Export/ExportEvent.h"
#include "Clipboard++Events/Export/ExportCloseEvent.h"
#include "Clipboard++Events/Export/ExportFileEvent.h"
#include "Clipboard++Events/ShortCutsMenu/ExpandEvent.h"
#include "Clipboard++Events/ShortCutsMenu/SearchEvent.h"
#include "Clipboard++Events/Edit/EditEvent.h"
#include "Clipboard++Events/Edit/EditCloseEvent.h"
#include "Clipboard++Events/Edit/EditDoneEvent.h"
#include "Clipboard++Events/Edit/ResetShortCutEvent.h"
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#include "Clipboard++Events/ShortCutsMenu/PasteEvent.h"
#include "Clipboard++Events/ShortCutsMenu/CopyEvent.h"
extern HWND lastWindow;
#endif
// The game's element context (declared in main.cpp).
extern Rml::Context* context;
MemoryCellManager* memoryCellManager = MemoryCellManager::Instance();
FileManager* fileManager = FileManager::Instance();
TranslationManager* translator = TranslationManager::Instance();
ShortCutsViewModel* shortCutsViewModel = ShortCutsViewModel::Instance();
KeyShortCutManager* keyShortCutsManager = KeyShortCutManager::Instance();
EditViewModel* editViewModel = EditViewModel::Instance();
std::map<std::string, std::unique_ptr<ClipboardEvent>> EventManager::events;

EventManager::EventManager() {}

EventManager::~EventManager() {}

void EventManager::LoadMap()
{
    events["clear"] = std::make_unique<ClearEvent>(memoryCellManager);
    events["insert"] = std::make_unique<InsertEvent>(memoryCellManager);
    events["load"] = std::make_unique<LoadEvent>(memoryCellManager);
    events["slot"] = std::make_unique<SlotEvent>(memoryCellManager);
    events["help"] = std::make_unique<HelpEvent>();
    events["import_search"] = std::make_unique<ImportSearchEvent>(fileManager, translator);
    events["import"] = std::make_unique<ImportEvent>();
    events["import_close"] = std::make_unique<ImportCloseEvent>();
    events["import_file"] = std::make_unique<ImportFileEvent>(memoryCellManager, fileManager, translator);
    events["export_search"] = std::make_unique<ExportSearchEvent>(fileManager, translator);
    events["export"] = std::make_unique<ExportEvent>();
    events["export_close"] = std::make_unique<ExportCloseEvent>();
    events["export_file"] = std::make_unique<ExportFileEvent>(memoryCellManager, fileManager, translator);
    events["expand"] = std::make_unique<ExpandEvent>();
    events["search"] = std::make_unique<SearchEvent>(shortCutsViewModel);
    #ifdef _WIN32
    events["paste"] = std::make_unique<PasteEvent>(lastWindow, memoryCellManager);
    events["copy"] = std::make_unique<CopyEvent>(lastWindow, memoryCellManager);
    #endif
    events["edit"] = std::make_unique<EditEvent>(memoryCellManager, editViewModel);
    events["edit_close"] = std::make_unique<EditCloseEvent>();
    events["edit_done"] = std::make_unique<EditDoneEvent>(memoryCellManager, keyShortCutsManager, editViewModel, translator,fileManager);
    events["reset"] = std::make_unique<ResetShortCutEvent>(editViewModel);
    events["autocopy"] = std::make_unique<AutoCopyEvent>(memoryCellManager);

}

void EventManager::ProcessEvent(Rml::Event &event, const Rml::String &value)
{
    if (events.empty())
        LoadMap();

    Rml::StringList commands;
    Rml::StringUtilities::ExpandString(commands, value, ';');
    for (size_t i = 0; i < commands.size(); ++i)
    {
        _ProcessCodeEvent(commands[i], &event);
    }
}

void EventManager::_ProcessCodeEvent(const Rml::String &value, Rml::Event* source_event) {
    if (events.empty())
        LoadMap();

    Rml::StringList values;
    Rml::StringUtilities::ExpandString(values, value, ' ');

    if (values.empty())
        return;

    auto it = events.find(values[0]);
    if (it != events.end()) {
        if(source_event)
            source_event->StopPropagation();
        it->second->handle(source_event, values);
    }

}

void EventManager::ChangeDocument(const Rml::String &documentToShowId, const Rml::String &documentToHideId)
{
    Rml::ElementDocument *documentToShow = context->GetDocument(documentToShowId);
    Rml::ElementDocument *documentToHide = context->GetDocument(documentToHideId);

    if (documentToShow && documentToHide)
    {
        documentToHide->Hide();
        documentToShow->Show();
    }
}
