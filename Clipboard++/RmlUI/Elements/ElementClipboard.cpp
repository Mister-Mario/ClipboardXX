#include "ElementClipboard.h"
#include <RmlUi/Core/Context.h>
#include <RmlUi/Core/Core.h>
#include <RmlUi/Core/ElementDocument.h>
#include <RmlUi/Core/Input.h>
#include <RmlUi/Core/SystemInterface.h>
#include "QClipboard/MemoryCells/MemoryCellManager.h"
#include "StringUtils.h"
#include "TranslationManager.h"
#include <format>
#include <Clipboard++Events/Main/AutoCopyEvent.h>
#include <GlobalFunctions.h>

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
   
   TranslationManager* translator = TranslationManager::Instance();
   MemoryCellManager* memoryCellManager = MemoryCellManager::Instance();
   Rml::ElementDocument* document = GlobalFunctions::context->GetDocument("main_window");
   if(Rml::Element* selectedCellNameElement = document->GetElementById("cell_name"))
      selectedCellNameElement->SetInnerRML(translator->getString(std::format("list.{}" ,memoryCellManager->getSelectedCell()->name())));
   if(Rml::Element* selectedCellConentElement = document->GetElementById("cell_content")){
      std::string content = memoryCellManager->getSelectedCell()->text().substr(0, 1000);
      selectedCellConentElement->SetInnerRML(StringUtils::escapeHtml(content));
   }
   if(Rml::Element* selectedCellPaste = document->GetElementById("shortcut_paste")){
      selectedCellPaste->SetInnerRML(StringUtils::escapeHtml(memoryCellManager->getSelectedCell()->getKeyShortCutPaste()->toString()));
   }
   if(Rml::Element* selectedCellCopy = document->GetElementById("shortcut_copy")){
      selectedCellCopy->SetInnerRML(StringUtils::escapeHtml(memoryCellManager->getSelectedCell()->getKeyShortCutCopy()->toString())); 
   }

   if(Rml::Element* checkbox = document->GetElementById("checkbox")){
      if(AutoCopyEvent::isOn())
         checkbox->SetInnerRML("On"); 
      else  
         checkbox->SetInnerRML("Off");
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
 