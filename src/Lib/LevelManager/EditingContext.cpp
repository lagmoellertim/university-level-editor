#include "EditingContext.hpp"

Layer EditingContext::getSelectedLayer() const
{
    return m_selectedLayer;
}

void EditingContext::setSelectedLayer(Layer selectedLayer)
{
    m_selectedLayer = selectedLayer;
    emit contextLayerSelectionChanged(this);
}

int EditingContext::getSelectedTileID() const
{
    return m_selectedTileID;
}

void EditingContext::setSelectedTileID(int selectedTileID)
{
    m_selectedTileID = selectedTileID;

    emit contextItemSelectionChanged(this);
}

Sprite* EditingContext::getSelectedSprite() const
{
    return m_selectedSprite;
}

void EditingContext::setSelectedSprite(Sprite* selectedSprite)
{
    m_selectedSprite = selectedSprite;

    emit contextItemSelectionChanged(this);
}


std::vector<Layer> EditingContext::getVisibleLayers()
{
    return m_visibleLayers;
}

void EditingContext::setVisibleLayers(std::vector<Layer> visibleLayers)
{
    m_visibleLayers = visibleLayers;
}

void EditingContext::hideLayer(Layer layer)
{
    m_visibleLayers.erase(std::remove(m_visibleLayers.begin(), m_visibleLayers.end(), layer), m_visibleLayers.end());

    emit contextLayerVisibilityChanged(this);
}

void EditingContext::showLayer(Layer layer)
{
    m_visibleLayers.erase(std::remove(m_visibleLayers.begin(), m_visibleLayers.end(), layer), m_visibleLayers.end());
    m_visibleLayers.push_back(layer);

    emit contextLayerVisibilityChanged(this);
}

std::vector<Background*> EditingContext::getVisibleBackgrounds()
{
    return m_visibleBackgrounds;
}


void EditingContext::setVisibleBackgrounds(std::vector<Background*> visibleBackgrounds)
{
    m_visibleBackgrounds = visibleBackgrounds;
    emit contextLayerVisibilityChanged(this);
}

void EditingContext::setBackgroundVisibility(Background* background, bool visible)
{
    m_visibleBackgrounds.erase(std::remove(m_visibleBackgrounds.begin(), m_visibleBackgrounds.end(), background), m_visibleBackgrounds.end());

    if (visible)
    {
        m_visibleBackgrounds.push_back(background);
    }

    emit contextLayerVisibilityChanged(this);
}