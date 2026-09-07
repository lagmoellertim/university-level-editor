#include "CanvasLayer.hpp"


CanvasLayer::CanvasLayer(QGraphicsScene* scene, LevelManager& levelManager)
    : QObject(), m_scene(scene), m_levelManager(levelManager)
{
}

void CanvasLayer::refresh()
{
    if (m_enabled)
    {
        enable();
    }
    else
    {
        disable();
    }

    if (m_visible)
    {
        show();
    }
    else
    {
        hide();
    }

    m_scene->setSceneRect(m_scene->itemsBoundingRect());
}