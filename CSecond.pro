QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    main.cpp \
    AttributeManager.cpp \
    StoryManager.cpp \
    GameManager.cpp \
    PoetryGame.cpp \
    BadmintonGame.cpp \
    MainWindow.cpp \
    StartWidget.cpp \
    GameWidget.cpp \
    StoryWidget.cpp \
    OptionWidget.cpp \
    ResultDialog.cpp

HEADERS += \
    AttributeManager.h \
    StoryManager.h \
    GameManager.h \
    PoetryGame.h \
    BadmintonGame.h \
    MainWindow.h \
    StartWidget.h \
    GameWidget.h \
    StoryWidget.h \
    OptionWidget.h \
    ResultDialog.h

RESOURCES += resources.qrc