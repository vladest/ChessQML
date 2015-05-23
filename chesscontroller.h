#ifndef CHESSCONTROLLER_H
#define CHESSCONTROLLER_H

#include <QObject>
#include "piece.h"

const int chessSide = 8;

class ChessController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Piece::PieceColor currentMoveTurn READ currentMoveTurn WRITE setCurrentMoveTurn NOTIFY currentMoveTurnChanged)
public:
    explicit ChessController(QObject *parent = 0);

    Piece::PieceColor currentMoveTurn() const;

signals:
    void piecePosChanged(Piece *piece);
    void pieceRemoved(int index);
    void currentMoveTurnChanged(Piece::PieceColor currentMoveTurn);

public slots:
    void initialize(); //initializes pieces to start position
    int position2Index(const QString pos);
    QString index2position(int index);
    void pieceIndexChanged(int pos);
    bool isValidMove(int fromindex, int toindex);
    Piece *getPieceByIndex(int index) const;
    void setCurrentMoveTurn(Piece::PieceColor currentMoveTurn);
    void makeMove(int fromindex, int toindex);

private:
    void cleanup();
private:
    Piece *_piecesSet[chessSide][chessSide];
    Piece::PieceColor m_currentMoveTurn;
};

#endif // CHESSCONTROLLER_H
