/**
 * @file SpriteEdit.hpp
 * @author Leveleditor-Gruppe
 * @brief Dialog Helper that deals with editing Sprites
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef LEVEL_EDITOR_SPRITEEDIT_HPP
#define LEVEL_EDITOR_SPRITEEDIT_HPP


#include "../../UI/GraphicsItem/GraphicsSpriteItem.hpp"
#include "../LevelManager/LevelManager.hpp"
namespace Dialog
{
    /**
     * The Dialog to edit a Sprite.
     * @param levelManager The levelManager to load and save data dealing with the current sprite
     * @param selectedSprite The currently selected Sprite
     */
    void editSprite(LevelManager& levelManager, GraphicsSpriteItem* selectedSprite);
}  // namespace Dialog


#endif  // LEVEL_EDITOR_SPRITEEDIT_HPP
