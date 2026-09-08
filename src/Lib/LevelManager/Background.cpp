#include "Background.hpp"
const QPixmap& Background::getBackgroundImage() const
{
    return m_backgroundImage;
}

Background::Background(const QPixmap& backgroundImage, std::string id)
    : QObject()
{
    m_backgroundImage = backgroundImage;
    m_id = id;
}

const std::string Background::getID() const
{
    return m_id;
}

int Background::getDepth() const
{
    return m_depth;
}


void Background::setDepth(int depth)
{
    m_depth = depth;

    emit depthChange(this);
}
int Background::getSpeed() const
{
    return m_speed;
}
void Background::setSpeed(int speed)
{
    m_speed = speed;
}
