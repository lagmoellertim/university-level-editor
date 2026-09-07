/**
 * @file LevelManager.hpp
 * @author Leveleditor-Gruppe
 * @brief Contains the LevelManager, the main DataStructure that manages the state of the entire Editor
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef LEVEL_EDITOR_LEVELMANAGER_HPP
#define LEVEL_EDITOR_LEVELMANAGER_HPP

#include "EditingContext.hpp"
#include "Level.hpp"
#include "Sound.hpp"
#include <QObject>
#include <map>
#include <vector>

/**
 * @brief The main DataStructure that manages all the Data that is displayed in the UI. It also uses signals and signal-rerouting
 * in order to notify the subscribed UI elements if a relevant change to the data structure occurs
 */
class LevelManager : public QObject
{
    Q_OBJECT

public:
    /**
     * Getter for the currently selected level
     * @return Pointer to the currently selected Level
     */
    Level* getSelectedLevel() const;

    /**
     * Sets the level defined by the id to be the new selected level
     * @param id The ID of the level that should be active (index in vector)
     * @emit levelSelectionChanged
     * @throw std::runtime_error if invalid ids where given
     */
    void setSelectedLevelByID(int id);

    /**
     * Gets the id of the currently selected level if there is one, else -1
     * @return ID of the level or -1
     */
    int getSelectedLevelID();

    /**
     * Adds a level to the Manager, connects all the necessary signals to slots, creates a Context and emits an event
     * @param level A pointer to a Level object (must stay in scope until LevelManager gets deleted, is automatically cleared then)
     * @emit levelListChanged
     * @throw std::runtime_error if level is a nullptr
     */
    void addLevel(Level* level);

    /**
     * Moves a Level from its old id (from id) to the new id (to id). A event is emit after this action.
     * @param fromID The current id of the level to move
     * @param toID The new id the level should have
     * @emit levelListChanged (although maybe unnecessary)
     * @throw std::runtime_error if invalid ids where given
     */
    void moveLevel(int fromID, int toID);

    /**
     * Removes the level that is associated with the id. If the to be deleted level is also the currently selected level, the currently selected
     * level is set to a nullptr. Both the level and its corresponding context are deleted afterwards. Events are emitted
     * @param id The id of the level to remove
     * @emit levelSelectionChanged only if the currently selected Level is the level that should be deleted
     * @emit levelListChanged
     * @throw std::runtime_error if invalid ids where given
     */
    void removeLevelByID(int id);

    /**
     * Getter for current context
     * @return The context matching the currently selected level if there is one, else nullptr
     */
    EditingContext* getSelectedContext() const;

    /**
     * Getter for level vector
     * @return the level vector
     */
    const std::vector<Level*>& getLevels() const;

    /**
     * Exports this Class into a HDF5 file with the specified filename
     * @param filename The path where the file should be saved
     */
    void save(const std::string& filename) const;

    /**
     * Imports a HDF5 file into this structure
     * @param filename  Path where the HDF5 file is located
     */
    void load(const std::string& filename);

    /**
     * Extends the current LevelManager with levels contained in another level file. The music is not copied
     * @param filename Path where the HDF5 file is located
     */
    void loadExtend(const std::string& filename);

    /**
     * Getter for the list of sounds of the LevelManager
     * @return The list of sounds
     */
    const std::vector<Sound*>& getSounds() const;

    /**
     * Overwrite the current list of sounds with new sounds
     * @param sounds The List of new sounds
     */
    void setSounds(const std::vector<Sound*>& sounds);

    /**
     * Adds a sound to the Level Manager
     * @param sound The Sound to add
     */
    void addSound(Sound* sound);

    /**
     * Returns a Sound object which is searched by the specified id
     * @param id The ID to search for
     * @return A pointer to the sound if a sound with the matching id was found, else a nullptr
     */
    Sound* getSoundByID(const std::string& id) const;

    /**
     * Removes all the levels from the level manager by using removeLevelByID
     * @emit Same as removeLevelByID
     */
    void clear();

    /**
     * Destructor for the Level Manager
     */
    ~LevelManager();

private:
    /**
     * Checks if the id references a valid level, else an exception is thrown
     * @param id The Level-ID to check
     * @throw std::runtime_error if invalid
     */
    void throwErrorOnInvalidID(int id);

    /// The List of Levels that are contained inside the Level Manager
    std::vector<Level*> m_levels;

    /// A Pointer to the currently selected level
    Level* m_selectedLevel = nullptr;

    /// A map that links an editing context to a level
    std::map<Level*, EditingContext*> m_contexts;

    /// A List of Sounds that are contained inside the Level Manager
    std::vector<Sound*> m_sounds;

signals:
    /// Levels were added or removed (Changes to the levels vector)
    void levelListChanged();

    /// The selected level has changed
    void levelSelectionChanged();

    /// The content of the item set of the currently selected level has changed (e.g. appended to the tile set, ...)
    void selectedLevelItemSetChanged();

    /// The metadata of an item inside the current level has changed (e.g. sprite id, sprite metadata, ...)
    void selectedLevelItemMetadataChanged();

    /// The content of the canvas of the currently selected level has changed (e.g. tiles placed, ...)
    void selectedLevelCanvasChanged();

    /// Emitted if a single tile has changed its content inside the current level
    void selectedLevelCanvasTileChanged(int tileID, const QPoint& position);

    /// If a sprite is placed on the canvas in the current level
    void selectedLevelCanvasSpritePlaced(Sprite* sprite, const QPoint& position);

    /// If a sprite is erased on the canvas in the current level
    void selectedLevelCanvasSpriteErased(Sprite* sprite, const QPoint& position);

    /// If something in the background layer of the current level changes
    void selectedLevelBackgroundChanged();

    /// Emitted if the metadata (e.g. name, ...) of the selected level has changed
    void selectedLevelMetadataChanged();

    /// Emitted if the Layer of the currently selected level is changed (e.g. from Tile Layer to Collision Layer)
    void selectedLevelLayerSelectionChanged();

    /// Emitted if the selected item for the current level has changed (e.g. a different tile is selected from the toolbar)
    void selectedLevelContextItemChanged();

    /// Emitted if the visibility of a layer of the current level has changed ( e.g. a tilemap is hidden)
    void selectedLevelContextLayerVisibiltyChanged();


public slots:
    /**
     * If the eventProducer is also the selected Level, this event is re-emitted to selectedLevelItemSetChanged
     * @param eventProducer The Level that produces this event
     * @emit selectedLevelItemSetChanged
     */
    void onLevelItemSetChanged(Level* eventProducer);

    /**
     * If the eventProducer is also the selected Level, this event is re-emitted to selectedLevelItemMetadataChanged
     * @param eventProducer The Level that produces this event
     * @emit selectedLevelItemMetadataChanged
     */
    void onLevelItemMetadataChanged(Level* eventProducer);

    /**
     * If the eventProducer is also the selected Level, this event is re-emitted to selectedLevelCanvasChanged
     * @param eventProducer The Level that produces this event
     * @emit selectedLevelCanvasChanged
     */
    void onLevelCanvasChanged(Level* eventProducer);

    /**
     * If the eventProducer is also the selected Level, this event is re-emitted to selectedLevelCanvasTileChanged
     * @param eventProducer The Level that produces this event
     * @param tileID The new tile ID
     * @param position The position where the new tile ID should be applied
     * @emit selectedLevelCanvasTileChanged
     */
    void onLevelCanvasTileChanged(Level* eventProducer, int tileID, const QPoint& position);

    /**
     * If the eventProducer is also the selected Level, this event is re-emitted to selectedLevelCanvasSpritePlaced
     * @param eventProducer The Level that produces this event
     * @param sprite The sprite that should be placed
     * @param position The position where the new sprite should be placed
     * @emit selectedLevelCanvasSpritePlaced
     */
    void onLevelCanvasSpritePlaced(Level* currentLevel, Sprite* sprite, const QPoint& position);

    /**
     * If the eventProducer is also the selected Level, this event is re-emitted to selectedLevelCanvasSpriteErased
     * @param eventProducer The Level that produces this event
     * @param sprite The sprite that should be erased
     * @param position The position where the new sprite should be erased
     * @emit selectedLevelCanvasSpriteErased
     */
    void onLevelCanvasSpriteErased(Level* currentLevel, Sprite* sprite, const QPoint& position);

    /**
     * If the eventProducer is also the selected Level, this event is re-emitted to selectedLevelMetadataChanged
     * @param eventProducer The Level that produces this event
     * @emit selectedLevelMetadataChanged
     */
    void onLevelMetadataChanged(Level* eventProducer);

    /**
     * If the eventProducer is also the selected Level, this event is re-emitted to selectedLevelBackgroundChanged
     * @param eventProducer The Level that produces this event
     * @emit selectedLevelBackgroundChanged
     */
    void onLevelBackgroundChanged(Level* eventProducer);

    /**
     * If the eventProducer is the context of the selected Level, this event is re-emitted to selectedLevelLayerSelectionChanged
     * @param eventProducer The Editing Context that produces this event
     * @emit selectedLevelLayerSelectionChanged
     */
    void onContextLayerSelectionChanged(EditingContext* eventProducer);

    /**
     * If the eventProducer is the context of the selected Level, this event is re-emitted to selectedLevelContextItemChanged
     * @param eventProducer The Editing Context that produces this event
     * @emit selectedLevelContextItemChanged
     */
    void onContextItemSelectionChanged(EditingContext* eventProducer);

    /**
     * If the eventProducer is the context of the selected Level, this event is re-emitted to selectedContextLayerVisibilityChanged
     * @param eventProducer The Editing Context that produces this event
     * @emit selectedLevelContextLayerVisibilityChanged
     */
    void onContextLayerVisibilityChanged(EditingContext* eventProducer);
};

#endif  // LEVEL_EDITOR_LEVELMANAGER_HPP
