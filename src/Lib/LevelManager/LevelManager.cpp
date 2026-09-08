#include "LevelManager.hpp"
#include "../HDF5/Handler.hpp"
#include <QBuffer>
#include <QMediaPlayer>

Level* LevelManager::getSelectedLevel() const
{
    return m_selectedLevel;
}

void LevelManager::setSelectedLevelByID(int id)
{
    throwErrorOnInvalidID(id);

    m_selectedLevel = m_levels[id];
    emit levelSelectionChanged();
}

int LevelManager::getSelectedLevelID()
{
    if (getSelectedLevel() == nullptr)
    {
        return -1;
    }

    auto it = find(m_levels.begin(), m_levels.end(), getSelectedLevel());

    if (it != m_levels.end())
    {
        return it - m_levels.begin();
    }

    return -1;
}

void LevelManager::addLevel(Level* level)
{
    if (level == nullptr)
    {
        throw std::runtime_error("Level is a nullptr!");
    }

    connect(level, &Level::levelMetadataChanged, this, &LevelManager::onLevelMetadataChanged);
    connect(level, &Level::levelItemSetChanged, this, &LevelManager::onLevelItemSetChanged);
    connect(level, &Level::levelCanvasChanged, this, &LevelManager::onLevelCanvasChanged);
    connect(level, &Level::levelCanvasTileChanged, this, &LevelManager::onLevelCanvasTileChanged);
    connect(level, &Level::levelItemMetadataChanged, this, &LevelManager::onLevelItemMetadataChanged);
    connect(level, &Level::levelCanvasSpritePlaced, this, &LevelManager::onLevelCanvasSpritePlaced);
    connect(level, &Level::levelCanvasSpriteErased, this, &LevelManager::onLevelCanvasSpriteErased);
    connect(level, &Level::levelBackgroundChanged, this, &LevelManager::onLevelBackgroundChanged);

    m_levels.push_back(level);

    auto* context = new EditingContext;
    context->setVisibleBackgrounds(level->getBackgrounds());

    connect(context, &EditingContext::contextLayerSelectionChanged, this, &LevelManager::onContextLayerSelectionChanged);
    connect(context, &EditingContext::contextItemSelectionChanged, this, &LevelManager::onContextItemSelectionChanged);
    connect(context, &EditingContext::contextLayerVisibilityChanged, this, &LevelManager::onContextLayerVisibilityChanged);

    m_contexts.insert(std::pair<Level*, EditingContext*>(level, context));

    emit levelListChanged();
}
void LevelManager::moveLevel(int fromID, int toID)
{
    throwErrorOnInvalidID(fromID);
    throwErrorOnInvalidID(toID);

    Level* level = m_levels[fromID];

    m_levels.erase(m_levels.begin() + fromID);
    m_levels.insert(m_levels.begin() + toID, level);

    emit levelListChanged();
}

void LevelManager::removeLevelByID(int id)
{
    throwErrorOnInvalidID(id);

    Level* level = m_levels[id];
    m_levels.erase(m_levels.begin() + id);

    EditingContext* context = m_contexts[level];
    m_contexts.erase(level);

    if (level == m_selectedLevel)
    {
        m_selectedLevel = nullptr;
        emit levelSelectionChanged();
    }

    emit levelListChanged();

    delete context;
    delete level;
}

EditingContext* LevelManager::getSelectedContext() const
{
    if (m_selectedLevel == nullptr)
    {
        return nullptr;
    }

    return m_contexts.at(m_selectedLevel);
}

const std::vector<Level*>& LevelManager::getLevels() const
{
    return m_levels;
}

void LevelManager::clear()
{
    int levelSize = m_levels.size();
    for (int i = 0; i < levelSize; ++i)
    {
        // Since the IDs are just the order, It's valid to remove the first (0) item m_level.size() times
        removeLevelByID(0);
    }

    for (auto& sound : m_sounds)
    {
        delete sound;
    }

    m_sounds.clear();
}

void LevelManager::throwErrorOnInvalidID(int id)
{
    if (id < 0 || id >= (int) m_levels.size())
    {
        throw std::runtime_error("Invalid ID given!");
    }
}

void LevelManager::onLevelItemSetChanged(Level* eventProducer)
{
    if (eventProducer == m_selectedLevel)
    {
        emit selectedLevelItemSetChanged();
    }
}

void LevelManager::onLevelItemMetadataChanged(Level* eventProducer)
{
    if (eventProducer == m_selectedLevel)
    {
        emit selectedLevelItemMetadataChanged();
    }
}

void LevelManager::onLevelCanvasChanged(Level* eventProducer)
{
    if (eventProducer == m_selectedLevel)
    {
        emit selectedLevelCanvasChanged();
    }
}

void LevelManager::onLevelCanvasTileChanged(Level* eventProducer, int tileID, const QPoint& position)
{
    if (eventProducer == m_selectedLevel)
    {
        emit selectedLevelCanvasTileChanged(tileID, position);
    }
}

void LevelManager::onLevelCanvasSpritePlaced(Level* eventProducer, Sprite* sprite, const QPoint& position)
{
    if (eventProducer == m_selectedLevel)
    {
        emit selectedLevelCanvasSpritePlaced(sprite, position);
    }
}

void LevelManager::onLevelCanvasSpriteErased(Level* eventProducer, Sprite* sprite, const QPoint& position)
{
    if (eventProducer == m_selectedLevel)
    {
        emit selectedLevelCanvasSpriteErased(sprite, position);
    }
}

void LevelManager::onLevelMetadataChanged(Level* eventProducer)
{
    if (eventProducer == m_selectedLevel)
    {
        emit selectedLevelMetadataChanged();
    }
}

void LevelManager::onLevelBackgroundChanged(Level* eventProducer)
{
    if (eventProducer == m_selectedLevel)
    {
        emit selectedLevelBackgroundChanged();
    }
}

void LevelManager::onContextLayerSelectionChanged(EditingContext* eventProducer)
{
    if (m_contexts[m_selectedLevel] == eventProducer)
    {
        emit selectedLevelLayerSelectionChanged();
    }
}

void LevelManager::onContextItemSelectionChanged(EditingContext* eventProducer)
{
    if (m_contexts[m_selectedLevel] == eventProducer)
    {
        emit selectedLevelContextItemChanged();
    }
}

void LevelManager::onContextLayerVisibilityChanged(EditingContext* eventProducer)
{
    if (m_contexts[m_selectedLevel] == eventProducer)
    {
        emit selectedLevelContextLayerVisibiltyChanged();
    }
}

LevelManager::~LevelManager()
{
    clear();

    m_levels.clear();
    m_contexts.clear();
    m_sounds.clear();
}

void LevelManager::save(const std::string& filename) const
{
    HDF5::exportHDF5(filename, this);
}

void LevelManager::load(const std::string& filename)
{
    clear();
    HDF5::importHDF5(filename, this, true);
}

const std::vector<Sound*>& LevelManager::getSounds() const
{
    return m_sounds;
}

void LevelManager::setSounds(const std::vector<Sound*>& sounds)
{
    m_sounds = sounds;
}

void LevelManager::addSound(Sound* sound)
{
    m_sounds.push_back(sound);
}

Sound* LevelManager::getSoundByID(const std::string& id) const
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

void LevelManager::loadExtend(const std::string& filename)
{
    HDF5::importHDF5(filename, this, false);
}
