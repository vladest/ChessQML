#include "chesscontroller.h"
#include <QQmlEngine>

ChessController::ChessController(QObject *parent) : QObject(parent) {
    qmlRegisterType<Piece>("Chess", 1, 0, "Piece");
    qRegisterMetaType<Piece*>();
    //clean board array
    for(int row = 0; row < chessSide; row++) {
        for(int column = 0; column < chessSide; column++) {
            _piecesSet[row][column] = Q_NULLPTR;
        }
    }
}

// delete already allocated items
void ChessController::cleanup() {
    for(int row = 0; row < chessSide; row++) {
        for(int column = 0; column < chessSide; column++) {
            if (_piecesSet[row][column] != Q_NULLPTR) {
                delete _piecesSet[row][column];
                _piecesSet[row][column] = Q_NULLPTR;
            }
        }
    }
}

void ChessController::initialize() {
    cleanup();
    for(int row = 0; row < chessSide; row++) {
        for(int column = 0; column < chessSide; column++) {
            if (row == 0 || row == 1 || row == 6 || row == 7) {
                _piecesSet[row][column] = new Piece;
                connect(_piecesSet[row][column], &Piece::pieceIndexChanged, this, &ChessController::pieceIndexChanged);
                QQmlEngine::setObjectOwnership(_piecesSet[row][column], QQmlEngine::CppOwnership);
                if (row == 0 || row == 1) //black. top of the board
                    _piecesSet[row][column]->setPieceColor(Piece::Black);
                else if (row == 6 || row == 7)
                    _piecesSet[row][column]->setPieceColor(Piece::White);
                if (row == 1 || row == 6)
                    _piecesSet[row][column]->setPieceType(Piece::Pawn);
                _piecesSet[row][column]->setPieceAlive(true);
                _piecesSet[row][column]->setPieceIndex(row * 8 + column);
            } else {
                _piecesSet[row][column] = Q_NULLPTR;
            }
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

    _piecesSet[7][0]->setPieceType(Piece::Rook);
    _piecesSet[7][1]->setPieceType(Piece::Knight);
    _piecesSet[7][2]->setPieceType(Piece::Bishop);
    _piecesSet[7][3]->setPieceType(Piece::King);
    _piecesSet[7][4]->setPieceType(Piece::Queen);
    _piecesSet[7][5]->setPieceType(Piece::Bishop);
    _piecesSet[7][6]->setPieceType(Piece::Knight);
    _piecesSet[7][7]->setPieceType(Piece::Rook);
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
    return QString("%1%2").arg(static_cast<char>(col+96)).arg(row);
}

void ChessController::pieceIndexChanged(int pos) {
    Piece *piece = static_cast<Piece*>(sender());
    if (piece) {
        emit piecePosChanged(piece);
    }
}

//move validator according to chess ruels
bool ChessController::isValidMove(int fromindex, int toindex) {
    if (fromindex == -1 || toindex == -1 || fromindex == toindex)
        return false;

    int fromrow = fromindex / 8;
    int fromcol = fromindex % 8;

    int torow = toindex / 8;
    int tocol = toindex % 8;

    //int direction = piece->pieceColor() == Piece::White? -1 : 1;

    Piece *source = getPieceByIndex(toindex);
    Piece *target = getPieceByIndex(toindex);

    switch(source->pieceType()) {
    case Piece::Pawn:
        if(tocol == fromcol && qAbs(torow - fromrow)==1 && target == Q_NULLPTR) return true;
        if(qAbs(tocol- fromcol) == 1 && qAbs(torow-fromrow)==1 && target != Q_NULLPTR) return true;
        if(source->pieceColor() == Piece::Black && fromrow == 1 && qAbs(fromrow-torow)==2 && target == Q_NULLPTR) return true;
        if(source->pieceColor() == Piece::White && fromrow == 6 && qAbs(fromrow-torow)==2 && target == Q_NULLPTR) return true;
        break;
    default:
        break;
    }
    return false;
}

Piece *ChessController::getPieceByIndex(int index) const {
    return _piecesSet[index / chessSide][index % chessSide];
}


