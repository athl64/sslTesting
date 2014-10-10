#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //socket init
    sslClient = new QSslSocket(this);

    connect(sslClient,SIGNAL(connected()),this,SLOT(sslConnected()));
    connect(sslClient,SIGNAL(disconnected()),this,SLOT(sslDisconnected()));
    connect(sslClient,SIGNAL(readyRead()),this,SLOT(sslReadyRead()));
    connect(sslClient,SIGNAL(encrypted()),this,SLOT(sslEncrypted()));
    connect(sslClient,SIGNAL(sslErrors(QList<QSslError>)),this,SLOT(sslError()));
    connect(sslClient,SIGNAL(bytesWritten(qint64)),this,SLOT(sslSentBytesLog(qint64)));
    //connect(sslClient,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(sslError()));
    connect(ui->menuAccount,SIGNAL(triggered(QAction*)),this,SLOT(showSetupWindow()));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(sslSend()));
    connect(ui->connectButton,SIGNAL(clicked()),this,SLOT(connectToServer()));
}

MainWindow::~MainWindow()
{
    delete sslClient;
    delete ui;
}

void MainWindow::connectToServer()
{
    QMessageBox *info = new QMessageBox(this);
    info->setText("check all fields");
    info->setWindowTitle("warning");
    QString host;
    qint64 port;
    QString name;
    QString pass;
    bool err = false;

    if(!ui->hostName->text().isEmpty())
    {
        host = ui->hostName->text();
    }
    else
    {
        err = true;
    }
    if(!ui->hostPort->text().isEmpty())
    {
        port = ui->hostPort->text().toInt();
    }
    else
    {
        err = true;
    }
    if(!ui->hostUser->text().isEmpty())
    {
        name = ui->hostUser->text();
    }
    else
    {
        err = true;
    }
    if(!ui->hostPass->text().isEmpty())
    {
        pass = ui->hostPass->text();
    }
    else
    {
        err = true;
    }

    if(err)
    {
        info->show();
    }
    else
    {
        if(sslClient->state() == QAbstractSocket::UnconnectedState)
        {
            sslClient->connectToHostEncrypted(host,port);

        }
        else
        {
            info->setText("can't connect to server - allready connected or another collision");
            info->show();
        }
    }
}

void MainWindow::sslConnected()
{
    qDebug() << "connected";
    ui->textBrowser->append("connected\n");

    QByteArray sendData;

    sendData.clear();
    sendData.append("user " + ui->hostUser->text() + "\r\n");
    sslClient->write(sendData);
    sslClient->flush();

    sslClient->waitForReadyRead(3000);

    sendData.clear();
    sendData.append("pass " + ui->hostPass->text() + "\r\n");
    sslClient->write(sendData);
    sslClient->flush();
}

void MainWindow::sslReadyRead()
{
    ui->textBrowser->append("i received: " + sslClient->readAll());
    qDebug() << "ready read (we received data from server)";
}

void MainWindow::sslDisconnected()
{
    qDebug() << "disconnected";
    ui->textBrowser->append("disconnected\n");
}

void MainWindow::sslEncrypted()
{
    QSslCipher cipher = sslClient->sessionCipher();
    QString sertificateStr = cipher.name() + " / " + cipher.encryptionMethod();

    //ui->textBrowser->append(sertificateStr);
    qDebug() << "encrypted\n" << sertificateStr;
    qDebug() << sslClient->peerCertificate().toText();
}

void MainWindow::sslError()
{
    qDebug() << "error: " << sslClient->errorString();
    //this is bad line, for develop and debug
    sslClient->ignoreSslErrors();
}

void MainWindow::sslSend()
{
    QString msg;
    if(!ui->lineEdit->text().isEmpty())
    {
        msg.clear();
        msg.append(ui->lineEdit->text() + "\r\n");
        QByteArray data;
        data.clear();
        data.append(msg);
        sslClient->write(data);
        ui->textBrowser->append("i sent: " + msg);
        ui->lineEdit->clear();
        sslClient->flush();
    }
}

void MainWindow::sslSentBytesLog(qint64 b)
{
    qDebug() << "bytes sent: " << b;
    //ui->textBrowser->append(QString::number(b));
}

void MainWindow::showSetupWindow()
{
    setupWindow = new account_details(this);
    setupWindow->show();
}
