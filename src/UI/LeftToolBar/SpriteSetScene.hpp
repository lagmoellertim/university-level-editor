/**
 * @file SpriteSetScene.hpp
 * @author Leveleditor-Gruppe
 * @brief
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */


#pragma once

#include "../../Lib/LevelManager/LevelManager.hpp"
#include "../GraphicsItem/GraphicsSpriteItem.hpp"
#include "ItemSetScene.hpp"
#include <vector>


/**
 * @brief Represents a set of Sprites displayed in a QGraphicsView
 *
 */
class SpriteSetScene : public ItemSetScene
{
    Q_OBJECT
public:
    /**
     * @brief Construct a new Sprite Set Scene object
     *
     * @param levelManager LevelManager (to get the actor Sprite)
     * @param itemSize Size of displayed Sprites
     * @param padding Padding between Sprites
     */
    SpriteSetScene(LevelManager& levelManager, int itemSize, int padding);

    /**
     * @brief Add a new SpriteSet to this scene (append) and call arrange
     *
     * @param spriteSet SpriteSet that will be appended
     * @param viewWidth Width of the GraphicsView (for arrange)
     */
    void addSpriteSet(const std::vector<Sprite*>& spriteSet, int viewWidth);

    /**
     * @brief Arrange Sprite positions to fit the viewWidth of GraphicsView for dynamic resizing
     *
     * @param viewWidth Width of the SpriteSetView
     */
    void arrange(int viewWidth) override;

signals:
    /**
     * @brief Sent, when a sprite is right clicked to open a Context Menu
     *
     * @param selectedSprite The right clicked Sprite
     * @param pos Position
     */
    void openContextMenu(GraphicsSpriteItem* selectedSprite, QPoint pos);

protected:
    /**
     * @brief Handles right-click on Sprites. Send openContextMenu signal.
     *
     * @param event
     */
    void mousePressEvent(QGraphicsSceneMouseEvent* event);

private:
    /// LevelManager
    LevelManager& m_levelManager;
};