/**
 * @file LayersSettingsWidget.hpp
 * @author Leveleditor-Gruppe
 * @brief Widget which holds lists for managing the different layers of the level like the tilemap, sprites and backgrounds.
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include "../../Lib/LevelManager/LevelManager.hpp"
#include "../View/LayersSettingsUI.hpp"
#include "LayerListItem.hpp"
#include <QSizePolicy>
#include <QtWidgets>

/**
 * @brief Widget which holds lists for managing the different layers of the level
 * like the tilemap, sprites and backgrounds.
 */
class LayersSettingsWidget : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Construct a new LayersSettingsWidget
     *
     * @param levelManager LevelManager
     * @param parent parent QWidget
     */
    LayersSettingsWidget(LevelManager& levelManager, QWidget* parent = nullptr);

    /**
     * @brief Destructor, frees memory.
     *
     */
    ~LayersSettingsWidget();

signals:
public slots:

    /**
     * @brief Slot for selecting a layer
     *
     * @param layer selected layer
     */
    void onLayerSelected(QListWidgetItem* layer);

    /**
     * @brief Slot for checking / unchecking a layer
     *
     * @param layer layer list item which checkbox was clicked
     */
    void onLayerVisibilityChanged(QListWidgetItem* layer);

    /**
     * @brief Slot for checking / unchecking a background
     *
     * @param bg layer list item which checkbox was clicked
     */
    void onBackgroundItemChanged(QListWidgetItem* bg);

    /**
     * @brief Slot for adding backgrounds.
     *
     */
    void onAddBackground();

    /**
     * @brief Slot for level change.
     *
     */
    void onLevelChanged();

    /**
     * @brief Slot for right click on background list item
     *
     * @param pos Position of click.
     */
    void onBackgroundRightClick(const QPoint& pos);

    /**
     * @brief Slot for right click on layer list item
     *
     * @param pos Position of click.
     */
    void onLayerRightClick(const QPoint& pos);

private:
    /**
     * @brief Ask for confirmation
     *
     * @param msg Message to display.
     * @return true if confirmed
     * @return false if not confirmed
     */
    bool displaySureDialog(std::string msg);

    /**
     * @brief Checks list for duplicates
     *
     * @return true if no duplicate was found
     * @return false if a duplicate was found
     */
    bool backgroundsListIsValid();

    /**
     * @brief Update the background list to match backgrounds in level
     *
     */
    void updateBackgroundList();

    /// UI elements for layers and backgrounds lists
    Ui_LayersSettings* m_layersView;

    /// List entry for the tilemap layer
    LayerListItem* m_tileMapLayerEntry;

    /// List entry for the sprite layer
    LayerListItem* m_spriteLayerEntry;

    /// List entry for the endposition layer
    LayerListItem* m_endPositionLayerEntry;

    /// LevelManager
    LevelManager& m_levelManager;
};