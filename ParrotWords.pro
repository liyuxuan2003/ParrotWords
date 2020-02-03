#-------------------------------------------------
#
# Project created by QtCreator 2020-01-22T14:49:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += texttospeech

TARGET = ParrotWords
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        MainWindow.cpp \
    Menu.cpp \
    LiLibrary/LiEasyLayout.cpp \
    LiLibrary/LiFileName.cpp \
    LiLibrary/LiFixedToLayout.cpp \
    LiLibrary/LiReadImageInfo.cpp \
    DataInputMenu.cpp \
    DataInput.cpp \
    ChooseMenu.cpp \
    Choose.cpp \
    ChooseReview.cpp \
    SpellMenu.cpp \
    Spell.cpp \
    SpellReview.cpp \
    LearnMenu.cpp \
    Learn.cpp \
    ChooseHelp.cpp \
    LearnHelp.cpp \
    SpellHelp.cpp \
    About.cpp

RC_FILE += Version.rc

HEADERS += \
        MainWindow.h \
    Menu.h \
    LiLibrary/LiEasyLayout.h \
    LiLibrary/LiFileName.h \
    LiLibrary/LiFixedToLayout.h \
    LiLibrary/LiReadImageInfo.h \
    DataInputMenu.h \
    DataInput.h \
    ChooseMenu.h \
    Choose.h \
    ChooseReview.h \
    SpellMenu.h \
    Spell.h \
    SpellReview.h \
    LearnMenu.h \
    Learn.h \
    ChooseHelp.h \
    LearnHelp.h \
    SpellHelp.h \
    About.h \
    Version.rc

FORMS += \
        MainWindow.ui \
    Menu.ui \
    DataInputMenu.ui \
    DataInput.ui \
    ChooseMenu.ui \
    Choose.ui \
    ChooseReview.ui \
    SpellMenu.ui \
    Spell.ui \
    SpellReview.ui \
    LearnMenu.ui \
    Learn.ui \
    ChooseHelp.ui \
    LearnHelp.ui \
    SpellHelp.ui \
    About.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Icon/ParrotWords.png \
    Icon/ParrotWords-16.ico \
    Icon/ParrotWords-32.ico \
    Icon/ParrotWords-48.ico \
    Icon/ParrotWords-64.ico \
    Icon/ParrotWords-128.ico

RESOURCES += \
    icon.qrc
