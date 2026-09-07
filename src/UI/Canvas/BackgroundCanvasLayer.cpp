#include "BackgroundCanvasLayer.hpp"

BackgroundCanvasLayer::BackgroundCanvasLayer(Background* background, QGraphicsScene* scene, LevelManager& LevelManager, double zValue)
    : CanvasLayer(scene, LevelManager), m_background(background)
{
    m_zValue = zValue;
    m_enabled = false;
    refresh();
}

BackgroundCanvasLayer::~BackgroundCanvasLayer()
{
    if (m_backgroundItem)
    {
        m_scene->removeItem(m_backgroundItem);
        delete m_backgroundItem;
    }
}


void BackgroundCanvasLayer::show()
{
    m_backgroundItem->setVisible(true);
    CanvasLayer::show();
}


void BackgroundCanvasLayer::hide()
{
    m_backgroundItem->setVisible(false);
    CanvasLayer::hide();
}


void BackgroundCanvasLayer::refresh()
{
    if (m_backgroundItem)
    {
        m_scene->removeItem(m_backgroundItem);
        delete m_backgroundItem;
        m_backgroundItem = nullptr;
    }

    Level* level = m_levelManager.getSelectedLevel();
    if (level)
    {
        int levelHeight = level->getLevelHeight() * level->getTileSize();
        int levelWidth = level->getLevelWidth() * level->getTileSize();
        m_backgroundItem = m_scene->addRect(0, 0, levelWidth, levelHeight);

        QBrush brush(m_background->getBackgroundImage().scaled(levelHeight, levelHeight, Qt::KeepAspectRatioByExpanding));
        m_backgroundItem->setBrush(brush);
        m_backgroundItem->setZValue(m_zValue);
        m_backgroundItem->setEnabled(false);
    }

    CanvasLayer::refresh();
}

const Background* BackgroundCanvasLayer::getBackground()
{
    return m_background;
}