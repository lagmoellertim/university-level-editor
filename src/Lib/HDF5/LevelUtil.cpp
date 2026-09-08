#include "LevelUtil.hpp"
#include "BackgroundUtil.hpp"
#include "Exceptions.hpp"
#include "SpriteUtil.hpp"
#include "Utils.hpp"

using namespace HDF5;
using namespace HighFive;

using std::string;
using std::vector;

const char* TILE_SET_NAME = "tile_set";
const char* TILE_MAP_NAME = "tile_map";
const char* LEVEL_NAME_ATTR = "level_name";
const char* TILE_SIZE_ATTR = "tile_size";
const char* END_POSITION_ATTR = "end_position";
const char* ACTOR_SPRITE_ID_ATTR = "actor_sprite_id";
const char* SPRITES_GROUP = "sprites";
const char* BACKGROUNDS_GROUP = "backgrounds";

Level* HDF5::Utils::importLevel(HighFive::Group& levelGroup)
{
    // Get Attributes from the level group
    string levelName;
    levelGroup.getAttribute(LEVEL_NAME_ATTR).read(levelName);

    int endPosition = 0;
    if (levelGroup.hasAttribute(END_POSITION_ATTR))
    {
        levelGroup.getAttribute(END_POSITION_ATTR).read(endPosition);
    }

    string actorSpriteID = "";
    if (levelGroup.hasAttribute(ACTOR_SPRITE_ID_ATTR))
    {
        levelGroup.getAttribute(ACTOR_SPRITE_ID_ATTR).read(actorSpriteID);
    }

    // Import the TileSet from the file
    DataSet tileSetDataset = levelGroup.getDataSet(TILE_SET_NAME);

    RawTileSetType rawTileSet;
    tileSetDataset.read(rawTileSet);

    vector<size_t> tileSetDimensions = tileSetDataset.getDimensions();

    if (tileSetDimensions.size() != 4)
    {
        throw DataException("Invalid Tile Set Dimensions");
    }
    size_t tileCountDimension = tileSetDimensions[0];
    size_t tileSizeDimension = tileSetDimensions[1];

    TileSetType tileSet;
    tileSet.reserve(tileCountDimension);

    for (size_t i = 0; i < tileCountDimension; ++i)
    {
        QImage tileImage = Utils::convertVectorToQImage(rawTileSet[i]);
        tileSet.push_back(QPixmap::fromImage(tileImage));
    }

    int tileSize = (int) tileSizeDimension;

    if (levelGroup.hasAttribute(TILE_SIZE_ATTR))
    {
        levelGroup.getAttribute(TILE_SIZE_ATTR).read(tileSize);
    }

    // Import the TileMap from the file
    TileMapType tileMap;
    DataSet tileMapDataset = levelGroup.getDataSet(TILE_MAP_NAME);
    tileMapDataset.read(tileMap);
    vector<size_t> tileMapDimensions = tileMapDataset.getDimensions();

    if (tileMapDimensions.size() != 2)
    {
        throw DataException("Invalid Tile Map Dimensions");
    }

    int levelWidth = tileMapDimensions[0];
    int levelHeight = tileMapDimensions[1];


    // Import the Sprites from the file
    vector<Sprite*> sprites;
    Sprite* actorSprite = nullptr;

    if (levelGroup.exist(SPRITES_GROUP))
    {
        Group spritesGroup = levelGroup.getGroup(SPRITES_GROUP);

        for (auto& spriteID : spritesGroup.listObjectNames())
        {
            DataSet spriteDataSet = spritesGroup.getDataSet(spriteID);
            Sprite* sprite = Utils::importSprite(spriteDataSet, spriteID);

            if (spriteID == actorSpriteID)
            {
                actorSprite = sprite;
            }

            sprites.push_back(sprite);
        }
    }

    // Import the Sprites from the file
    vector<Background*> backgrounds;
    if (levelGroup.exist(BACKGROUNDS_GROUP))
    {
        Group backgroundsGroup = levelGroup.getGroup(BACKGROUNDS_GROUP);

        for (auto& backgroundID : backgroundsGroup.listObjectNames())
        {
            DataSet backgroundDataSet = backgroundsGroup.getDataSet(backgroundID);
            backgrounds.push_back(Utils::importBackground(backgroundDataSet, backgroundID));
        }
    }

    auto* level = new Level(tileSize, levelWidth, levelHeight);
    level->setLevelName(levelName);
    level->setTileMap(tileMap);
    level->setTileSet(tileSet);
    level->setSprites(sprites);
    level->setBackgrounds(backgrounds);
    level->setEndPosition(endPosition);

    if (actorSprite != nullptr)
    {
        level->setActorSprite(actorSprite);
    }

    return level;
}

void HDF5::Utils::exportLevel(HighFive::Group& levelGroup, const Level* level)
{
    if (level == nullptr)
    {
        throw HDF5::DataException("level is a nullptr!");
    }

    // Set the level group attributes
    levelGroup.createAttribute(LEVEL_NAME_ATTR, level->getLevelName());
    levelGroup.createAttribute(TILE_SIZE_ATTR, level->getTileSize());
    levelGroup.createAttribute(END_POSITION_ATTR, level->getEndPosition());

    if (level->getActorSprite() != nullptr)
    {
        levelGroup.createAttribute(ACTOR_SPRITE_ID_ATTR, level->getActorSprite()->getID());
    }

    // Export TileMap
    DataSet tileMapDataset = levelGroup.createDataSet<int>(TILE_MAP_NAME, DataSpace::From(level->getTileMap()));
    tileMapDataset.write(level->getTileMap());

    unsigned int tileSetSize = level->getTileSet().size();

    // Generate Raw TileSet from given TileSet
    RawTileSetType rawTileSet(tileSetSize);
    for (size_t i = 0; i < tileSetSize; ++i)
    {
        QImage tileImage = level->getTileSet()[i].toImage();
        Utils::convertQImageToVector(tileImage, rawTileSet[i]);
    }

    // Export the Raw TileSet
    DataSet tileSetDataset = levelGroup.createDataSet<unsigned char>(TILE_SET_NAME, DataSpace::From(rawTileSet));
    tileSetDataset.write(rawTileSet);

    // Export the Sprites
    Group spritesGroup = levelGroup.createGroup(SPRITES_GROUP);
    for (auto& sprite : level->getSprites())
    {
        Utils::exportSprite(spritesGroup, sprite);
    }

    Group backgroundsGroup = levelGroup.createGroup(BACKGROUNDS_GROUP);
    for (auto& background : level->getBackgrounds())
    {
        Utils::exportBackground(backgroundsGroup, background);
    }
}
