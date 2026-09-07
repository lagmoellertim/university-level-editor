#include "Utils.hpp"

#include <vector>

void HDF5::Utils::convertQImageToVector(const QImage& source, RawImageType& target)
{
    target.resize(source.height());

    for (int y = 0; y < source.height(); ++y)
    {
        target[y].resize(source.width());

        QRgb* row = (QRgb*) source.scanLine(y);

        for (int x = 0; x < source.width(); ++x)
        {
            target[y][x].resize(4);
            target[y][x][0] = (unsigned char) ((unsigned char*) &row[x])[2];
            target[y][x][1] = (unsigned char) ((unsigned char*) &row[x])[1];
            target[y][x][2] = (unsigned char) ((unsigned char*) &row[x])[0];
            target[y][x][3] = (unsigned char) ((unsigned char*) &row[x])[3];
        }
    }
}

QImage HDF5::Utils::convertVectorToQImage(const RawImageType& source)
{
    int height = source.size();
    int width = 0;

    if (height > 0)
    {
        width = source[0].size();
    }

    QImage image(width, height, QImage::Format_ARGB32);

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            const std::vector<unsigned char>& currentPixel = source[y][x];
            image.setPixel((int) x, (int) y, qRgba(currentPixel[0], currentPixel[1], currentPixel[2], currentPixel[3]));
        }
    }

    return image;
}