#include "ElementShortcuts.h"
#include <RmlUi/Core/Context.h>
#include <RmlUi/Core/Core.h>
#include <RmlUi/Core/ElementDocument.h>
#include <RmlUi/Core/Input.h>
#include <RmlUi/Core/SystemInterface.h>
#include "QClipboard/MemoryCells/MemoryCellManager.h"
#include "StringUtils.h"
#include "TranslationManager.h"
#include <format>

 // The applicaction's element context (declared in main.cpp).
extern Rml::Context* context;
TranslationManager* translatorShortCuts = TranslationManager::Instance();
 
 ElementShortcuts::ElementShortcuts(const Rml::String& tag) : Rml::Element(tag)
 {
   viewModel = new ShortCutsViewModel();
 }
 
 ElementShortcuts::~ElementShortcuts()
 {
   delete viewModel;
 }
 
 
 void ElementShortcuts::OnUpdate()
 {
   
   Rml::ElementDocument* document = context->GetDocument("shortcuts_menu");

   Rml::ElementList celdas;
   document->GetElementsByClassName(celdas, "c-cell");

   for(size_t i = 0; i < 3; i++){
      if(ClipboardInterface* cell = viewModel->getMemoryCell(i)){
         if(auto celda = celdas.at(i)) {
            celda->SetClassNames("c-cell");
            celda->GetChild(0)->SetInnerRML(translatorShortCuts->getString(std::format("list.{}" ,cell->name())));
            celda->GetChild(1)->SetInnerRML(StringUtils::escapeHtml(cell->text()).substr(0, 30));
         }
      }
      else {
         if(auto celda = celdas.at(i)) {
            celda->SetClassNames("c-cell c-none");
         }
      }
   }

   if(auto celda = celdas.at(viewModel->getSelectedCell()))
      celda->SetClassNames("c-cell c-glow-border");

}
 
 void ElementShortcuts::OnRender()
 {
    //Empty body
 }
 
 void ElementShortcuts::OnChildAdd(Rml::Element* element)
 {
    //Empty body
 }
 
 void ElementShortcuts::OnChildRemove(Rml::Element* element)
 {
    //Empty body
 }
 