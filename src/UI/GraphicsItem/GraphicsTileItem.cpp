/******************************************************************************
 *  GraphicsTileItem.cpp
 *  Copyright (c) 2020 Thomas Wiemann.
 *
 *  Restricted usage. Licensed for participants of the
 *  course "The C++ Programming Language" only.
 *
 *  No unauthorized distribution.
 ******************************************************************************/

#include <QGraphicsColorizeEffect>

#include "GraphicsTileItem.hpp"


GraphicsTileItem::GraphicsTileItem(QPixmap* tilePixmap, int index)
    : m_index(index)
{
    setPixmap(*tilePixmap);
}

GraphicsTileItem::GraphicsTileItem(QColor* color, int w, int h)
    : m_index(-1)
{
    QPixmap pm(w, h);
    pm.fill(*color);
    setPixmap(pm);
}

int GraphicsTileItem::index() const
{
    return m_index;
}

void GraphicsTileItem::setIndex(int i)
{
    m_index = i;
}