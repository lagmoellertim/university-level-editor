#include "ItemPreviewWidget.hpp"

ItemPreviewWidget::ItemPreviewWidget(LevelManager& levelManager, QWidget* parent)
    : QWidget(parent), m_levelManager(levelManager)
{
    m_view = Ui_ItemPreview();
    m_view.setupUi(this);
    m_view.view->setScene(&m_scene);

    connect(&levelManager, &LevelManager::selectedLevelContextItemChanged, this, &ItemPreviewWidget::update);
    connect(&levelManager, &LevelManager::selectedLevelLayerSelectionChanged, this, &ItemPreviewWidget::update);
    connect(&levelManager, &LevelManager::levelSelectionChanged, this, &ItemPreviewWidget::update);
    connect(&levelManager, &LevelManager::selectedLevelItemSetChanged, this, &ItemPreviewWidget::update);
    connect(&levelManager, &LevelManager::selectedLevelItemMetadataChanged, this, &ItemPreviewWidget::update);
}

void ItemPreviewWidget::update()
{
    EditingContext* context = m_levelManager.getSelectedContext();
    m_scene.clear();

    if (context)
    {
        QPixmap* pm = nullptr;

        switch (context->getSelectedLayer())
        {
            case Layer::TILE_LAYER:
            {
                int selectedTileID = context->getSelectedTileID();

                if (selectedTileID >= 0)
                {
                    QPixmap temp = m_levelManager.getSelectedLevel()->getTileSet()[selectedTileID];
                    pm = new QPixmap(temp.scaled(m_view.view->width(), m_view.view->height(), Qt::KeepAspectRatio));
                }

                break;
            }

            case Layer::SPRITE_LAYER:
            {
                Sprite* selectedSprite = context->getSelectedSprite();


                if (selectedSprite)
                {
                    QPixmap temp = selectedSprite->getFrames()[0];
                    pm = new QPixmap(temp.scaled(m_view.view->width(), m_view.view->height(), Qt::KeepAspectRatio));
                }

                break;
            }
            case Layer::ENDPOSITION_LAYER:
            default:
            {
                break;
            }
        }

        if (pm)
        {
            m_scene.addItem(new QGraphicsPixmapItem(*pm));
            delete pm;
        }
    }
}

void ItemPreviewWidget::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    update();
}