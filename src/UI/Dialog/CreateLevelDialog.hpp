/**
 * @file CreateLevelDialog.hpp
 * @author Leveleditor-Gruppe
 * @brief
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */


#pragma once

#include "../View/CreateLevelUI.hpp"


/**
 * @brief Dialog for creating a new Level
 *
 */
class CreateLevelDialog : public QDialog
{
public:
    /**
     * @brief Construct a CreateLevelDialog object
     *
     * @param parent
     */
    CreateLevelDialog(QWidget* parent = nullptr);

    /**
     * @brief Get entered level width
     *
     * @return int level width
     */
    int levelWidth() const;

    /**
     * @brief Get entered level height
     *
     * @return int level height
     */
    int levelHeight() const;

    /**
     * @brief Get entered tile size
     *
     * @return int tile size
     */
    int tileSize() const;

    /**
     * @brief Get entered level name
     *
     * @return QString level name
     */
    QString levelName() const;

public slots:
    /**
     * @brief Connected to Level Name Input. Used to check if the entered name is empty.
     *
     */
    void onTextChanged(const QString& text);

private:
    /// Dialog Ui
    Ui_CreateLevelDialog m_UI;
};