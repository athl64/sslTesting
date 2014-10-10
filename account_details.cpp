#include "account_details.h"
#include "ui_account_details.h"

account_details::account_details(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::account_details)
{
    ui->setupUi(this);

    connect(ui->cancelButton,SIGNAL(clicked()),this,SLOT(close()));
}

account_details::~account_details()
{
    delete ui;
}
