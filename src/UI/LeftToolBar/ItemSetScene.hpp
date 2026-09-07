/**
 * @file ItemSetScene.hpp
 * @author Leveleditor-editor
 * @brief
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */


#pragma once

#include <QGraphicsScene>


/**
 * @brief Base Class of the TileSet / Sprite Scene
 *
 */
class ItemSetScene : public QGraphicsScene
{
    Q_OBJECT

public:
    /**
     * @brief Construct a new ItemSetScene object
     *
     * @param itemSize Display Size of items
     * @param padding Padding between items
     */
    ItemSetScene(int itemSize, int padding);

    /**
     * @brief Clear scene
     *
     */
    virtual void clear();

    /**
     * @brief Arrange item positions to fit the viewWidth for dynamic resizing
     *
     * @param viewWidth Width of the ItemSetView
     */
    virtual void arrange(int viewWidth) = 0;

signals:
    /**
     * @brief Whenever a new item from the itemSet is selected, this signal is sent
     *
     * @param selectedItem The selected item
     */
    void selectedItemUpdated(QGraphicsPixmapItem* selectedItem);

public slots:
    /**
     * @brief Called whenever something changes, used to update size
     *
     */
    virtual void onChange();

protected:
    /**
     * @brief Mouse press event that is handled when the ItemSetScene is clicked
     *
     * @param event
     */
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);

    /// Size of the displayed items
    const int m_itemSize;

    /// Padding between items
    const int m_padding;
};