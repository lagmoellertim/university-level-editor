/**
 * @file Utils.hpp
 * @author Leveleditor-Gruppe
 * @brief Util for converting between the QImage format and raw image data vectors
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef LEVEL_EDITOR_UTILS_HPP
#define LEVEL_EDITOR_UTILS_HPP


#include <QImage>
#include <vector>

namespace HDF5::Utils
{
    /**
     * Internal Type Definition used for Representing a RawImageType (Height x Width x 4 (RGBA))
     */
    typedef std::vector<std::vector<std::vector<unsigned char>>> RawImageType;

    /**
     * Writes the contents of a QImage into the RawImage Data structure (given via reference)
     * @param source The source Image Data in form of a QImage object
     * @param target A reference to nested unsigned char vectors where the image data should be written to
     */
    void convertQImageToVector(const QImage& source, RawImageType& target);

    /**
     * Converts the source Raw Image into a QImage object which is then returned
     * @param source The Raw Data Source of the Image (RawImageType)
     * @return A QImage instance which contains the parsed raw imaged data
     */
    QImage convertVectorToQImage(const RawImageType& source);
}  // namespace HDF5::Utils


#endif  // LEVEL_EDITOR_UTILS_HPP
