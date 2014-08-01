#include "settingspage.h"
#include <QListWidget>

SettingsPage::SettingsPage(QObject *parent) :
    Core::IOptionsPage(parent)
{
    m_id = Core::Id("CodePasterSettings");
    m_category = Core::Id("CodePaster");
    m_displayName = tr("Code snippets");
    m_displayCategory = tr("CodePaster");
    m_categoryIcon = tr(":/todo");

    dialog = new SettingsDialog();
}

SettingsPage::~SettingsPage()
{
    delete dialog;
}

QWidget *SettingsPage::widget()
{
    return dialog;
}

void SettingsPage::apply()
{

}

void SettingsPage::finish()
{

}
