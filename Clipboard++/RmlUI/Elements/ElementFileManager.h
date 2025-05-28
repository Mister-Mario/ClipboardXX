 #ifndef RMLUI_ELEMENT_FILE_MANAGER_H
 #define RMLUI_ELEMENT_FILE_MANAGER_H
 
 #include <RmlUi/Core/Element.h>
 #include <RmlUi/Core/EventListener.h>

 class ElementFileManager : public Rml::Element {
 public:
     ElementFileManager(const Rml::String& tag);
     virtual ~ElementFileManager();
 
     /// This will get called when we're added to the tree, which allows us to bind to events.
     void OnChildAdd(Rml::Element* element) override;
 
     /// This will get called when we're removed from the tree, which allows us to clean up the event listeners previously added.
     void OnChildRemove(Element* element) override;
 
 protected:
     /// Updates the game.
     void OnUpdate() override;
     /// Renders the game.
     void OnRender() override;
 };
 
 #endif
 