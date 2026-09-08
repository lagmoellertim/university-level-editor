#include "Sprite.hpp"

Sprite::Sprite(const std::vector<QPixmap>& frames)
    : QObject(), m_frames(frames)
{
    m_frames = frames;
    m_scaledFrames = std::vector(frames);
}

const std::vector<QPixmap>& Sprite::getFrames() const
{
    return m_scaledFrames;
}

unsigned int Sprite::getWidth() const
{
    if (m_scaledFrames.empty())
    {
        return 0;
    }

    return m_scaledFrames[0].width();
}

unsigned int Sprite::getHeight() const
{
    if (m_scaledFrames.empty())
    {
        return 0;
    }

    return m_scaledFrames[0].height();
}

const std::string& Sprite::getID() const
{
    return m_id;
}

void Sprite::setID(const std::string& id)
{
    m_id = id;

    emit idChanged(this);
}

void Sprite::setHeight(int height)
{
    if (height <= 0)
    {
        throw std::runtime_error("New Height can not be <= 0");
    }

    m_scaledFrames.clear();
    m_scaledFrames.reserve(m_frames.size());

    for (auto& frame : m_frames)
    {
        m_scaledFrames.push_back(frame.scaled(INT_MAX, height, Qt::KeepAspectRatio));
    }

    emit positionsChanged(this);
}

const std::vector<QPoint>& Sprite::getCoordinates() const
{
    return m_coordinates;
}

void Sprite::setCoordinates(const std::vector<QPoint>& coordinateVector)
{
    m_coordinates = coordinateVector;

    emit positionsChanged(this);
}

void Sprite::addCoordinates(QPoint& coordinates)
{
    m_coordinates.push_back(coordinates);

    emit positionAdded(this, coordinates);
}

void Sprite::removeCoordinates(QPoint& coordinates)
{
    auto it = find(m_coordinates.begin(), m_coordinates.end(), coordinates);

    if (it != m_coordinates.end())
    {
        int index = it - m_coordinates.begin();
        m_coordinates.erase(m_coordinates.begin() + index);
    }
    else
    {
        throw std::runtime_error("This coordinate is not in this sprite");
    }

    emit positionRemoved(this, coordinates);
}

const std::vector<std::string>& Sprite::getModifierAttributes() const
{
    return m_modifierAttributes;
}

void Sprite::setModifierAttributes(const std::vector<std::string>& modifierAttributes)
{
    m_modifierAttributes = modifierAttributes;

    emit modifierChanged(this);
}

void Sprite::addModifierAttribute(const std::string& modifierAttribute)
{
    m_modifierAttributes.push_back(modifierAttribute);

    emit modifierChanged(this);
}

void Sprite::removeModifierAttribute(const std::string& modifierAttribute)
{
    auto it = find(m_modifierAttributes.begin(), m_modifierAttributes.end(), modifierAttribute);

    if (it != m_modifierAttributes.end())
    {
        int index = it - m_modifierAttributes.begin();
        m_modifierAttributes.erase(m_modifierAttributes.begin() + index);
    }
    else
    {
        throw std::runtime_error("This coordinate is not in this sprite");
    }

    emit modifierChanged(this);
}
