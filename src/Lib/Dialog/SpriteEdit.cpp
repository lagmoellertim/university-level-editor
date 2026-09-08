#include "SpriteEdit.hpp"
#include "../../UI/Dialog/SpriteEditDialog.hpp"

void Dialog::editSprite(LevelManager& levelManager, GraphicsSpriteItem* selectedSprite)
{
    EditingContext* context = levelManager.getSelectedContext();
    Level* level = levelManager.getSelectedLevel();

    if (context)
    {
        Sprite* sprite = selectedSprite->getSprite();

        SpriteEditDialog dialog(sprite, level);
        dialog.setModal(true);
        dialog.show();

        if (dialog.exec())
        {
            std::string newID = dialog.getID();

            sprite->setModifierAttributes(dialog.getModifiers());
            sprite->setID(newID);
            sprite->setHeight(dialog.getHeight());

            if (dialog.isActor())
            {
                level->setActorSprite(sprite);
            }
        }
    }
}