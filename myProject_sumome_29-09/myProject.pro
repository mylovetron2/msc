QT       += core gui
QT       += sql widgets
QT       += widgets serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    booleancheckboxdelegate.cpp \
    checkboxdelegate.cpp \
    colorlisteditor.cpp \
    comboboxcolordelegate.cpp \
    command.cpp \
    commandclosearmmsc.cpp \
    commanddmt.cpp \
    commandmsc.cpp \
    commandopenarmmsc.cpp \
    commandsumome.cpp \
    curveattribute.cpp \
    curvesetting.cpp \
    datatableview.cpp \
    dmtview.cpp \
    emitter.cpp \
    headerwiget.cpp \
    loaddata.cpp \
    main.cpp \
    mainwindow.cpp \
    msccolorview.cpp \
    mscpolarview.cpp \
    mydatatable.cpp \
    parameterdialog.cpp \
    qcustomplot.cpp \
    settingsdialog.cpp \
    spinboxdelegate.cpp \
    tablemodel.cpp \
    tablewidget.cpp \
    trackview.cpp \
    trackviewwidget.cpp

HEADERS += \
    booleancheckboxdelegate.h \
    checkboxdelegate.h \
    colorlisteditor.h \
    comboboxcolordelegate.h \
    command.h \
    commandclosearmmsc.h \
    commanddmt.h \
    commandmsc.h \
    commandopenarmmsc.h \
    commandsumome.h \
    connection.h \
    curveattribute.h \
    curvesetting.h \
    datatableview.h \
    dmtview.h \
    emitter.h \
    headerwiget.h \
    loaddata.h \
    mainwindow.h \
    msccolorview.h \
    mscpolarview.h \
    mydatatable.h \
    parameterdialog.h \
    qcustomplot.h \
    settingsdialog.h \
    spinboxdelegate.h \
    structureHeader.h \
    tablemodel.h \
    tablewidget.h \
    trackview.h \
    trackviewwidget.h

FORMS += \
    dmtview.ui \
    loaddata.ui \
    mainwindow.ui \
    parameterdialog.ui \
    settingsdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    mymodel.qmodel

RESOURCES += \
    res.qrc
