#include "SpriteUtil.hpp"
#include "Exceptions.hpp"
#include "Utils.hpp"

#include <string>
#include <vector>

using namespace HDF5;
using namespace HighFive;

using std::string;
using std::vector;

const char* COORDINATES_ATTR = "coordinates";
const char* MODIFIER_ATTR = "modifiers";

Sprite* HDF5::Utils::importSprite(HighFive::DataSet& spriteDataSet, std::string spriteID)
{
    RawSpriteCollectionType rawSpriteCollection;

    spriteDataSet.read(rawSpriteCollection);
    vector<size_t> tileSetDimensions = spriteDataSet.getDimensions();

    if (tileSetDimensions.size() != 4)
    {
        throw DataException("Invalid Tile Set Dimensions");
    }

    int frameCount = tileSetDimensions[0];
    int frameHeight = tileSetDimensions[1];
    int frameWidth = tileSetDimensions[2];

    vector<QPixmap> frames;
    frames.reserve(frameCount);

    for (int i = 0; i < frameCount; ++i)
    {
        QImage tileImage = Utils::convertVectorToQImage(rawSpriteCollection[i]);
        frames.push_back(QPixmap::fromImage(tileImage));
    }

    vector<QPoint> coordinateCollection;
    if (spriteDataSet.hasAttribute(COORDINATES_ATTR))
    {
        RawCoordinateCollectionType rawCoordinateCollection;
        spriteDataSet.getAttribute(COORDINATES_ATTR).read(rawCoordinateCollection);

        coordinateCollection.reserve(coordinateCollection.size());

        for (auto& coordinates : rawCoordinateCollection)
        {
            coordinateCollection.emplace_back(coordinates[0] + frameWidth / 2, coordinates[1] + frameHeight / 2);
        }
    }


    vector<string> modifierAttributes;
    if (spriteDataSet.hasAttribute(MODIFIER_ATTR))
    {
        spriteDataSet.getAttribute(MODIFIER_ATTR).read(modifierAttributes);
    }

    Sprite* sprite = new Sprite(frames);
    sprite->setCoordinates(coordinateCollection);
    sprite->setModifierAttributes(modifierAttributes);
    sprite->setID(spriteID);

    return sprite;
}

void HDF5::Utils::exportSprite(HighFive::Group& spritesGroup, const Sprite* sprite)
{
    if (sprite == nullptr)
    {
        throw HDF5::DataException("sprite is a nullptr!");
    }

    unsigned int frameCount = sprite->getFrames().size();

    RawSpriteCollectionType rawSpriteCollection(frameCount);
    for (size_t i = 0; i < frameCount; ++i)
    {
        QImage frame = sprite->getFrames()[i].toImage();
        Utils::convertQImageToVector(frame, rawSpriteCollection[i]);
    }

    DataSet spriteDataSet = spritesGroup.createDataSet<unsigned char>(sprite->getID(), DataSpace::From(rawSpriteCollection));
    spriteDataSet.write(rawSpriteCollection);

    if (!sprite->getModifierAttributes().empty())
    {
        spriteDataSet.createAttribute(MODIFIER_ATTR, sprite->getModifierAttributes());
    }

    const vector<QPoint>& coordinateCollection = sprite->getCoordinates();
    if (!coordinateCollection.empty())
    {
        std::vector<std::vector<int>> rawCoordinateCollection;
        rawCoordinateCollection.reserve(coordinateCollection.size());

        for (auto& coordinates : coordinateCollection)
        {
            std::vector<int> rawCoordinates{coordinates.x() - ((int) sprite->getWidth() / 2), coordinates.y() - ((int) sprite->getHeight() / 2)};
            rawCoordinateCollection.push_back(rawCoordinates);
        }

        spriteDataSet.createAttribute(COORDINATES_ATTR, rawCoordinateCollection);
    }
}