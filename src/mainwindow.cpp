#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "settingswidget.h"
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->barcodeLineEdit->setFocus();
    ui->centerLabel->setStyleSheet("font-size: " + settings.value("productFontSize").toString() + "px");
    ui->scanProductLabel->setStyleSheet("font-size: " + settings.value("homeFontSize").toString() + "px");
    showLogo();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showLogo()
{
    ui->centerLabel->setPixmap(QPixmap(settings.value("logoPath").toString()));
    ui->scanProductLabel->setText(settings.value("homeText").toString());
}

void MainWindow::showSettingsWidget()
{
    SettingsWidget *settingsWidget = new SettingsWidget;
    QRect rect(x(), y(), width() * 0.8, height() * 0.8);
    rect.moveCenter(geometry().center());
    settingsWidget->setGeometry(rect);
    settingsWidget->show();
}

void MainWindow::searchProduct()
{
    manager = new QNetworkAccessManager();
    request.setUrl(QUrl(serverUrl.toString() + "/product?barcode=" + ui->barcodeLineEdit->text()));

    QObject::connect(manager, &QNetworkAccessManager::finished,
                     this, &MainWindow::managerFinished);
    manager->get(request);
    ui->centerLabel->setText(tr("Loading.."));

    ui->barcodeLineEdit->clear();

    ui->scanProductLabel->setText("");

    QTimer::singleShot(6000, this, &MainWindow::showLogo);
}

void MainWindow::managerFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QJsonObject jsonObj = QJsonDocument::fromJson(reply->readAll()).object();
        QString productName = jsonObj["name"].toString();
        QLocale locale(QLocale::system());

        ui->centerLabel->setText(productName
                                 + "\n"
                                 + settings.value("currencySymbol").toString()
                                 + " "
                                 + QString::number(jsonObj["price"].toDouble(), 'f', 2).replace(".", locale.decimalPoint()));

    } else if (reply->error() == QNetworkReply::ContentNotFoundError) {
        ui->centerLabel->setText(tr("Error: not found"));
    } else {
        ui->centerLabel->setText("Could not connect to server.");
    }
}
