#include "TileMapLayer.hpp"
#include <QPainter>


TileMapLayer::TileMapLayer(QGraphicsScene* scene, LevelManager& levelManager, double zValue)
    : CanvasLayer(scene, levelManager)
{
    m_zValue = zValue;

    // Redraw completely on tilemap change
    connect(&m_levelManager, &LevelManager::selectedLevelCanvasChanged, this, &TileMapLayer::refresh);
    // Redraw also on tileset change, just in case
    connect(&m_levelManager, &LevelManager::selectedLevelItemSetChanged, this, &TileMapLayer::refresh);
    // Redraw also on layer change
    connect(&m_levelManager, &LevelManager::selectedLevelLayerSelectionChanged, this, &TileMapLayer::refresh);
    // Redraw also on level change
    connect(&m_levelManager, &LevelManager::levelSelectionChanged, this, &TileMapLayer::refresh);

    // Draw Tile, if only one tile of the tilemap changed
    connect(&m_levelManager, &LevelManager::selectedLevelCanvasTileChanged, this, &TileMapLayer::drawTile);
}

void TileMapLayer::refresh()
{
    Level* level = m_levelManager.getSelectedLevel();
    if (level)
    {
        m_tileSize = level->getTileSize();
        setTileMapIDs(level->getTileMap());
    }
    else
    {
        clearGraphicsTileItems();
    }

    CanvasLayer::refresh();
}

void TileMapLayer::drawTile(int tileID, const QPoint& position)
{
    GraphicsTileItem* clickedItem = m_tileMapTileItems[position.x()][position.y()];

    EditingContext* context = m_levelManager.getSelectedContext();
    Level* level = m_levelManager.getSelectedLevel();

    if (context && level && clickedItem)
    {
        clickedItem->setIndex(context->getSelectedTileID());
        if (clickedItem->index() == -1)
        {
            QPixmap pm(m_tileSize, m_tileSize);
            pm.fill(m_backgroundColor);
            clickedItem->setPixmap(pm);
        }
        else
        {
            clickedItem->setPixmap(level->getTileSet()[clickedItem->index()].scaled(m_tileSize, m_tileSize));
        }
    }
}

void TileMapLayer::handleMousePressEvent(QGraphicsSceneMouseEvent* event)
{
    // Draw or select item on mouse Press

    Level* level = m_levelManager.getSelectedLevel();
    EditingContext* context = m_levelManager.getSelectedContext();

    if (level == nullptr || context == nullptr)
    {
        return;
    }

    QPointF p = event->scenePos();
    int xIndex = p.x() / m_tileSize;
    int yIndex = p.y() / m_tileSize;

    // for left and right mouse buttons: draw or select tile
    if (-1 < xIndex && xIndex < (int) level->getLevelWidth() && -1 < yIndex && yIndex < (int) level->getLevelHeight())
    {

        if (event->button() == Qt::LeftButton)
        {
            // Set tile
            m_leftMouseButtonPressed = true;
            int tileID = context->getSelectedTileID();
            level->setTileAt(tileID, xIndex, yIndex);
        }
        else if (event->button() == Qt::RightButton)
        {
            // Pick tile from tilemap
            GraphicsTileItem* clickedItem = m_tileMapTileItems[xIndex][yIndex];
            context->setSelectedTileID(clickedItem->index());
        }
    }
}

void TileMapLayer::handleMouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    // Draw while pressing left

    Level* level = m_levelManager.getSelectedLevel();
    EditingContext* context = m_levelManager.getSelectedContext();

    if (level == nullptr || context == nullptr)
    {
        return;
    }

    QPointF p = event->scenePos();
    int xIndex = p.x() / m_tileSize;
    int yIndex = p.y() / m_tileSize;

    // if left mouse button pressed: draw tiles
    if (-1 < xIndex && xIndex < (int) level->getLevelWidth() && -1 < yIndex && yIndex < (int) level->getLevelHeight())
    {
        if (m_leftMouseButtonPressed)
        {
            // Set tile
            m_leftMouseButtonPressed = true;
            int tileID = context->getSelectedTileID();
            level->setTileAt(tileID, xIndex, yIndex);
        }
    }
}


void TileMapLayer::handleMouseReleasedEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        // Stop drawing while moving mouse
        m_leftMouseButtonPressed = false;
    }
}

void TileMapLayer::setTileMapIDs(const std::vector<std::vector<int>>& tileMapIDs)
{
    // Clear scene
    clearGraphicsTileItems();

    drawGrid();

    Level* level = m_levelManager.getSelectedLevel();

    if (level == nullptr)
    {
        return;
    }

    int levelWidth = level->getLevelWidth();
    int levelHeight = level->getLevelHeight();
    const std::vector<QPixmap>& tileSet = level->getTileSet();

    // Create new GraphicsTileItems with the correct pixmap and index and add them to the scene
    for (int x = 0; x < levelWidth; x++)
    {
        m_tileMapTileItems.push_back(std::vector<GraphicsTileItem*>());
        for (int y = 0; y < levelHeight; y++)
        {
            int id = tileMapIDs[x][y];
            GraphicsTileItem* graphicsTileItem;

            if (id == -1)
            {
                // air
                graphicsTileItem = new GraphicsTileItem(&m_backgroundColor, m_tileSize, m_tileSize);
            }
            else
            {
                // get correct pixmap
                QPixmap pm = tileSet[id].scaled(m_tileSize, m_tileSize);
                graphicsTileItem = new GraphicsTileItem(&pm, id);
            }
            // add graphics tile item to scene and store it in a map
            graphicsTileItem->setOffset(x * m_tileSize, y * m_tileSize);
            graphicsTileItem->setZValue(m_zValue);
            if (!m_visible)
            {
                graphicsTileItem->setVisible(false);
            }


            m_tileMapTileItems[x].push_back(graphicsTileItem);
            m_scene->addItem(graphicsTileItem);
        }
    }
}

void TileMapLayer::clearGraphicsTileItems()
{
    // remove and delete all graphics tile items
    if (m_tileMapTileItems.size() == 0)
    {
        return;
    }

    int levelWidth = m_tileMapTileItems.size();
    int levelHeight = m_tileMapTileItems[0].size();

    for (int x = 0; x < levelWidth; x++)
    {
        for (int y = 0; y < levelHeight; y++)
        {
            m_scene->removeItem(m_tileMapTileItems[x][y]);
            delete m_tileMapTileItems[x][y];
            m_tileMapTileItems[x][y] = nullptr;
        }
        m_tileMapTileItems[x].clear();
    }
    m_tileMapTileItems.clear();

    if (m_grid != nullptr)
    {
        m_scene->removeItem(m_grid);
        delete m_grid;
    }
}

void TileMapLayer::enable()
{
    for (std::vector<GraphicsTileItem*> column : m_tileMapTileItems)
    {
        for (GraphicsTileItem* i : column)
        {
            i->setEnabled(true);
        }
    }
}

void TileMapLayer::disable()
{
    for (std::vector<GraphicsTileItem*> column : m_tileMapTileItems)
    {
        for (GraphicsTileItem* i : column)
        {
            i->setEnabled(false);
        }
    }
}


void TileMapLayer::drawGrid()
{
    Level* level = m_levelManager.getSelectedLevel();

    if (level == nullptr)
    {
        return;
    }

    int levelWidth = level->getLevelWidth();
    int levelHeight = level->getLevelHeight();

    QColor borderColor = Qt::black;
    QColor fillColor = QColor(200, 200, 200, 125);

    QPixmap pixmap(level->getTileSize(), level->getTileSize());
    pixmap.fill(Qt::transparent);

    QPainter painter;
    painter.begin(&pixmap);

    QPen linePen = QPen(fillColor);
    linePen.setStyle(Qt::SolidLine);
    painter.setPen(linePen);

    painter.drawRect(0, 0, level->getTileSize() - 1, level->getTileSize() - 1);

    QRectF rect = QRectF(0, 0, levelWidth * level->getTileSize(), levelHeight * level->getTileSize());
    m_grid = m_scene->addRect(rect, borderColor, pixmap);
    m_grid->setZValue(m_zValue - 0.01);
    m_grid->setEnabled(false);
}


void TileMapLayer::hide()
{
    for (std::vector<GraphicsTileItem*> column : m_tileMapTileItems)
    {
        for (GraphicsTileItem* i : column)
        {
            i->setVisible(false);
        }
    }
    CanvasLayer::hide();
}

void TileMapLayer::show()
{
    for (std::vector<GraphicsTileItem*> column : m_tileMapTileItems)
    {
        for (GraphicsTileItem* i : column)
        {
            i->setVisible(true);
        }
    }
    CanvasLayer::show();
}
