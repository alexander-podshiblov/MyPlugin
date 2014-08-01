#include "settingsdialog.h"
#include "ui_settingsdialog.h"


SettingsDialog::SettingsDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);


    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(addSnippet()));
    connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(delSnippet()));
    connect(ui->listWidget, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(editName(QListWidgetItem*)));
    connect(ui->clearButton, SIGNAL(clicked()), ui->keySequenceEdit, SLOT(clear()));
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::addSnippet()
{
    QListWidgetItem *item = new QListWidgetItem();
    item->setText(tr("added"));
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    ui->listWidget->addItem(item);


}

void SettingsDialog::delSnippet()
{
    QListWidgetItem *item = ui->listWidget->currentItem();
    ui->listWidget->removeItemWidget(item);
}

void SettingsDialog::editName(QListWidgetItem *item)
{

}
