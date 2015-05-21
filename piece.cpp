#include "piece.h"
#include <QPainter>

Piece::Piece(QQuickItem *parent): QQuickPaintedItem(parent)
  , m_type(NoType)
  , m_piececolor(NoColor)
  , m_pieceAlive(false) {
    setFlag(QQuickItem::ItemHasContents, true);
}

Piece::PieceType Piece::pieceType() const {
    return m_type;
}

Piece::PieceColor Piece::pieceColor() const {
    return m_piececolor;
}

QString Piece::piecePosition() const {
    return m_position;
}

void Piece::paint(QPainter *painter) {
    if (!_image.isNull()) {
        //qDebug() << "updating" << boundingRect();
        painter->drawImage(boundingRect(), _image);
    }
}

void Piece::setPieceType(Piece::PieceType type) {
    if (m_type == type)
        return;

    m_type = type;
    emit pieceTypeChanged(type);
    loadImage();
}

void Piece::setPieceColor(Piece::PieceColor piececolor) {
    if (m_piececolor == piececolor)
        return;

    m_piececolor = piececolor;
    emit pieceColorChanged(piececolor);
    loadImage();
}

void Piece::setPiecePosition(QString position) {
    if (m_position == position)
        return;

    m_position = position;
    emit piecePositionChanged(position);
}

bool Piece::pieceAlive() const {
    return m_pieceAlive;
}

void Piece::setPieceAlive(bool pieceAlive) {
    if (m_pieceAlive == pieceAlive)
        return;
    m_pieceAlive = pieceAlive;
    emit pieceAliveChanged(pieceAlive);
    if (m_pieceAlive)
        setVisible(true);
    else
        setVisible(false);
}

void Piece::loadImage() {
    if (m_type != NoType && m_piececolor != NoColor && _image.isNull()) {
        QString piecetype = "pawn";
        QString piececolor = "white";
        switch (m_type) {
        case Rook: piecetype = "rook"; break;
        case Knight: piecetype = "knight"; break;
        case Bishop: piecetype = "bishop"; break;
        case King: piecetype = "king"; break;
        case Queen: piecetype = "queen"; break;
        }
        if (m_piececolor == Black)
            piececolor = "black";
        QString imgpath = QString(":/img/%1_%2.svg").arg(piecetype).arg(piececolor);
        if (!_image.load(imgpath)) {
            qWarning() << "Error loading image:" << imgpath;
            return;
        }
        update();
    }
}

