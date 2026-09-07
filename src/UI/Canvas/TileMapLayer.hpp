/**
 * @file TileMapLayer.hpp
 * @author Leveleditor-Gruppe
 * @brief Layer which manages all Tiles visible on the leveleditor canvas.
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include "../GraphicsItem/GraphicsTileItem.hpp"
#include "CanvasLayer.hpp"

/**
 * @brief  Layer which manages all Tiles visible on the leveleditor canvas.
 * Also displays a grid which indicates where tiles may be placed.
 */
class TileMapLayer : public CanvasLayer
{
public:
    /**
     * @brief Construct a new Tilemap.
     *
     * @param scene Canvas scene to which all tiles and the grid will be added
     * @param levelManager LevelManager
     * @param zValue z-value of this layer. Layers with higher z-values be drawn in front of layers with lower z-values.
     */
    TileMapLayer(QGraphicsScene* scene, LevelManager& levelManager, double zValue = 1.);

    /**
     * @brief Handles the given Mouse Event.
     * On left click, the selected tile will be placed at mouse position.
     * On right click, the clicked tile will be selected.
     *
     * @param event Mouse Event.
     */
    void handleMousePressEvent(QGraphicsSceneMouseEvent* event);

    /**
     * @brief Handle the given Mouse Event.
     * If the Mouse is moved while pressing left, the selected tile will be placed continuously at the mouse position.
     *
     * @param event Mouse Event.
     */
    void handleMouseMoveEvent(QGraphicsSceneMouseEvent* event);

    /**
     * @brief Handle the given Mouse Event.
     * Registers the release of the left mouse button, so that the continuous tile placement stops.
     *
     * @param event
     */
    void handleMouseReleasedEvent(QGraphicsSceneMouseEvent* event);

    /**
     * @brief Enables all tiles of this layer for mouse interaction.
     *
     */
    void enable() override;

    /**
     * @brief Disables all tiles of this layer for mouse interaction.
     *
     */
    void disable() override;

    /**
     * @brief Hides all tiles of this layer. The grid will still be visible.
     *
     */
    void hide() override;

    /**
     * @brief Shows all tiles of this layer.
     *
     */
    void show() override;

signals:
public slots:
    /**
     * @brief Redraws all tiles and the grid of the selected level.
     *
     */
    void refresh();

    /**
     * @brief Draw one tile at the given position.
     *
     * @param tileID Tile-ID of the tile to be drawn
     * @param position Position in tile coordinates at which the tile should be drawn.
     */
    void drawTile(int tileID, const QPoint& position);

private:
    /**
     * @brief Sets the Tilemap-IDs and updates this layer accordingly.
     *
     * @param tileMapIDs Tilemap-Tile-IDs
     */
    void setTileMapIDs(const std::vector<std::vector<int>>& tileMapIDs);

    /**
     * @brief Draws a grid which indicates where tiles may be placed.
     *
     */
    void drawGrid();

    /**
     * @brief Deletes all GraphicsTileItems of this layer.
     *
     */
    void clearGraphicsTileItems();

    /// Tile width and height.
    int m_tileSize = 32;

    /// GraphicsTileItems which make up the tilemap.
    std::vector<std::vector<GraphicsTileItem*>> m_tileMapTileItems;

    /// Grid which indicates where tiles may be placed.
    QGraphicsRectItem* m_grid;

    /// State which indicates whether the left mouse button is pressed. Used for continuous tile placement.
    bool m_leftMouseButtonPressed = false;
};