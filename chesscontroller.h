#ifndef CHESSCONTROLLER_H
#define CHESSCONTROLLER_H

#include <QObject>
#include <QTime>
#include "piece.h"

const int chessSide = 8;

struct GameMove {
    int timeOffset;
    int fromIndex;
    int toIndex;
};

class ChessController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Piece::PieceColor currentMoveTurn READ currentMoveTurn WRITE setCurrentMoveTurn NOTIFY currentMoveTurnChanged)
    Q_PROPERTY(bool gameRunning READ gameRunning WRITE setGameRunning NOTIFY gameRunningChanged)
    Q_PROPERTY(int movesNumber READ movesNumber WRITE setMovesNumber NOTIFY movesNumberChanged)
    Q_PROPERTY(GameMode gameMode READ gameMode WRITE setgameMode NOTIFY gameModeChanged)

    Q_ENUMS(GameMode)

public:
    enum GameMode {
        Playing,
        Playback
    };

    explicit ChessController(QObject *parent = 0);
    Piece::PieceColor currentMoveTurn() const;
    bool gameRunning() const;
    int movesNumber() const;
    GameMode gameMode() const;

signals:
    void piecePosChanged(Piece *piece);
    void pieceRemoved(int index);
    void currentMoveTurnChanged(Piece::PieceColor currentMoveTurn);
    void gameRunningChanged(bool gameRunning);
    void gameLoaded(bool loaded);
    void gameSaved(bool saved);
    void movesNumberChanged(int movesNumber);
    void gameModeChanged(GameMode gameMode);

public slots:
    void initialize(); //initializes pieces to start position
    void pieceIndexChanged(int pos);
    bool isValidMove(int fromindex, int toindex);
    Piece *getPieceByIndex(int index) const;
    void setCurrentMoveTurn(Piece::PieceColor currentMoveTurn);
    void makeMove(int fromindex, int toindex);
    void setGameRunning(bool gameRunning);
    void loadGame(const QUrl &chessFile);
    void saveGame(const QString &chessFile);
    void setMovesNumber(int movesNumber);
    void setgameMode(GameMode gameMode);
    void nextMove();
    void prevMove();

private:
    void cleanup();
private:
    Piece *m_piecesSet[chessSide][chessSide];
    Piece::PieceColor m_currentMoveTurn;
    bool m_gameRunning;
    QTime m_gameTimer;
    QList<GameMove> m_gameMoves;
    int m_movesNumber;
    GameMode m_gameMode;
    int m_playBackIndex;
};

#endif // CHESSCONTROLLER_H
