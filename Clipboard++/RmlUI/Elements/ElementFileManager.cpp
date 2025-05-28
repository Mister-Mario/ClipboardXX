#include "ElementFileManager.h"
#include <RmlUi/Core/Context.h>
#include <RmlUi/Core/Core.h>
#include <RmlUi/Core/ElementDocument.h>
#include <RmlUi/Core/Input.h>
#include <RmlUi/Core/SystemInterface.h>
#include "QClipboard/MemoryCells/MemoryCellManager.h"
#include "StringUtils.h"
#include "FileManager.h"


// The applicaction's element context (declared in main.cpp).
extern Rml::Context* context;

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
   Rml::ElementDocument* fileManagerImport = context->GetDocument("file_manager_import");

   if (!fileManagerImport)
      return;

   if(Rml::Element* filePath = fileManagerImport->GetElementById("file_import_path")){
      std::string content = fileManager->getLastFile().substr(0, 100);
      filePath->SetInnerRML(Utils::escapeHtml(content));
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
 