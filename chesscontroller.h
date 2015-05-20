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

public slots:
    void initialize(); //initializes pieces to start position

private:
    Piece *_piecesSet[4][8];
};

#endif // CHESSCONTROLLER_H
