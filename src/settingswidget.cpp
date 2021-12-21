#include "settingswidget.h"
#include "ui_settingswidget.h"
#include <QFileDialog>

SettingsWidget::SettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsWidget)
{
    ui->setupUi(this);

    ui->homeFontSizeSpinBox->setValue(settings.value("homeFontSize").toInt());
    ui->homeTextLineEdit->setText(settings.value("homeText").toString());
    logoPath = settings.value("logoPath").toString();
    ui->currencySymbolLineEdit->setText(settings.value("currencySymbol").toString());
    ui->productFontSizeSpinBox->setValue(settings.value("productFontSize").toInt());
}

SettingsWidget::~SettingsWidget()
{
    delete ui;
}

void SettingsWidget::save()
{
    settings.setValue("homeFontSize", ui->homeFontSizeSpinBox->value());
    settings.setValue("homeText", ui->homeTextLineEdit->text());
    settings.setValue("logoPath", logoPath);
    settings.setValue("currencySymbol", ui->currencySymbolLineEdit->text());
    settings.setValue("productFontSize", ui->productFontSizeSpinBox->value());
    close();
}

void SettingsWidget::selectLogo()
{
    QFileDialog fileDialog;
    if(fileDialog.exec()){
        logoPath = fileDialog.selectedFiles().first();
    }
}
