QT       += core gui printsupport multimedia
greaterThan(QT_MAJOR_VERSION,(X= QT_MAJOR_VERSION - 1)): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    RPN.c \
    calc_credit.c \
    credit.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp

HEADERS += \
    RPN.h \
    calc_credit.h \
    credit.h \
    mainwindow.h \
    qcustomplot.h

ICON = icon/icon.icns

FORMS += \
    credit.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../../PLOT_calc.png \
    memes/PLOT_calc.png

RESOURCES += \
    img.qrc
