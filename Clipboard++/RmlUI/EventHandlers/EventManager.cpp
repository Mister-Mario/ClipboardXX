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
#include <ShortCutsViewModel.h>
#include "Clipboard++Events/ClearEvent.h"
#include "Clipboard++Events/InsertEvent.h"
#include "Clipboard++Events/LoadEvent.h"
#include "Clipboard++Events/SlotEvent.h"
#include "Clipboard++Events/HelpEvent.h"
#include "Clipboard++Events/ImportSearchEvent.h"
#include "Clipboard++Events/ImportEvent.h"
#include "Clipboard++Events/ImportCloseEvent.h"
#include "Clipboard++Events/ImportFileEvent.h"
#include "Clipboard++Events/ExportSearchEvent.h"
#include "Clipboard++Events/ExportEvent.h"
#include "Clipboard++Events/ExportCloseEvent.h"
#include "Clipboard++Events/ExportFileEvent.h"
#include "Clipboard++Events/ExpandEvent.h"
#include "Clipboard++Events/SearchEvent.h"

// The game's element context (declared in main.cpp).
extern Rml::Context *context;
MemoryCellManager *memoryCellManager = MemoryCellManager::Instance();
FileManager *fileManager = FileManager::Instance();
TranslationManager *translator = TranslationManager::Instance();
ShortCutsViewModel *shortCutsViewModel = ShortCutsViewModel::Instance();
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
}

void EventManager::ProcessEvent(Rml::Event &event, const Rml::String &value)
{
    if (events.empty())
        LoadMap();
    Rml::StringList commands;
    Rml::StringUtilities::ExpandString(commands, value, ';');
    for (size_t i = 0; i < commands.size(); ++i)
    {

        Rml::StringList values;
        Rml::StringUtilities::ExpandString(values, commands[i], ' ');

        if (values.empty())
            return;

        if (values[0] == "search")
        {
            ;
        }

        auto it = events.find(values[0]);
        if (it != events.end())
            it->second->handle(event, values);
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
