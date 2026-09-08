/**
 * @file SpriteLayer.hpp
 * @author Leveleditor-Gruppe
 * @brief Layer which manages all sprites on the leveleditor canvas.
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include "../GraphicsItem/GraphicsSpriteItem.hpp"
#include "CanvasLayer.hpp"

/**
 * @brief Layer which manages all sprites on the leveleditor canvas.
 *
 */
class SpriteLayer : public CanvasLayer
{
    Q_OBJECT
public:
    /**
     * @brief Construct a new SpriteLayer
     *
     * @param scene Canvas Scene to which the sprites will be added.
     * @param levelManager LevelManager
     * @param zValue z-value of this layer. Layers with higher z-values be drawn in front of layers with lower z-values.
     */
    SpriteLayer(QGraphicsScene* scene, LevelManager& levelManager, double zValue = 2.);

    /**
     * @brief Handle the given Mouse Event.
     * Places a Sprite on left click at the mouse position. Removes the clicked Sprite on right click.
     *
     * @param event Mouse Event
     */
    void handleMousePressEvent(QGraphicsSceneMouseEvent* event) override;

    /**
     * @brief Does nothing.
     *
     * @param event Mouse Event
     */
    void handleMouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

    /**
     * @brief Does nothing.
     *
     * @param event Mouse Event
     */
    void handleMouseReleasedEvent(QGraphicsSceneMouseEvent* event) override;

    /**
     * @brief Enables all sprites for mouse interaction.
     *
     */
    void enable() override;

    /**
     * @brief Disables all sprites for mouse interaction.
     *
     */
    void disable() override;

    /**
     * @brief Shows all Sprites.
     *
     */
    void show() override;

    /**
     * @brief Hides all Sprites.
     *
     */
    void hide() override;

signals:
public slots:
    /**
     * @brief Redraws all sprites of the selected level.
     *
     */
    void refresh() override;

    /**
     * @brief Draws one sprite on the canvas at the given position.
     *
     * @param sprite Type of sprite to be drawn on the canvas.
     * @param position Position at which the sprite should be drawn.
     */
    void drawSprite(Sprite* sprite, const QPoint& position);

    /**
     * @brief Removes one Sprite at given position.
     *
     * @param sprite Type of sprite to be removed from the canvas.
     * @param position Position of the sprite which should be removed.
     */
    void removeSprite(Sprite* sprite, const QPoint& position);

private:
    /**
     * @brief Deletes all GraphicsSpriteItems on the canvas.
     *
     */
    void clearSpriteTileItems();

    /// All Sprites which are placed on the canvas.
    std::vector<GraphicsSpriteItem*> m_sprites;
};