QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Area.cpp \
    Function.cpp \
    Newton_opt.cpp \
    Optimization_method.cpp \
    Random_search.cpp \
    Stop_criterion.cpp \
    dialog.cpp \
    main.cpp \
    mainwindow.cpp \
    optimizationscene.cpp

HEADERS += \
    Area.h \
    Function.h \
    Newton_opt.h \
    Optimization_method.h \
    Random_search.h \
    Stop_criterion.h \
    dialog.h \
    mainwindow.h \
    optimizationscene.h

FORMS += \
    dialog.ui \
    mainwindow.ui

INCLUDEPATH += \
    ./eigen

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
