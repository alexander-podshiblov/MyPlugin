#include "settingspage.h"
#include <QListWidget>
#include <QSettings>
#include <coreplugin/icore.h>

SettingsPage::SettingsPage(QObject *parent, QList<Snippet> *s) :
    Core::IOptionsPage(parent)
{
    m_id = Core::Id("CodePasterSettings");
    m_category = Core::Id("CodePaster");
    m_displayName = tr("Code snippets");
    m_displayCategory = tr("CodePaster");
    m_categoryIcon = tr("");
    snippets = s;



}

SettingsPage::~SettingsPage()
{
    delete dialog;
}

QWidget *SettingsPage::widget()
{
    dialog = new SettingsDialog(0, snippets);
    settingsStatus = false;
    connect(dialog, SIGNAL(settingsChanged()), this, SLOT(settingsChanded()));

    return dialog;
}

void SettingsPage::settingsChanded()
{
    settingsStatus = true;
}

void SettingsPage::apply()
{
    if (settingsStatus)
    {
        QSettings *settings = Core::ICore::instance()->settings();
        settings->beginGroup(tr("CodePasterPlugin"));

        settings->setValue(tr("Snippets"), qVariantFromValue(*snippets));

        settings->endGroup();
        settings->sync();




        settingsStatus = false;
    }
}

void SettingsPage::finish()
{
    emit needToReadSettings();
}
