/**
 * @file ImportSoundDialog.hpp
 * @author Leveleditor-Gruppe
 * @brief
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */


#pragma once

#include "../View/ImportSoundUI.hpp"


/**
 * @brief Dialog for importing sounds
 *
 */
class ImportSoundDialog : public QDialog
{
public:
    /**
     * @brief Construct a ImportSoundDialog object
     *
     * @param soundList list of current sounds to check if id is unique
     * @param parent
     */
    ImportSoundDialog(std::vector<std::string> soundList, QWidget* parent = nullptr);

    /**
     * @brief Get the entered Sound ID
     *
     * @return std::string Sound ID
     */
    std::string getID() const;

    /**
     * @brief Pre-fill a suggested sound ID (e.g. from the selected filename)
     *
     * @param id Suggested sound ID
     */
    void setSuggestedID(const QString& id);

public slots:
    /**
     * @brief Called when the Sound ID inside of LineEdit has changed. Used to check if id is unique.
     *
     */
    void onTextChanged(const QString& text);

private:
    /// Dialog Ui
    Ui_ImportSoundDialog m_UI;

    /// List of current sounds
    std::vector<std::string> m_soundList;
};