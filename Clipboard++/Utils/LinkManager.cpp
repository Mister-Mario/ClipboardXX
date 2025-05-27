#include "LinkManager.h"

#include <QDesktopServices>
#include <QUrl>
#include <QLocale>
#include <RmlUi/Core/Log.h>

void openHelp()  {
    QLocale default_locale = QLocale::system();
    QString locale_name = default_locale.name();
    QString link_string = QString("https://github.com/Mister-Mario/Advanced-Clipboard/blob/main/help-guides/help-%1.md").arg(locale_name);
    QUrl url(link_string);
    if (!QDesktopServices::openUrl(url)) {
        Rml::Log::Message(Rml::Log::LT_ERROR, "Can't open link '%s'", link_string);
    }
}