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
#include "Utils/LinkManager.h"
#include "Utils/FileManager.h"
#include "Utils/TranslationManager.h"
 
// The game's element context (declared in main.cpp).
extern Rml::Context* context;
MemoryCellManager* memoryCellManager = MemoryCellManager::Instance();
FileManager* fileManager = FileManager::Instance();
TranslationManager* translationManager = TranslationManager::Instance();


EventManager::EventManager() {}

EventManager::~EventManager() {}


void EventManager::ProcessEvent(Rml::Event& event, const Rml::String& value) {

    Rml::StringList commands;
    Rml::StringUtilities::ExpandString(commands, value, ';');
    for (size_t i = 0; i < commands.size(); ++i) {

        Rml::StringList values;
        Rml::StringUtilities::ExpandString(values, commands[i], ' ');

        if (values.empty())
            return;
        
        if (values[0] == "clear"){
            memoryCellManager->getSelectedCell()->clear();
        }

        if (values[0] == "insert") {
            auto cell = memoryCellManager->getSelectedCell();
            Rml::String input = "";
            if (auto element = event.GetCurrentElement()->GetOwnerDocument()->GetElementById("input")){
                input = element->GetAttribute<Rml::String>("value", "");
                element->SetAttribute("value", "");
            }
            cell->setText(input);       
        }

        if (values[0] == "load") {
            memoryCellManager->getMemoryCell(0)->setText(memoryCellManager->getSelectedCell()->text());
        }

        if (values[0] == "slot") {
            memoryCellManager->setSelectedCell(std::stoi(values[1]));
        }

        if (values[0] == "help") {
            openHelp();
        }

        if (values[0] == "import") {
            changeDocument("file_manager_import", "main_window");
        }

        if (values[0] == "import_search") {
            fileManager->openFile();
        }

        if (values[0] == "import_close") {
            changeDocument("main_window", "file_manager_import");
        }

        if (values[0] == "import_file") {
            if(auto delimiterInput = event.GetCurrentElement()->GetOwnerDocument()->GetElementById("delimiter_input")){
                Rml::String strDelimiter = delimiterInput->GetAttribute<Rml::String>("value", "");
                if(strDelimiter.length() != 0 || fileManager->getLastFile().length() != 0) {
                    const char* delimiter = strDelimiter.c_str();
                    char finalDelimiter;
                    if (strDelimiter.length() > 1 && strDelimiter[0] == '\\') 
                    {
                        switch (strDelimiter[1]) 
                        {
                            case 't':
                                finalDelimiter = '\t';
                                break;
                            case 'n':
                                finalDelimiter = '\n';
                                break;
                            case 'r':
                                finalDelimiter = '\r';
                                break;
                            case '\\':
                                finalDelimiter = '\\';
                                break;
                            default:
                                finalDelimiter = strDelimiter[1];
                                break;
                        }
                    }
                    else 
                    {
                        finalDelimiter = strDelimiter[0];
                    }
                    memoryCellManager->loadCells(fileManager->readFile(fileManager->getLastFile().c_str(), finalDelimiter));
                    changeDocument("main_window", "file_manager_import");
                }
                    
            }

        }
    }
}

void EventManager::changeDocument(const Rml::String& documentToShowId, const Rml::String& documentToHideId) {
    Rml::ElementDocument* documentToShow = context->GetDocument(documentToShowId);
    Rml::ElementDocument* documentToHide = context->GetDocument(documentToHideId);

    if (documentToShow && documentToHide) {
        documentToHide->Hide();
        documentToShow->Show();
    }
}