#include "SpriteEditDialog.hpp"
#include <QMenu>


SpriteEditDialog::SpriteEditDialog(Sprite* sprite, Level* level, QWidget* parent)
    : QDialog(parent), m_level(level), m_oldID(sprite->getID())
{
    m_UI.setupUi(this);
    m_UI.buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    setWindowTitle("Edit Sprite");

    connect(m_UI.idInput, &QLineEdit::textChanged, this, &SpriteEditDialog::onTextChanged);
    connect(m_UI.addModifierButton, &QPushButton::released, this, &SpriteEditDialog::onAddModifier);

    // Enable Right-click and DragDrop
    QListWidget* modifierList = m_UI.modifierListView;
    modifierList->setContextMenuPolicy(Qt::CustomContextMenu);
    modifierList->setDragDropMode(QAbstractItemView::DragDrop);
    modifierList->setDefaultDropAction(Qt::MoveAction);

    connect(modifierList, &SpriteEditDialog::customContextMenuRequested, this, &SpriteEditDialog::onItemRightClick);

    // Fill list with current modifiers
    for (std::string modifier : sprite->getModifierAttributes())
    {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(modifier));
        item->setFlags(item->flags() | Qt::ItemIsEditable);
        modifierList->addItem(item);
    }

    m_UI.heightInput->setValue(sprite->getHeight());
    m_UI.idInput->setText(QString::fromStdString(sprite->getID()));
    m_UI.isActorBox->setChecked(sprite == level->getActorSprite());
}

std::vector<std::string> SpriteEditDialog::getModifiers() const
{
    QListWidget* modifierList = m_UI.modifierListView;
    std::vector<std::string> modifiers;

    for (int i = 0; i < modifierList->count(); ++i)
    {
        modifiers.push_back(modifierList->item(i)->text().toStdString());
    }

    return modifiers;
}

int SpriteEditDialog::getHeight() const
{
    return m_UI.heightInput->value();
}

std::string SpriteEditDialog::getID() const
{
    return m_UI.idInput->text().toStdString();
}

bool SpriteEditDialog::isActor() const
{
    return m_UI.isActorBox->isChecked();
}

void SpriteEditDialog::onTextChanged(const QString& text)
{
    QPushButton* okButton = m_UI.buttonBox->button(QDialogButtonBox::Ok);
    std::string stdText = text.toStdString();

    if (text.isEmpty() || ((stdText != m_oldID) && m_level->getSpriteByID(stdText)))
    {
        okButton->setEnabled(false);
    }
    else
    {
        okButton->setEnabled(true);
    }
}

void SpriteEditDialog::onItemRightClick(const QPoint& pos)
{
    QListWidget* modifiers = m_UI.modifierListView;
    QPoint item = modifiers->mapToGlobal(pos);

    // Obtain Level item and position
    int row = modifiers->indexAt(pos).row();

    if (row < 0)
    {
        return;
    }

    QListWidgetItem* listItem = modifiers->itemAt(pos);

    // Open context menu
    QMenu submenu;
    submenu.addAction("Rename");
    submenu.addAction("Delete");

    QAction* rightClickItem = submenu.exec(item);
    if (rightClickItem)
    {
        if (rightClickItem->text().contains("Delete"))
        {
            modifiers->takeItem(row);
        }
        else if (rightClickItem->text().contains("Rename"))
        {
            modifiers->editItem(listItem);
        }
    }
}

void SpriteEditDialog::onAddModifier()
{
    QListWidgetItem* item = new QListWidgetItem(m_UI.modifierInput->text());
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    m_UI.modifierListView->addItem(item);
    m_UI.modifierInput->clear();
}