#include "ElementClipboard.h"
#include <RmlUi/Core/Context.h>
#include <RmlUi/Core/Core.h>
#include <RmlUi/Core/ElementDocument.h>
#include <RmlUi/Core/Input.h>
#include <RmlUi/Core/SystemInterface.h>
#include "QClipboard/MemoryCells/MemoryCellManager.h"
#include "StringUtils.h"

 // The applicaction's element context (declared in main.cpp).
extern Rml::Context* context;
 
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
    MemoryCellManager* memoryCellManager = MemoryCellManager::Instance();
    Rml::ElementDocument* document = context->GetDocument("main_window");
    if(Rml::Element* selectedCellNameElement = document->GetElementById("cell_name"))
        selectedCellNameElement->SetInnerRML(memoryCellManager->getSelectedCell()->name());
    if(Rml::Element* selectedCellConentElement = document->GetElementById("cell_content")){
        std::string content = memoryCellManager->getSelectedCell()->text().substr(0, 1000);
        selectedCellConentElement->SetInnerRML(Utils::escapeHtml(content));
    }

}
 
 void ElementClipboard::OnRender()
 {
    //Empty body
 }
 
 void ElementClipboard::OnChildAdd(Rml::Element* element)
 {
    //Empty body
 }
 
 void ElementClipboard::OnChildRemove(Rml::Element* element)
 {
    //Empty body
 }
 