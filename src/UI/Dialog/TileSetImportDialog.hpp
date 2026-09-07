/**
 * @file TileSetImportDialog.hpp
 * @author Leveleditor-Gruppe
 * @brief
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef LEVEL_EDITOR_TILESETIMPORTDIALOG_HPP
#define LEVEL_EDITOR_TILESETIMPORTDIALOG_HPP

#include "ResourceImportDialog.hpp"

/**
 * @brief Dialog for importing a new TilSet
 *
 */
class TileSetImportDialog : public ResourceImportDialog
{
    Q_OBJECT

protected:
    /**
     * @brief Get the Tile Size
     *
     * @return QPoint (Size, Size)
     */
    QPoint getItemSize() const override;

public:
    /**
     * @brief Construct a new Tile Set Import Dialog object
     *
     * @param pixmap Pixmap used to save the TileSet
     * @param parent
     */
    TileSetImportDialog(QPixmap& pixmap, QWidget* parent = nullptr);
};


#endif  // LEVEL_EDITOR_TILESETIMPORTDIALOG_HPP
