#include "SoundEditDialog.hpp"
#include "../../Lib/AssetImport/AssetImport.hpp"
#include "ImportSoundDialog.hpp"
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
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
    connect(soundList, &QListWidget::currentItemChanged, this, [this](QListWidgetItem* current, QListWidgetItem*) {
        onSoundSelected(current);
    });
    connect(soundList, &QListWidget::itemChanged, this, &SoundEditDialog::onItemChanged);

    m_mediaPlayer = new QMediaPlayer(this);
    m_audioOutput = new QAudioOutput(this);
    m_mediaPlayer->setAudioOutput(m_audioOutput);
    m_audioOutput->setVolume(1.0f);

    connect(m_mediaPlayer, &QMediaPlayer::playbackStateChanged, this, [this](QMediaPlayer::PlaybackState state) {
        if (state == QMediaPlayer::PlayingState) {
            m_UI.playButton->setText("Pause");
        } else {
            m_UI.playButton->setText("Play");
        }
    });

    m_sounds = std::vector(levelManager.getSounds());

    for (Sound* sound : m_sounds)
    {
        auto* item = new QListWidgetItem(QString::fromStdString(sound->getID()));
        item->setFlags(item->flags() | Qt::ItemIsEditable);
        soundList->addItem(item);
    }

    if (soundList->count() > 0)
    {
        soundList->setCurrentRow(0);
        onSoundSelected(soundList->item(0));
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
#ifdef __EMSCRIPTEN__
    QFileDialog::getOpenFileContent(tr("WAV (*.wav)"),
        [this](const QString &fileName, const QByteArray &fileContent) {
            if (fileName.isEmpty() || fileContent.isEmpty() || !fileName.endsWith(".wav", Qt::CaseInsensitive)) {
                return;
            }
            std::vector<std::string> soundList;
            for (int i = 0; i < m_UI.soundListView->count(); ++i)
            {
                soundList.push_back(m_UI.soundListView->item(i)->text().toStdString());
            }

            auto* dialog = new ImportSoundDialog(soundList, this);
            dialog->setAttribute(Qt::WA_DeleteOnClose);
            QString baseName = QFileInfo(fileName).completeBaseName();
            if (!baseName.isEmpty()) {
                dialog->setSuggestedID(baseName);
            }

            connect(dialog, &QDialog::accepted, this, [this, dialog, fileContent]() {
                Sound* sound = new Sound(dialog->getID(), fileContent);
                m_sounds.push_back(sound);
                auto* item = new QListWidgetItem(QString::fromStdString(sound->getID()));
                item->setFlags(item->flags() | Qt::ItemIsEditable);
                m_UI.soundListView->addItem(item);
                m_UI.soundListView->setCurrentItem(item);
                onSoundSelected(item);
            });
            dialog->open();
        });
#else
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
        auto* item = new QListWidgetItem(QString::fromStdString(sound->getID()));
        item->setFlags(item->flags() | Qt::ItemIsEditable);
        m_UI.soundListView->addItem(item);
        m_UI.soundListView->setCurrentItem(item);
        onSoundSelected(item);
    }
#endif
}

void SoundEditDialog::onTogglePlay()
{
    if (!m_currentSound && m_UI.soundListView->count() > 0)
    {
        m_UI.soundListView->setCurrentRow(0);
        onSoundSelected(m_UI.soundListView->item(0));
    }

    if (!m_currentSound)
    {
        return;
    }

    if (m_mediaPlayer->playbackState() == QMediaPlayer::PlayingState)
    {
        m_mediaPlayer->pause();
    }
    else
    {
        if (m_mediaPlayer->mediaStatus() == QMediaPlayer::EndOfMedia)
        {
            m_mediaPlayer->setPosition(0);
        }
        m_mediaPlayer->play();
    }
}

void SoundEditDialog::onSoundSelected(QListWidgetItem* item)
{
    m_mediaPlayer->stop();
    m_mediaPlayer->setSource(QUrl());
    if (m_tempAudioFile)
    {
        delete m_tempAudioFile;
        m_tempAudioFile = nullptr;
    }

    if (item != nullptr)
    {
        m_currentSound = getSoundByID(item->text().toStdString());

        if (m_currentSound != nullptr && !m_currentSound->getRawSoundData().isEmpty())
        {
            const QByteArray& rawData = m_currentSound->getRawSoundData();
            QString ext = "wav";
            if (rawData.startsWith("RIFF"))
                ext = "wav";
            else if (rawData.startsWith("OggS"))
                ext = "ogg";
            else if (rawData.startsWith("ID3") || (rawData.size() >= 2 && (unsigned char)rawData[0] == 0xFF && ((unsigned char)rawData[1] & 0xE0) == 0xE0))
                ext = "mp3";
            else if (rawData.startsWith("fLaC"))
                ext = "flac";

            m_tempAudioFile = new QTemporaryFile(QDir::tempPath() + "/preview_XXXXXX." + ext, this);
            if (m_tempAudioFile->open())
            {
                m_tempAudioFile->write(rawData);
                m_tempAudioFile->flush();
                m_tempAudioFile->close();
                m_mediaPlayer->setSource(QUrl::fromLocalFile(m_tempAudioFile->fileName()));
            }
        }
    }
    else
    {
        m_currentSound = nullptr;
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
    m_mediaPlayer->stop();
    m_mediaPlayer->setSource(QUrl());
    delete m_tempAudioFile;
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
