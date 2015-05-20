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

    Q_PROPERTY(PieceType piecetype READ pieceType WRITE setPieceType NOTIFY pieceTypeChanged)
    Q_PROPERTY(PieceColor piececolor READ pieceColor WRITE setPieceColor NOTIFY pieceColorChanged)
    Q_PROPERTY(QString piecePosition READ piecePosition WRITE setPiecePosition NOTIFY piecePositionChanged)
    Q_PROPERTY(bool pieceAlive READ pieceAlive WRITE setPieceAlive NOTIFY pieceAliveChanged)

    Piece(QQuickPaintedItem * parent = 0);

    PieceType pieceType() const;
    PieceColor pieceColor() const;
    QString piecePosition() const;
    bool pieceAlive() const;

    void paint(QPainter * painter);

public slots:
    void setPieceType(PieceType piecetype);
    void setPieceColor(PieceColor piececolor);
    void setPiecePosition(QString position);
    void setPieceAlive(bool pieceAlive);

signals:
    void pieceTypeChanged(PieceType piecetype);
    void pieceColorChanged(PieceColor piececolor);
    void piecePositionChanged(QString position);
    void pieceAliveChanged(bool pieceAlive);

private:
    QImage _image; //piece image
    PieceType m_type;
    PieceColor m_piececolor;
    QString m_position;
    bool m_pieceAlive;
};

#endif // CHESSMAN_H
