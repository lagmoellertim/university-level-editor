/**
 * @file Background.hpp
 * @author Leveleditor-Gruppe
 * @brief Contains Representation of Background Images
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef LEVEL_EDITOR_BACKGROUND_HPP
#define LEVEL_EDITOR_BACKGROUND_HPP


#include <QPixmap>

/**
 * @brief This class is used for the Internal Data Representation of Background Images inside the LevelManager
 */
class Background : public QObject
{
    Q_OBJECT
public:
    /**
     * Constructor of the background object
     * @param backgroundImage The Content of the Image in form of a QPixmap
     * @param id The ID of the Background
     */
    Background(const QPixmap& backgroundImage, std::string id);

    /**
     * Getter for the Image QPixmap
     * @return The Image Content (QPixmap) of the Background
     */
    const QPixmap& getBackgroundImage() const;

    /**
     * Getter for the ID of the Background
     * @return The ID of the Background
     */
    const std::string getID() const;

    /**
     * Getter for the Depth (Parallax Attribute)
     * @return The Depth of the Background
     */
    int getDepth() const;

    /**
     * Setter for the Depth (Parallax Attribute)
     * @param depth The Depth of the Background
     * @emit depthChange
     */
    void setDepth(int depth);

    /**
     * Getter for the Speed (Parallax Attribute)
     * @return The Speed of the Background
     */
    int getSpeed() const;

    /**
     * Setter for the Speed (Parallax Attribute)
     * @param speed The Speed of the Background
     */
    void setSpeed(int speed);

private:
    /// The Image Content of the Background
    QPixmap m_backgroundImage;

    /// The Depth (Parallax Attribute) of the Background
    int m_depth = 0;

    /// The Speed (Parallax Attribute) of the Background
    int m_speed = 0;

    /// The ID of the Background
    std::string m_id;

signals:
    /// Emitted if the parallax depth of this background gets changed
    void depthChange(Background* background);
};


#endif  // LEVEL_EDITOR_BACKGROUND_HPP
