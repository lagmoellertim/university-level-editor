/**
 * @file CanvasView.hpp
 * @author Leveleditor-Gruppe
 * @brief QGraphicsView for the leveleditor canvas which allows zooming in/out and dragging.
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <QGraphicsView>
#include <QtWidgets>

/**
 * @brief QGraphicsView for the leveleditor canvas which allows zooming in and out.
 *
 */
class CanvasView : public QGraphicsView
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a new CanvasView.
     *
     * @param parent Parent QWidget
     */
    CanvasView(QWidget* parent = nullptr);

    /**
     * @brief Construct a new CanvasView for the given scene.
     *
     * @param scene Scene which should be displayed
     * @param parent Parent QWidget
     */
    CanvasView(QGraphicsScene* scene, QWidget* parent = nullptr);

    /**
     * @brief Destructor, frees Memory.
     *
     */
    ~CanvasView();

protected:
    /**
     * @brief Called if middle mouse button is pressed. Used for dragging functionality.
     *
     * @param event Mouse Event
     */
    virtual void mousePressEvent(QMouseEvent* event) override;

    /**
     * @brief Drags the canvas, if the middle mouse button is pressed and the mouse moved.
     *
     * @param event Mouse Event
     */
    virtual void mouseMoveEvent(QMouseEvent* event) override;

    /**
     * @brief Called if mouse button is released on the canvas. Stops dragging the canvas if middle mouse button is released.
     *
     * @param event Mouse Event
     */
    virtual void mouseReleaseEvent(QMouseEvent* event) override;

    /**
     * @brief Called if mouse wheel is scrolled. Zooms in and out of the scene.
     *
     * @param event Mouse event
     */
    virtual void wheelEvent(QWheelEvent* event) override;

private:
    /**
     * @brief Zooms the scene by the given factor.
     *
     * @param factor zoom factor
     */
    void zoom(double factor);

    /// State which indicates whether the view is currently being dragged.
    bool m_isPanning = false;

    /// Panning start position.
    QPointF m_panningStartPos;
};
