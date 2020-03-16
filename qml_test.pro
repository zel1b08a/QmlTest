QT += quick
CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

HEADERS += \
    bank.h \
    bankmodel.h \
    configmodel.h \
    client.h

SOURCES += \
    bank.cpp \
    bankmodel.cpp \
    configmodel.cpp \
    main.cpp \
    client.cpp

RESOURCES += qml.qrc

QML_IMPORT_PATH =

QML_DESIGNER_IMPORT_PATH =

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
