#include "EndPositionLayer.hpp"

EndPositionLayer::EndPositionLayer(QGraphicsScene* scene, LevelManager& levelManager, double zValue)
    : CanvasLayer(scene, levelManager)
{
    connect(&m_levelManager, &LevelManager::selectedLevelMetadataChanged, this, &EndPositionLayer::refresh);
    connect(&m_levelManager, &LevelManager::levelSelectionChanged, this, &EndPositionLayer::refresh);

    m_zValue = zValue;
    m_enabled = false;
}

EndPositionLayer::~EndPositionLayer()
{
}


void EndPositionLayer::handleMousePressEvent(QGraphicsSceneMouseEvent* event)
{
    EditingContext* context = m_levelManager.getSelectedContext();
    Level* level = m_levelManager.getSelectedLevel();

    if (level == nullptr || context == nullptr)
    {
        return;
    }

    if (context->getSelectedLayer() != Layer::ENDPOSITION_LAYER)
    {
        return;
    }

    if (event->button() == Qt::LeftButton)
    {
        int levelWidth = level->getLevelWidth() * level->getTileSize();
        int levelHeight = level->getLevelHeight() * level->getTileSize();

        int mouseX = event->scenePos().toPoint().x();
        int mouseY = event->scenePos().toPoint().y();
        if (0 < mouseX && mouseX < levelWidth && 0 < mouseY && mouseY < levelHeight)
        {
            level->setEndPosition(mouseX);
        }
    }
}

void EndPositionLayer::show()
{
    if (m_endLine)
    {
        m_endLine->setVisible(true);
    }
    CanvasLayer::show();
}

void EndPositionLayer::hide()
{
    if (m_endLine)
    {
        m_endLine->setVisible(false);
    }
    CanvasLayer::hide();
}

void EndPositionLayer::refresh()
{
    Level* level = m_levelManager.getSelectedLevel();

    if (level == nullptr)
    {
        return;
    }

    if (m_endLine)
    {
        delete m_endLine;
        m_endLine = nullptr;
    }

    int levelHeight = level->getLevelHeight() * level->getTileSize();
    int x = level->getEndPosition();

    QPen pen = QPen(QColor(50, 255, 50, 200));
    pen.setWidth(5);
    m_endLine = m_scene->addLine(x, 0, x, levelHeight, pen);
    if (!m_visible)
    {
        m_endLine->setVisible(false);
    }
    m_endLine->setEnabled(false);
    m_endLine->setZValue(m_zValue);
}