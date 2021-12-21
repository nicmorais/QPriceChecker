#include "loginwidget.h"
#include "ui_loginwidget.h"
#include <QMessageBox>
#include "mainwindow.h"

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);

    QString serverIP = settings.value("serverIP").toString();
    int serverPort = settings.value("serverPort").toInt();

    ui->serverIPLineEdit->setText(serverIP);
    ui->serverPortSpinBox->setValue(serverPort);

    if(serverIP != "" && serverPort != 0){
        connect();
    }
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::connect()
{
    manager = new QNetworkAccessManager();
    request.setUrl(QUrl("http://" + ui->serverIPLineEdit->text()
                        + ":" + QString::number(ui->serverPortSpinBox->value())));
    QObject::connect(manager, &QNetworkAccessManager::finished,
                     this, &LoginWidget::managerFinished);
    manager->get(request);
    ui->connectBtn->setEnabled(false);
}

void LoginWidget::managerFinished(QNetworkReply *reply)
{
    ui->connectBtn->setEnabled(true);
    if(reply->error()){
        QMessageBox errorMsg;
        errorMsg.setIcon(QMessageBox::Warning);
        errorMsg.setWindowTitle(tr("Network error"));
        errorMsg.setText(tr("Could not connect to server: ") + reply->errorString());
        errorMsg.exec();
    }else{
        settings.setValue("serverIP", ui->serverIPLineEdit->text());
        settings.setValue("serverPort", ui->serverPortSpinBox->value());
        MainWindow *mainWindow = new MainWindow;
        mainWindow->serverUrl = reply->url();
        mainWindow->show();
        close();
    }

}
