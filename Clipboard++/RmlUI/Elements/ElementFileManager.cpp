#include "ElementFileManager.h"
#include <RmlUi/Core/Context.h>
#include <RmlUi/Core/Core.h>
#include <RmlUi/Core/ElementDocument.h>
#include <RmlUi/Core/Input.h>
#include <RmlUi/Core/SystemInterface.h>
#include "QClipboard/MemoryCells/MemoryCellManager.h"
#include "StringUtils.h"
#include "FileManager.h"
#include <GlobalFunctions.h>

ElementFileManager::ElementFileManager(const Rml::String& tag) : Rml::Element(tag)
{
   //Empty body
}

ElementFileManager::~ElementFileManager()
{
   //Empty body
}


void ElementFileManager::OnUpdate()
{
   FileManager* fileManager = FileManager::Instance();
    Rml::ElementDocument* activeDoc = nullptr;

    Rml::ElementDocument* importDoc = GlobalFunctions::context->GetDocument("file_manager_import");
    if (importDoc && importDoc->IsVisible()) {
        activeDoc = importDoc;
    } else {
        Rml::ElementDocument* exportDoc = GlobalFunctions::context->GetDocument("file_manager_export");
        if (exportDoc && exportDoc->IsVisible()) {
            activeDoc = exportDoc;
        }
    }

    if (!activeDoc) {
        return;
    }

   if(Rml::Element* filePath = activeDoc->GetElementById("file_path")){
      std::string content = fileManager->getLastFile().substr(0, 100);
      filePath->SetInnerRML(StringUtils::escapeHtml(content));
   }

}

void ElementFileManager::OnRender()
{
   //Empty body
}

void ElementFileManager::OnChildAdd(Rml::Element* element)
{
   //Empty body
}

void ElementFileManager::OnChildRemove(Rml::Element* element)
{
   //Empty body
}
 