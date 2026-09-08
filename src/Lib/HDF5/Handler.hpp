/**
 * @file Handler.hpp
 * @author Leveleditor-Gruppe
 * @brief Importing and Exporting of LevelManager Objects to and from the HDF5 File. This is the only file (and of course the Exceptions.hpp) of the HDF5 module that needs to be imported by the user
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef LEVEL_EDITOR_HANDLER_HPP
#define LEVEL_EDITOR_HANDLER_HPP

#include "../LevelManager/LevelManager.hpp"
#include <string>

/// Generates and parses HDF5-Files according to the docs in the GitLab wiki: https://gitlab.informatik.uni-osnabrueck.de/cpp2021/praktikum2/-/wikis/HDF5-Level-Struktur
namespace HDF5
{
    /**
     * Import a HDF5-File
     * If errors occur, an exception is thrown
     * @param filename The filename where the HDF5 File is located
     * @param levelManager A pointer to a LevelManager Object where the HDF5-File should be imported into. If no exception is thrown, the object is filled with the relevant information contained in the HDF5 File
     * @param importMusic Whether the music of the level should be imported or not (useful for the extension feature)
     * @throws FileException on file related errors
     * @throws DataException on data related issues
     */
    void importHDF5(const std::string& filename, LevelManager* levelManager, bool importMusic);

    /**
     * Exports the data contained in the level manager into a HDF5 file
     * @param filename The path to the file where it should be saved
     * @param levelManager A pointer to the filled LevelManager object that should be saved
     * @throws FileException on file related errors
     * @throws DataException on data related issues
     */
    void exportHDF5(const std::string& filename, const LevelManager* levelManager);
}  // namespace HDF5


#endif  // LEVEL_EDITOR_HANDLER_HPP
