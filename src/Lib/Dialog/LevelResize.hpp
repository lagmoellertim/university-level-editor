/**
 * @file LevelResize.hpp
 * @author Leveleditor-Gruppe
 * @brief Dialog Helper that deals with resizing Levels
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef LEVEL_EDITOR_LEVELRESIZE_HPP
#define LEVEL_EDITOR_LEVELRESIZE_HPP


#include "../LevelManager/LevelManager.hpp"
namespace Dialog
{
    /**
     * Dialog used for resizing the level. If the dialog was filled out successfully and potentially appearing warnings were accepted,
     * functions in the levelManager are called to automatically resize the level to the specified size
     * @param levelManager A reference to the levelManager interface
     * @param parent A Pointer to the parent widget or a nullptr
     */
    void resizeLevel(LevelManager& levelManager, QWidget* parent = nullptr);
}  // namespace Dialog


#endif  // LEVEL_EDITOR_LEVELRESIZE_HPP
