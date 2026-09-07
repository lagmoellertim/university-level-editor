/**
 * @file ResourceImportDialog.hpp
 * @author Leveleditor-Gruppe
 * @brief
 * @version 0.1
 * @date 2022-02-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef LEVEL_EDITOR_DIALOG_H
#define LEVEL_EDITOR_DIALOG_H


#include "../View/ResourceImportUI.hpp"
#include <QDialog>


/**
 * @brief Base class for Resource Import Dialogs
 *
 */
class ResourceImportDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Construct a new Resource Import Dialog object
     *
     * @param pixmap The pixmap containing multiple Items to start the slicing process with
     * @param parent A pointer to the parent widget or nullptr
     */
    ResourceImportDialog(QPixmap& pixmap, QWidget* parent = nullptr);

    /**
     * @brief Destroy the Resource Import Dialog object
     *
     */
    ~ResourceImportDialog() = default;

    /**
     * @brief Generates a vector of pixmaps containing the sliced items if everything was successful
     *
     * @return std::vector<QPixmap>* Pointer to a vector of pixmaps on success, else nullptr
     */
    std::vector<QPixmap>* generatePixmapVector();

protected:
    /**
     * Getter
     * @return Returns the padding entered in the UI
     */
    int getPadding() const;

    /**
     * This is overwritten, indicates the size of a single Item inside the pixmap
     * @return QPoint, with x being width and y being height
     */
    virtual QPoint getItemSize() const = 0;

    /**
     * Renders the preview of the item based on the entered values in the ui
     */
    void renderPreview();

    /// Dialog ui
    Ui_ResourceImportDialog m_ui{};

    /// The pixmap that will be returned
    QPixmap m_pixmap;

    /// Scale Preview active
    bool m_scalePreview = true;

private:
    /// Color from color picker
    QColor m_color;

    /**
     * Getter
     * @return Returns whether or not transparency mapping (replacement of a color for transparency) is enabled or not
     */
    bool isTransparencyMappingEnabled() const;

    /**
     * Checks whether is empty (only consists of transparent pixels)
     * @param image The image to check
     * @return True if empty, false otherwise
     */
    static bool isImageEmpty(const QImage& image);

public slots:
    /**
     * @brief Opens up the color picker, writes the resulting color into m_color
     *
     */
    void onColorPickerRequested();

    /**
     * @brief Updates the Button background color and active state
     *
     */
    void onButtonUpdate();

    /**
     * @brief Render Preview
     *
     */
    void onElementClicked();

    /**
     * @brief Render Preview
     *
     */
    void onTransparencyColorUpdated();

    /**
     * @brief Render Preview
     *
     * @param value
     */
    void onValueChanged(int value);

signals:
    /// After a color is selected, this event is fired to notify the others on the color change
    void transparencyColorUpdated();
};


#endif  // LEVEL_EDITOR_DIALOG_H
