#ifndef CHESSMAN_H
#define CHESSMAN_H

#include <QQuickPaintedItem>
#include <QImage>

class Piece : public QQuickPaintedItem
{
    Q_OBJECT
public:
    enum PieceType { NoType, Pawn, Knight, Bishop, Rook, Queen, King };
    enum PieceColor { NoColor, Black, White };

    Q_ENUMS(PieceType)
    Q_ENUMS(PieceColor)

    Q_PROPERTY(PieceType pieceType READ pieceType WRITE setPieceType NOTIFY pieceTypeChanged)
    Q_PROPERTY(PieceColor pieceColor READ pieceColor WRITE setPieceColor NOTIFY pieceColorChanged)
    Q_PROPERTY(int pieceIndex READ pieceIndex WRITE setPieceIndex NOTIFY pieceIndexChanged)
    Q_PROPERTY(bool pieceAlive READ pieceAlive WRITE setPieceAlive NOTIFY pieceAliveChanged)

    Piece(QQuickItem * parent = 0);

    PieceType pieceType() const;
    PieceColor pieceColor() const;
    int pieceIndex() const;
    bool pieceAlive() const;

    void paint(QPainter * painter);

public slots:
    void setPieceType(PieceType piecetype);
    void setPieceColor(PieceColor piececolor);
    void setPieceIndex(int pieceindex);
    void setPieceAlive(bool pieceAlive);

signals:
    void pieceTypeChanged(PieceType piecetype);
    void pieceColorChanged(PieceColor piececolor);
    void pieceIndexChanged(int pieceindex);
    void pieceAliveChanged(bool pieceAlive);

private:
    void loadImage();
private:
    QImage _image; //piece image
    PieceType m_type;
    PieceColor m_piececolor;
    int m_index;
    bool m_pieceAlive;
};

#endif // CHESSMAN_H
