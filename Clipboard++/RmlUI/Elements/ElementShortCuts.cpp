#include "ElementShortcuts.h"
#include <RmlUi/Core/Context.h>
#include <RmlUi/Core/Core.h>
#include <RmlUi/Core/ElementDocument.h>
#include <RmlUi/Core/Input.h>
#include <RmlUi/Core/SystemInterface.h>
#include "StringUtils.h"
#include "TranslationManager.h"
#include <format>

 // The applicaction's element context (declared in main.cpp).
extern Rml::Context* context;
TranslationManager* translatorShortCuts = TranslationManager::Instance();
 
 ElementShortcuts::ElementShortcuts(const Rml::String& tag) : Rml::Element(tag)
 {
   viewModel = ShortCutsViewModel::Instance();
 }
 
 ElementShortcuts::~ElementShortcuts() {}
 
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
            celda->GetChild(1)->SetInnerRML(StringUtils::escapeHtml(cell->text()).substr(0, 80));
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
   Rml::Element::OnChildAdd(element);

	if (element == this)
	{
		GetOwnerDocument()->AddEventListener(Rml::EventId::Keydown, this);
	}
 }
 
 void ElementShortcuts::OnChildRemove(Rml::Element* element)
 {
   Rml::Element::OnChildRemove(element);

	if (element == this)
	{
		GetOwnerDocument()->RemoveEventListener(Rml::EventId::Keydown, this);
	}
 }

 void ElementShortcuts::ProcessEvent(Rml::Event& event) {
   if (event == Rml::EventId::Keydown) {
		bool key_down = (event == Rml::EventId::Keydown);
		Rml::Input::KeyIdentifier key_identifier = (Rml::Input::KeyIdentifier)event.GetParameter<int>("key_identifier", 0);

      if (key_identifier == Rml::Input::KI_DOWN)
         viewModel->moveDownIndex();
      if (key_identifier == Rml::Input::KI_UP)
         viewModel->moveUpIndex();
	}
 }
 