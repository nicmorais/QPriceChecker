QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/loginwidget.cpp \
    src/settingswidget.cpp

HEADERS += \
    src/mainwindow.h \
    src/loginwidget.h \
    src/settingswidget.h

FORMS += \
    src/mainwindow.ui \
    src/loginwidget.ui \
    src/settingswidget.ui
    
TRANSLATIONS += \
    i18n/QPriceChecker_pt_BR.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
