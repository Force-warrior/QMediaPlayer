QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia multimediawidgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG(debug, debug|release) {
    UI_DIR = $$PWD/tmp/debug/ui
    MOC_DIR = $$PWD/tmp/debug/moc
    OBJECTS_DIR = $$PWD/tmp/debug/objects
    RCC_DIR = $$PWD/tmp/debug/resources

    win32:DESTDIR = $$shell_path($$PWD/debug)
    macx:DESTDIR = $$shell_path($$PWD)
} else {
    UI_DIR = $$PWD/tmp/release/ui
    MOC_DIR = $$PWD/tmp/release/moc
    OBJECTS_DIR = $$PWD/tmp/release/objects
    RCC_DIR = $$PWD/tmp/release/resources

    QMAKE_CFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
    QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CXXFLAGS_RELEASE_WITH_DEBUGINFO
    QMAKE_OBJECTIVE_CFLAGS_RELEASE = $$QMAKE_OBJECTIVE_CFLAGS_RELEASE_WITH_DEBUGINFO
    QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO

    win32:DESTDIR = $$shell_path($$PWD/release)
    macx:DESTDIR = $$shell_path($$PWD)
}


SOURCES += \
    MediaPlayerFrame.cpp \
    UserContentFrame.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    MediaPlayerFrame.h \
    UserContentFrame.h \
    mainwindow.h

FORMS += \
    MediaPlayerFrame.ui \
    UserContentFrame.ui \
    mainwindow.ui


win32:{

    SOURCES += \

    HEADERS += \

    # 拷贝二进制
    CONFIG(debug, debug|release) {
       DEST_DIR = $$shell_path($$PWD\debug)
    } else {
       DEST_DIR = $$shell_path($$PWD\release)
    }
    QMAKE_POST_LINK += $$quote(xcopy /S /y $$shell_path($$PWD\res\*) $$DEST_DIR $$escape_expand(\\n\\t))
}
macx:{

}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
