#include "chesscontroller.h"

ChessController::ChessController(QObject *parent) : QObject(parent) {
    qmlRegisterType<Piece>("Chess", 1, 0, "Piece");

    //setup pieces matrix. This data is constant during game
    for(int row = 0; row < 4; row++) {
        for(int column= 0; column < 8; column++) {
            _pieces[column][row] = new Piece;
            if (row == 0 || row == 1) //white
                _pieces[row][column]->setPieceColor(Piece::White);
            else
                _pieces[row][column]->setPieceColor(Piece::Black);
            if (row == 1 || row == 7)
                _pieces[row][column]->setPieceType(Piece::Pawn);
        }
    }
    _pieces[0][0]->setPieceType(Piece::Rook);
    _pieces[0][1]->setPieceType(Piece::Knight);
    _pieces[0][2]->setPieceType(Piece::Bishop);
    _pieces[0][3]->setPieceType(Piece::King);
    _pieces[0][4]->setPieceType(Piece::Queen);
    _pieces[0][5]->setPieceType(Piece::Bishop);
    _pieces[0][6]->setPieceType(Piece::Knight);
    _pieces[0][7]->setPieceType(Piece::Rook);

    _pieces[3][0]->setPieceType(Piece::Rook);
    _pieces[3][1]->setPieceType(Piece::Knight);
    _pieces[3][2]->setPieceType(Piece::Bishop);
    _pieces[3][3]->setPieceType(Piece::King);
    _pieces[3][4]->setPieceType(Piece::Queen);
    _pieces[3][5]->setPieceType(Piece::Bishop);
    _pieces[3][6]->setPieceType(Piece::Knight);
    _pieces[3][7]->setPieceType(Piece::Rook);

}

void ChessController::initialize() {
    char rownumbers[] = {'1', '2', '7', '8'};
    for(int row = 0; row < 4; row++) {
        for(int column= 0; column < 8; column++) {
            _pieces[row][column]->setPiecePosition(QString(static_cast<char>(column+61)) + QString(rownumbers[row]));
            _pieces[row][column]->setPieceAlive(true);
        }
    }
}

