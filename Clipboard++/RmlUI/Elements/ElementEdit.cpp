#include "ElementEdit.h"
#include <RmlUi/Core/Context.h>
#include <RmlUi/Core/Core.h>
#include <RmlUi/Core/ElementDocument.h>
#include <RmlUi/Core/Input.h>
#include <RmlUi/Core/SystemInterface.h>
#include "StringUtils.h"
#include "TranslationManager.h"
#include <format>
#include "EventManager.h"
#include <GlobalFunctions.h>

 // The applicaction's element context (declared in main.cpp).
TranslationManager* translatorEdit = TranslationManager::Instance();
 
 ElementEdit::ElementEdit(const Rml::String& tag) : Rml::Element(tag)
 {
   viewModel = EditViewModel::Instance();
 }
 
 ElementEdit::~ElementEdit() {}
 
 void ElementEdit::OnUpdate()
 {
   
   Rml::ElementDocument* document = GlobalFunctions::context->GetDocument("edit");
    auto oldShortCut = document->GetElementById("old");
   if(viewModel->GetSelectedShortCut() && oldShortCut){
      oldShortCut->SetInnerRML(StringUtils::escapeHtml(viewModel->GetSelectedShortCut()->toString()));
   }

   if(auto newShortCut = document->GetElementById("new")){
      std::string content = KeyShortCut::toString(viewModel->GetNewShortCut());

      if(content == "")
         newShortCut->SetInnerRML(translatorEdit->getString("edit.placeholder"));
      else
         newShortCut->SetInnerRML(StringUtils::escapeHtml(content));
   }


}
 
 void ElementEdit::OnRender()
 {
    //Empty body
 }
 
 void ElementEdit::OnChildAdd(Rml::Element* element)
 {
   Rml::Element::OnChildAdd(element);

	if (element == this)
	{
		GetOwnerDocument()->AddEventListener(Rml::EventId::Keydown, this);
	}
 }
 
 void ElementEdit::OnChildRemove(Rml::Element* element)
 {
   Rml::Element::OnChildRemove(element);

   if (element == this) {
      if (Rml::Element* owner_document = GetOwnerDocument()) {
         owner_document->RemoveEventListener(Rml::EventId::Keydown, this);
      }
   }
 }

 void ElementEdit::ProcessEvent(Rml::Event& event) {
   if (event == Rml::EventId::Keydown) {
		bool key_down = (event == Rml::EventId::Keydown);
		Rml::Input::KeyIdentifier key_identifier = (Rml::Input::KeyIdentifier)event.GetParameter<int>("key_identifier", 0);
      viewModel->RegisterKey(key_identifier);
	}  
 }
 