#include "NewLevel.hpp"
#include "../../UI/Dialog/CreateLevelDialog.hpp"

void Dialog::newLevel(LevelManager& levelManager)
{
    CreateLevelDialog dialog;
    dialog.setModal(true);

    dialog.show();

    // Create Level if a name has been entered
    if (dialog.exec())
    {
        Level* level = new Level(dialog.tileSize(), dialog.levelWidth(), dialog.levelHeight());
        level->setLevelName(dialog.levelName().toStdString());

        // Add new Level to LevelManager and set it as selected Level
        levelManager.addLevel(level);
        levelManager.setSelectedLevelByID(levelManager.getLevels().size() - 1);
    }
}