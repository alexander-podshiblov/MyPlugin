#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include <QMessageBox>
#include <coreplugin/icore.h>
#include <QList>

SettingsDialog::SettingsDialog(QWidget *parent, QList<Snippet> *s) :
    QWidget(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    snippets = s;

    for (int i = 0; i < snippets->size(); i++)
    {
        QListWidgetItem *item = new QListWidgetItem();
        item->setFlags(item->flags() | Qt::ItemIsEditable);
        item->setText(snippets->at(i).getName());
        ui->listWidget->addItem(item);
    }

    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(addSnippet()));
    connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(delSnippet()));
    connect(ui->listWidget, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(editName(QListWidgetItem*)));
    connect(ui->clearButton, SIGNAL(clicked()), ui->keySequenceEdit, SLOT(clear()));
    connect(ui->keySequenceEdit, SIGNAL(editingFinished()), this, SLOT(addKeyToSnippet()));
    connect(ui->listWidget, SIGNAL(currentRowChanged(int)), this, SLOT(rowChanged(int)));
    connect(ui->textEdit, SIGNAL(textChanged()), this, SLOT(addCodeToSnippet()));


}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::addSnippet()
{
    QListWidgetItem *item = new QListWidgetItem();
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    ui->listWidget->addItem(item);
    ui->listWidget->editItem(item);

    Snippet *s = new Snippet;
    snippets->insert(snippets->size(), *s);

    emit settingsChanged();
}

void SettingsDialog::delSnippet()
{
    int row = ui->listWidget->currentRow();
    if(row < 0)
        return;

    delete ui->listWidget->takeItem(row);
    snippets->removeAt(row);

    emit settingsChanged();
}

void SettingsDialog::editName(QListWidgetItem *item)
{
    ui->listWidget->setCurrentItem(item);
    (*snippets)[ui->listWidget->currentRow()].setName(item->text());

    emit settingsChanged();
}


void SettingsDialog::addKeyToSnippet()
{
    if (snippets->size() == 0)
        return;
    (*snippets)[ui->listWidget->currentRow()].setKeySequence(ui->keySequenceEdit->keySequence());

    emit settingsChanged();
}

void SettingsDialog::rowChanged(int row)
{
    if(row < 0)
    {
        ui->keySequenceEdit->clear();
        ui->textEdit->clear();
    }
    else
    {
        ui->keySequenceEdit->setKeySequence(snippets->at(row).getKeySequence());
        ui->textEdit->setText(snippets->at(row).getCode());
    }
}

void SettingsDialog::addCodeToSnippet()
{
    if (snippets->size() == 0 || ui->listWidget->currentRow() == -1)
        return;
    (*snippets)[ui->listWidget->currentRow()].setCode(ui->textEdit->toPlainText());

    settingsChanged();
}


