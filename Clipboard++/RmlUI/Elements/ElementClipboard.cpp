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

 #include "ElementClipboard.h"
 #include <RmlUi/Core/Context.h>
 #include <RmlUi/Core/Core.h>
 #include <RmlUi/Core/ElementDocument.h>
 #include <RmlUi/Core/Input.h>
 #include <RmlUi/Core/SystemInterface.h>
#include "QClipboard/MemoryCells/MemoryCellManager.h"
#include <format>

 // The applicaction's element context (declared in main.cpp).
extern Rml::Context* context;
extern MemoryCellManager* memoryCellManager;
 
 ElementClipboard::ElementClipboard(const Rml::String& tag) : Rml::Element(tag)
 {
    //Empty body
 }
 
 ElementClipboard::~ElementClipboard()
 {
    //Empty body
 }
 
 
 void ElementClipboard::OnUpdate()
 {
    Rml::ElementDocument* document = context->GetDocument("main_window");
    Rml::Element* clipboard_title_element = nullptr;
    size_t memoryCells = memoryCellManager->getMemoryCellCount();
    for(size_t i = 0; i < memoryCells; i++) {
        clipboard_title_element = document->GetElementById(std::format("cell_{}", i));
        if(clipboard_title_element){
            clipboard_title_element->SetInnerRML(memoryCellManager->getMemoryCell(i)->text());
        }
    }
}
 
 void ElementClipboard::OnRender()
 {
    //Empty body
 }
 
 void ElementClipboard::OnChildAdd(Rml::Element* element)
 {
    /* Rml::Element::OnChildAdd(element);
 
     if (element == this)
     {
         GetOwnerDocument()->AddEventListener(Rml::EventId::Load, this);
         GetOwnerDocument()->AddEventListener(Rml::EventId::Keydown, this);
         GetOwnerDocument()->AddEventListener(Rml::EventId::Keyup, this);
     }*/
 }
 
 void ElementClipboard::OnChildRemove(Rml::Element* element)
 {
    /* Rml::Element::OnChildRemove(element);
 
     if (element == this)
     {
         GetOwnerDocument()->RemoveEventListener(Rml::EventId::Load, this);
         GetOwnerDocument()->RemoveEventListener(Rml::EventId::Keydown, this);
         GetOwnerDocument()->RemoveEventListener(Rml::EventId::Keyup, this);
     } */
 }
 