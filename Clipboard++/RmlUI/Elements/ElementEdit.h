 #ifndef RMLUI_ELEMENT_EDIT_H
 #define RMLUI_ELEMENT_EDIT_H
 
 #include <RmlUi/Core/Element.h>
 #include <RmlUi/Core/EventListener.h>
 #include <EditViewModel.h>
 #include <memory>

 class ElementEdit : public Rml::Element, public Rml::EventListener {
 public:
     ElementEdit(const Rml::String& tag);
     virtual ~ElementEdit();
 
     /// This will get called when we're added to the tree, which allows us to bind to events.
     void OnChildAdd(Rml::Element* element) override;
 
     /// This will get called when we're removed from the tree, which allows us to clean up the event listeners previously added.
     void OnChildRemove(Element* element) override;
  
     void ProcessEvent(Rml::Event& event) override;
 protected:
     /// Updates the game.
     void OnUpdate() override;
     /// Renders the game.
     void OnRender() override;
 private:
     EditViewModel* viewModel;
 };
 
 #endif
 