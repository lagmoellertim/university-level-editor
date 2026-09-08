/**
 * @file CanvasLayer.hpp
 * @author Leveleditor-Gruppe
 * @brief Abstract CanvasLayer class for all layers of the leveleditor canvas.
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include "../../Lib/LevelManager/LevelManager.hpp"
#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsSceneMouseEvent>

/**
 * @brief Abstract CanvasLayer class for all layers of the leveleditor canvas.
 *
 */
class CanvasLayer : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Construct a new Canvas Layer
     *
     * @param scene Canvas scene
     * @param levelManager LevelManager
     */
    CanvasLayer(QGraphicsScene* scene, LevelManager& levelManager);

    /**
     * @brief Mouse-Press-Event-Handler for the layer.
     *
     * @param event Mouse Event
     */
    virtual void handleMousePressEvent(QGraphicsSceneMouseEvent* event) = 0;

    /**
     * @brief Mouse-Move-Event-Handler for the layer.
     *
     * @param event Mouse Event
     */
    virtual void handleMouseMoveEvent(QGraphicsSceneMouseEvent* event) = 0;

    /**
     * @brief Mouse-Released-Event-Handler for the layer.
     *
     * @param event Mouse Event
     */
    virtual void handleMouseReleasedEvent(QGraphicsSceneMouseEvent* event) = 0;

    /**
     * @brief Redraws this layer with regard to visibility.
     *
     */
    virtual void refresh();

    /**
     * @brief Enables this layer, e.g. for mouse clicks.
     * Enables items of this layer for which mouse interaction should be possible, e.g. tiles, sprites.
     * Not all items of a layer must be enabled, if no mouse interaction should be allowed with them.
     */
    virtual void enable()
    {
        m_enabled = true;
    };

    /**
     * @brief Disables this layer, thus, removes mouse interaction with them. See enable().
     *
     */
    virtual void disable()
    {
        m_enabled = false;
    };

    /**
     * @brief Hides this layer.
     *
     */
    virtual void hide()
    {
        m_visible = false;
    };

    /**
     * @brief Shows this layer.
     *
     */
    virtual void show()
    {
        m_visible = true;
    };

protected:
    /// Background color of layer.
    QColor m_backgroundColor = QColor(255, 255, 255, 0);

    /// State whether this layer is enabled.
    bool m_enabled = false;

    /// State whether this layer is visible.
    bool m_visible = true;

    /// Z-value of this layer. Layers with higher z-values will be drawn on top of layers with lower z-values.
    qreal m_zValue = 1.;

    /// Canvas scene to which the items of this layer will be added.
    QGraphicsScene* m_scene = nullptr;

    /// LevelManager.
    LevelManager& m_levelManager;
};