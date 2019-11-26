QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    accountconfirm.cpp \
    admin_item_database.cpp \
    admin_member_database.cpp \
    admincreate.cpp \
    adminlogin.cpp \
    createcheck.cpp \
    main.cpp \
    mainwindow.cpp \
    manager_item_database.cpp \
    manager_member_database.cpp \
    managercreate.cpp \
    managerlogin.cpp \
    userdata.cpp

HEADERS += \
    accountconfirm.h \
    admin_item_database.h \
    admin_member_database.h \
    admincreate.h \
    adminlogin.h \
    createcheck.h \
    mainwindow.h \
    manager_item_database.h \
    manager_member_database.h \
    managercreate.h \
    managerlogin.h \
    userdata.h

FORMS += \
    accountconfirm.ui \
    admin_item_database.ui \
    admin_member_database.ui \
    admincreate.ui \
    adminlogin.ui \
    createcheck.ui \
    mainwindow.ui \
    manager_item_database.ui \
    manager_member_database.ui \
    managercreate.ui \
    managerlogin.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
