#include "Handler.hpp"
#include "Exceptions.hpp"
#include "LevelUtil.hpp"
#include <filesystem>
#include <highfive/H5File.hpp>

const char* LEVEL_GROUP = "levels";
const char* SOUND_GROUP = "sounds";

using namespace HDF5;
using namespace HighFive;

using std::string;

void HDF5::importHDF5(const string& filename, LevelManager* levelManager, bool importMusic)
{
    if (levelManager == nullptr)
    {
        throw HDF5::DataException("levelManager is a nullptr!");
    }

    try
    {
        File file(filename, File::ReadOnly);

        if (file.exist(LEVEL_GROUP))
        {
            Group levelBaseGroup = file.getGroup(LEVEL_GROUP);

            for (auto& levelName : levelBaseGroup.listObjectNames())
            {
                Group levelGroup = levelBaseGroup.getGroup(levelName);

                levelManager->addLevel(Utils::importLevel(levelGroup));
            }
        }

        if (file.exist(SOUND_GROUP) && importMusic)
        {
            Group soundBaseGroup = file.getGroup(SOUND_GROUP);

            for (auto& soundName : soundBaseGroup.listObjectNames())
            {
                DataSet soundDataSet = soundBaseGroup.getDataSet(soundName);

                std::vector<unsigned char> rawSoundDataVector;
                soundDataSet.read(rawSoundDataVector);

                QByteArray rawSoundData = QByteArray(reinterpret_cast<char*>(rawSoundDataVector.data()), rawSoundDataVector.size());

                Sound* sound = new Sound(soundName, rawSoundData);

                levelManager->addSound(sound);
            }
        }
    }
    catch (const HighFive::FileException& e)
    {
        throw HDF5::FileException(e.what());
    }
    catch (const HighFive::Exception& e)
    {
        throw HDF5::DataException(e.what());
    }
}

void HDF5::exportHDF5(const string& filename, const LevelManager* levelManager)
{
    if (levelManager == nullptr)
    {
        throw HDF5::DataException("levelManager is a nullptr!");
    }

    try
    {
        std::filesystem::remove(filename);
    }
    catch (const std::filesystem::filesystem_error& e)
    {
        throw HDF5::FileException(e.what());
    }


    try
    {
        File file(filename, File::ReadWrite | File::Create | File::Overwrite | File::Truncate);

        Group levelBaseGroup = file.createGroup(LEVEL_GROUP);

        int i = 0;
        for (auto& level : levelManager->getLevels())
        {
            Group levelGroup = levelBaseGroup.createGroup(std::to_string(i++));
            Utils::exportLevel(levelGroup, level);
        }

        Group soundBaseGroup = file.createGroup(SOUND_GROUP);
        for (auto& sound : levelManager->getSounds())
        {
            std::vector<unsigned char> rawSoundDataVector(sound->getRawSoundData().begin(), sound->getRawSoundData().end());

            DataSet tileSetDataset = soundBaseGroup.createDataSet<unsigned char>(sound->getID(), DataSpace::From(rawSoundDataVector));
            tileSetDataset.write(rawSoundDataVector);
        }
    }
    catch (const HighFive::FileException& e)
    {
        throw HDF5::FileException(e.what());
    }
    catch (const HighFive::Exception& e)
    {
        throw HDF5::DataException(e.what());
    }
}