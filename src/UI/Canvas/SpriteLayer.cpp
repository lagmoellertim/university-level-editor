#include "SpriteLayer.hpp"


SpriteLayer::SpriteLayer(QGraphicsScene* scene, LevelManager& levelManager, double zValue)
    : CanvasLayer(scene, levelManager)
{
    m_zValue = zValue;

    // Redraw completely on tilemap change
    connect(&m_levelManager, &LevelManager::selectedLevelCanvasChanged, this, &SpriteLayer::refresh);
    // Redraw also on tileset change, just in case
    connect(&m_levelManager, &LevelManager::selectedLevelItemSetChanged, this, &SpriteLayer::refresh);
    // Redraw also on layer change
    connect(&m_levelManager, &LevelManager::selectedLevelLayerSelectionChanged, this, &SpriteLayer::refresh);
    // Redraw also on level change
    connect(&m_levelManager, &LevelManager::levelSelectionChanged, this, &SpriteLayer::refresh);

    // Draw Sprite if placed
    connect(&m_levelManager, &LevelManager::selectedLevelCanvasSpritePlaced, this, &SpriteLayer::drawSprite);

    // Remove Sprite if erased
    connect(&m_levelManager, &LevelManager::selectedLevelCanvasSpriteErased, this, &SpriteLayer::removeSprite);
}


void SpriteLayer::handleMousePressEvent(QGraphicsSceneMouseEvent* event)
{
    EditingContext* context = m_levelManager.getSelectedContext();
    Level* level = m_levelManager.getSelectedLevel();

    if (level == nullptr || context == nullptr)
    {
        return;
    }

    if (context->getSelectedLayer() != Layer::SPRITE_LAYER)
    {
        return;
    }

    bool placeSprite = false;
    bool removeSprite = false;
    // Try to place sprite
    Sprite* selectedSprite = context->getSelectedSprite();

    if (event->button() == Qt::LeftButton)
    {
        if (selectedSprite != nullptr)
        {
            placeSprite = true;
        }
        else
        {
            removeSprite = true;
        }
    }
    else if (event->button() == Qt::RightButton)
    {
        removeSprite = true;
    }


    if (placeSprite)
    {
        // place sprite at mouse position
        QPoint mouseScenePos = event->scenePos().toPoint();
        selectedSprite->addCoordinates(mouseScenePos);
    }
    else if (removeSprite)
    {
        // remove Sprite at mouse position
        QGraphicsItem* clickedItem = m_scene->itemAt(event->scenePos(), QTransform());

        if (clickedItem == nullptr || !clickedItem->isEnabled())
        {
            return;
        }
        GraphicsSpriteItem* clickedSprite = static_cast<GraphicsSpriteItem*>(clickedItem);
        QPoint pos = clickedSprite->offset().toPoint() + QPoint(clickedSprite->getSprite()->getWidth() / 2, clickedSprite->getSprite()->getHeight() / 2);

        Sprite* sprite = clickedSprite->getSprite();

        sprite->removeCoordinates(pos);
    }
}

void SpriteLayer::handleMouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
}

void SpriteLayer::handleMouseReleasedEvent(QGraphicsSceneMouseEvent* event)
{
}


void SpriteLayer::refresh()
{
    clearSpriteTileItems();

    Level* level = m_levelManager.getSelectedLevel();

    if (level == nullptr)
    {
        return;
    }

    for (Sprite* sprite : level->getSprites())
    {
        for (QPoint p : sprite->getCoordinates())
        {
            drawSprite(sprite, p);
        }
    }

    CanvasLayer::refresh();
}

void SpriteLayer::drawSprite(Sprite* sprite, const QPoint& position)
{
    if (!sprite)
    {
        return;
    }
    int spriteWidth = sprite->getWidth();
    int spriteHeight = sprite->getHeight();

    int size = sprite->getWidth() > sprite->getHeight() ? sprite->getWidth() : sprite->getHeight();
    GraphicsSpriteItem* graphicsSpriteItem = new GraphicsSpriteItem(sprite, size);

    graphicsSpriteItem->setOffset(position - QPoint(spriteWidth / 2, spriteHeight / 2));
    graphicsSpriteItem->setZValue(m_zValue);

    if (!m_visible)
    {
        graphicsSpriteItem->setVisible(false);
    }


    m_sprites.push_back(graphicsSpriteItem);
    m_scene->addItem(graphicsSpriteItem);
}

void SpriteLayer::removeSprite(Sprite* sprite, const QPoint& position)
{
    auto it = std::find_if(m_sprites.begin(), m_sprites.end(), [sprite, position](const GraphicsSpriteItem* obj)
                           {
                               QPoint deltaToCenter = QPoint(sprite->getWidth() / 2, sprite->getHeight() / 2);
                               return obj->offset().toPoint() == position - deltaToCenter && obj->getSprite() == sprite;
                           });

    if (it != m_sprites.end())
    {
        GraphicsSpriteItem* tempToDelete = *it;
        (*it)->setEnabled(false);
        m_scene->removeItem(*it);
        m_sprites.erase(it);
        delete tempToDelete;
    }
}

void SpriteLayer::clearSpriteTileItems()
{
    for (GraphicsSpriteItem* sprite : m_sprites)
    {
        m_scene->removeItem(sprite);
        delete sprite;
    }
    m_sprites.clear();
}


void SpriteLayer::enable()
{
    for (GraphicsSpriteItem* s : m_sprites)
    {
        s->setEnabled(true);
    }
    CanvasLayer::enable();
}

void SpriteLayer::disable()
{
    for (GraphicsSpriteItem* s : m_sprites)
    {
        s->setEnabled(true);
    }
    CanvasLayer::disable();
}


void SpriteLayer::show()
{
    for (GraphicsSpriteItem* s : m_sprites)
    {
        s->setVisible(true);
    }
    CanvasLayer::show();
}

void SpriteLayer::hide()
{
    for (GraphicsSpriteItem* s : m_sprites)
    {
        s->setVisible(false);
    }
    CanvasLayer::hide();
}