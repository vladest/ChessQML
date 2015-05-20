TEMPLATE = app

QT += qml quick

SOURCES += main.cpp \
    piece.cpp \
    chesscontroller.cpp

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

DISTFILES += \
    qml/main.qml \
    qml/ChessBoard.qml

HEADERS += \
    piece.h \
    chesscontroller.h
