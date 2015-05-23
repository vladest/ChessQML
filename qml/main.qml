import QtQuick 2.4
import QtQuick.Window 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2

ApplicationWindow {
    title: qsTr("ChessQML")
    width: 800
    height: 480
    visible: true
    FileDialog {
        id: fileOpenDialog
        title: qsTr("Choose chess file to load:")
        folder: "."
        selectExisting: true
        nameFilters: [ "QML Chess files (*.chess)", "All files (*)" ]
        onAccepted: {
            chessController.loadGame(fileOpenDialog.fileUrl)
        }
    }

    Connections {
        target: chessController
        onGameLoaded: {
            if (loaded) {
                gameControls.visible = true
                chessBoard.restart()
            }
        }
    }

    Row {
        anchors.fill: parent
        spacing: 10

        ChessBoard {
            id: chessBoard
            height: parent.height
            width: chessBoard.height

        }
        Column {
            id: buttons
            anchors.left: chessBoard.right
            anchors.right: parent.right
            spacing: 4
            Button {
                id: startButton
                anchors.left: parent.left
                anchors.right: parent.right

                text: chessController.gameRunning ? qsTr("Stop") : qsTr("Start")
                onClicked: {
                    chessController.gameRunning = !chessController.gameRunning
                    if (chessController.gameRunning)
                        chessBoard.restart()
                }
            }
            Button {
                id: loadButton
                anchors.left: parent.left
                anchors.right: parent.right
                enabled: !chessController.gameRunning

                text: qsTr("Load")
                onClicked: {
                    fileOpenDialog.open()
                }
            }
            Label {
                text: qsTr("Enter file name to save:")
            }

            TextField {
                anchors.left: parent.left
                anchors.right: parent.right
                id: saveFileName
            }

            Button {
                id: saveButton
                anchors.left: parent.left
                anchors.right: parent.right
                enabled: !chessController.gameRunning && chessController.movesNumber > 0
                text: qsTr("Save")
                onClicked: {
                    if (saveFileName.text != "")
                        chessController.saveGame(saveFileName.text)
                }
            }
            Row {
                id: gameControls
                anchors.left: parent.left
                anchors.right: parent.right
                visible: false
                Button {
                    id: prevButton
                    text: "<<"
                    onClicked: {
                        chessController.prevMove()
                    }
                }
                Button {
                    id: nextButton
                    text: ">>"
                    onClicked: {
                        chessController.nextMove()
                    }
                }
            }
        }
    }
}
