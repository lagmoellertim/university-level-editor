/**
 * @file LevelUtil.hpp
 * @author Leveleditor-Gruppe
 * @brief Importing and Exporting of Level Objects to and from the HDF5 File.
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef LEVEL_EDITOR_LEVELUTIL_HPP
#define LEVEL_EDITOR_LEVELUTIL_HPP

#include "../LevelManager/Level.hpp"
#include <QPixmap>
#include <highfive/H5File.hpp>
#include <string>
#include <vector>

namespace HDF5
{
    /**
     * Helper Type definition for TileMaps
     */
    typedef std::vector<std::vector<int>> TileMapType;

    /**
     * Helper Type definition for TileSets
     */
    typedef std::vector<QPixmap> TileSetType;

    /**
     * Used for Internal Representation of Collection of Image Arrays
     */
    typedef std::vector<std::vector<std::vector<std::vector<unsigned char>>>> RawTileSetType;

    namespace Utils
    {
        /**
         * Import a level from the HDF5 Group levelGroup and return a pointer to the filled Level. This is usually called by HDF5::importHDF5 (Handler).
         * If the level group could be parsed correctly, this level will contain the data that was in the level group.
         * Otherwise, an exception is thrown
         * @param levelGroup The group that contains the current level data
         * @return A pointer to a Level object, needs to be deleted by the user
         * @throw On Failure, some child of HighFive::Exception is thrown
         */
        Level* importLevel(HighFive::Group& levelGroup);

        /**
         * Exports a level from the level pointer into the HDF5 Group levelGroup. This is usually called by HDF5::exportHDF5 (Handler).
         * If the Level Data is valid and the export was successful, the resulting HDF5 group should contain the data of this level.
         * Otherwise, an exception is thrown
         * @param levelGroup The group the current level should be written to
         * @param level A pointer to the level that should be exported
         * @throw On Failure, some child of HighFive::Exception is thrown
         */
        void exportLevel(HighFive::Group& levelGroup, const Level* level);
    }  // namespace Utils
}  // namespace HDF5


#endif  // LEVEL_EDITOR_LEVELUTIL_HPP
