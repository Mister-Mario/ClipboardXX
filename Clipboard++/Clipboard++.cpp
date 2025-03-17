#include <RmlUi/Core.h>

class MyRenderInterface : public Rml::RenderInterface
{
    // RmlUi sends vertices, indices and draw commands through this interface for your
    // application to render how you'd like.
    /* ... */
}

struct ApplicationData {
    bool show_text = true;
    Rml::String animal = "dog";
} my_data;

int main(int argc, char** argv)
{
    // Initialize the window and graphics API being used, along with your game or application.

    /* ... */

    MyRenderInterface render_interface;

    // Install the custom interfaces.
    Rml::SetRenderInterface(&render_interface);

    // Now we can initialize RmlUi.
    Rml::Initialise();

    // Create a context to display documents within.
    Rml::Context* context =
        Rml::CreateContext("main", Rml::Vector2i(window_width, window_height));

    // Tell RmlUi to load the given fonts.
    Rml::LoadFontFace("LatoLatin-Regular.ttf");
    // Fonts can be registered as fallback fonts, as in this case to display emojis.
    Rml::LoadFontFace("NotoEmoji-Regular.ttf", true);

    // Set up data bindings to synchronize application data.
    if (Rml::DataModelConstructor constructor = context->CreateDataModel("animals"))
    {
        constructor.Bind("show_text", &my_data.show_text);
        constructor.Bind("animal", &my_data.animal);
    }

    // Now we are ready to load our document.
    Rml::ElementDocument* document = context->LoadDocument("hello_world.rml");
    document->Show();

    // Replace and style some text in the loaded document.
    Rml::Element* element = document->GetElementById("world");
    element->SetInnerRML(reinterpret_cast<const char*>(u8"🌍"));
    element->SetProperty("font-size", "1.5em");

    bool exit_application = false;
    while (!exit_application)
    {
        // We assume here that we have some way of updating and retrieving inputs internally.
        if (my_input->KeyPressed(KEY_ESC))
            exit_application = true;

        // Submit input events such as MouseMove and key events (not shown) to the context.
        if (my_input->MouseMoved())
            context->ProcessMouseMove(mouse_pos.x, mouse_pos.y, 0);

        // Update the context to reflect any changes resulting from input events, animations,
        // modified and added elements, or changed data in data bindings.
        context->Update();

        // Prepare the application for rendering, such as by clearing the window. This calls
        // into the RmlUi backend interface, replace with your own procedures as appropriate.
        Backend::BeginFrame();
        
        // Render the user interface. All geometry and other rendering commands are now
        // submitted through the render interface.
        context->Render();

        // Present the rendered content, such as by swapping the swapchain. This calls into
        // the RmlUi backend interface, replace with your own procedures as appropriate.
        Backend::PresentFrame();
    }

    Rml::Shutdown();

    return 0;
}