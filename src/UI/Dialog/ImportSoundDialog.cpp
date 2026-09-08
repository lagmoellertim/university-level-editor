#include "ImportSoundDialog.hpp"
#include <QPushButton>


ImportSoundDialog::ImportSoundDialog(std::vector<std::string> soundList, QWidget* parent)
    : QDialog(parent), m_soundList(soundList)
{
    m_UI.setupUi(this);
    setWindowTitle("Enter Sound ID");
    m_UI.buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    connect(m_UI.soundIDInput, &QLineEdit::textChanged, this, &ImportSoundDialog::onTextChanged);
}

void ImportSoundDialog::onTextChanged(const QString& text)
{
    std::string stdText = text.toStdString();

    if (stdText.length() == 0 || std::find(m_soundList.begin(), m_soundList.end(), stdText) != m_soundList.end())
    {
        m_UI.buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
    else
    {
        m_UI.buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
}

std::string ImportSoundDialog::getID() const
{
    return m_UI.soundIDInput->text().toStdString();
}

void ImportSoundDialog::setSuggestedID(const QString& id)
{
    m_UI.soundIDInput->setText(id);
    m_UI.soundIDInput->selectAll();
}