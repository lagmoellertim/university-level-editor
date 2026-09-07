#include "Level.hpp"


Level::Level(unsigned int tileSize, unsigned int levelWidth, unsigned int levelHeight)
    : QObject()
{
    m_tileSize = tileSize;
    m_levelWidth = levelWidth;
    m_levelHeight = levelHeight;

    for (int i = 0; i < (int) m_levelWidth; ++i)
    {
        std::vector<int> column(m_levelHeight);
        std::fill(column.begin(), column.end(), -1);
        m_tileMap.push_back(column);
    }
}

Level::~Level()
{
    for (auto& sprite : m_sprites)
    {
        delete sprite;
    }

    m_sprites.clear();
}

const std::string& Level::getLevelName() const
{
    return m_levelName;
}

unsigned int Level::getTileSize() const
{
    return m_tileSize;
}

unsigned int Level::getLevelWidth() const
{
    return m_levelWidth;
}

unsigned int Level::getLevelHeight() const
{
    return m_levelHeight;
}

const std::vector<QPixmap>& Level::getTileSet() const
{
    return m_tileSet;
}

const std::vector<std::vector<int>>& Level::getTileMap() const
{
    return m_tileMap;
}

void Level::setLevelName(const std::string& levelName)
{
    m_levelName = levelName;

    emit levelMetadataChanged(this);
}
void Level::setTileSet(const std::vector<QPixmap>& tileSet)
{
    m_tileSet = tileSet;

    emit levelItemSetChanged(this);
}

void Level::clearTileSet()
{
    clearTileMap();
    std::vector<QPixmap> emptySet;
    setTileSet(emptySet);
}

void Level::clearTileMap()
{
    std::vector<std::vector<int>> emptyMap;
    for (int i = 0; i < (int) m_levelWidth; ++i)
    {
        std::vector<int> column(m_levelHeight);
        std::fill(column.begin(), column.end(), -1);
        emptyMap.push_back(column);
    }

    setTileMap(emptyMap);
}

void Level::clearSpriteSet()
{
    std::vector<Sprite*> emptySprites;
    setSprites(emptySprites);
    m_actorSprite = nullptr;
}

void Level::clearSprites()
{
    std::vector<QPoint> emptyCoordinates;
    for (Sprite* sprite : m_sprites)
    {
        sprite->setCoordinates(emptyCoordinates);
    }
}

void Level::setTileMap(const std::vector<std::vector<int>>& tileMap)
{
    m_tileMap = tileMap;

    emit levelCanvasChanged(this);
}

void Level::setWidth(unsigned int width)
{
    if (width == 0)
    {
        throw std::runtime_error("width can not be 0!");
    }

    m_tileMap.resize(width);

    if (width > m_levelWidth)
    {
        for (int i = (int) m_levelWidth; i < (int) width; ++i)
        {
            m_tileMap[i].resize(m_levelHeight);
            std::fill(m_tileMap[i].begin(), m_tileMap[i].end(), -1);
        }
    }

    m_levelWidth = width;

    emit levelCanvasChanged(this);
}

void Level::setHeight(unsigned int height)
{
    if (height == 0)
    {
        throw std::runtime_error("height can not be 0!");
    }

    for (auto& column : m_tileMap)
    {
        column.resize(height);

        if (height > m_levelHeight)
        {
            for (int i = (int) m_levelHeight; i < (int) height; ++i)
            {
                column[i] = -1;
            }
        }
    }

    m_levelHeight = height;

    emit levelCanvasChanged(this);
}

void Level::setTileAt(int tileID, int x, int y)
{
    m_tileMap.at(x).at(y) = tileID;

    emit levelCanvasTileChanged(this, tileID, QPoint(x, y));
}

void Level::appendToTileSet(std::vector<QPixmap>& tileSet)
{
    for (auto& pixmap : tileSet)
    {
        m_tileSet.push_back(pixmap.scaled((int) m_tileSize, (int) m_tileSize));
    }

    emit levelItemSetChanged(this);
}

void Level::addSprite(Sprite* sprite)
{
    if (!sprite)
    {
        throw std::runtime_error("Nullptr given!");
    }

    connectSprite(sprite);

    m_sprites.push_back(sprite);

    emit levelCanvasChanged(this);
    emit levelItemSetChanged(this);
}

void Level::setSprites(std::vector<Sprite*>& sprites)
{
    m_sprites = sprites;

    for (auto& sprite : m_sprites)
    {
        if (!sprite)
        {
            throw std::runtime_error("Nullptr given!");
        }

        connectSprite(sprite);
    }

    emit levelCanvasChanged(this);
    emit levelItemSetChanged(this);
}

const std::vector<Sprite*>& Level::getSprites() const
{
    return m_sprites;
}

void Level::removeSprite(const Sprite* sprite)
{
    if (!sprite)
    {
        throw std::runtime_error("Nullptr given!");
    }

    auto it = find(m_sprites.begin(), m_sprites.end(), sprite);

    if (it != m_sprites.end())
    {
        int index = it - m_sprites.begin();
        m_sprites.erase(m_sprites.begin() + index);

        if (m_actorSprite == sprite)
        {
            m_actorSprite = nullptr;
        }

        delete sprite;
        emit levelItemSetChanged(this);
    }
    else
    {
        throw std::runtime_error("This sprite is not in this level");
    }
}

void Level::setBackgrounds(std::vector<Background*>& backgrounds)
{
    for (auto& background : backgrounds)
    {
        connect(background, &Background::depthChange, this, &Level::onLevelBackgroundDepthChanged);
    }

    m_backgrounds = backgrounds;

    emit levelBackgroundChanged(this);
}

const std::vector<Background*>& Level::getBackgrounds() const
{
    return m_backgrounds;
}

void Level::addBackground(Background* background)
{
    connect(background, &Background::depthChange, this, &Level::onLevelBackgroundDepthChanged);
    m_backgrounds.push_back(background);

    emit levelBackgroundChanged(this);
}

void Level::removeBackground(const Background* background)
{
    if (!background)
    {
        throw std::runtime_error("Nullptr given!");
    }

    auto it = find(m_backgrounds.begin(), m_backgrounds.end(), background);

    if (it != m_backgrounds.end())
    {
        int index = it - m_backgrounds.begin();
        m_backgrounds.erase(m_backgrounds.begin() + index);
        delete background;
    }
    else
    {
        throw std::runtime_error("This background is not in this level");
    }

    emit levelBackgroundChanged(this);
}

int Level::getEndPosition() const
{
    return m_endPosition;
}

void Level::setEndPosition(int endPosition)
{
    m_endPosition = endPosition;

    emit levelMetadataChanged(this);
}

const Sprite* Level::getActorSprite() const
{
    return m_actorSprite;
}

void Level::setActorSprite(Sprite* actorSprite)
{
    if (!actorSprite)
    {
        throw std::runtime_error("Actor Sprite is a nullptr!");
    }

    auto it = find(m_sprites.begin(), m_sprites.end(), actorSprite);

    if (it != m_sprites.end())
    {
        m_actorSprite = actorSprite;

        emit levelItemMetadataChanged(this);
    }
    else
    {
        throw std::runtime_error("The actor sprite is not in this level!");
    }
}

void Level::onLevelItemMetadataChanged(const Sprite* sprite)
{
    emit levelItemMetadataChanged(this);
}

void Level::onLevelCanvasSpritePositionsChanged(const Sprite* sprite)
{
    emit levelCanvasChanged(this);
    emit levelItemSetChanged(this);
}

void Level::onLevelCanvasSpritePlaced(Sprite* sprite, const QPoint& position)
{
    emit levelCanvasSpritePlaced(this, sprite, position);
}

void Level::onLevelCanvasSpriteErased(Sprite* sprite, const QPoint& position)
{
    emit levelCanvasSpriteErased(this, sprite, position);
}

void Level::onLevelBackgroundDepthChanged(const Background* background)
{
    emit levelBackgroundChanged(this);
}

void Level::connectSprite(Sprite* sprite) const
{
    connect(sprite, &Sprite::idChanged, this, &Level::onLevelItemMetadataChanged);
    connect(sprite, &Sprite::modifierChanged, this, &Level::onLevelItemMetadataChanged);
    connect(sprite, &Sprite::positionAdded, this, &Level::onLevelCanvasSpritePlaced);
    connect(sprite, &Sprite::positionRemoved, this, &Level::onLevelCanvasSpriteErased);
    connect(sprite, &Sprite::positionsChanged, this, &Level::onLevelCanvasSpritePositionsChanged);
}

const Sprite* Level::getSpriteByID(const std::string& id) const
{
    for (int i = 0; i < (int) m_sprites.size(); ++i)
    {
        if (m_sprites[i]->getID() == id)
        {
            return m_sprites[i];
        }
    }

    return nullptr;
}
