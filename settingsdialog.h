#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QWidget>
#include <QListWidget>
#include <snippet.h>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent, QList<Snippet> *s);
    ~SettingsDialog();

public slots:
    void addSnippet();
    void delSnippet();
    void editName(QListWidgetItem *item);
    void addKeyToSnippet();
    void addCodeToSnippet();
    void rowChanged(int row);


private:
    Ui::SettingsDialog *ui;
    QList<Snippet> *snippets;

signals:
    void settingsChanged();

};

#endif // SETTINGSDIALOG_H
