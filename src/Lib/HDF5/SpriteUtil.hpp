/**
 * @file SpriteUtil.hpp
 * @author Leveleditor-Gruppe
 * @brief Importing and Exporting of Sprite Objects to and from the HDF5 File.
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef LEVEL_EDITOR_SPRITEUTIL_HPP
#define LEVEL_EDITOR_SPRITEUTIL_HPP

#include "../LevelManager/Sprite.hpp"
#include <QPixmap>
#include <highfive/H5File.hpp>
#include <string>
#include <vector>

namespace HDF5
{
    /**
     * Used for Internal Representation of Collection of Image Arrays
     */
    typedef std::vector<std::vector<std::vector<std::vector<unsigned char>>>> RawSpriteCollectionType;
    /**
     * Used for Internal Representation of Collection of Coordinates
     */
    typedef std::vector<std::vector<int>> RawCoordinateCollectionType;

    namespace Utils
    {
        /**
         * Import a Sprite from the HDF5 DataSet spriteDataSet and return a pointer to the filled Sprite. This is usually called by HDF5::importLevel (LevelUtil).
         * If the Sprite dataset could be parsed correctly, this level will contain the parsed data that was in the datset.
         * Otherwise, an exception is thrown
         * @param spriteDataSet The dataset that contains the current sprite data
         * @param spriteID The ID of the Sprite that should be imported
         * @return A pointer to a Sprite object, needs to be deleted by the user
         * @throw On Failure, some child of HighFive::Exception is thrown
         */
        Sprite* importSprite(HighFive::DataSet& spriteDataSet, std::string spriteID);

        /**
         * Exports a Sprite from the sprite pointer into the HDF5 Group spritesGroup. This is usually called by HDF5::exportLevel (LevelUtil).
         * If the Sprite Data is valid and the export was successful, the resulting HDF5 group should contain the data of this sprite.
         * Otherwise, an exception is thrown
         * @param spritesGroup The group the current sprite should be written to
         * @param sprite A pointer to the sprite that should be exported
         * @throw On Failure, some child of HighFive::Exception is thrown
         */
        void exportSprite(HighFive::Group& spritesGroup, const Sprite* sprite);
    }  // namespace Utils
}  // namespace HDF5


#endif  // LEVEL_EDITOR_SPRITEUTIL_HPP
