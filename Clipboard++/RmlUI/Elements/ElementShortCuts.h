 #ifndef RMLUI_ELEMENT_SHORTCUTS_H
 #define RMLUI_ELEMENT_SHORTCUTS_H
 
 #include <RmlUi/Core/Element.h>
 #include <RmlUi/Core/EventListener.h>
 #include <ShortCutsViewModel.h>
 #include <memory>

 class ElementShortcuts : public Rml::Element, public Rml::EventListener {
 public:
     ElementShortcuts(const Rml::String& tag);
     virtual ~ElementShortcuts();
 
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
     ShortCutsViewModel* viewModel;
 };
 
 #endif
 