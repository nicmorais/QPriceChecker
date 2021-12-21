#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QSettings>

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();

private:
    Ui::LoginWidget *ui;
    QNetworkAccessManager *manager;
    QNetworkRequest request;
    QSettings settings;

private Q_SLOTS:
    void connect();
    void managerFinished(QNetworkReply *reply);

};

#endif // LOGINWIDGET_H
