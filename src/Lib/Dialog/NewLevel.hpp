/**
 * @file NewLevel.hpp
 * @author Leveleditor-Gruppe
 * @brief Dialog Helper that deals with creating new Levels
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef LEVEL_EDITOR_NEWLEVEL_HPP
#define LEVEL_EDITOR_NEWLEVEL_HPP


#include "../LevelManager/LevelManager.hpp"
namespace Dialog
{
    /**
     * Dialog to create a new level. On successful completion of this dialog, the level is automatically created in the levelManager
     * @param levelManager A reference to the levelManager
     */
    void newLevel(LevelManager& levelManager);
}  // namespace Dialog

#endif  // LEVEL_EDITOR_NEWLEVEL_HPP
