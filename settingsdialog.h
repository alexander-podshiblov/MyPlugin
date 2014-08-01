#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QWidget>
#include <QListWidget>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();

public slots:
    void addSnippet();
    void delSnippet();
    void editName(QListWidgetItem *item);


private:
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
