#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include <QMessageBox>
#include <coreplugin/icore.h>

SettingsDialog::SettingsDialog(QWidget *parent, QList<Snippet *> *s) :
    QWidget(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    snippets = s;

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
    snippets->insert(snippets->size(), s);
}

void SettingsDialog::delSnippet()
{
    int row = ui->listWidget->currentRow();
    Snippet *temp = snippets->at(row);
    snippets->removeAt(row);
    delete temp;
    delete ui->listWidget->takeItem(row);


    ui->textEdit->clear();

    for(int i = 0; i < snippets->size(); i++)
    {
        ui->textEdit->insertPlainText(tr("<") + snippets->at(i)->getName() + tr(">") + tr("\n"));
    }
}

void SettingsDialog::editName(QListWidgetItem *item)
{
    ui->listWidget->setCurrentItem(item);
    snippets->at(ui->listWidget->currentRow())->setName(item->text());
}

void SettingsDialog::addKeyToSnippet()
{
    snippets->at(ui->listWidget->currentRow())->setKeySequence(ui->keySequenceEdit->keySequence());
}

void SettingsDialog::rowChanged(int row)
{
    ui->keySequenceEdit->setKeySequence(snippets->at(row)->getKeySequence());
    ui->textEdit->setText(snippets->at(row)->getCode());
}

void SettingsDialog::addCodeToSnippet()
{
    snippets->at(ui->listWidget->currentRow())->setCode(ui->textEdit->toPlainText());
}


