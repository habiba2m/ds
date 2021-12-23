QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    check.cpp \
    compress.cpp \
    decompress.cpp \
    formatting.cpp \
    json.cpp \
    main.cpp \
    minify.cpp \
    xml_editor.cpp

HEADERS += \
    Consistency.h \
    Formatting.h \
    compress.h \
    decompress.h \
    minify.h \
    node.h \
    tree.h \
    xml_editor.h

FORMS += \
    xml_editor.ui

RC_ICONS = icon.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
