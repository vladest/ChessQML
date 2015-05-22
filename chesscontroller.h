#ifndef CHESSCONTROLLER_H
#define CHESSCONTROLLER_H

#include <QObject>
#include "piece.h"

const int chessSide = 8;

class ChessController : public QObject
{
    Q_OBJECT
public:
    explicit ChessController(QObject *parent = 0);

signals:
    void piecePosChanged(Piece *piece);
public slots:
    void initialize(); //initializes pieces to start position
    int position2Index(const QString pos);
    QString index2position(int index);
    void pieceIndexChanged(int pos);
    bool isValidMove(int fromindex, int toindex);
    Piece *getPieceByIndex(int index) const;
private:
    void cleanup();
private:
    Piece *_piecesSet[chessSide][chessSide];
};

#endif // CHESSCONTROLLER_H
