#include "codepasterplugin.h"
#include "codepasterconstants.h"

#include <coreplugin/icore.h>
#include <coreplugin/icontext.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/coreconstants.h>

#include <QAction>
#include <QMessageBox>
#include <QMainWindow>
#include <QMenu>

#include <QtPlugin>
#include <QMetaType>

#include <texteditor/basetexteditor.h>

using namespace CodePaster::Internal;

CodePasterPlugin::CodePasterPlugin()
{
    // Create your members
    pm = ExtensionSystem::PluginManager::instance();

    qRegisterMetaTypeStreamOperators<Snippet>("Snippet");
    qRegisterMetaTypeStreamOperators<SnippetList>("SnippetList");
    readSettings();

    sniffer = new Sniffer(Core::EditorManager::instance(), &snippets);
    connect(sniffer, SIGNAL(needPrint(int)), this, SLOT(printSnippet(int)));


}

CodePasterPlugin::~CodePasterPlugin()
{
    // Unregister objects from the plugin manager's object pool
    // Delete members

    //delete sniffer;

}

void CodePasterPlugin::printSnippet(int i)
{
    TextEditor::BaseTextEditor *editor = static_cast<TextEditor::BaseTextEditor *>(Core::EditorManager::instance()->currentEditor());
    editor->insert(snippets.at(i).getCode());

}

void CodePasterPlugin::readSettings()
{
    QSettings *settings = Core::ICore::instance()->settings();
    settings->beginGroup(tr("CodePasterPlugin"));
    snippets = settings->value(tr("Snippets")).value<SnippetList>();

    settings->endGroup();
}

bool CodePasterPlugin::initialize(const QStringList &arguments, QString *errorString)
{
    // Register objects in the plugin manager's object pool
    // Load settings
    // Add actions to menus
    // Connect to other plugins' signals
    // In the initialize function, a plugin can be sure that the plugins it
    // depends on have initialized their members.

    Q_UNUSED(arguments)
    Q_UNUSED(errorString)

    QAction *action = new QAction(tr("ClassDiagram action"), this);
    Core::Command *cmd = Core::ActionManager::registerAction(action, Constants::ACTION_ID,
                                                             Core::Context(Core::Constants::C_GLOBAL));
    cmd->setDefaultKeySequence(QKeySequence(tr("+Ctrl+Alt+A")));
    connect(action, SIGNAL(triggered()), this, SLOT(triggerAction()));


    settingsPage = new SettingsPage(this, &snippets);
    connect(settingsPage, SIGNAL(needToReadSettings()), this, SLOT(readSettings()));
    addAutoReleasedObject(settingsPage);


    connect(Core::EditorManager::instance(), SIGNAL(currentEditorChanged(Core::IEditor*)), this, SLOT(editorChanged()));


    return true;
}

void CodePasterPlugin::editorChanged()
{

    Core::EditorManager::instance()->currentEditor()->widget()->installEventFilter(sniffer);
}

void CodePasterPlugin::extensionsInitialized()
{
    // Retrieve objects from the plugin manager's object pool
    // In the extensionsInitialized function, a plugin can be sure that all
    // plugins that depend on it are completely initialized.
}

ExtensionSystem::IPlugin::ShutdownFlag CodePasterPlugin::aboutToShutdown()
{
    // Save settings
    // Disconnect from signals that are not needed during shutdown
    // Hide UI (if you add UI that is not in the main window directly)
    return SynchronousShutdown;
}

void CodePasterPlugin::triggerAction()
{

    QMessageBox::information(Core::ICore::mainWindow(),
                             tr("Action triggered"),
                             tr("This is an action from CodePaster."));
/*
    QList<QObject*> objects = pm->allObjects();
    QListWidget* listWidget = new QListWidget;
    Q_FOREACH(QObject* obj, objects)
    {
        QString objInfo = QString(tr("%1 (%2)"))
        .arg(obj->objectName())
        .arg(tr(obj->metaObject()->className()));
        listWidget->addItem(objInfo);
    }
    listWidget->show();



    if (editor)
    {
        TextEditor::BaseTextEditor *te = dynamic_cast<TextEditor::BaseTextEditor*> (editor);
        te->insert(tr("rger"));
    }

    Core::IEditor *editor = Core::EditorManager::instance()->currentEditor();
  */

}



Q_EXPORT_PLUGIN2(CodePaster, CodePasterPlugin)

