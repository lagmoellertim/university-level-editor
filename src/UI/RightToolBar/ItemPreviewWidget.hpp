/**
 * @file ItemPreviewWidget.hpp
 * @author Leveleditor-Gruppe
 * @brief Widget which shows a preview of the selected item.
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <QWidget>
#include <QtWidgets>

#include "../../Lib/LevelManager/LevelManager.hpp"
#include "../View/ItemPreviewUI.hpp"

/**
 * @brief Widget which shows a preview of the selected item.
 * Used in the right toolbar.
 *
 */
class ItemPreviewWidget : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Construct a new ItemPreviewWidget.
     *
     * @param levelManager LevelManager
     * @param parent Parent Widget.
     */
    ItemPreviewWidget(LevelManager& levelManager, QWidget* parent = nullptr);

    /**
     * @brief Updates the preview of the selected item.
     *
     */
    void update();

protected:
    /**
     * @brief Handles this widget's resizing
     *
     * @param event ResizeEvent
     */
    void resizeEvent(QResizeEvent* event);

private:
    /// View of the Preview. Holds a QGraphicsView on which the selected item will be drawn.
    Ui_ItemPreview m_view;

    /// Scene which holds the selected item for preview.
    QGraphicsScene m_scene;

    /// LevelManager
    LevelManager& m_levelManager;
};