#include "chesscontroller.h"

ChessController::ChessController(QObject *parent) : QObject(parent) {
    qmlRegisterType<Piece>("Chess", 1, 0, "Piece");

    for(int row = 0; row < 4; row++) {
        for(int column= 0; column < 8; column++) {
            _pieces[column][row] = new Piece;
            if (row == 0 || row == 1) //white
                _pieces[row][column]->setPieceColor(Piece::White);
            else
                _pieces[row][column]->setPieceColor(Piece::Black);
            if (row == 1 || row == 7)
                _pieces[row][column]->setPieceType(Piece::Rook);
        }
    }
}

void ChessController::initialize() {
    char rownumbers[] = {'1', '2', '7', '8'};
    for(int row = 0; row < 4; row++) {
        for(int column= 0; column < 8; column++) {
            _pieces[row][column]->setPieceAlive(true);
            _pieces[row][column]->setPiecePosition(QString(static_cast<char>(column+61)) + QString(rownumbers[row]));
        }
    }
}

