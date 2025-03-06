QT       += core gui
QT       += concurrent
QT       += charts

INCLUDEPATH += $$[QT_INSTALL_HEADERS]/QtCharts
DEPENDPATH += $$[QT_INSTALL_HEADERS]/QtCharts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    agent.cpp \
    agents.cpp \
    heatmapanimation.cpp \
    main.cpp \
    mainwindow.cpp \
    simulation.cpp \
    sirmodel.cpp

HEADERS += \
    agent.h \
    agents.h \
    heatmapanimation.h \
    mainwindow.h \
    simulation.h \
    sirmodel.h

FORMS += \
    dialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
