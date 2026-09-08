/**
 * @file LayerListItem.hpp
 * @author Leveleditor-Gruppe
 * @brief ListItem which represents a specific layer of the level, e.g. tilemap, sprites, backgrounds.
 * Used in the right toolbar, for selecting different layers and changing their visibility.
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <QtWidgets>

/**
 * @brief All layer types.
 *
 */
enum LayerType
{
    TILEMAP,
    SPRITES,
    BACKGROUND,
    ENDPOSITION
};

/**
 * @brief ListItem which represents a specific layer of the level, e.g. tilemap, sprites, backgrounds.
 * Used in the right toolbar, for selecting different layers and changing their visibility.
 *
 */
class LayerListItem : public QListWidgetItem
{
public:
    /**
     * @brief Construct a new LayerListItem.
     *
     * @param type Type of layer which this list item should represent.
     * @param name Name of the list item.
     * @param parent ListWidget of this list item
     */
    LayerListItem(LayerType type, const QString& name, QListWidget* parent = nullptr);

    /**
     * @brief Get the represented layer type.
     *
     * @return LayerType represented layer type
     */
    LayerType getLayerType();

private:
    /**
     * @brief Type of Layer represented by this list item.
     *
     */
    LayerType m_type;
};