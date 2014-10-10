#ifndef ACCOUNT_DETAILS_H
#define ACCOUNT_DETAILS_H

#include <QDialog>

namespace Ui {
class account_details;
}

class account_details : public QDialog
{
    Q_OBJECT

public:
    explicit account_details(QWidget *parent = 0);
    ~account_details();

private:
    Ui::account_details *ui;
};

#endif // ACCOUNT_DETAILS_H
