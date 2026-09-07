/**
 * @file BackgroundUtil.hpp
 * @author Leveleditor-Gruppe
 * @brief Importing and Exporting of backgrounds to and from the HDF5 File
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef LEVEL_EDITOR_BACKGROUNDUTIL_HPP
#define LEVEL_EDITOR_BACKGROUNDUTIL_HPP

#include "../LevelManager/Background.hpp"
#include <QPixmap>
#include <highfive/H5File.hpp>
#include <string>
#include <vector>

namespace HDF5
{
    /**
     * Used for Internal Representation of Collection of Image Arrays
     */
    typedef std::vector<std::vector<std::vector<unsigned char>>> RawBackgroundImageType;

    namespace Utils
    {
        /**
         * Function to import a background from the given Dateset. It converts the Raw Background into an Instance
         * of the Background class. The Attributes (speed and depth) are also transferred to the instance.
         * @param backgroundDataSet The DateSet where the raw Background Image is saved in
         * @param backgroundID The ID of the current dataset to set the instance id accordingly
         * @return A pointer to a background instance (must be deleted by the user)
         * @throw On Failure, some child of HighFive::Exception is thrown
         */
        Background* importBackground(HighFive::DataSet& backgroundDataSet, std::string backgroundID);

        /**
         * Export and convert a background instance to a raw background and save it to the background group. The Name of the
         * Dataset that is created in this function is equal to the id of the background.
         * @param backgroundGroup The group where the Background DataSet should be saved in
         * @param background A Pointer to the Background Instance that should be saved
         * @throw On Failure, some child of HighFive::Exception is thrown
         */
        void exportBackground(HighFive::Group& backgroundGroup, const Background* background);
    }  // namespace Utils
}  // namespace HDF5


#endif  // LEVEL_EDITOR_BACKGROUNDUTIL_HPP
