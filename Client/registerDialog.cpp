#include "registerDialog.h"
#include "ui_registerDialog.h"
#include <QMessageBox>

RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    QMessageBox::information(this, "Регистрация", "Вы успешно зарегистрированы!");
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::onOkClicked() {}
void RegisterDialog::onCancelClicked() {}
