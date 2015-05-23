import QtQuick 2.4
import Chess 1.0
Item {
    id: root
    property int cellSize: width / 8
    width: parent.width > parent.height ? parent.height : parent.width
    height: parent.width > parent.height ? parent.height : parent.width
    anchors.centerIn: parent

    property int moveFromIndex: -1 //no selection == -1, otherwise - index
    property int moveToIndex: -1
    property int moveTurn: chessController.currentMoveTurn

    function restart() {
        clearField()
        chessController.initialize()
    }

    function clearField() {
        for (var i = 0; i < repeater.count; i++) {
            repeater.itemAt(i).piece = null
        }
    }

    onMoveToIndexChanged: {
        if (moveFromIndex != -1 && moveToIndex != -1) {
            chessController.makeMove(moveFromIndex, moveToIndex)
            var oldindex = moveFromIndex
            moveFromIndex = -1
            repeater.itemAt(oldindex).setColor()
            moveToIndex = -1
        }
    }

    Connections {
        target: chessController
        onPiecePosChanged: {
            //console.log(piece.piecePosition, chessController.position2Index(piece.piecePosition))
            repeater.itemAt(piece.pieceIndex).piece = piece
        }
        onPieceRemoved: {
            repeater.itemAt(index).piece = null
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
                function setColor() {
                    chessCell.color = root.moveFromIndex == index ? "blue" :
                                                                    ((Math.floor(index / 8) % 2) === 0)
                                                                    ? (index % 2  === 1 ? "#D18B47" : "#FFCE9E")
                                                                    : (index % 2  === 0 ? "#D18B47" : "#FFCE9E")
                }
                Rectangle {
                    id: chessCell
                    anchors.fill: parent
                    property Piece piece: chessController.getPieceByIndex(index)
                    color: item.setColor()
                    border.color: "black";
                    border.width: 1
                    onPieceChanged: {
                        if (piece != null) {
                            chessCell.children = piece
                            piece.z = 1
                            piece.anchors.fill = chessCell
                            piece.width = chessCell.width
                            piece.height = chessCell.height
                        } else {

                        }
                    }
                }
                //transparent item for mouse handle
                Item {
                    anchors.fill: parent
                    //z: 100
                    MouseArea {
                        id: mouseSquareArea
                        anchors.fill: parent
                        hoverEnabled: true
                        onEntered: {
                            if (root.moveFromIndex != -1) {
                                if (chessController.isValidMove(root.moveFromIndex, index)) {
                                    chessCell.color = "lightgreen"
                                } else {
                                    chessCell.color = "red"
                                }
                            }
                        }

                        onExited: {
                            item.setColor()
                        }

                        onClicked: {
                            console.log("clicked pos:", chessController.index2position(index), chessCell.piece)
                            var oldindex = -1
                            if (chessCell.piece !== null) {
                                if (chessCell.piece.pieceColor === root.moveTurn) {
                                    if (root.moveFromIndex == -1)
                                        root.moveFromIndex = index
                                    else {
                                        oldindex = root.moveFromIndex
                                        root.moveFromIndex = -1
                                        repeater.itemAt(oldindex).setColor()
                                        if (root.moveToIndex != -1) { //cleanup destination
                                            oldindex = root.moveToIndex
                                            repeater.itemAt(oldindex).setColor()
                                            root.moveToIndex = -1
                                        }
                                        root.moveFromIndex = index
                                    }
                                }
                            } else {
                                if (root.moveFromIndex != -1) {// piece selected
                                    if (root.moveToIndex == -1) {//check if destination already selected
                                        if (chessController.isValidMove(root.moveFromIndex, index))
                                            root.moveToIndex = index
                                    } else { //choose another destination
                                        root.moveToIndex = -1
                                        if (chessController.isValidMove(root.moveFromIndex, index))
                                            root.moveToIndex = index
                                    }
                                }
                            }
                            item.setColor()
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
