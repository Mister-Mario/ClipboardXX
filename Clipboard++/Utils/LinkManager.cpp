#include "LinkManager.h"

#include <QDesktopServices>
#include <QUrl>
#include <QLocale>
#include <RmlUi/Core/Log.h>

void openHelp()  {
    QLocale default_locale = QLocale::system();
    QString locale_name = default_locale.name();
    QString link_string = "";
    if(locale_name.contains("es"))
        link_string = "https://github.com/Mister-Mario/Advanced-Clipboard/blob/main/help-guides/help-es_ES.md";
    else
        link_string = "https://github.com/Mister-Mario/Advanced-Clipboard/blob/main/help-guides/help-en_US.md";
    QUrl url(link_string);
    if (!QDesktopServices::openUrl(url)) {
        Rml::Log::Message(Rml::Log::LT_ERROR, "Can't open link '%s'", link_string);
    }
}