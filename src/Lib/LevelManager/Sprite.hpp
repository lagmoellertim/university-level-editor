/**
 * @file Sprite.hpp
 * @author Leveleditor-Gruppe
 * @brief Contains Representation of Sprites
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef LEVEL_EDITOR_SPRITE_HPP
#define LEVEL_EDITOR_SPRITE_HPP


#include <QObject>
#include <QPixmap>
#include <string>
#include <vector>


/**
 * @brief This class is used for the Internal Data Representation of Sprites inside the LevelManager
 */
class Sprite : public QObject
{
    Q_OBJECT
public:
    /**
     * Constructor for Sprite objects
     * @param frames A collection of frames of the sprite
     */
    Sprite(const std::vector<QPixmap>& frames);

    /**
     * Getter for the scaled frames of this sprite
     * @return The scaled frames
     */
    const std::vector<QPixmap>& getFrames() const;

    /**
     * Getter for the width of the scaled frames
     * @return The width of the scaled frames
     */
    unsigned int getWidth() const;

    /**
     * Getter for the height of the scaled frames
     * @return The height of the scaled frames
     */
    unsigned int getHeight() const;

    /**
     * Sets the height and rescales the frames from the original frames
     * (so there is no loss in quality when first scaling down and then up again)
     * @param height The new height
     * @emit positionsChanged
     */
    void setHeight(int height);

    /**
     * Getter for the ID of the Sprite
     * @return The ID of the Sprite
     */
    const std::string& getID() const;

    /**
     * Setter for the ID of the Sprite
     * @param id The new ID of the sprite
     * @emit idChanged
     */
    void setID(const std::string& id);

    /**
     * Getter for the Coordinates where the Sprite should be rendered
     * @return The Coordinates Array
     */
    const std::vector<QPoint>& getCoordinates() const;

    /**
     * Setter to overwrite the current Coordinates of the Sprite with new ones
     * @param coordinateVector The new coordinates of the sprite
     * @emit positionsChanged
     */
    void setCoordinates(const std::vector<QPoint>& coordinateVector);

    /**
     * Adds coordinates to the sprite
     * @param coordinates The coordinates that should be added to the sprite
     * @emit positionAdded
     */
    void addCoordinates(QPoint& coordinates);

    /**
     * Removes coordinates from the sprite
     * @param coordinates The coordinates that should be removed from the sprite
     * @emit positionRemoved
     */
    void removeCoordinates(QPoint& coordinates);

    /**
     * Getter for the Modifier Attributes
     * @return The Array of Modifier Attributes
     */
    const std::vector<std::string>& getModifierAttributes() const;

    /**
     * Overwrite the current modifier attributes with the new modifier attributes
     * @param modifierAttributes The new Modifier Attributes that should be used
     * @emit modifierChanged
     */
    void setModifierAttributes(const std::vector<std::string>& modifierAttributes);

    /**
     * Adds a modifier attribute to the sprite
     * @param modifierAttribute The attribute to add
     * @emit modifierChanged
     */
    void addModifierAttribute(const std::string& modifierAttribute);

    /**
     * Removes a modifier attribute from the sprite
     * @param modifierAttribute The attribute to remove
     * @emit modifierChanged
     */
    void removeModifierAttribute(const std::string& modifierAttribute);

private:
    /// The unscaled frames (only used internally)
    std::vector<QPixmap> m_frames;

    /// The frames that are scaled (derived from m_frames)
    std::vector<QPixmap> m_scaledFrames;

    /// The ID of the Sprite
    std::string m_id;

    /// The List of coordinates where the Sprite should appear
    std::vector<QPoint> m_coordinates;

    /// The List of String Modifier Attributes this Sprite has
    std::vector<std::string> m_modifierAttributes;

signals:
    /// Emitted if the ID of this sprite changes
    void idChanged(const Sprite* sprite);

    /// Emitted if the String Modifiers of this sprite change
    void modifierChanged(const Sprite* sprite);

    /// Emitted if more than one coordinate is changed
    void positionsChanged(const Sprite* sprite);

    /// Emitted if one coordinate is added to the sprite
    void positionAdded(Sprite* sprite, const QPoint&);

    /// Emitted if one coordinate is removed from the sprite
    void positionRemoved(Sprite* sprite, const QPoint&);
};


#endif  // LEVEL_EDITOR_SPRITE_HPP
