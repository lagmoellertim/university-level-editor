#include "GraphicsSpriteItem.hpp"
#include <QPainter>


GraphicsSpriteItem::GraphicsSpriteItem(Sprite* sprite, int size, bool fitInSquare)
    : m_sprite(sprite)
{
    QPixmap pm = sprite->getFrames()[0].scaled(size, size, Qt::KeepAspectRatio);

    // Put the scaled Sprite Pixmap inside a transparent square
    if (fitInSquare)
    {
        QPixmap base(size, size);
        base.fill(Qt::transparent);

        QPainter painter(&base);
        painter.drawPixmap((size - pm.width()) / 2, (size - pm.height()) / 2, pm.width(), pm.height(), pm);

        setPixmap(base);
    }
    else
    {
        setPixmap(pm);
    }
}

Sprite* GraphicsSpriteItem::getSprite() const
{
    return m_sprite;
}

void GraphicsSpriteItem::setSprite(Sprite* sprite, int size)
{
    setPixmap(sprite->getFrames()[0].scaled(size, size));
    m_sprite = sprite;
}
