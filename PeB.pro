QT += core gui svg xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PeB_Emulator
TEMPLATE = app

INCLUDEPATH += include \
               include/PeB_Window


SOURCES += src/main.cpp \
           src/PeB_UI.cpp \
           src/PeBSvgItem.cpp

HEADERS += include/PeB_UI.h \
           include/PeBSvgItem.h

FORMS += include/PeB_Window/mainwindow.ui

# Output Directories
UI_DIR = build/ui         # ui_*.h files
MOC_DIR = build/moc       # moc_*.cpp files
OBJECTS_DIR = build/obj   # *.o files
DESTDIR = build/bin       # final executable
