#include "SpriteSetScene.hpp"
#include <QGraphicsSceneMouseEvent>
#include <QMenu>


SpriteSetScene::SpriteSetScene(LevelManager& levelManager, int itemSize, int padding)
    : ItemSetScene(itemSize, padding), m_levelManager(levelManager)
{
}

void SpriteSetScene::addSpriteSet(const std::vector<Sprite*>& spriteSet, int viewWidth)
{
    // Insert GraphicsSpriteItems
    for (Sprite* sprite : spriteSet)
    {
        GraphicsSpriteItem* item = new GraphicsSpriteItem(sprite, m_itemSize, true);
        addItem(item);

        std::string spriteID = sprite->getID();
        std::string label;

        if (m_levelManager.getSelectedLevel())
        {
            if (m_levelManager.getSelectedLevel()->getActorSprite() == sprite)
            {
                label += "★";

                if (spriteID.length() > 7)
                {
                    label += spriteID.substr(0, 7);
                    label += "...";
                }
                else
                {
                    label += spriteID;
                }
            }
            else
            {
                if (spriteID.length() > 8)
                {
                    label += spriteID.substr(0, 8);
                    label += "...";
                }
                else
                {
                    label += spriteID;
                }
            }
        }

        QGraphicsTextItem* textItem = new QGraphicsTextItem(QString::fromStdString(label));

        addItem(textItem);
    }

    arrange(viewWidth);
}

void SpriteSetScene::arrange(int viewWidth)
{
    // Set tile positions based on current ItemSetView width
    int viewItemsPerRow = viewWidth / m_itemSize - 1;
    int index = 0;
    int textHeight = 0;

    if (viewItemsPerRow > 0)
    {
        // Arrange Pixmaps
        for (QGraphicsItem* item : items(Qt::AscendingOrder))
        {
            int itemPosX = (index / 2 % viewItemsPerRow) * (m_itemSize + m_padding);
            int itemPosY = (index / 2 / viewItemsPerRow) * (m_itemSize + 2 * m_padding + textHeight);

            // Sprite Pixmap
            if (index % 2 == 0)
            {
                item->setPos(itemPosX, itemPosY);
            }
            // Sprite Label
            else
            {
                QGraphicsTextItem* text = static_cast<QGraphicsTextItem*>(item);
                textHeight = text->boundingRect().height();
                int textWidth = text->boundingRect().width();
                item->setPos(itemPosX + (m_itemSize - textWidth) / 2, itemPosY + m_itemSize + m_padding);
            }

            ++index;
        }
    }
}

void SpriteSetScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    ItemSetScene::mousePressEvent(event);
    GraphicsSpriteItem* item = dynamic_cast<GraphicsSpriteItem*>(itemAt(event->scenePos(), QTransform()));

    if (item && event->button() == Qt::RightButton)
    {
        emit openContextMenu(item, event->scenePos().toPoint());
    }
}