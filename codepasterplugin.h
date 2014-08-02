#ifndef CODEPASTER_H
#define CODEPASTER_H

#include "codepaster_global.h"

#include <extensionsystem/iplugin.h>

#include "settingspage.h"
#include "snippet.h"

namespace CodePaster {
namespace Internal {

class CodePasterPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "CodePaster.json")

public:
    CodePasterPlugin();
    ~CodePasterPlugin();

    bool initialize(const QStringList &arguments, QString *errorString);
    void extensionsInitialized();
    ShutdownFlag aboutToShutdown();

private slots:
    void triggerAction();
    void readSettings();

private:
    SettingsPage *settingsPage;
    QList<Snippet> snippets;
};

} // namespace Internal
} // namespace CodePaster

#endif // CODEPASTER_H
