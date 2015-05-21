#include "chesscontroller.h"
#include <QQmlEngine>

ChessController::ChessController(QObject *parent) : QObject(parent) {
    qmlRegisterType<Piece>("Chess", 1, 0, "Piece");
    qRegisterMetaType<Piece*>();

    //setup pieces matrix. This data is constant during game
    for(int row = 0; row < 4; row++) {
        for(int column = 0; column < 8; column++) {
            _piecesSet[row][column] = new Piece;
            connect(_piecesSet[row][column], &Piece::piecePositionChanged, this, &ChessController::piecePositionChanged);
            QQmlEngine::setObjectOwnership(_piecesSet[row][column], QQmlEngine::CppOwnership);
            if (row == 0 || row == 1) //white
                _piecesSet[row][column]->setPieceColor(Piece::White);
            else
                _piecesSet[row][column]->setPieceColor(Piece::Black);
            if (row == 1 || row == 2)
                _piecesSet[row][column]->setPieceType(Piece::Pawn);
        }
    }
    _piecesSet[0][0]->setPieceType(Piece::Rook);
    _piecesSet[0][1]->setPieceType(Piece::Knight);
    _piecesSet[0][2]->setPieceType(Piece::Bishop);
    _piecesSet[0][3]->setPieceType(Piece::King);
    _piecesSet[0][4]->setPieceType(Piece::Queen);
    _piecesSet[0][5]->setPieceType(Piece::Bishop);
    _piecesSet[0][6]->setPieceType(Piece::Knight);
    _piecesSet[0][7]->setPieceType(Piece::Rook);

    _piecesSet[3][0]->setPieceType(Piece::Rook);
    _piecesSet[3][1]->setPieceType(Piece::Knight);
    _piecesSet[3][2]->setPieceType(Piece::Bishop);
    _piecesSet[3][3]->setPieceType(Piece::King);
    _piecesSet[3][4]->setPieceType(Piece::Queen);
    _piecesSet[3][5]->setPieceType(Piece::Bishop);
    _piecesSet[3][6]->setPieceType(Piece::Knight);
    _piecesSet[3][7]->setPieceType(Piece::Rook);

}

void ChessController::initialize() {
    char rownumbers[] = {'1', '2', '7', '8'};
    for(int row = 0; row < 4; row++) {
        for(int column= 0; column < 8; column++) {
            _piecesSet[row][column]->setPiecePosition(QString("%1%2").arg(static_cast<char>(column+97)).arg(rownumbers[row]));
            _piecesSet[row][column]->setPieceAlive(true);
        }
    }
}

int ChessController::position2Index(const QString pos) {
    int index = -1;
    if (pos.size() == 2) {
        index = ((8 - (pos.at(1).toLatin1() - 48)) * 8 + (pos.at(0).toLatin1() - 96)) - 1 ;
    }
    return index;
}

QString ChessController::index2position(int index) {
    int row = 8 - (index / 8);
    int col = (index % 8) + 1;
    qDebug() << row << col;
    return QString("%1%2").arg(static_cast<char>(col+96)).arg(row);
}

void ChessController::piecePositionChanged(const QString &pos) {
    Piece *piece = static_cast<Piece*>(sender());
    if (piece) {
        emit piecePosChanged(piece);
    }
}

