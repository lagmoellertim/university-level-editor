#include "Sound.hpp"
#include <QFile>
#include <QIODevice>
Sound::Sound(const std::string& id, const QByteArray& rawSoundData)
{
    m_id = id;
    m_rawSoundData = rawSoundData;
}

const std::string& Sound::getID() const
{
    return m_id;
}

const QByteArray& Sound::getRawSoundData() const
{
    return m_rawSoundData;
}

Sound* Sound::fromFile(const std::string& id, const std::string& filename)
{
    QFile file(filename.c_str());

    if (!file.open(QIODevice::ReadOnly))
    {
        throw std::runtime_error("File could not be read!");
    }

    return new Sound(id, file.readAll());
}

void Sound::setID(const std::string& id)
{
    m_id = id;
}
