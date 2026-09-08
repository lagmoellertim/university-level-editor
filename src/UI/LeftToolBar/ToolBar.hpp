/**
 * @file ToolBar.hpp
 * @author Leveleditor-Gruppe
 * @brief
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */


#pragma once

#include "../../Lib/LevelManager/LevelManager.hpp"
#include "../View/ToolBarUI.hpp"
#include "SpriteSetScene.hpp"
#include "TileSetScene.hpp"
#include <QWidget>


/**
 * @brief Represents the Editor ToolBar Widget (left side). Handles TileSet / SpriteSet import and interaction, Level creation and editing.
 *
 */
class ToolBar : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Construct a new ToolBar object
     *
     * @param levelManager LevelManager that holds level info
     * @param parent Parent Widget
     */
    ToolBar(LevelManager& levelManager, QWidget* parent = nullptr);

    /**
     * @brief Destroy the ToolBar object
     *
     */
    virtual ~ToolBar();

    /**
     * @brief Clear this ToolBar's content
     *
     */
    void clear();

public slots:
    /**
     * @brief New item from ItemSet selected, connected to ItemSetView. Used to update the Editing Context.
     *
     * @param selectedTile The selected tile
     */
    void onItemSelectionUpdate(QGraphicsItem* selectedItem);

    /**
     * @brief Sprite from Scene has been right clicked, connected to SpriteSetView. Open Context Menu (Edit, Rename).
     *
     * @param selectedSprite Clicked Sprite
     * @param pos Position
     */
    void onOpenSpriteContextMenu(GraphicsSpriteItem* selectedSprite, QPoint pos);

    /**
     * @brief Create new Level, connected to NewLevelButton. Opens a dialog to enter properties.
     *
     */
    void onNewLevel();

    /**
     * @brief Level from LevelList selected, connected to LevelList. Updates the selected Level inside of LevelManager.
     *
     * @param item Selected item
     */
    void onLevelSelected(QListWidgetItem* item);

    /**
     * @brief Add a new ItemSet to the current Level, connected to AddItemSetButton. Opens right dialog depending on selected Level.
     *
     */
    void onAddItemSet();

    /**
     * @brief Clear the active ItemSet, TileSet / Sprites depending on selected Layer, connected to ClearTileSetButton.
     *
     */
    void onClearItemSet();

    /**
     * @brief Level from LevelList right-clicked, connected to LevelList. Open Context Menu (Delete, Rename, Resize).
     *
     * @param pos Click position
     */
    void onItemRightClick(const QPoint& pos);

    /**
     * @brief Enable Eraser mode. Sets selected Tile / Sprite to -1 / nullptr.
     *
     */
    void onEraserSelected();

    /**
     * @brief LevelList changed, connected to LevelManager. Clear the LevelList and reload content from LevelManager.
     *
     */
    void onLevelListChanged();

    /**
     * @brief Selected Level changed, connected to LevelManager. Set the right row in LevelList and call updateItemSet.
     *
     */
    void onLevelSelectionChanged();

    /**
     * @brief Selected Level's ItemSet changed, connected to LevelManager. Call updateItemSet.
     *
     */
    void onSelectedLevelItemSetChanged();

    /**
     * @brief Selected Level's active layer changed, connected to LevelManager. Call update ItemSet.
     *
     */
    void onSelectedLevelLayerSelectionChanged();

    /**
     * @brief Selected Levels's active item metadata changed, connected to LevelManager. Call updateItemSet.
     *
     */
    void onSelectedLevelItemMetadataChanged();

    /**
     * @brief Level from LevelList changed, connected to LevelList. Handle Level renaming.
     *
     * @param item The changed list item
     */
    void onItemChanged(QListWidgetItem* item);

    /**
     * @brief Items in LevelList moved, connected to LevelList. Handle Level positioning.
     *
     * @param sourceParent
     * @param sourceStart Level's old position
     * @param sourceEnd
     * @param destinationParent
     * @param destinationRow Level's new position
     */
    void onItemMoved(const QModelIndex& sourceParent, int sourceStart, int sourceEnd, const QModelIndex& destinationParent, int destinationRow);

protected:
    /**
     * @brief Handles this widget's dynamic resizing. Calls ItemSets arrange method.
     *
     * @param event
     */
    void resizeEvent(QResizeEvent* event);

private:
    /**
     * @brief Update current ItemSet (Clear and reload from LevelManager).
     *
     */
    void updateItemSet();

    /**
     * @brief Asks the user for confirmation
     *
     * @param msg Display Message
     * @return true If Yes was clicked
     * @return false If No was clicked
     */
    bool displaySureDialog(std::string msg);

    /// LevelManager that holds level info (interface to other components)
    LevelManager& m_levelManager;

    /// This ToolBar's Ui
    Ui_Toolbar m_uiToolBar;

    /// This ToolBar's TileSetScene
    TileSetScene* m_tileSetScene;

    /// This ToolBar's SpriteSetScene
    SpriteSetScene* m_spriteSetScene;
};