#include "ItemSetScene.hpp"
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>


ItemSetScene::ItemSetScene(int itemSize, int padding)
    : m_itemSize(itemSize), m_padding(padding)
{
    connect(this, &QGraphicsScene::changed, this, &ItemSetScene::onChange);
}

void ItemSetScene::onChange()
{
    // Used to shrink the TileSetView
    setSceneRect(itemsBoundingRect());
}

void ItemSetScene::clear()
{
    QGraphicsScene::clear();
    setSceneRect(itemsBoundingRect());
}

void ItemSetScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    // Emit selected item
    QGraphicsScene::mousePressEvent(event);
    QGraphicsPixmapItem* item = dynamic_cast<QGraphicsPixmapItem*>(itemAt(event->scenePos(), QTransform()));

    if (item)
    {
        emit selectedItemUpdated(item);
    }
}