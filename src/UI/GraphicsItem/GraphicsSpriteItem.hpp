/**
 * @file GraphicsSpriteItem.hpp
 * @author Leveleditor-Gruppe
 * @brief
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */


#pragma once

#include "../../Lib/LevelManager/Sprite.hpp"
#include <QGraphicsPixmapItem>
#include <QWidget>

/**
 * @brief   Represents a sprite in the QGraphicScene
 *
 */
class GraphicsSpriteItem : public QGraphicsPixmapItem
{
public:
    /**
     * @brief   Construct a new GraphicsSpriteItem object
     *
     * @param sprite Pointer to the corresponding sprite object with pixmap
     * @param size Size to scale the Pixmap
     * @param fitInSquare Will draw the pixmap onto a transparent square pixmap
     */
    GraphicsSpriteItem(Sprite* sprite, int size, bool fitInSquare = false);

    /**
     * @brief Get the Sprite object
     *
     * @return Sprite* The Sprite object
     */
    Sprite* getSprite() const;

    /**
     * @brief Set the Sprite object
     *
     * @param sprite Pointer to corresponding sprite object
     * @param size Size to scale the Pixmap
     */
    void setSprite(Sprite* sprite, int size);

private:
    /// Corresponding sprite pointer
    Sprite* m_sprite;
};
