#include "CanvasScene.hpp"

CanvasScene::CanvasScene(LevelManager& levelManager, QObject* parent)
    : QGraphicsScene(parent), m_tileMapLayer(this, levelManager),
      m_spriteLayer(this, levelManager), m_endPositionLayer(this, levelManager),
      m_activeLayer(nullptr), m_levelManager(levelManager)
{
    connect(&m_levelManager, &LevelManager::selectedLevelLayerSelectionChanged, this, &CanvasScene::updateActiveLayer);
    connect(&m_levelManager, &LevelManager::levelSelectionChanged, this, &CanvasScene::updateActiveLayer);
    connect(&m_levelManager, &LevelManager::selectedLevelContextLayerVisibiltyChanged, this, &CanvasScene::updateLayerVisibility);

    connect(&m_levelManager, &LevelManager::selectedLevelBackgroundChanged, this, &CanvasScene::refreshBackgrounds);
    connect(&m_levelManager, &LevelManager::levelSelectionChanged, this, &CanvasScene::refreshBackgrounds);
    connect(&m_levelManager, &LevelManager::selectedLevelCanvasChanged, this, &CanvasScene::refreshBackgrounds);
}


CanvasScene::~CanvasScene()
{
}

void CanvasScene::updateActiveLayer()
{
    EditingContext* context = m_levelManager.getSelectedContext();
    if (!context)
    {
        m_activeLayer = nullptr;
    }
    else
    {
        switch (context->getSelectedLayer())
        {
            case Layer::TILE_LAYER:
                m_activeLayer = &m_tileMapLayer;
                break;
            case Layer::SPRITE_LAYER:
                m_activeLayer = &m_spriteLayer;
                break;
            case Layer::ENDPOSITION_LAYER:
                m_activeLayer = &m_endPositionLayer;
                break;
            default:
                m_activeLayer = nullptr;
                break;
        }
    }

    enableCorrectLayer();
}


void CanvasScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (m_activeLayer != nullptr)
    {
        m_activeLayer->handleMousePressEvent(event);
    }

    QGraphicsScene::mousePressEvent(event);
}

void CanvasScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if (m_activeLayer != nullptr)
    {
        m_activeLayer->handleMouseMoveEvent(event);
    }

    QGraphicsScene::mouseMoveEvent(event);
}

void CanvasScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if (m_activeLayer != nullptr)
    {
        m_activeLayer->handleMouseReleasedEvent(event);
    }

    QGraphicsScene::mouseReleaseEvent(event);
}


void CanvasScene::enableCorrectLayer()
{
    std::vector<CanvasLayer*> layers{&m_tileMapLayer, &m_spriteLayer};

    for (CanvasLayer* l : layers)
    {
        if (l == m_activeLayer)
        {
            l->enable();
        }
        else
        {
            l->disable();
        }
    }
}

void CanvasScene::updateLayerVisibility()
{
    EditingContext* context = m_levelManager.getSelectedContext();
    Level* level = m_levelManager.getSelectedLevel();

    if (context && level)
    {
        m_spriteLayer.hide();
        m_tileMapLayer.hide();
        m_endPositionLayer.hide();
        for (Layer l : context->getVisibleLayers())
        {
            if (l == Layer::TILE_LAYER)
            {
                m_tileMapLayer.show();
            }
            else if (l == Layer::SPRITE_LAYER)
            {
                m_spriteLayer.show();
            }
            else if (l == Layer::ENDPOSITION_LAYER)
            {
                m_endPositionLayer.show();
            }
        }

        // first hide all backgrounds
        for (BackgroundCanvasLayer* b : m_backgroundLayers)
        {
            b->hide();
        }
        // show all backgrounds
        for (Background* b : context->getVisibleBackgrounds())
        {
            auto layer = std::find_if(m_backgroundLayers.begin(), m_backgroundLayers.end(), [b](BackgroundCanvasLayer* obj)
                                      { return b == obj->getBackground(); });

            if (layer != m_backgroundLayers.end())
            {
                (*layer)->show();
            }
        }
    }
}


void CanvasScene::refreshBackgrounds()
{
    for (BackgroundCanvasLayer* b : m_backgroundLayers)
    {
        delete b;
        b = nullptr;
    }
    m_backgroundLayers.clear();

    Level* level = m_levelManager.getSelectedLevel();
    if (level)
    {
        for (Background* b : level->getBackgrounds())
        {
            m_backgroundLayers.push_back(new BackgroundCanvasLayer(b, this, m_levelManager, -b->getDepth()));
        }
    }
    updateLayerVisibility();
    setSceneRect(itemsBoundingRect());
}