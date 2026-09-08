#include "LevelResize.hpp"
#include "../../UI/View/ChangeLevelSizeUI.hpp"
#include <QDialog>
#include <QMessageBox>

void Dialog::resizeLevel(LevelManager& levelManager, QWidget* parent)
{
    if (levelManager.getSelectedLevel() == nullptr)
    {
        return;
    }

    Level* level = levelManager.getSelectedLevel();

    QDialog dialog(parent);
    dialog.setModal(true);

    Ui_Dialog uiDialog;

    uiDialog.setupUi(&dialog);
    uiDialog.widthInput->setValue(level->getLevelWidth());
    uiDialog.heightInput->setValue(level->getLevelHeight());

    dialog.show();

    if (dialog.exec() == 0)
    {
        return;
    }

    int newWidth = uiDialog.widthInput->value();
    int newHeight = uiDialog.heightInput->value();

    if (newWidth < (int) level->getLevelWidth() || newHeight < (int) level->getLevelHeight())
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(&dialog, "Change Level Size", "The new level is smaller than the current one, so some tiles in the tile map could may be removed. Continue?",
                                      QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::No)
        {
            return;
        }
    }

    level->setWidth(newWidth);
    level->setHeight(newHeight);
}