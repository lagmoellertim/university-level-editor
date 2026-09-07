#include "CanvasWidget.hpp"


CanvasWidget::CanvasWidget(LevelManager& levelManager, QWidget* parent)
    : QWidget(parent), m_scene(levelManager, this), m_levelManager(levelManager)
{
    m_view = new Ui_TileMapCanvas();
    m_view->setupUi(this);
    m_view->gridLayout->addWidget(new CanvasView(&m_scene, this));
}

CanvasWidget::~CanvasWidget()
{
    delete m_view;
}
