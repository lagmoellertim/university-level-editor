#include "TileSetImportDialog.hpp"
#include <QBitmap>

TileSetImportDialog::TileSetImportDialog(QPixmap& pixmap, QWidget* parent)
    : ResourceImportDialog(pixmap, parent)
{
    m_ui.dialogSpecificLabel->setText("Tile-Size");
    setWindowTitle("Import TileSet");
    m_scalePreview = true;
    renderPreview();
}

QPoint TileSetImportDialog::getItemSize() const
{
    int tileSize = m_ui.dialogSpecificInput->value();
    return {tileSize, tileSize};
}
