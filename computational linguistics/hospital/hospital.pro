QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    form_add.cpp \
    form_add_sensors.cpp \
    form_delete.cpp \
    form_edit.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    form_add.h \
    form_add_sensors.h \
    form_delete.h \
    form_edit.h \
    mainwindow.h

FORMS += \
    form_add.ui \
    form_add_sensors.ui \
    form_delete.ui \
    form_edit.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
