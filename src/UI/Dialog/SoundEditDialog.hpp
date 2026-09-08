/**
 * @file SoundEditDialog.hpp
 * @author Leveleditor-Gruppe
 * @brief
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */


#pragma once

#include "../../Lib/LevelManager/LevelManager.hpp"
#include "../View/SoundEditUI.hpp"
#include <QBuffer>
#include <QMediaPlayer>


/**
 * @brief Dialog for editing sounds
 *
 */
class SoundEditDialog : public QDialog
{
public:
    /**
     * @brief Construct a SoundEditDialog object
     *
     * @param levelManager LevelManager
     * @param parent
     */
    SoundEditDialog(LevelManager& levelManager, QWidget* parent = nullptr);

    /**
     * @brief Destroy the Sound Edit Dialog object
     *
     */
    ~SoundEditDialog();

    /**
     * @brief Get the List of entered Sounds
     *
     * @return std::vector<Sound*> list of entered sounds
     */
    std::vector<Sound*> getSounds() const;

public slots:
    /**
     * @brief Sound from List right-clicked. Open context menu.
     *
     * @param pos Click position
     */
    void onItemRightClick(const QPoint& pos);

    /**
     * @brief Toggle Sound Play / Pause
     *
     */
    void onTogglePlay();

    /**
     * @brief Add new Sound to SoundList, connected to Add Button
     *
     */
    void onAddSound();

    /**
     * @brief Called when a Sound from the list has been selected
     *
     */
    void onSoundSelected(QListWidgetItem* item);

    /**
     * @brief Called when a Sound ID has changed. Used to check if id is unique
     *
     * @param item list item
     */
    void onItemChanged(QListWidgetItem* item);


private:
    /// Dialog Ui
    Ui_SoundEditDialog m_UI;

    /// Current playing sound
    Sound* m_currentSound = nullptr;

    /// List of current sounds
    std::vector<Sound*> m_sounds;

    /// LevelManager
    LevelManager& m_levelManager;

    /// Media Player for Sound preview
    QMediaPlayer* m_mediaPlayer;

    /// Audio Buffer
    QBuffer* m_audioBuffer;

    /**
     * @brief Get the Sound Object by it's ID
     *
     * @param id Sound id
     * @return Sound* Sound object or nullptr if it does not exist
     */
    Sound* getSoundByID(const std::string& id);
};