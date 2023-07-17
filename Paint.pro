QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bboxdecorator.cpp \
    canvas.cpp \
    circle.cpp \
    graphobjkt.cpp \
    line.cpp \
    main.cpp \
    paint.cpp \
    polygone.cpp \
    polyline.cpp \
    rectangle.cpp \
    scene.cpp

HEADERS += \
    bboxdecorator.h \
    canvas.h \
    circle.h \
    graphobjkt.h \
    line.h \
    paint.h \
    polygone.h \
    polyline.h \
    rectangle.h \
    scene.h \
    triangle.h

FORMS += \
    paint.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
