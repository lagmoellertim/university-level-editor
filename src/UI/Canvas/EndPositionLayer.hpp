/**
 * @file EndPositionLayer.hpp
 * @author Leveleditor-Gruppe
 * @brief Layer which manages the line indicating the level end.
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include "CanvasLayer.hpp"
#include <QtWidgets>

/**
 * @brief Layer which manages the line indicating the level ending.
 *
 */
class EndPositionLayer : public CanvasLayer
{
    Q_OBJECT
public:
    /**
     * @brief Construct a new EndPositionLayer.
     *
     * @param scene canvas scene
     * @param levelManager LevelManager
     * @param zValue z-value of this layer. Layers with higher z-values will be drawn in front of layers with lower z-values.
     */
    EndPositionLayer(QGraphicsScene* scene, LevelManager& levelManager, double zValue = 3.);

    /**
     * @brief Destroy the EndPositionLayer.
     *
     */
    ~EndPositionLayer();

    /**
     * @brief Handles the given event. Sets the new level ending position on left click.
     *
     * @param event Mouse Event
     */
    void handleMousePressEvent(QGraphicsSceneMouseEvent* event) override;

    /**
     * @brief Does nothing.
     *
     * @param event Mouse Event
     */
    void handleMouseMoveEvent(QGraphicsSceneMouseEvent* event) override{};

    /**
     * @brief Does nothing.
     *
     * @param event Mouse Event
     */
    void handleMouseReleasedEvent(QGraphicsSceneMouseEvent* event) override{};

    /**
     * @brief Does nothing.
     *
     */
    void enable() override{};

    /**
     * @brief Does nothing.
     *
     */
    void disable() override{};


    /**
     * @brief Shows this layer.
     *
     */
    void show() override;

    /**
     * @brief Hides this layer.
     *
     */
    void hide() override;

signals:
public slots:
    /**
     * @brief Redraws all tiles from the line indicating the ending of the level.
     *
     */
    void refresh() override;

private:
    /// Line representing the end of the level.
    QGraphicsLineItem* m_endLine = nullptr;
};
