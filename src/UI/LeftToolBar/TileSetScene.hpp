/**
 * @file TileSetScene.hpp
 * @author Leveleditor-Gruppe
 * @brief
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "../GraphicsItem/GraphicsTileItem.hpp"
#include "ItemSetScene.hpp"
#include <vector>


/**
 * @brief Represents a TileSet displayed in a QGraphicsView
 *
 */
class TileSetScene : public ItemSetScene
{
    Q_OBJECT
public:
    /**
     * @brief Construct a new Tile Set Scene object
     *
     * @param itemSize Size of displayed Tiles (pixels)
     * @param padding Padding between Tiles
     */
    TileSetScene(int itemSize, int padding);

    /**
     * @brief Add a new TileSet to this scene (append) and call arrange
     *
     * @param tileSet TileSet that will be appended
     * @param viewWidth Width of the GraphicsView (for arrange method)
     */
    void addTileSet(const std::vector<QPixmap>& tileSet, int viewWidth);

    /**
     * @brief Arrange tile positions to fit the viewWidth of GraphicsView for dynamic resizing
     *
     * @param viewWidth Width of the TileSetView
     */
    void arrange(int viewWidth) override;

    /**
     * @brief Clear all tiles
     *
     */
    void clear() override;

private:
    /// Used to set the tile ids, incremented after every added tile
    int m_currentId;
};