/**
 * @file Sound.hpp
 * @author Leveleditor-Gruppe
 * @brief Contains Representation of Sounds
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef LEVEL_EDITOR_MUSIC_HPP
#define LEVEL_EDITOR_MUSIC_HPP


#include <QByteArray>
#include <string>

/**
 * @brief This class is used for the Internal Data Representation of Sounds inside the LevelManager
 */
class Sound
{
public:
    /**
     * Constructor for Sound objects
     * @param id The ID of the sound
     * @param rawSoundData The raw binary data of the sound file
     */
    Sound(const std::string& id, const QByteArray& rawSoundData);

    /**
     * Creates a new Sound object and directly imports a music file that should be used for the binary data
     * @param id The ID of the Sound object
     * @param filename The filename where the audio file that should be imported is located
     * @return A Pointer to a Sound object (needs to be deleted by the user)
     * @throw std::runtime_error If the file access fails
     */
    static Sound* fromFile(const std::string& id, const std::string& filename);

    /**
     * Getter for the ID of the Sound
     * @return The ID of the Sound
     */
    const std::string& getID() const;

    /**
     * Setter for the ID of the Sound
     * @param id The new ID of the Sound
     */
    void setID(const std::string& id);

    /**
     * Getter for the Raw Sound Data of this Sound
     * @return A byte array of raw sound file data
     */
    const QByteArray& getRawSoundData() const;

private:
    /// The ID of the Sound
    std::string m_id;

    /// The Raw Sound Data
    QByteArray m_rawSoundData;
};


#endif  // LEVEL_EDITOR_MUSIC_HPP
