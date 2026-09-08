#include "AssetImport.hpp"
#include "../../UI/Dialog/BackgroundImportDialog.hpp"
#include "../../UI/Dialog/ImportSoundDialog.hpp"
#include "../../UI/Dialog/SpriteImportDialog.hpp"
#include "../../UI/Dialog/TileSetImportDialog.hpp"
#include <QFileDialog>
#include <QMessageBox>

std::vector<QPixmap>* AssetImport::importTileSet(QWidget* parent)
{
    QString filename = Utils::getFilename("Open Tile Set", parent, "PNG (*.png);;");

    if (filename == "")
    {
        return nullptr;
    }

    QPixmap pixmap(filename);

    if (pixmap.isNull())
    {
        std::string message("An Error occured while opening/reading the file");
        QMessageBox::critical(parent, "File Error", QString::fromStdString(message));
        return nullptr;
    }

    TileSetImportDialog dialog(pixmap);

    dialog.show();

    if (dialog.exec() == 0)
    {
        return nullptr;
    }

    return dialog.generatePixmapVector();
}

Sprite* AssetImport::importSprite(Level* level, QWidget* parent)
{
    QString filename = Utils::getFilename("Open Sprite Frames", parent, "PNG (*.png);;");

    if (filename == "")
    {
        return nullptr;
    }

    QPixmap pixmap(filename);

    if (pixmap.isNull())
    {
        std::string message("An Error occured while opening/reading the file");
        QMessageBox::critical(parent, "File Error", QString::fromStdString(message));
        return nullptr;
    }

    SpriteImportDialog dialog(pixmap, level);

    dialog.show();

    if (dialog.exec() == 0)
    {
        return nullptr;
    }

    std::vector<QPixmap>* result = dialog.generatePixmapVector();

    if (result == nullptr)
    {
        delete result;
        return nullptr;
    }

    if (result->empty())
    {
        delete result;
        return nullptr;
    }

    auto* sprite = new Sprite(*result);
    sprite->setID(dialog.getSpriteID());

    delete result;
    return sprite;
}

Sound* AssetImport::importSound(std::vector<std::string> soundList, QWidget* parent)
{
    QString filename = Utils::getFilename("Open Sound File", parent, "WAV (*.wav);;");

    if (filename == "")
    {
        return nullptr;
    }

    ImportSoundDialog dialog(soundList, parent);

    dialog.show();
    dialog.setModal(true);

    if (dialog.exec() == 0)
    {
        return nullptr;
    }

    try
    {
        Sound* sound = Sound::fromFile(dialog.getID(), filename.toStdString());
        return sound;
    }
    catch (std::runtime_error& e)
    {
        std::string message("An Error occured while opening/reading the file");
        QMessageBox::critical(parent, "File Error", QString::fromStdString(message));
        return nullptr;
    }
}

Background* AssetImport::importBackground(Level* level, QWidget* parent)
{
    QString filename = Utils::getFilename("Open Background", parent, "PNG (*.png);;");

    if (filename == "")
    {
        return nullptr;
    }

    BackgroundImportDialog dialog(level, parent);

    dialog.show();
    dialog.setModal(true);

    if (dialog.exec() == 0)
    {
        return nullptr;
    }

    try
    {
        QPixmap pixmap(filename);

        Background* background = new Background(pixmap, dialog.getID());
        background->setDepth(dialog.getParallaxInput());
        background->setSpeed(dialog.getSpeedInput());

        return background;
    }
    catch (std::runtime_error& e)
    {
        std::string message("An Error occured while opening/reading the file");
        QMessageBox::critical(parent, "File Error", QString::fromStdString(message));
        return nullptr;
    }
}


QString AssetImport::Utils::getFilename(QString openName, QWidget* parent, const std::string& allowedExtensions)
{
    return QFileDialog::getOpenFileName(parent,
                                        QDialog::tr(openName.toStdString().c_str()), "",
                                        QDialog::tr(allowedExtensions.c_str()));
}
