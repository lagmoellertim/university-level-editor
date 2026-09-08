/**
 * @file Exceptions.hpp
 * @author Leveleditor-Gruppe
 * @brief Definition of Data- and File-Exceptions for the HDF5 Utility
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef LEVEL_EDITOR_EXCEPTIONS_HPP
#define LEVEL_EDITOR_EXCEPTIONS_HPP

#include <stdexcept>

namespace HDF5
{
    /**
     * @brief Exception used for errors dealing with file related issues
     */
    class FileException : public std::runtime_error
    {
    public:
        explicit FileException(const std::string& what)
            : std::runtime_error(what.c_str())
        {
        }
    };

    /**
     * @brief Exception for every other exception thrown by HighFive (Data related)
     */
    class DataException : public std::runtime_error
    {
    public:
        explicit DataException(const std::string& what)
            : std::runtime_error(what.c_str())
        {
        }
    };
}  // namespace HDF5

#endif  // LEVEL_EDITOR_EXCEPTIONS_HPP
