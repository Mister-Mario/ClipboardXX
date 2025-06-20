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

 #ifndef RMLUI_EVENTMANAGER_H
 #define RMLUI_EVENTMANAGER_H
 
 #include <RmlUi/Core/ElementDocument.h>
 #include <RmlUi/Core/Event.h>
 #include <RmlUi/Core/Types.h>
 #include "Clipboard++Events/Clipboard++Event.h"
 
 class EventHandler;
 
 /**
     @author Peter Curry
  */
 
 class EventManager {
 public:
    /// Releases all event handlers registered with the manager.
    static void Shutdown();

    /// Processes an event coming through from RmlUi.
    /// @param[in] event The RmlUi event that spawned the application event.
    /// @param[in] value The application-specific event value.
    static void ProcessEvent(Rml::Event& event, const Rml::String& value);
    static void LoadMap();
    static void ChangeDocument(const Rml::String& document_to_show, const Rml::String& document_to_hide);

    //Added methods
    
    static void _ProcessCodeEvent(const Rml::String &value, Rml::Event* source_event = nullptr);

 private:
     EventManager();
     ~EventManager();
    
    static std::map<std::string, std::unique_ptr<ClipboardEvent>> events;
     
 };
 
 #endif
 