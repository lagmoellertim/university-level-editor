/**
 * @file BackgroundCanvasLayer.hpp
 * @author Leveleditor-Gruppe
 * @brief Layer for one background of the level for the leveleditor canvas.
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
 * @brief Layer for one background for the leveleditor canvas.
 */
class BackgroundCanvasLayer : public CanvasLayer
{
public:
    /**
     * @brief Construct a new BackgroundCanvasLayer.
     *
     * @param m_background Pointer to the background which should be represented by this layer
     * @param scene Leveleditor canvas scene to which the background will be added.
     * @param LevelManager LevelManager
     * @param zValue z-value of this layer. Layers with higher z-values will be drawn in front of layers with lower z-values.
     */
    BackgroundCanvasLayer(Background* m_background, QGraphicsScene* scene, LevelManager& LevelManager, double zValue = 0.);

    /**
     * @brief Destructor, frees memory.
     *
     */
    ~BackgroundCanvasLayer();

    /**
     * @brief Does nothing.
     *
     * @param event Mouse Event
     */
    void handleMousePressEvent(QGraphicsSceneMouseEvent* event) override{};

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
     * @brief Does nothing.
     *
     */
    void show() override;

    /**
     * @brief Does nothing.
     *
     */
    void hide() override;

    /**
     * @brief Returns the background which is represented by this layer.
     *
     * @return const Background* Background which is represented by this layer.
     */
    const Background* getBackground();

signals:
public slots:
    /**
     * @brief Redraws this background.
     *
     */
    void refresh() override;

private:
    /// Background which this layer visualizes on the levelditor canvas.
    Background* m_background;

    /// GraphicsItem which visualizes m_background on the leveleditor canvas.
    QGraphicsRectItem* m_backgroundItem = nullptr;
};
