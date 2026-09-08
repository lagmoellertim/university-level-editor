/**
 * @file CanvasScene.hpp
 * @author Leveleditor-Gruppe
 * @brief Tilemap-Canvas on which tiles, sprites and the endposition of a level can be drawn.
 * @version 0.1
 * @date 2022-02-18
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <QtWidgets>
#include <vector>

#include "../../Lib/LevelManager/EditingContext.hpp"
#include "../../Lib/LevelManager/LevelManager.hpp"
#include "BackgroundCanvasLayer.hpp"
#include "EndPositionLayer.hpp"
#include "SpriteLayer.hpp"
#include "TileMapLayer.hpp"


/**
 * @brief Scene which holds all layers visible on the Canvas.
 *
 */
class CanvasScene : public QGraphicsScene
{
    Q_OBJECT

public:
    /**
     * @brief Construct new empty CanvasScene without any tiles, sprites.
     *
     * @param levelManager LevelManager
     * @param parent parent Qwidget
     */
    CanvasScene(LevelManager& levelManager, QObject* parent = nullptr);

    /**
     * @brief Destructor, frees memory
     *
     */
    ~CanvasScene();

    void enableCorrectLayer();

signals:
public slots:

    /**
     * @brief Updates the active layer (m_activeLayer) based on the selected Layer.
     *
     */
    void updateActiveLayer();

    /**
     * @brief Update which layers are visible on the canvas.
     *
     */
    void updateLayerVisibility();

    /**
     * @brief Redraws all backgrounds of the selected level.
     *
     */
    void refreshBackgrounds();

protected:
    /**
     * @brief Called if a mouse button is pressed while on the canvas. The event is then handled by the active layer.
     *
     * @param event Mouse Event
     */
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);

    /**
     * @brief  Called if the mouse is moved on the canvas. The event is then handled by the active layer.
     *
     * @param event Mouse Event
     */
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event);

    /**
     * @brief Called if a mouse button is released while on the canvas. The event is then handled by the active layer.
     *
     * @param event Mouse Event
     */
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

private:
    /// Tilemap layer which manages all tiles on the canvas, the interaction with them and the tile grid.
    TileMapLayer m_tileMapLayer;

    /// Sprite layer which holds all sprites on the canvas.
    SpriteLayer m_spriteLayer;

    /// Layer on which the end position of a level is placed.
    EndPositionLayer m_endPositionLayer;

    /// Currently active layer which is editable.
    CanvasLayer* m_activeLayer;

    std::vector<BackgroundCanvasLayer*> m_backgroundLayers;

    /// LevelManager
    LevelManager& m_levelManager;
};