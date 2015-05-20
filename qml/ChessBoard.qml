import QtQuick 2.4

Item {
    id: root
    property int cellSize: width / 8
    width: parent.width > parent.height ? parent.height : parent.width
    height: parent.width > parent.height ? parent.height : parent.width
    anchors.centerIn: parent

    Grid {
        id: boardGrid
        anchors.fill: parent;
        property int cellSize: parent.cellSize;
        rows: 8
        columns: 8

        // 64 ChessBoard tiles - from top left to buttom right
        Repeater {
            model: 64
            Rectangle {
                id: chessCell
                color: ((Math.floor(index / 8) % 2) === 0)
                       ? (index % 2  === 1 ? "#D18B47" : "#FFCE9E")
                         : (index % 2  === 0 ? "#D18B47" : "#FFCE9E")
                border.color: "brown";
                border.width: 1
                width: root.cellSize;
                height: root.cellSize;

                // handle click on piece - to show available moves
                MouseArea {
                    id: mouseSquareArea
                    anchors.fill: parent
                    onReleased: {
                        //board.showAndMove(index);
                    }
                }
            }

        }
    }
}
