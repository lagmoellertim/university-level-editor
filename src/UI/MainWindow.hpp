/**
 * @file MainWindow.hpp
 * @author Leveleditor-Gruppe
 * @brief Main window.
 * It displays a left toolbar for item and level selection,
 * a canvas for placing items in a level
 * and a right toolbar with a item preview and layer settings.
 * @version 0.1
 * @date 2022-02-18
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <QtWidgets>

#include "Canvas/CanvasWidget.hpp"
#include "LeftToolBar/ToolBar.hpp"
#include "RightToolBar/ItemPreviewWidget.hpp"
#include "RightToolBar/LayersSettingsWidget.hpp"
#include "View/MainWindowUI.hpp"

/**
 * @brief Main window.
 * It displays a left toolbar for item and level selection,
 * a canvas for placing items in a level
 * and a right toolbar with a item preview and layer settings.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Construct a new Main Window
     *
     * @param levelManager LevelManager
     */
    MainWindow(LevelManager& levelManager);

    /**
     * @brief Destructor, frees memory.
     *
     */
    virtual ~MainWindow();


private slots:
    void handleSave();
    void handleLoadExtend();
    void handleLoad();
    void handleImportSound();
    void handleManageSounds();
    void updateWindowTitle();

private:
    /// Main window UI.
    Ui_MainWindow m_mainWindowUi;

    /// Tilemap canvas.
    CanvasWidget* m_tileMapCanvas;

    /// Left Toolbar.
    ToolBar* m_toolBar;

    /// Right Bar for layer settings.
    LayersSettingsWidget* m_layersSettings;

    /// Preview for selected item.
    ItemPreviewWidget* m_itemPreview;

    /// Widget for storing UI elements of the right bar vertically.
    QSplitter* m_rightBar;

    /// Widget for storing left toolbar, tilemap canvas and right bar horizontally.
    QSplitter m_splitter;

    /// Level manager.
    LevelManager& m_levelManager;
};
