#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QSslSocket>
#include <QtNetwork/QAbstractSocket>
#include <QtNetwork/QSslCipher>
#include <QDebug>
#include <QMessageBox>
#include "account_details.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private:
    QSslSocket *sslClient;
    account_details *setupWindow;

private slots:
    void connectToServer();
    void sslConnected();
    void sslReadyRead();
    void sslDisconnected();
    void sslEncrypted();
    void sslError();
    void sslSend();
    void sslSentBytesLog(qint64 b);

    void showSetupWindow();
};

#endif // MAINWINDOW_H
