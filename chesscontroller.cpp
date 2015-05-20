#include "chesscontroller.h"

ChessController::ChessController(QObject *parent) : QObject(parent) {
    qmlRegisterType<Piece>("Chess", 1, 0, "Piece");

    //setup pieces matrix. This data is constant during game
    for(int row = 0; row < 4; row++) {
        for(int column = 0; column < 8; column++) {
            _piecesSet[row][column] = new Piece;
            if (row == 0 || row == 1) //white
                _piecesSet[row][column]->setPieceColor(Piece::White);
            else
                _piecesSet[row][column]->setPieceColor(Piece::Black);
            if (row == 1 || row == 7)
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
            _piecesSet[row][column]->setPiecePosition(QString(static_cast<char>(column+61)) + QString(rownumbers[row]));
            _piecesSet[row][column]->setPieceAlive(true);
        }
    }
}

