#include "ToolBar.hpp"
#include "../../Lib/AssetImport/AssetImport.hpp"
#include "../../Lib/Dialog/LevelResize.hpp"
#include "../../Lib/Dialog/NewLevel.hpp"
#include "../../Lib/Dialog/SpriteEdit.hpp"
#include "../Dialog/SpriteEditDialog.hpp"
#include <QMenu>
#include <QMessageBox>

ToolBar::ToolBar(LevelManager& levelManager, QWidget* parent)
    : QWidget(parent), m_levelManager(levelManager)
{
    m_uiToolBar.setupUi(this);

    // Enable LevelList context menu and movable items
    m_uiToolBar.levelListView->setContextMenuPolicy(Qt::CustomContextMenu);
    m_uiToolBar.levelListView->setDragDropMode(QAbstractItemView::InternalMove);  // QAbstractItemView::DragDrop
    m_uiToolBar.levelListView->setDefaultDropAction(Qt::MoveAction);

    m_tileSetScene = new TileSetScene(32, 2);
    m_spriteSetScene = new SpriteSetScene(levelManager, 64, 4);
    m_uiToolBar.itemSetView->setScene(m_tileSetScene);
    m_uiToolBar.itemSetView->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    // Connect Ui elements to slots
    connect(m_tileSetScene, &ItemSetScene::selectedItemUpdated, this, &ToolBar::onItemSelectionUpdate);
    connect(m_spriteSetScene, &ItemSetScene::selectedItemUpdated, this, &ToolBar::onItemSelectionUpdate);
    connect(m_spriteSetScene, &SpriteSetScene::openContextMenu, this, &ToolBar::onOpenSpriteContextMenu);
    connect(m_uiToolBar.newLevelButton, &QPushButton::released, this, &ToolBar::onNewLevel);
    connect(m_uiToolBar.levelListView, &QListWidget::itemPressed, this, &ToolBar::onLevelSelected);
    connect(m_uiToolBar.levelListView, &QListWidget::itemChanged, this, &ToolBar::onItemChanged);
    connect(m_uiToolBar.levelListView, &ToolBar::customContextMenuRequested, this, &ToolBar::onItemRightClick);
    connect(m_uiToolBar.addItemSetButton, &QPushButton::released, this, &ToolBar::onAddItemSet);
    connect(m_uiToolBar.clearItemSetButton, &QPushButton::released, this, &ToolBar::onClearItemSet);
    connect(m_uiToolBar.levelListView->model(), &QAbstractItemModel::rowsMoved, this, &ToolBar::onItemMoved);
    connect(m_uiToolBar.eraserButton, &QPushButton::released, this, &ToolBar::onEraserSelected);

    // Connect LevelManager to slots
    connect(&m_levelManager, &LevelManager::levelListChanged, this, &ToolBar::onLevelListChanged);
    connect(&m_levelManager, &LevelManager::levelSelectionChanged, this, &ToolBar::onLevelSelectionChanged);
    connect(&m_levelManager, &LevelManager::selectedLevelItemSetChanged, this, &ToolBar::onSelectedLevelItemSetChanged);
    connect(&m_levelManager, &LevelManager::selectedLevelLayerSelectionChanged, this, &ToolBar::onSelectedLevelLayerSelectionChanged);
    connect(&m_levelManager, &LevelManager::selectedLevelItemMetadataChanged, this, &ToolBar::onSelectedLevelItemMetadataChanged);
}

ToolBar::~ToolBar()
{
    delete m_tileSetScene;
    delete m_spriteSetScene;
}

void ToolBar::clear()
{
    m_tileSetScene->clear();
    m_spriteSetScene->clear();
    m_uiToolBar.levelListView->clear();
}

void ToolBar::onItemSelectionUpdate(QGraphicsItem* selectedItem)
{
    EditingContext* context = m_levelManager.getSelectedContext();

    if (context)
    {
        switch (context->getSelectedLayer())
        {
            case TILE_LAYER:
            {
                GraphicsTileItem* tile = static_cast<GraphicsTileItem*>(selectedItem);
                context->setSelectedTileID(tile->index());
                break;
            }

            case SPRITE_LAYER:
            {
                GraphicsSpriteItem* sprite = static_cast<GraphicsSpriteItem*>(selectedItem);
                context->setSelectedSprite(sprite->getSprite());
                break;
            }
            default:
            {
                break;
            }
        }
    }
}

void ToolBar::onOpenSpriteContextMenu(GraphicsSpriteItem* selectedSprite, QPoint pos)
{
    QMenu submenu;
    submenu.addAction("Edit");
    submenu.addAction("Delete");

    Level* level = m_levelManager.getSelectedLevel();
    EditingContext* context = m_levelManager.getSelectedContext();

    if (level && context)
    {
        QAction* rightClickItem = submenu.exec(m_uiToolBar.itemSetView->mapToGlobal(pos));

        if (rightClickItem)
        {
            if (rightClickItem->text().contains("Delete") && displaySureDialog("Clear this Sprite?\nIt will also be removed from the level!"))
            {
                context->setSelectedSprite(nullptr);
                level->removeSprite(selectedSprite->getSprite());
            }
            else if (rightClickItem->text().contains("Edit"))
            {
                Dialog::editSprite(m_levelManager, selectedSprite);
            }
        }
    }
}

void ToolBar::onNewLevel()
{
    Dialog::newLevel(m_levelManager);
}

void ToolBar::onLevelSelected(QListWidgetItem* item)
{
    m_levelManager.setSelectedLevelByID(m_uiToolBar.levelListView->currentRow());
}

void ToolBar::onAddItemSet()
{
    Level* level = m_levelManager.getSelectedLevel();

    if (level)
    {
        switch (m_levelManager.getSelectedContext()->getSelectedLayer())
        {
            case TILE_LAYER:
            {
                // Import new TileSet
                std::vector<QPixmap>* newTileSet = AssetImport::importTileSet();

                if (newTileSet)
                {
                    level->appendToTileSet(*newTileSet);
                }

                delete newTileSet;
                break;
            }

            case SPRITE_LAYER:
            {
                // Import new Sprite
                Sprite* newSprite = AssetImport::importSprite(level);

                if (newSprite)
                {
                    level->addSprite(newSprite);
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

void ToolBar::onClearItemSet()
{
    Level* level = m_levelManager.getSelectedLevel();

    if (level)
    {
        switch (m_levelManager.getSelectedContext()->getSelectedLayer())
        {
            case TILE_LAYER:
            {
                if (displaySureDialog("Clear all Tiles?\nThey will also be removed from the level!"))
                {
                    level->clearTileSet();
                }

                break;
            }

            case SPRITE_LAYER:
            {
                if (displaySureDialog("Clear all Sprites?\nThey will also be removed from the level!"))
                {
                    level->clearSpriteSet();
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

void ToolBar::onItemRightClick(const QPoint& pos)
{
    QPoint item = m_uiToolBar.levelListView->mapToGlobal(pos);

    // Obtain Level item and position
    int row = m_uiToolBar.levelListView->indexAt(pos).row();

    if (row < 0)
    {
        return;
    }

    QListWidgetItem* listItem = m_uiToolBar.levelListView->itemAt(pos);

    // Set clicked item as selected
    m_levelManager.setSelectedLevelByID(row);

    // Open context menu
    QMenu submenu;
    submenu.addAction("Resize");
    submenu.addAction("Rename");
    submenu.addAction("Delete");

    QAction* rightClickItem = submenu.exec(item);
    if (rightClickItem)
    {
        if (rightClickItem->text().contains("Delete") && displaySureDialog("Delete this level?"))
        {
            m_levelManager.removeLevelByID(row);
        }
        else if (rightClickItem->text().contains("Rename"))
        {
            m_uiToolBar.levelListView->editItem(listItem);
        }
        else if (rightClickItem->text().contains("Resize"))
        {
            Dialog::resizeLevel(m_levelManager);
        }
    }
}

void ToolBar::onEraserSelected()
{
    EditingContext* context = m_levelManager.getSelectedContext();

    if (context)
    {
        context->setSelectedTileID(-1);
        context->setSelectedSprite(nullptr);
    }
}

void ToolBar::onLevelListChanged()
{
    // Clear LevelList and refill with Levels from LevelManager
    m_uiToolBar.levelListView->clear();
    auto x = m_levelManager.getLevels();

    for (Level* level : m_levelManager.getLevels())
    {
        auto* item = new QListWidgetItem(QString::fromStdString(level->getLevelName()));

        // Make item editable and add it to LevelList
        item->setFlags(item->flags() | Qt::ItemIsEditable);
        m_uiToolBar.levelListView->addItem(item);
    }

    // Keep selected Level or select last Level if none is selected
    if (m_levelManager.getLevels().size() > 0)
    {
        int newSelectionPosition = m_levelManager.getSelectedLevelID();

        if (newSelectionPosition == -1)
        {
            newSelectionPosition = m_levelManager.getLevels().size() - 1;
        }

        m_levelManager.setSelectedLevelByID(newSelectionPosition);
    }
}

void ToolBar::updateItemSet()
{
    // Clear scenes, set the right one and fill it
    m_tileSetScene->clear();
    m_spriteSetScene->clear();
    Level* level = m_levelManager.getSelectedLevel();

    if (level)
    {
        switch (m_levelManager.getSelectedContext()->getSelectedLayer())
        {
            case TILE_LAYER:
            {
                m_uiToolBar.addItemSetButton->setText("Add TileSet");
                m_uiToolBar.clearItemSetButton->setText("Clear TileSet");
                m_uiToolBar.itemSetView->setScene(m_tileSetScene);
                m_tileSetScene->addTileSet(level->getTileSet(), m_uiToolBar.itemSetView->width());
                break;
            }

            case SPRITE_LAYER:
            {
                m_uiToolBar.addItemSetButton->setText("Add Sprite");
                m_uiToolBar.clearItemSetButton->setText("Clear Sprites");
                m_uiToolBar.itemSetView->setScene(m_spriteSetScene);
                m_spriteSetScene->addSpriteSet(level->getSprites(), m_uiToolBar.itemSetView->width());
                break;
            }

            default:
                break;
        }
    }
}

bool ToolBar::displaySureDialog(std::string msg)
{
    return QMessageBox::question(this, "Confirm Action", QString::fromStdString(msg), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes;
}

void ToolBar::onLevelSelectionChanged()
{
    // Select current Level
    m_uiToolBar.levelListView->setCurrentRow(m_levelManager.getSelectedLevelID());
    updateItemSet();
}

void ToolBar::onSelectedLevelItemSetChanged()
{
    updateItemSet();
}

void ToolBar::onSelectedLevelLayerSelectionChanged()
{
    updateItemSet();
}

void ToolBar::onSelectedLevelItemMetadataChanged()
{
    updateItemSet();
}

void ToolBar::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);

    EditingContext* context = m_levelManager.getSelectedContext();

    if (context)
    {
        switch (m_levelManager.getSelectedContext()->getSelectedLayer())
        {
            case TILE_LAYER:
            {
                m_tileSetScene->arrange(m_uiToolBar.itemSetView->width());
                break;
            }

            case SPRITE_LAYER:
            {
                m_spriteSetScene->arrange(m_uiToolBar.itemSetView->width());
                break;
            }

            default:
                break;
        }
    }
}

void ToolBar::onItemChanged(QListWidgetItem* item)
{
    Level* level = m_levelManager.getSelectedLevel();

    // Rename changed LevelItem
    if (level)
    {
        std::string newText = item->text().toStdString();

        // Do not allow empty level name
        if (newText.length() > 0)
        {
            level->setLevelName(newText);
        }
        else
        {
            item->setText(QString::fromStdString(level->getLevelName()));
        }
    }
}

void ToolBar::onItemMoved(const QModelIndex& sourceParent, int sourceStart, int sourceEnd, const QModelIndex& destinationParent, int destinationRow)
{
    // Move selected LevelItem to right position
    if (destinationRow == m_uiToolBar.levelListView->count())
    {
        destinationRow -= 1;
    }

    m_levelManager.moveLevel(sourceStart, destinationRow);
}
