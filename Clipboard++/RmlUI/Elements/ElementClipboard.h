 #ifndef RMLUI_ELEMENTCLIPBOARD_H
 #define RMLUI_ELEMENTCLIPBOARD_H
 
 #include <RmlUi/Core/Element.h>

 class ElementClipboard : public Rml::Element {
 public:
     ElementClipboard(const Rml::String& tag);
     virtual ~ElementClipboard();
 
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
 