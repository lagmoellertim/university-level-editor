/**
 * @file SpriteEditDialog.hpp
 * @author Leveleditor-Gruppe
 * @brief
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */


#pragma once

#include "../../Lib/LevelManager/Level.hpp"
#include "../../Lib/LevelManager/Sprite.hpp"
#include "../View/SpriteEditUI.hpp"


/**
 * @brief Dialog for editing Sprites
 *
 */
class SpriteEditDialog : public QDialog
{
public:
    /**
     * @brief Construct a new Sprite Edit Dialog object
     *
     * @param sprite The edited Sprite
     * @param level The selected Level
     * @param parent
     */
    SpriteEditDialog(Sprite* sprite, Level* level, QWidget* parent = nullptr);

    /**
     * @brief Get List of Modifiers
     *
     * @return std::vector<std::string> Modifiers
     */
    std::vector<std::string> getModifiers() const;

    /**
     * @brief Get the entered Sprite Height
     *
     * @return int Sprite Height
     */
    int getHeight() const;

    /**
     * @brief Get the entered Sprite ID
     *
     * @return std::string Sprite ID
     */
    std::string getID() const;

    /**
     * @brief Check if the sprite is the actor
     *
     * @return true if is actor
     * @return false if is not actor
     */
    bool isActor() const;

public slots:
    /**
     * @brief Connected to Sprite ID Input, for checking unique ids
     *
     */
    void onTextChanged(const QString& text);

    /**
     * @brief Modifier from List right-clicked. Open context menu.
     *
     * @param pos Click position
     */
    void onItemRightClick(const QPoint& pos);

    /**
     * @brief Add a modifier string to the list, connected to Add Button
     *
     */
    void onAddModifier();

private:
    /// Dialog Ui
    Ui_SpriteEditDialog m_UI;

    /// Current Level
    Level* m_level;

    /// Old ID for checking unique ids
    std::string m_oldID;
};