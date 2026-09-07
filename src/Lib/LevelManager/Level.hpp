/**
 * @file Level.hpp
 * @author Leveleditor-Gruppe
 * @brief Contains Representation of Levels
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef LEVEL_EDITOR_LEVEL_HPP
#define LEVEL_EDITOR_LEVEL_HPP

#include "Background.hpp"
#include "Sprite.hpp"
#include "string"
#include "vector"
#include <QObject>
#include <QPixmap>

/**
 * @brief This class is used for the Internal Data Representation of Levels inside the LevelManager
 */
class Level : public QObject
{
    Q_OBJECT

public:
    /**
     * Constructor for a Level
     * @param tileSize The TileSize to use (all tiles are scaled to this size, can't be changed later)
     * @param levelWidth The width of the level (in tiles)
     * @param levelHeight The height of the level (in tiles)
     */
    Level(unsigned int tileSize, unsigned int levelWidth, unsigned int levelHeight);

    /**
     * Destructor for a Level
     */
    ~Level();

    /**
     * Getter for the Level Name
     * @return The Level Name
     */
    const std::string& getLevelName() const;

    /**
     * Getter for the Tile Size
     * @return The Tile Size
     */
    unsigned int getTileSize() const;

    /**
     * Getter for the Level Width
     * @return The Level Width
     */
    unsigned int getLevelWidth() const;

    /**
     * Getter for the Level Height
     * @return The Level Height
     */
    unsigned int getLevelHeight() const;

    /**
     * Getter for the Tile Set
     * @return The Tile Set
     */
    const std::vector<QPixmap>& getTileSet() const;

    /**
     * Getter for the Tile Map
     * @return The Tile Map
     */
    const std::vector<std::vector<int>>& getTileMap() const;

    /**
     * Sets the name of the level and emit an event
     * @param levelName The new name of this level
     * @emit levelMetadataChanged
     */
    void setLevelName(const std::string& levelName);

    /**
     * Changes the tile set and emits an event
     * @param tileSet The new tile set
     * @emit levelItemSetChanged
     */
    void setTileSet(const std::vector<QPixmap>& tileSet);

    /**
     * Changes the tile map and emits an event
     * @param tileMap The new tile map
     * @emit levelCanvasChanged
     */
    void setTileMap(const std::vector<std::vector<int>>& tileMap);

    /**
     * Removes the Tiles from the TileSet and from the TileMap (otherwise the TileMap would reference invalid tiles)
     * @emit levelItemSetChanged
     * @emit levelCanvasChanged
     */
    void clearTileSet();

    /**
     * Removes the Tiles from the TileMap (they are still in the TileSet afterwards)
     * @emit levelCanvasChanged
     */
    void clearTileMap();

    /**
     * Removes all the Sprites from the level
     * @emit levelCanvasChanged
     * @emit levelItemSetChanged
     */
    void clearSpriteSet();

    /**
     * Removes all the positions of the Sprites from the level, so the sprites themself are still in the level,
     * but they don't appear in the canvas
     * @emit positionsChanged
     */
    void clearSprites();

    /**
     * Updates the width of the level to the new level width
     * @param width The new width of the level
     * @emit levelCanvasChanged
     */
    void setWidth(unsigned int width);

    /**
     * Updates the height of the level to new level height
     * @param height The new height of the level
     * @emit levelCanvasChanged
     */
    void setHeight(unsigned int height);

    /**
     * Sets the tile at position (x, y) to the tileID and emit an event
     * @param tileID The new Tile ID
     * @param x x-Coordinate
     * @param y y-Coordinate
     * @emit levelCanvasTileChanged
     */
    void setTileAt(int tileID, int x, int y);

    /**
     * Appends this tileSet to the tileset of the level. It also resizes all the
     * tiles to the tile size specified in this level. Then emits a signal
     * @param tileSet The tile set to append
     * @emit levelItemSetChanged
     */
    void appendToTileSet(std::vector<QPixmap>& tileSet);

    /**
     * Sets the sprites of this level to the new sprites given and connects them to the right signals
     * @param sprites The new sprites
     * @emit levelCanvasChanged
     * @emit levelItemSetChanged
     */
    void setSprites(std::vector<Sprite*>& sprites);

    /**
     * Getter for the Sprite List
     * @return The Sprite List
     */
    const std::vector<Sprite*>& getSprites() const;

    /**
     * Adds and connects the sprite
     * @param sprite The sprite to add
     * @emit levelCanvasChanged
     * @emit levelItemSetChanged
     */
    void addSprite(Sprite* sprite);

    /**
     * Removes a sprite from the level
     * @param sprite The sprite to remove
     * @throw std::runtime_error if an error occurs
     * @emit levelItemSetChanged
     */
    void removeSprite(const Sprite* sprite);

    /**
     * Get the sprite by the specified ID
     * @param id The ID to search for
     * @return A pointer to the matching sprite, or a nullptr if no matching sprite was found
     */
    const Sprite* getSpriteByID(const std::string& id) const;

    /**
     * Sets the backgrounds of this level to the new backgrounds given
     * @param backgrounds The new backgrounds that should be displayed in the level
     * @emit levelBackgroundChanged
     */
    void setBackgrounds(std::vector<Background*>& backgrounds);

    /**
     * Getter for the Backgrounds
     * @return The Backgrounds
     */
    const std::vector<Background*>& getBackgrounds() const;

    /**
     * Adds the background to the Level
     * @param background The background to add
     * @emit levelBackgroundChanged
     */
    void addBackground(Background* background);

    /**
     * Removes the background from the Level
     * @param background The background to remove
     * @emit levelBackgroundChanged
     */
    void removeBackground(const Background* background);

    /**
     * Getter for the Level End Position
     * @return The Level End Position
     */
    int getEndPosition() const;

    /**
     * Set the new Level End Position
     * @param endPosition The new Level End Position
     * @emit levelMetadataChanged
     */
    void setEndPosition(int endPosition);

    /**
     * Get the actor sprite
     * @return The actor sprite (may be a nullptr if the no sprite is set to be the actor)
     */
    const Sprite* getActorSprite() const;

    /**
     * Set the actor sprite
     * @param actorSprite A Pointer to a Sprite that is either a nullptr or a pointer to a sprite inside of m_sprites
     */
    void setActorSprite(Sprite* actorSprite);


private:
    /// The Name of the Level
    std::string m_levelName;

    /// The End Position (x-Coordinate) of the level
    int m_endPosition;

    /// The actor sprite
    Sprite* m_actorSprite = nullptr;

    /// The Size of a single tile in px
    unsigned int m_tileSize = 0;

    /// The Height of a level in tiles
    unsigned int m_levelHeight = 0;

    /// The Width of a level in tiles
    unsigned int m_levelWidth = 0;

    /// The TileSet of the level
    std::vector<QPixmap> m_tileSet;

    /// The TileMap of the level
    std::vector<std::vector<int>> m_tileMap;

    /// The Sprites of the level
    std::vector<Sprite*> m_sprites;

    /// The Backgrounds of the level
    std::vector<Background*> m_backgrounds;

    /**
     * Function to connect sprite signals to all the important level slots
     * @param sprite
     */
    void connectSprite(Sprite* sprite) const;

signals:
    /// Emitted if the metadata (e.g. name, ...) of this level has changed
    void levelMetadataChanged(Level* currentLevel);

    /// The content of the item set of this level has changed (e.g. appended to the tile set, ...)
    void levelItemSetChanged(Level* currentLevel);

    /// The metadata of an item inside this level has changed (e.g. sprite id, sprite metadata, ...)
    void levelItemMetadataChanged(Level* currentLevel);

    /// The content of the canvas of this level has changed (e.g. tiles placed, ...)
    void levelCanvasChanged(Level* currentLevel);

    /// Emitted if a single tile has changed its content
    void levelCanvasTileChanged(Level* currentLevel, int tileID, const QPoint& position);

    /// Emitted if a sprite is placed on the canvas in this level
    void levelCanvasSpritePlaced(Level* currentLevel, Sprite* sprite, const QPoint& position);

    /// Emitted if a sprite is erased from the canvas of this level
    void levelCanvasSpriteErased(Level* currentLevel, Sprite* sprite, const QPoint& position);

    /// Emitted if something in the background layer of this level changes
    void levelBackgroundChanged(Level* currentLevel);

public slots:
    /**
     * This event is re-emitted to levelItemMetadataChanged
     * @param sprite The sprite where this event was emitted from
     * @emit levelItemMetadataChanged
     */
    void onLevelItemMetadataChanged(const Sprite* sprite);

    /**
     * This event is re-emitted to levelCanvasSpritePlaced
     * @param sprite The sprite where this event was emitted from
     * @param position The Position where the sprite was placed
     * @emit levelCanvasSpritePlaced
     */
    void onLevelCanvasSpritePlaced(Sprite* sprite, const QPoint& position);

    /**
     * This event is re-emitted to levelCanvasSpriteErased
     * @param sprite The sprite where this event was emitted from
     * @param position The Position where the sprite was erased
     * @emit levelCanvasSpriteErased
     */
    void onLevelCanvasSpriteErased(Sprite* sprite, const QPoint& position);

    /**
     * This event is re-emitted to levelCanvasChanged and levelItemSetChanged
     * @param sprite The sprite where this event was emitted from
     * @emit levelCanvasChanged
     * @emit levelItemSetChanged
     */
    void onLevelCanvasSpritePositionsChanged(const Sprite* sprite);

    /**
     * This event is re-emitted to levelBackgroundChanged
     * @param background The Background which depth was changed
     * @emit levelBackgroundChanged
     */
    void onLevelBackgroundDepthChanged(const Background* background);
};


#endif  // LEVEL_EDITOR_LEVEL_HPP
