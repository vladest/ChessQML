import QtQuick 2.4
import QtQuick.Window 2.0
import QtQuick.Controls 1.2

ApplicationWindow {

    title: qsTr("ChessQML")
    width: 640
    height: 480
    visible: true
    ChessBoard {
        //anchors.fill: parent
        anchors.margins: 5
    }
}
