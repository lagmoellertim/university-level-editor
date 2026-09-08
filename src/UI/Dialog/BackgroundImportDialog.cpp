#include "BackgroundImportDialog.hpp"
#include <QPushButton>


BackgroundImportDialog::BackgroundImportDialog(Level* level, QWidget* parent)
    : QDialog(parent)
{
    m_UI.setupUi(this);
    m_UI.buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    connect(m_UI.backgroundIDInput, &QLineEdit::textChanged, this, &BackgroundImportDialog::onTextChanged);

    for (Background* bg : level->getBackgrounds())
    {
        m_backgroundIDs.push_back(bg->getID());
    }
}

std::string BackgroundImportDialog::getID() const
{
    return m_UI.backgroundIDInput->text().toStdString();
}

int BackgroundImportDialog::getParallaxInput() const
{
    return m_UI.parallaxLayerInput->value();
}

int BackgroundImportDialog::getSpeedInput() const
{
    return m_UI.layerSpeedInput->value();
}

void BackgroundImportDialog::onTextChanged(const QString& text)
{
    std::string stdText = text.toStdString();

    if (text.isEmpty() || std::find(m_backgroundIDs.begin(), m_backgroundIDs.end(), stdText) != m_backgroundIDs.end())
    {
        m_UI.buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
    else
    {
        m_UI.buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
}
