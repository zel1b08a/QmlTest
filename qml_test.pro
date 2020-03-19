QT += quick
CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

HEADERS += \
    client.h \
    coefficientitem.h \
    configmodel.h

SOURCES += \
    main.cpp \
    client.cpp \
    coefficientitem.cpp \
    configmodel.cpp

RESOURCES += qml.qrc

QML_IMPORT_PATH =

QML_DESIGNER_IMPORT_PATH =

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
