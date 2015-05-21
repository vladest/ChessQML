import QtQuick 2.4
import Chess 1.0
Item {
    id: root
    property int cellSize: width / 8
    width: parent.width > parent.height ? parent.height : parent.width
    height: parent.width > parent.height ? parent.height : parent.width
    anchors.centerIn: parent

    function restart() {
        chessController.initialize()
    }

    Connections {
        target: chessController
        onPiecePosChanged: {
            //console.log(piece.piecePosition, chessController.position2Index(piece.piecePosition))
            repeater.itemAt(chessController.position2Index(piece.piecePosition)).piece = piece
        }
    }

    Grid {
        id: boardGrid
        anchors.fill: parent;
        property int cellSize: parent.cellSize;
        rows: 8
        columns: 8

        Repeater {
            id: repeater
            model: 64
            Item {
                id: item
                width: root.cellSize;
                height: root.cellSize;
                property alias piece: chessCell.piece
                property bool selected: false
                onSelectedChanged: {
                    chessCell.setColor()
                }

                Rectangle {
                    id: chessCell
                    anchors.fill: parent
                    function setColor() {
                        return item.selected ? "red" : ((Math.floor(index / 8) % 2) === 0)
                                                   ? (index % 2  === 1 ? "#D18B47" : "#FFCE9E")
                                                   : (index % 2  === 0 ? "#D18B47" : "#FFCE9E")
                    }

                    property Piece piece: null
                    color: setColor()
                    border.color: "black";
                    border.width: 1
                    onPieceChanged: {
                        if (piece != null) {
                            chessCell.children = piece
                            piece.z = 1
                            piece.anchors.fill = chessCell
                            piece.width = chessCell.width
                            piece.height = chessCell.height
                        }
                    }
                }
                //transparent item for mouse handle
                Item {
                    anchors.fill: parent
                    z: 100
                    MouseArea {
                        id: mouseSquareArea
                        anchors.fill: parent
                        onClicked: {

                            item.selected = !item.selected
                            console.log("clicked pos:", chessController.index2position(index), item.selected)

                        }
                    }
                }
            }

        }
    }
    Component.onCompleted: {
        restart()
    }
}
