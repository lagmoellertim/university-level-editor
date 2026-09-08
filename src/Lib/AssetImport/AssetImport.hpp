/**
 * @file AssetImport.hpp
 * @author Leveleditor-Gruppe
 * @brief Dialog Helper that handles importing all kinds of required editor assets (TileSets, TileMaps, Sounds and Backgrounds)
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef LEVEL_EDITOR_ASSETIMPORT_HPP
#define LEVEL_EDITOR_ASSETIMPORT_HPP

#include "../LevelManager/Level.hpp"
#include "../LevelManager/Sound.hpp"
#include "../LevelManager/Sprite.hpp"
#include <QPixmap>
#include <vector>

namespace AssetImport
{
    /**
     * Opens an import dialog procedure for Tile Sets. If a correct TileSet was selected
     * inside the dialog, this function will return a pointer to the vector, otherwise nullptr.
     * This pointer needs to be deleted by the user
     * @param parent A Pointer to the parent widget or a nullptr
     * @return Nullptr on error or Pointer to vector on success
     */
    std::vector<QPixmap>* importTileSet(QWidget* parent = nullptr);

    /**
     * Opens an import dialog procedure for Sprite Frames. If a correct Sprite was selected
     * inside the dialog, this function will return a pointer to the Sprite, otherwise nullptr.
     * This pointer needs to be deleted by the user
     * @param parent A Pointer to the parent widget or a nullptr
     * @return Nullptr on error or Pointer to Sprite on success
     */
    Sprite* importSprite(Level* level, QWidget* parent = nullptr);

    /**
     * Opens an import dialog procedure for Sounds. If a correct sound was selected
     * inside the dialog, this function will return a pointer to the Sprite, otherwise nullptr.
     * This pointer needs to be deleted by the user
     * @param soundList A list of sound ids that are currently in use. Used to check for conflicts in ids (id needs to be unique)
     * @param parent A Pointer to the parent widget or a nullptr
     * @return Nullptr on error or Pointer to Sound on success
     */
    Sound* importSound(std::vector<std::string> soundList, QWidget* parent = nullptr);

    /**
     * Opens an import dialog procedure for Backgrounds. If a correct sound was selected
     * inside the dialog, this function will return a pointer to the Background, otherwise nullptr.
     * This pointer needs to be deleted by the user
     * @param level A pointer to the current level to check for id conflicts
     * @param parent A Pointer to the parent widget or a nullptr
     * @return Nullptr on error or Pointer to Background on success
     */
    Background* importBackground(Level* level, QWidget* parent = nullptr);

    namespace Utils
    {
        /**
         * Opens a file modal.
         * @param openName The Text that is displayed on the open button in the file select window
         * @param parent A Pointer to the parent widget or a nullptr
         * @param allowedExtensions A string that contains the extensions that the file that should be opened can have
         * @return Returns the selected path
         */
        QString getFilename(QString openName, QWidget* parent, const std::string& allowedExtensions);
    }  // namespace Utils
};     // namespace AssetImport


#endif  // LEVEL_EDITOR_ASSETIMPORT_HPP
