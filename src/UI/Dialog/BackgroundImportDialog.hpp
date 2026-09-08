/**
 * @file BackgroundImportDialog.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */


#pragma once

#include "../../Lib/LevelManager/Level.hpp"
#include "../View/ImportBackgroundUI.hpp"


/**
 * @brief Dialog for importing backgrounds
 *
 */
class BackgroundImportDialog : public QDialog
{
public:
    /**
     * @brief Construct a BackgroundImportDialog object
     *
     * @param levelManager LevelManager
     * @param parent
     */
    BackgroundImportDialog(Level* level, QWidget* parent = nullptr);

    /**
     * @brief Return entered Background ID
     *
     * @return std::string Background ID
     */
    std::string getID() const;

    /**
     * @brief Get entered Parallax Depth
     *
     * @return int Parallax depth
     */
    int getParallaxInput() const;

    /**
     * @brief Get entered Speed
     *
     * @return int Speed
     */
    int getSpeedInput() const;

public slots:
    /**
     * @brief Called when the entered Background ID changes. Used to check if entered id is unique
     *
     * @param item
     */
    void onTextChanged(const QString& text);

private:
    /// Dialog Ui
    Ui_BackgroundImportDialog m_UI;

    /// Current Background ids for checking if ids are unique
    std::vector<std::string> m_backgroundIDs;
};