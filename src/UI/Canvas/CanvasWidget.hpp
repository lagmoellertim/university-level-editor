/**
 * @file CanvasWidget.hpp
 * @author Leveleditor-Gruppe
 * @brief QWidget which holdes the leveleditor canvas and its scene.
 * @version 0.1
 * @date 2022-02-18
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <QWidget>

#include "../View/TileMapCanvasUI.hpp"
#include "CanvasScene.hpp"
#include "CanvasView.hpp"

/**
 * @brief QWidget which holdes the leveleditor canvas and its scene.
 *
 */
class CanvasWidget : public QWidget
{
    Q_OBJECT

public:
    /// Construct a new Tile Map Canvas.
    CanvasWidget(LevelManager& levelManger, QWidget* parent = nullptr);

    /// Destructor.
    ~CanvasWidget();

signals:
public slots:

private:
    /// Canvas scene
    CanvasScene m_scene;

    /// UI elements
    Ui_TileMapCanvas* m_view;

    /// Level Manager
    LevelManager& m_levelManager;
};