#include "SoundEditDialog.hpp"
#include "../../Lib/AssetImport/AssetImport.hpp"
#include <QMenu>


SoundEditDialog::SoundEditDialog(LevelManager& levelManager, QWidget* parent)
    : QDialog(parent), m_levelManager(levelManager)
{
    m_UI.setupUi(this);
    setWindowTitle("Edit Sounds");

    connect(m_UI.addSoundButton, &QPushButton::released, this, &SoundEditDialog::onAddSound);
    connect(m_UI.playButton, &QPushButton::released, this, &SoundEditDialog::onTogglePlay);

    // Enable Right-click and DragDrop
    QListWidget* soundList = m_UI.soundListView;
    soundList->setContextMenuPolicy(Qt::CustomContextMenu);
    soundList->setDragDropMode(QAbstractItemView::DragDrop);
    soundList->setDefaultDropAction(Qt::MoveAction);

    connect(soundList, &SoundEditDialog::customContextMenuRequested, this, &SoundEditDialog::onItemRightClick);
    connect(soundList, &QListWidget::itemPressed, this, &SoundEditDialog::onSoundSelected);
    connect(soundList, &QListWidget::itemChanged, this, &SoundEditDialog::onItemChanged);

    m_mediaPlayer = new QMediaPlayer();
    m_sounds = std::vector(levelManager.getSounds());

    for (Sound* sound : m_sounds)
    {
        auto* item = new QListWidgetItem(QString::fromStdString(sound->getID()));
        item->setFlags(item->flags() | Qt::ItemIsEditable);
        soundList->addItem(item);
    }
}

void SoundEditDialog::onItemRightClick(const QPoint& pos)
{
    QListWidget* sounds = m_UI.soundListView;
    QPoint item = sounds->mapToGlobal(pos);

    // Obtain Level item and position
    int row = sounds->indexAt(pos).row();

    if (row < 0)
    {
        return;
    }

    QListWidgetItem* listItem = sounds->itemAt(pos);

    onSoundSelected(listItem);

    // Open context menu
    QMenu submenu;
    submenu.addAction("Rename");
    submenu.addAction("Delete");

    QAction* rightClickItem = submenu.exec(item);
    if (rightClickItem)
    {
        if (rightClickItem->text().contains("Delete"))
        {
            if (getSoundByID(listItem->text().toStdString()) == m_currentSound)
            {
                onSoundSelected(nullptr);
            }

            int soundSize = m_sounds.size();
            for (int i = 0; i < soundSize; ++i)
            {
                if (m_sounds[i] == getSoundByID(listItem->text().toStdString()))
                {
                    m_sounds.erase(m_sounds.begin() + i);
                    break;
                }
            }

            delete getSoundByID(listItem->text().toStdString());
            delete sounds->takeItem(row);
        }
        else if (rightClickItem->text().contains("Rename"))
        {
            sounds->editItem(listItem);
        }
    }
}

void SoundEditDialog::onAddSound()
{
    // Create List of all entries to parse in importSound Function
    std::vector<std::string> soundList;
    for (int i = 0; i < m_UI.soundListView->count(); ++i)
    {
        soundList.push_back(m_UI.soundListView->item(i)->text().toStdString());
    }

    Sound* sound = AssetImport::importSound(soundList, this);

    if (sound)
    {
        m_sounds.push_back(sound);
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(sound->getID()));
        item->setFlags(item->flags() | Qt::ItemIsEditable);
        m_UI.soundListView->addItem(item);
    }
}

void SoundEditDialog::onTogglePlay()
{
    if (m_mediaPlayer->state() == QMediaPlayer::State::PlayingState)
    {
        m_mediaPlayer->pause();
    }
    else
    {
        m_mediaPlayer->play();
    }
}

void SoundEditDialog::onSoundSelected(QListWidgetItem* item)
{
    if (item != nullptr)
    {
        m_currentSound = getSoundByID(item->text().toStdString());

        if (m_currentSound != nullptr)
        {
            m_audioBuffer = new QBuffer(m_mediaPlayer);
            m_audioBuffer->setData(m_currentSound->getRawSoundData());
            m_audioBuffer->open(QIODevice::ReadOnly);

            m_mediaPlayer->setMedia(QMediaContent(), m_audioBuffer);
        }
    }
    else
    {
        m_currentSound = nullptr;
        m_mediaPlayer->setMedia(QMediaContent());
    }
}

void SoundEditDialog::onItemChanged(QListWidgetItem* item)
{
    // Rename changed LevelItem
    if (m_currentSound)
    {
        std::string newText = item->text().toStdString();

        // Do not allow empty level name
        if (newText.length() > 0)
        {
            for (auto& sound : m_sounds)
            {
                if (sound != m_currentSound)
                {
                    if (item->text().toStdString() == sound->getID())
                    {
                        item->setText(QString::fromStdString(m_currentSound->getID()));
                        return;
                    }
                }
            }

            m_currentSound->setID(newText);
        }
        else
        {
            item->setText(QString::fromStdString(m_currentSound->getID()));
        }
    }
}

SoundEditDialog::~SoundEditDialog()
{
    delete m_mediaPlayer;
}

Sound* SoundEditDialog::getSoundByID(const std::string& id)
{
    for (int i = 0; i < (int) m_sounds.size(); ++i)
    {
        if (m_sounds[i]->getID() == id)
        {
            return m_sounds[i];
        }
    }

    return nullptr;
}
std::vector<Sound*> SoundEditDialog::getSounds() const
{
    return m_sounds;
}
