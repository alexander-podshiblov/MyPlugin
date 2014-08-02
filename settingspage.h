#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

#include <QIcon>
#include <coreplugin/dialogs/ioptionspage.h>
#include <coreplugin/id.h>
#include "settingsdialog.h"

class SettingsPage : public Core::IOptionsPage
{
    Q_OBJECT

public:
    SettingsPage(QObject *parent, QList<Snippet> *s);
    ~SettingsPage();
/*
    Id id() const { return m_id; }
    QString displayName() const { return m_displayName; }
    Id category() const { return m_category; }
    QString displayCategory() const { return m_displayCategory; }
    QIcon categoryIcon() const { return QIcon(m_categoryIcon); }
*/
    //virtual bool matches(const QString &searchKeyWord) const;

    QWidget *widget();
    void apply();
    void finish();

public slots:
    void settingsChanded();

protected:
/*
    void setId(Id id) { m_id = id; }
    void setDisplayName(const QString &displayName) { m_displayName = displayName; }
    void setCategory(Id category) { m_category = category; }
    void setDisplayCategory(const QString &displayCategory) { m_displayCategory = displayCategory; }
    void setCategoryIcon(const QString &categoryIcon) { m_categoryIcon = categoryIcon; }

    Id m_id;
    Id m_category;
    QString m_displayName;
    QString m_displayCategory;
    QString m_categoryIcon;
*/
private:
    SettingsDialog *dialog;
    bool settingsStatus;
    QList<Snippet> *snippets;

signals:
    void needToReadSettings();

};

#endif // SETTINGSPAGE_H
