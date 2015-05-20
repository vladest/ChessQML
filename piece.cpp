#include "piece.h"
#include <QPainter>

Piece::Piece(QQuickPaintedItem *parent): QQuickPaintedItem(parent)
, m_type(NoType)
, m_piececolor(NoColor)
, m_pieceAlive(false) {
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
    if (!_image.isDetached()) {
        painter->drawImage(boundingRect(), _image);
    }
}

void Piece::setPieceType(Piece::PieceType type) {
    if (m_type == type)
        return;

    m_type = type;
    emit pieceTypeChanged(type);
    update();
}

void Piece::setPieceColor(Piece::PieceColor piececolor) {
    if (m_piececolor == piececolor)
        return;

    m_piececolor = piececolor;
    emit pieceColorChanged(piececolor);
    update();
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
}

