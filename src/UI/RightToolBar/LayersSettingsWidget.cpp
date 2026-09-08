#include "LayersSettingsWidget.hpp"
#include "../../Lib/AssetImport/AssetImport.hpp"
#include "../View/EditBackgroundUI.hpp"
#include <set>


LayersSettingsWidget::LayersSettingsWidget(LevelManager& levelManager, QWidget* parent)
    : QWidget(parent), m_levelManager(levelManager)
{
    m_layersView = new Ui_LayersSettings();
    m_layersView->setupUi(this);

    m_tileMapLayerEntry = new LayerListItem(LayerType::TILEMAP, QString("Tilemap"));
    m_spriteLayerEntry = new LayerListItem(LayerType::SPRITES, QString("Sprites"));
    m_endPositionLayerEntry = new LayerListItem(LayerType::ENDPOSITION, QString("EndPosition"));

    m_tileMapLayerEntry->setCheckState(Qt::Checked);
    m_spriteLayerEntry->setCheckState(Qt::Checked);
    m_endPositionLayerEntry->setCheckState(Qt::Checked);

    m_layersView->layerList->addItem(m_tileMapLayerEntry);
    m_layersView->layerList->addItem(m_spriteLayerEntry);
    m_layersView->layerList->addItem(m_endPositionLayerEntry);

    m_layersView->layerList->setContextMenuPolicy(Qt::CustomContextMenu);
    m_layersView->backgroundsList->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(m_layersView->layerList, &QListWidget::itemPressed, this, &LayersSettingsWidget::onLayerSelected);
    connect(m_layersView->layerList, &QListWidget::itemChanged, this, &LayersSettingsWidget::onLayerVisibilityChanged);

    connect(m_layersView->backgroundsList, &QListWidget::itemChanged, this, &LayersSettingsWidget::onBackgroundItemChanged);
    connect(m_layersView->backgroundsList, &LayersSettingsWidget::customContextMenuRequested, this, &LayersSettingsWidget::onBackgroundRightClick);
    connect(m_layersView->layerList, &LayersSettingsWidget::customContextMenuRequested, this, &LayersSettingsWidget::onLayerRightClick);
    connect(m_layersView->pushButton, &QPushButton::released, this, &LayersSettingsWidget::onAddBackground);
    connect(&m_levelManager, &LevelManager::levelSelectionChanged, this, &LayersSettingsWidget::onLevelChanged);
}

LayersSettingsWidget::~LayersSettingsWidget()
{
    delete m_layersView;
    delete m_tileMapLayerEntry;
    delete m_spriteLayerEntry;
}

void LayersSettingsWidget::onLayerSelected(QListWidgetItem* layer)
{
    EditingContext* context = m_levelManager.getSelectedContext();

    if (context)
    {
        LayerListItem* layerItem = static_cast<LayerListItem*>(layer);

        switch (layerItem->getLayerType())
        {
            case LayerType::TILEMAP:
            {
                context->setSelectedLayer(Layer::TILE_LAYER);
                break;
            }

            case LayerType::SPRITES:
            {
                context->setSelectedLayer(Layer::SPRITE_LAYER);
                break;
            }

            case LayerType::ENDPOSITION:
            {
                context->setSelectedLayer(Layer::ENDPOSITION_LAYER);
                break;
            }
            case LayerType::BACKGROUND:
            default:
            {
                break;
            }
        }
    }
}

void LayersSettingsWidget::onLayerVisibilityChanged(QListWidgetItem* layer)
{
    EditingContext* context = m_levelManager.getSelectedContext();

    if (context)
    {
        LayerListItem* layerItem = static_cast<LayerListItem*>(layer);

        switch (layerItem->getLayerType())
        {
            case LayerType::TILEMAP:
            {
                if (layerItem->checkState())
                {
                    context->showLayer(Layer::TILE_LAYER);
                }
                else
                {
                    context->hideLayer(Layer::TILE_LAYER);
                }

                break;
            }

            case LayerType::SPRITES:
            {
                if (layerItem->checkState())
                {
                    context->showLayer(Layer::SPRITE_LAYER);
                }
                else
                {
                    context->hideLayer(Layer::SPRITE_LAYER);
                }

                break;
            }

            case LayerType::ENDPOSITION:
            {
                if (layerItem->checkState())
                {
                    context->showLayer(Layer::ENDPOSITION_LAYER);
                }
                else
                {
                    context->hideLayer(Layer::ENDPOSITION_LAYER);
                }

                break;
            }
            default:
            {
                break;
            }
        }
    }
}

void LayersSettingsWidget::onAddBackground()
{
    Level* level = m_levelManager.getSelectedLevel();
    EditingContext* context = m_levelManager.getSelectedContext();

    if (level && context)
    {
        Background* bg = AssetImport::importBackground(m_levelManager.getSelectedLevel());

        if (bg)
        {
            LayerListItem* item = new LayerListItem(LayerType::BACKGROUND, QString::fromStdString(bg->getID()));
            m_layersView->backgroundsList->addItem(item);
            item->setCheckState(Qt::Checked);
            item->setFlags(item->flags() | Qt::ItemIsEditable);
            context->setBackgroundVisibility(bg, true);

            level->addBackground(bg);
        }
    }
}

void LayersSettingsWidget::onBackgroundItemChanged(QListWidgetItem* item)
{
    if (!backgroundsListIsValid())
    {
        updateBackgroundList();
        return;
    }

    EditingContext* context = m_levelManager.getSelectedContext();
    Level* level = m_levelManager.getSelectedLevel();

    if (level && context)
    {
        Background* levelBg = nullptr;
        std::string itemName = item->text().toStdString();

        for (Background* bg : level->getBackgrounds())
        {
            if (bg->getID() == itemName)
            {
                levelBg = bg;
                break;
            }
        }

        if (levelBg)
        {
            if (item->checkState() == Qt::Checked)
            {
                context->setBackgroundVisibility(levelBg, true);
            }
            else
            {
                context->setBackgroundVisibility(levelBg, false);
            }
        }
    }
}

void LayersSettingsWidget::onLevelChanged()
{
    m_layersView->backgroundsList->clear();
    Level* level = m_levelManager.getSelectedLevel();
    EditingContext* context = m_levelManager.getSelectedContext();

    if (level && context)
    {
        std::vector<Background*> visibleBackgrounds = context->getVisibleBackgrounds();

        for (Background* bg : level->getBackgrounds())
        {
            LayerListItem* item = new LayerListItem(LayerType::BACKGROUND, QString::fromStdString(bg->getID()));
            m_layersView->backgroundsList->addItem(item);

            if (std::find(visibleBackgrounds.begin(), visibleBackgrounds.end(), bg) != visibleBackgrounds.end())
            {
                item->setCheckState(Qt::Checked);
            }
            else
            {
                item->setCheckState(Qt::Unchecked);
            }

            m_layersView->backgroundsList->addItem(item);
        }

        std::vector<Layer> visibleLayers = context->getVisibleLayers();
        QListWidget* layers = m_layersView->layerList;

        for (int i = 0; i < layers->count(); ++i)
        {
            LayerListItem* layerItem = static_cast<LayerListItem*>(layers->item(i));

            switch (layerItem->getLayerType())
            {
                case LayerType::TILEMAP:
                {
                    if (context->getSelectedLayer() == Layer::TILE_LAYER)
                    {
                        layers->setCurrentItem(layerItem);
                    }

                    if (std::find(visibleLayers.begin(), visibleLayers.end(), Layer::TILE_LAYER) != visibleLayers.end())
                    {
                        layerItem->setCheckState(Qt::Checked);
                    }
                    else
                    {
                        layerItem->setCheckState(Qt::Unchecked);
                    }

                    break;
                }

                case LayerType::SPRITES:
                {
                    if (context->getSelectedLayer() == Layer::SPRITE_LAYER)
                    {
                        layers->setCurrentItem(layerItem);
                    }

                    if (std::find(visibleLayers.begin(), visibleLayers.end(), Layer::SPRITE_LAYER) != visibleLayers.end())
                    {
                        layerItem->setCheckState(Qt::Checked);
                    }
                    else
                    {
                        layerItem->setCheckState(Qt::Unchecked);
                    }

                    break;
                }

                case LayerType::ENDPOSITION:
                {
                    if (context->getSelectedLayer() == Layer::ENDPOSITION_LAYER)
                    {
                        layers->setCurrentItem(layerItem);
                    }

                    if (std::find(visibleLayers.begin(), visibleLayers.end(), Layer::ENDPOSITION_LAYER) != visibleLayers.end())
                    {
                        layerItem->setCheckState(Qt::Checked);
                    }
                    else
                    {
                        layerItem->setCheckState(Qt::Unchecked);
                    }

                    break;
                }
                default:
                {
                    break;
                }
            }
        }
    }

    updateBackgroundList();
}

void LayersSettingsWidget::onBackgroundRightClick(const QPoint& pos)
{
    QListWidget* backgroundsList = m_layersView->backgroundsList;
    QPoint item = backgroundsList->mapToGlobal(pos);

    // Obtain Level item and position
    int row = backgroundsList->indexAt(pos).row();

    if (row < 0)
    {
        return;
    }

    QListWidgetItem* listItem = backgroundsList->itemAt(pos);

    // Open context menu
    QMenu submenu;
    submenu.addAction("Edit");
    submenu.addAction("Rename");
    submenu.addAction("Delete");

    QAction* rightClickItem = submenu.exec(item);
    if (rightClickItem)
    {
        Level* level = m_levelManager.getSelectedLevel();
        std::vector<Background*> levelBackgrounds = level->getBackgrounds();
        std::string selectedId = listItem->text().toStdString();
        Background* selectedBg = nullptr;

        for (Background* bg : levelBackgrounds)
        {
            if (bg->getID() == selectedId)
            {
                selectedBg = bg;
                break;
            }
        }

        if (selectedBg)
        {
            if (rightClickItem->text().contains("Delete") && displaySureDialog("Delete this Background?"))
            {
                backgroundsList->takeItem(row);
                level->removeBackground(selectedBg);
            }
            else if (rightClickItem->text().contains("Edit"))
            {
                QDialog dialog;
                Ui_BackgroundAttributeChangeDialog ui{};
                ui.setupUi(&dialog);

                ui.parallaxLayerInput->setValue(selectedBg->getDepth());
                ui.layerSpeedInput->setValue(selectedBg->getSpeed());

                dialog.show();
                dialog.setModal(true);

                if (dialog.exec() == 0)
                {
                    return;
                }

                selectedBg->setDepth(ui.parallaxLayerInput->value());
                selectedBg->setSpeed(ui.layerSpeedInput->value());
            }
            else if (rightClickItem->text().contains("Rename"))
            {
                backgroundsList->editItem(listItem);
            }
        }
    }
}

void LayersSettingsWidget::onLayerRightClick(const QPoint& pos)
{
    QListWidget* layerList = m_layersView->layerList;
    QPoint item = layerList->mapToGlobal(pos);

    // Obtain Level item and position
    int row = layerList->indexAt(pos).row();

    if (row < 0)
    {
        return;
    }

    LayerListItem* layerItem = static_cast<LayerListItem*>(layerList->itemAt(pos));
    Level* level = m_levelManager.getSelectedLevel();

    if (level && layerItem->getLayerType() != LayerType::ENDPOSITION)
    {
        // Open context menu
        QMenu submenu;
        submenu.addAction("Clear");

        QAction* rightClickItem = submenu.exec(item);
        if (rightClickItem && rightClickItem->text().contains("Clear") && displaySureDialog("Clear this Layer?"))
        {
            switch (layerItem->getLayerType())
            {
                case LayerType::TILEMAP:
                {
                    level->clearTileMap();
                    break;
                }

                case LayerType::SPRITES:
                {
                    level->clearSprites();
                    break;
                }

                case ENDPOSITION:
                case BACKGROUND:
                default:
                {
                    break;
                }
            }
        }
    }
}

bool LayersSettingsWidget::displaySureDialog(std::string msg)
{
    return QMessageBox::question(this, "Confirm Action", QString::fromStdString(msg), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes;
}

bool LayersSettingsWidget::backgroundsListIsValid()
{
    QListWidget* list = m_layersView->backgroundsList;
    std::set<std::string> ids;

    for (int i = 0; i < list->count(); ++i)
    {
        std::string itemId = list->item(i)->text().toStdString();

        if (std::find(ids.begin(), ids.end(), itemId) != ids.end())
        {
            return false;
        }

        ids.insert(itemId);
    }

    return true;
}

void LayersSettingsWidget::updateBackgroundList()
{
    m_layersView->backgroundsList->clear();
    Level* level = m_levelManager.getSelectedLevel();
    EditingContext* context = m_levelManager.getSelectedContext();

    if (level && context)
    {
        std::vector<Background*> visibleBackgrounds = context->getVisibleBackgrounds();

        for (Background* bg : level->getBackgrounds())
        {
            LayerListItem* item = new LayerListItem(LayerType::BACKGROUND, QString::fromStdString(bg->getID()));
            m_layersView->backgroundsList->addItem(item);
            item->setFlags(item->flags() | Qt::ItemIsEditable);

            if (std::find(visibleBackgrounds.begin(), visibleBackgrounds.end(), bg) != visibleBackgrounds.end())
            {
                item->setCheckState(Qt::Checked);
            }
            else
            {
                item->setCheckState(Qt::Unchecked);
            }

            m_layersView->backgroundsList->addItem(item);
        }

        std::vector<Layer> visibleLayers = context->getVisibleLayers();
        QListWidget* layers = m_layersView->layerList;

        for (int i = 0; i < layers->count(); ++i)
        {
            LayerListItem* layerItem = static_cast<LayerListItem*>(layers->item(i));

            switch (layerItem->getLayerType())
            {
                case LayerType::TILEMAP:
                {
                    if (context->getSelectedLayer() == Layer::TILE_LAYER)
                    {
                        layers->setCurrentItem(layerItem);
                    }

                    if (std::find(visibleLayers.begin(), visibleLayers.end(), Layer::TILE_LAYER) != visibleLayers.end())
                    {
                        layerItem->setCheckState(Qt::Checked);
                    }
                    else
                    {
                        layerItem->setCheckState(Qt::Unchecked);
                    }

                    break;
                }

                case LayerType::SPRITES:
                {
                    if (context->getSelectedLayer() == Layer::SPRITE_LAYER)
                    {
                        layers->setCurrentItem(layerItem);
                    }

                    if (std::find(visibleLayers.begin(), visibleLayers.end(), Layer::SPRITE_LAYER) != visibleLayers.end())
                    {
                        layerItem->setCheckState(Qt::Checked);
                    }
                    else
                    {
                        layerItem->setCheckState(Qt::Unchecked);
                    }

                    break;
                }

                case LayerType::ENDPOSITION:
                case LayerType::BACKGROUND:
                default:
                {
                    break;
                }
            }
        }
    }
}