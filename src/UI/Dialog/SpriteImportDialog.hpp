/**
 * @file SpriteImportDialog.hpp
 * @author Leveleditor-Gruppe
 * @brief
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */


#ifndef LEVEL_EDITOR_SPRITEIMPORTDIALOG_HPP
#define LEVEL_EDITOR_SPRITEIMPORTDIALOG_HPP

#include "../../Lib/LevelManager/Level.hpp"
#include "ResourceImportDialog.hpp"

/**
 * @brief Dialog for importing Sprites
 *
 */
class SpriteImportDialog : public ResourceImportDialog
{
    Q_OBJECT

private:
    /// Sprite id input
    QLineEdit* m_idInput = nullptr;

    /// Current Level
    Level* m_level;

protected:
    /**
     * @brief Return Sprite Size
     *
     * @return QPoint Sprite Size (Size, Size)
     */
    QPoint getItemSize() const override;

public:
    /**
     * @brief Construct a new Sprite Import Dialog object
     *
     * @param pixmap Pixmap used to save the SpriteSet
     * @param level Current Level
     * @param parent
     */
    SpriteImportDialog(QPixmap& pixmap, Level* level, QWidget* parent = nullptr);

    /**
     * @brief Get entered Sprite ID
     *
     * @return std::string Sprite ID
     */
    std::string getSpriteID();

public slots:
    /**
     * @brief Connected to Sprite ID Input, used to check unique / not empty id
     *
     */
    void onTextChanged(const QString& text);
};

#endif  // LEVEL_EDITOR_SPRITEIMPORTDIALOG_HPP
