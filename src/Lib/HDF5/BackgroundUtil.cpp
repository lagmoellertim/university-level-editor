#include "BackgroundUtil.hpp"
#include "Exceptions.hpp"
#include "Utils.hpp"

#include <string>
#include <vector>

using namespace HDF5;
using namespace HighFive;

using std::string;
using std::vector;

const char* DEPTH_ATTR = "depth";
const char* SPEED_ATTR = "speed";

Background* HDF5::Utils::importBackground(HighFive::DataSet& backgroundDataSet, std::string backgroundID)
{
    RawBackgroundImageType rawBackgroundImage;

    backgroundDataSet.read(rawBackgroundImage);
    vector<size_t> tileSetDimensions = backgroundDataSet.getDimensions();

    if (tileSetDimensions.size() != 3)
    {
        throw DataException("Invalid Background Dimensions");
    }

    QImage tileImage = Utils::convertVectorToQImage(rawBackgroundImage);
    QPixmap backgroundImage = QPixmap::fromImage(tileImage);

    int depth = 0;
    if (backgroundDataSet.hasAttribute(DEPTH_ATTR))
    {
        backgroundDataSet.getAttribute(DEPTH_ATTR).read(depth);
    }

    int speed = 0;
    if (backgroundDataSet.hasAttribute(SPEED_ATTR))
    {
        backgroundDataSet.getAttribute(SPEED_ATTR).read(speed);
    }

    auto* background = new Background(backgroundImage, backgroundID);
    background->setDepth(depth);
    background->setSpeed(speed);

    return background;
}

void HDF5::Utils::exportBackground(HighFive::Group& backgroundGroup, const Background* background)
{
    if (background == nullptr)
    {
        throw HDF5::DataException("background is a nullptr!");
    }

    RawBackgroundImageType rawBackgroundImage;

    QImage frame = background->getBackgroundImage().toImage();
    Utils::convertQImageToVector(frame, rawBackgroundImage);

    DataSet backgroundDataSet = backgroundGroup.createDataSet<unsigned char>(background->getID(), DataSpace::From(rawBackgroundImage));
    backgroundDataSet.write(rawBackgroundImage);

    backgroundDataSet.createAttribute(DEPTH_ATTR, background->getDepth());
    backgroundDataSet.createAttribute(SPEED_ATTR, background->getSpeed());
}