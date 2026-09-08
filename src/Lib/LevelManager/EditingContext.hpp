/**
 * @file EditingContext.hpp
 * @author Leveleditor-Gruppe
 * @brief Contains the Editing Context that describes the current editor state
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef LEVEL_EDITOR_EDITINGCONTEXT_HPP
#define LEVEL_EDITOR_EDITINGCONTEXT_HPP


#include "Background.hpp"
#include "Sprite.hpp"
#include <QObject>

/// Layers on which a level can be edited.
enum Layer
{
    TILE_LAYER,
    SPRITE_LAYER,
    ENDPOSITION_LAYER
};

/**
 * @brief Holds the editing context of each level of the LevelManager. This includes the selected tile and layer
 */
class EditingContext : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Get the currently selected Layer
     * @return Layer
     */
    Layer getSelectedLayer() const;

    /**
     * @brief Set the Selected Layer
     * @param selectedLayer Layer
     */
    void setSelectedLayer(Layer selectedLayer);

    /**
     * @brief Get the tile-ID of the selected tile.
     * @return int Tile-ID
     */
    int getSelectedTileID() const;

    /**
     * @brief Set the tile-ID of the selected tile.
     * @param selectedTileID tile-ID of selected tile
     */
    void setSelectedTileID(int selectedTileID);

    /**
     * @brief Get the Selected Sprite object
     * @return Sprite*
     */
    Sprite* getSelectedSprite() const;

    /**
     * @brief Set the Selected Sprite object
     * @param selectedSprite Pointer to selected sprite
     */
    void setSelectedSprite(Sprite* selectedSprite);

    /**
     * @brief Get the Visible Layers.
     *
     * @return std::vector<Layer> Visible layers
     */
    std::vector<Layer> getVisibleLayers();

    /**
     * @brief Set given layer as Visible, all others will be set as invsible.
     *
     * @param visibleLayers Visible layers
     */
    void setVisibleLayers(std::vector<Layer> visibleLayers);

    /**
     * @brief Set the given layer as invisible.
     *
     * @param layer Layer which should be invisible
     */
    void hideLayer(Layer layer);

    /**
     * @brief Set the given layer as visible.
     *
     * @param layer Layer which should be visible.
     */
    void showLayer(Layer layer);

    /**
     * @brief Get all visible backgrounds
     *
     * @return std::vector<Background*> all visible backgrounds
     */
    std::vector<Background*> getVisibleBackgrounds();

    /**
     * @brief Set all visible backgrounds, all others will be invisible
     *
     * @param visibleBackgrounds all backgrounds which should be visible
     */
    void setVisibleBackgrounds(std::vector<Background*> visibleBackgrounds);

    /**
     * @brief Set the visibility of the given background
     *
     * @param background Background which visibility will be set
     * @param visibility True means background should be visible
     */
    void setBackgroundVisibility(Background* background, bool visibility);

private:
    /// Selected Layer.
    Layer m_selectedLayer = TILE_LAYER;
    /// Visible Layers.
    std::vector<Layer> m_visibleLayers{TILE_LAYER, SPRITE_LAYER, ENDPOSITION_LAYER};

    /// All backgrounds inside this array are set to visible in the UI
    std::vector<Background*> m_visibleBackgrounds;
    /// Tile-ID of selected tile.
    int m_selectedTileID = -1;
    /// Pointer to selected sprite
    Sprite* m_selectedSprite = nullptr;

signals:
    /// The selected Layer has changed.
    void contextLayerSelectionChanged(EditingContext* currentContext);

    /// The tile-ID of the selected Item has changed.
    void contextItemSelectionChanged(EditingContext* currentContext);

    /// A layer or backgroudn changed its visibility state.
    void contextLayerVisibilityChanged(EditingContext* currentContext);
};


#endif  // LEVEL_EDITOR_EDITINGCONTEXT_HPP
