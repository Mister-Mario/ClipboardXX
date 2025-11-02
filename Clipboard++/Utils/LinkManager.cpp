#include "LinkManager.h"

#include <QDesktopServices>
#include <QUrl>
#include <QLocale>
#include <RmlUi/Core/Log.h>

/**
 * @brief Opens the appropriate help guide in the user's default web browser.
 * @details It determines the user's system language. If the language is Spanish,
 * it opens the Spanish help guide on GitHub; otherwise, it defaults to the
 * English version. It logs an error if the URL cannot be opened.
 */
void openHelp()  {
    QLocale default_locale = QLocale::system();
    QString locale_name = default_locale.name();
    QString link_string = "";

    // Select the appropriate URL based on the system's locale.
    if(locale_name.contains("es"))
        link_string = "https://github.com/Mister-Mario/ClipboardXX/wiki/help-es_ES";
    else
        link_string = "https://github.com/Mister-Mario/ClipboardXX/wiki/help-en_US";
    
    QUrl url(link_string);

    // Attempt to open the URL and log an error on failure.
    if (!QDesktopServices::openUrl(url)) {
        Rml::Log::Message(Rml::Log::LT_ERROR, "Can't open link '%s'", link_string.toStdString().c_str());
    }
}
