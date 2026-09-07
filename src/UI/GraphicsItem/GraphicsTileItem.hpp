/**
 * @file GraphicsTileItem.hpp
 * @author Leveleditor-Gruppe
 * @brief
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */


/******************************************************************************
 *  GraphicsTileItem.hpp
 *  Copyright (c) 2020 Thomas Wiemann.
 *
 *  Restricted usage. Licensed for participants of the
 *  course "The C++ Programming Language" only.
 *
 *  No unauthorized distribution.
 ******************************************************************************/

#pragma once

#include <QGraphicsPixmapItem>
#include <QWidget>

/**
 * @brief   Class to represent a tile in the QGraphicScene
 *
 */
class GraphicsTileItem : public QGraphicsPixmapItem
{
public:
    /**
     * @brief   Construct a new Graphics Tile Item object
     *
     * @param tilePixmap pixmap for tile
     * @param index      Tile index stored in the item
     */
    GraphicsTileItem(QPixmap* tilePixmap, int index);

    /**
     * @brief   Construct a new Graphics Tile Item object with plain color.
     *          Used to render a default color for empty tiles
     *
     * @param color     Color for empty spaces
     * @param w         Tile width
     * @param h         Tile height
     */
    GraphicsTileItem(QColor* color, int w, int h);

    /**
     * @brief Return the Tiles index
     *
     * @return int
     */
    int index() const;

    /**
     * @brief Set the Index object
     *
     * @param i
     */
    void setIndex(int i);

private:
    /// Tile index
    int m_index;
};