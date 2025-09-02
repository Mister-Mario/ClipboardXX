#include "ElementShortcuts.h"
#include <RmlUi/Core/Context.h>
#include <RmlUi/Core/Core.h>
#include <RmlUi/Core/ElementDocument.h>
#include <RmlUi/Core/Input.h>
#include <RmlUi/Core/SystemInterface.h>
#include "StringUtils.h"
#include "TranslationManager.h"
#include <format>
#include "ClipboardLogic/KeyShortCuts/KeyShortCutManager.h"
#include "EventManager.h"

TranslationManager* translatorShortCuts = TranslationManager::Instance();
extern Rml::Context* contextClipboardXX;

 ElementShortcuts::ElementShortcuts(const Rml::String& tag) : Rml::Element(tag)
 {
   viewModel = ShortCutsViewModel::Instance();
 }
 
 ElementShortcuts::~ElementShortcuts() {}
 
 void ElementShortcuts::OnUpdate()
 {
   
   Rml::ElementDocument* document = contextClipboardXX->GetDocument("shortcuts_menu");

   Rml::ElementList celdas;
   document->GetElementsByClassName(celdas, "c-cell");

   for(size_t i = 0; i < 3; i++){
      if(ClipboardInterface* cell = viewModel->getMemoryCell(i)){
         if(auto celda = celdas.at(i)) {
            celda->SetClassNames("c-cell");
            celda->GetChild(0)->SetInnerRML(translatorShortCuts->getString(std::format("list.{}" ,cell->name())));
            celda->GetChild(1)->SetInnerRML(StringUtils::escapeHtml(cell->text()).substr(0, 80));
            celda->GetChild(2)->SetAttribute("onclick", cell->getKeyShortCutCopy()->getEvent());
            celda->GetChild(3)->SetAttribute("onclick", cell->getKeyShortCutPaste()->getEvent());
         }
      }
      else {
         if(auto celda = celdas.at(i)) {
            celda->SetClassNames("c-cell c-none");
         }
      }
   }
   if(viewModel->hasSelectedCell())
      if(auto celda = celdas.at(viewModel->getSelectedCell()))
         celda->SetClassNames("c-cell c-glow-border");

   Rml::ElementList borders;
   document->GetElementsByClassName(borders, "c-cells__border");
   if(borders.size() == 2){
      if(!viewModel->canMoveUp())
         borders[0]->SetClassNames("c-cells__border c-none");
      else
         borders[0]->SetClassNames("c-cells__border");

      if(!viewModel->canMoveDown()) 
         borders[1]->SetClassNames("c-cells__border c-none");
      else
         borders[1]->SetClassNames("c-cells__border");
   }


}
 
 void ElementShortcuts::OnRender()
 {
    //Empty body
 }
 
 void ElementShortcuts::OnChildAdd(Rml::Element* element)
 {
   Rml::Element::OnChildAdd(element);

	if (element == this)
	{
		GetOwnerDocument()->AddEventListener(Rml::EventId::Keydown, this, true);
	}
 }
 
 void ElementShortcuts::OnChildRemove(Rml::Element* element)
 {
   Rml::Element::OnChildRemove(element);

   if (element == this) {
      if (Rml::Element* owner_document = GetOwnerDocument()) {
         owner_document->RemoveEventListener(Rml::EventId::Keydown, this, true);
      }

   }
 }

 void ElementShortcuts::ProcessEvent(Rml::Event& event) {
   if (event == Rml::EventId::Keydown) {
		bool key_down = (event == Rml::EventId::Keydown);
		Rml::Input::KeyIdentifier key_identifier = (Rml::Input::KeyIdentifier)event.GetParameter<int>("key_identifier", 0);

      if (key_identifier == Rml::Input::KI_ESCAPE) {

         event.StopImmediatePropagation();

         if (Rml::ElementDocument* owner_document = this->GetOwnerDocument()) {
            if (Rml::Element* focused_element = owner_document->GetFocusLeafNode()) {
               focused_element->Blur();
            }
         }
         return;
      }

      if (key_identifier == Rml::Input::KI_DOWN){
         event.StopImmediatePropagation();
         viewModel->moveDownIndex();
         return;
      }
      if (key_identifier == Rml::Input::KI_UP){
         event.StopImmediatePropagation();
         viewModel->moveUpIndex();
         return;
      }

      if(auto shortCut = KeyShortCutManager::Instance()->FilterShortCuts(key_identifier)){
         EventManager::_ProcessCodeEvent(shortCut->getEvent());
      }
	}  
 }
 