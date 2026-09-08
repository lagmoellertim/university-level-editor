#include "CanvasView.hpp"

CanvasView::CanvasView(QWidget* parent)
    : QGraphicsView(parent)
{
    setMouseTracking(true);
}

CanvasView::CanvasView(QGraphicsScene* scene, QWidget* parent)
    : QGraphicsView(scene, parent)
{
    setMouseTracking(true);
}

CanvasView::~CanvasView()
{
}

void CanvasView::mousePressEvent(QMouseEvent* event)
{
    // for middle mouse button: scroll/drag scene
    if (event->button() == Qt::MiddleButton && !m_isPanning)
    {
        m_isPanning = true;
        setCursor(Qt::ClosedHandCursor);
        m_panningStartPos.setX(event->x());
        m_panningStartPos.setY(event->y());
    }
    QGraphicsView::mousePressEvent(event);
}

void CanvasView::mouseMoveEvent(QMouseEvent* event)
{
    if (m_isPanning)
    {
        // scroll / drag scene
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - (event->x() - m_panningStartPos.x()));
        verticalScrollBar()->setValue(verticalScrollBar()->value() - (event->y() - m_panningStartPos.y()));
        m_panningStartPos.setX(event->x());
        m_panningStartPos.setY(event->y());
    }
    QGraphicsView::mouseMoveEvent(event);
}

void CanvasView::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::MiddleButton)
    {
        m_isPanning = false;
        setCursor(Qt::ArrowCursor);
    }
    QGraphicsView::mouseReleaseEvent(event);
}

void CanvasView::wheelEvent(QWheelEvent* event)
{
    if (event->modifiers() & Qt::ControlModifier)
    {
        if (event->angleDelta().y() != 0)
        {
            zoom(qPow(1.0015, event->angleDelta().y()));
            event->accept();
        }
    }
    else
    {
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - event->angleDelta().x());
        verticalScrollBar()->setValue(verticalScrollBar()->value() - event->angleDelta().y());
    }
}


void CanvasView::zoom(double factor)
{

    QPoint m_mousePosRelativeToWidget = mapFromGlobal(QCursor::pos());
    QPointF m_mousePosInScene = mapToScene(m_mousePosRelativeToWidget);

    // zoom
    scale(factor, factor);

    // reposition center, so that the tile which was originally below the cursor is still below the cursor
    QPointF viewPortCenter = QPointF(viewport()->width() / 2.0, viewport()->height() / 2.0);
    QPointF deltaViewPortPos = m_mousePosRelativeToWidget - viewPortCenter;
    QPointF newViewportCenter = mapFromScene(m_mousePosInScene) - deltaViewPortPos;
    centerOn(mapToScene(newViewportCenter.toPoint()));
}