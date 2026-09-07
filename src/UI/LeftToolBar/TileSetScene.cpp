#include "TileSetScene.hpp"


TileSetScene::TileSetScene(int itemSize, int padding)
    : ItemSetScene(itemSize, padding), m_currentId(0)
{
}

void TileSetScene::addTileSet(const std::vector<QPixmap>& tileSet, int viewWidth)
{
    // Insert correctly scaled GraphicsTileItems
    for (const QPixmap& tile : tileSet)
    {
        QPixmap pm = tile.scaled(m_itemSize, m_itemSize);
        GraphicsTileItem* item = new GraphicsTileItem(&pm, m_currentId++);
        addItem(item);
    }

    arrange(viewWidth);
}

void TileSetScene::arrange(int viewWidth)
{
    // Set tile positions based on current ItemSetView width
    int viewItemsPerRow = viewWidth / m_itemSize - 1;
    int index = 0;

    if (viewItemsPerRow > 0)
    {
        // Arrange Pixmaps
        for (QGraphicsItem* item : items(Qt::AscendingOrder))
        {
            item->setPos((index % viewItemsPerRow) * (m_itemSize + m_padding),
                         (index / viewItemsPerRow) * (m_itemSize + m_padding));

            ++index;
        }
    }
}

void TileSetScene::clear()
{
    // Clear tiles and reset current id
    ItemSetScene::clear();
    m_currentId = 0;
}