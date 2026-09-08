#include "LayerListItem.hpp"

LayerListItem::LayerListItem(LayerType type, const QString& name, QListWidget* parent)
    : QListWidgetItem(name, parent), m_type(type)
{
}

LayerType LayerListItem::getLayerType()
{
    return m_type;
}