import QtQuick 2.4
import QtQuick.Window 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

ApplicationWindow {

    title: qsTr("ChessQML")
    width: 640
    height: 480
    visible: true
    RowLayout {
        anchors.fill: parent
        spacing: 10
        ColumnLayout {
            id: buttons
            anchors.margins: 5
            Layout.fillHeight: true
            Button {
                id: startButton
                text: qsTr("Start")
            }

        }

        ChessBoard {
            //anchors.fill: parent
            anchors.margins: 5
        }
        Item {
            id: flow
            Layout.fillHeight: true
        }
    }
}
