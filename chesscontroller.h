#ifndef CHESSCONTROLLER_H
#define CHESSCONTROLLER_H

#include <QObject>
#include "piece.h"

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
    void piecePositionChanged(const QString &pos);

private:
    Piece *_piecesSet[4][8];
};

#endif // CHESSCONTROLLER_H
