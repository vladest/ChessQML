#include "chesscontroller.h"
#include <QQmlEngine>

ChessController::ChessController(QObject *parent) : QObject(parent)
  , m_currentMoveTurn(Piece::NoColor)
  , m_gameRunning(false)
  , m_movesNumber(0)
  , m_gameMode(Playing)
  , m_playBackIndex(-1) {
    qmlRegisterType<Piece>("Chess", 1, 0, "Piece");
    qRegisterMetaType<Piece*>();
    //clean _pieceSet array
    for(int row = 0; row < chessSide; row++) {
        for(int column = 0; column < chessSide; column++) {
            m_piecesSet[row][column] = Q_NULLPTR;
        }
    }
}

// delete alreatorow allocated items
void ChessController::cleanup() {
    for(int row = 0; row < chessSide; row++) {
        for(int column = 0; column < chessSide; column++) {
            if (m_piecesSet[row][column] != Q_NULLPTR) {
                delete m_piecesSet[row][column];
                m_piecesSet[row][column] = Q_NULLPTR;
            }
        }
    }
}

void ChessController::initialize() {
    cleanup();
    for(int row = 0; row < chessSide; row++) {
        for(int column = 0; column < chessSide; column++) {
            if (row == 0 || row == 1 || row == 6 || row == 7) {
                m_piecesSet[row][column] = new Piece;
                QQmlEngine::setObjectOwnership(m_piecesSet[row][column], QQmlEngine::CppOwnership);
                connect(m_piecesSet[row][column], &Piece::pieceIndexChanged, this, &ChessController::pieceIndexChanged, Qt::QueuedConnection);
                if (row == 0 || row == 1) //black. top of the _pieceSet
                    m_piecesSet[row][column]->setPieceColor(Piece::Black);
                else if (row == 6 || row == 7)
                    m_piecesSet[row][column]->setPieceColor(Piece::White);
                if (row == 1 || row == 6)
                    m_piecesSet[row][column]->setPieceType(Piece::Pawn);
                m_piecesSet[row][column]->setPieceAlive(true);
                m_piecesSet[row][column]->setPieceIndex(row * 8 + column);
            } else {
                m_piecesSet[row][column] = Q_NULLPTR;
            }
        }
    }
    m_piecesSet[0][0]->setPieceType(Piece::Rook);
    m_piecesSet[0][1]->setPieceType(Piece::Knight);
    m_piecesSet[0][2]->setPieceType(Piece::Bishop);
    m_piecesSet[0][3]->setPieceType(Piece::King);
    m_piecesSet[0][4]->setPieceType(Piece::Queen);
    m_piecesSet[0][5]->setPieceType(Piece::Bishop);
    m_piecesSet[0][6]->setPieceType(Piece::Knight);
    m_piecesSet[0][7]->setPieceType(Piece::Rook);

    m_piecesSet[7][0]->setPieceType(Piece::Rook);
    m_piecesSet[7][1]->setPieceType(Piece::Knight);
    m_piecesSet[7][2]->setPieceType(Piece::Bishop);
    m_piecesSet[7][3]->setPieceType(Piece::King);
    m_piecesSet[7][4]->setPieceType(Piece::Queen);
    m_piecesSet[7][5]->setPieceType(Piece::Bishop);
    m_piecesSet[7][6]->setPieceType(Piece::Knight);
    m_piecesSet[7][7]->setPieceType(Piece::Rook);
    setCurrentMoveTurn(Piece::White);
    m_gameTimer.restart();
}

void ChessController::pieceIndexChanged(int pos) {
    Q_UNUSED(pos)
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

    Piece *source = getPieceByIndex(fromindex);
    if (source == Q_NULLPTR)
        return false;
    Piece *target = getPieceByIndex(toindex);

    if (target != Q_NULLPTR && source->pieceColor() == target->pieceColor())
        return false;

    int x_dir = fromcol > tocol ? -1 : 1; //define derection increments
    int y_dir = fromrow > torow ? -1 : 1;

    switch(source->pieceType()) {
    case Piece::Pawn:
        if(tocol == fromcol && qAbs(torow - fromrow)==1 && target == Q_NULLPTR)
            return true;
        if(qAbs(tocol - fromcol) == 1 && qAbs(torow-fromrow)==1)
            return true;
        if(source->pieceColor() == Piece::Black && fromrow == 1 && tocol == fromcol && qAbs(fromrow-torow)==2 && target == Q_NULLPTR)
            return true;
        if(source->pieceColor() == Piece::White && fromrow == 6 && tocol == fromcol && qAbs(fromrow-torow)==2 && target == Q_NULLPTR)
            return true;
        break;
    case Piece::Rook:
        if(torow == fromrow || tocol == fromcol) { // Moving straight
            if(tocol==fromcol) { // Moving vertically
                int row = fromrow + y_dir;
                while (row != torow) {
                    if(m_piecesSet[row][tocol] != Q_NULLPTR) { //non vacant cell on the path
                        return false;
                    }
                    row += y_dir;
                }
            }
            if(torow == fromrow) { // Moving horizontally
                int col = fromcol + x_dir;
                while (col != tocol) {
                    if(m_piecesSet[torow][col] != Q_NULLPTR) { //non vacant cell on the path
                        return false;
                    }
                    col += x_dir;
                }
            }
            return true;
        }
        break;
    case Piece::Knight:
        if((qAbs(torow - fromrow) == 2 && qAbs(tocol - fromcol) == 1)
                || (qAbs(tocol - fromcol)==2 && qAbs(torow - fromrow) == 1)) {
            return true;
        }
        break;
    case Piece::Bishop:
        if(qAbs(torow - fromrow) == qAbs(tocol - fromcol)) { // check diagonal
            int row = fromrow + y_dir;
            int col = fromcol + x_dir;
            while (col != tocol && row != torow) {
                if(m_piecesSet[row][col] != Q_NULLPTR) { //non vacant cell on the path
                    return false;
                }
                row += y_dir;
                col += x_dir;
            }
            return true;
        }
        break;
    case Piece::Queen:
        if(qAbs(torow - fromrow) == qAbs(tocol - fromcol)) { // Moving diagonally
            int row = fromrow + y_dir;
            int col = fromcol + x_dir;
            while (col != tocol && row != torow) {
                if(m_piecesSet[row][col] != Q_NULLPTR) { //non vacant cell on the path
                    return false;
                }
                row += y_dir;
                col += x_dir;
            }
            return true;
        }
        if(torow == fromrow || tocol == fromcol) { // Moving straight
            if(tocol==fromcol) { // Moving vertically
                int row = fromrow + y_dir;
                while (row != torow) {
                    if(m_piecesSet[row][tocol] != Q_NULLPTR) { //non vacant cell on the path
                        return false;
                    }
                    row += y_dir;
                }
            }
            if(torow == fromrow) { // Moving horizontally
                int col = fromcol + x_dir;
                while (col != tocol) {
                    if(m_piecesSet[torow][col] != Q_NULLPTR) { //non vacant cell on the path
                        return false;
                    }
                    col += x_dir;
                }
            }
            return true;
        }
        break;
    case Piece::King:
        if(qAbs(torow - fromrow) <= 1 && qAbs(tocol - fromcol) <= 1)
            return true;
        break;
    default:
        break;
    }
    return false;
}

Piece *ChessController::getPieceByIndex(int index) const {
    return m_piecesSet[index / chessSide][index % chessSide];
}

Piece::PieceColor ChessController::currentMoveTurn() const {
    return m_currentMoveTurn;
}

void ChessController::setCurrentMoveTurn(Piece::PieceColor currentMoveTurn) {
    if (m_currentMoveTurn == currentMoveTurn)
        return;

    m_currentMoveTurn = currentMoveTurn;
    emit currentMoveTurnChanged(currentMoveTurn);
}

void ChessController::makeMove(int fromindex, int toindex) {
    if (fromindex == -1 || toindex == -1 || fromindex == toindex)
        return;

    int fromrow = fromindex / 8;
    int fromcol = fromindex % 8;

    int torow = toindex / 8;
    int tocol = toindex % 8;
    if (!m_piecesSet[fromrow][fromcol])
        return;

    m_piecesSet[torow][tocol] = m_piecesSet[fromrow][fromcol];
    m_piecesSet[fromrow][fromcol] = Q_NULLPTR;
    m_piecesSet[torow][tocol]->setPieceIndex(toindex);
    emit pieceRemoved(fromindex);
    if (currentMoveTurn() == Piece::White)
        setCurrentMoveTurn(Piece::Black);
    else
        setCurrentMoveTurn(Piece::White);
    if (m_gameMode == Playing) {
        GameMove gm;
        gm.timeOffset = m_gameTimer.elapsed();
        gm.fromIndex = fromindex;
        gm.toIndex = toindex;
        m_gameMoves.append(gm);
        setMovesNumber(m_gameMoves.size());
    }
}

bool ChessController::gameRunning() const {
    return m_gameRunning;
}

void ChessController::setGameRunning(bool gameRunning) {
    if (m_gameRunning == gameRunning)
        return;

    m_gameRunning = gameRunning;
    emit gameRunningChanged(gameRunning);
    setgameMode(Playing);
    if (m_gameRunning)
        m_gameMoves.clear();
}

void ChessController::loadGame(const QUrl &chessFile) {
    m_gameMoves.clear();
    QFile file(chessFile.toLocalFile());
    if(!file.open( QIODevice::ReadOnly)) {
        emit gameLoaded(false);
        qWarning() << "error loading file" << chessFile.toLocalFile();
        return;
    }

    QDataStream stream(&file);
    stream.setVersion( QDataStream::Qt_5_0);
    while (!stream.atEnd()) {
        GameMove gm;
        stream.readRawData((char *)&gm, sizeof(GameMove));
        m_gameMoves.append(gm);
        qDebug() << "added" << gm.fromIndex << gm.toIndex;
    }

    file.close();
    setMovesNumber(m_gameMoves.size());
    emit gameLoaded(true);
    setgameMode(Playback);
}

void ChessController::saveGame(const QString &chessFile) {
    QFile file(chessFile);
    if(!file.open(QIODevice::WriteOnly)) {
        emit gameSaved(false);
        return;
    }

    QDataStream stream( &file );
    stream.setVersion( QDataStream::Qt_5_0 );
    foreach (GameMove gm, m_gameMoves) {
        stream.writeRawData((const char *)&gm, sizeof(GameMove));
    }

    file.close();
    emit gameSaved(true);
}

int ChessController::movesNumber() const {
    return m_movesNumber;
}

void ChessController::setMovesNumber(int movesNumber) {
    if (m_movesNumber == movesNumber)
        return;

    m_movesNumber = movesNumber;
    emit movesNumberChanged(movesNumber);
}

ChessController::GameMode ChessController::gameMode() const {
    return m_gameMode;
}

void ChessController::setgameMode(ChessController::GameMode gameMode) {
    if (m_gameMode == gameMode)
        return;

    m_gameMode = gameMode;
    emit gameModeChanged(gameMode);
    if (m_gameMode == Playback)
        m_playBackIndex = 0;
}

void ChessController::nextMove() {
    qDebug() << m_playBackIndex << m_gameMoves.size();
    if (m_playBackIndex < 0 || m_playBackIndex >= m_gameMoves.size())
        return;
    GameMove gm = m_gameMoves.at(m_playBackIndex);
    makeMove(gm.fromIndex, gm.toIndex);
    m_playBackIndex++;
}

void ChessController::prevMove() {
    if (m_playBackIndex <= 0)
        return;
    GameMove gm = m_gameMoves.at(m_playBackIndex - 1);
    makeMove(gm.toIndex, gm.fromIndex);
    m_playBackIndex--;

}
