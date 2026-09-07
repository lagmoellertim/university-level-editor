#include "CreateLevelDialog.hpp"
#include <QPushButton>

CreateLevelDialog::CreateLevelDialog(QWidget* parent)
    : QDialog(parent)
{
    m_UI.setupUi(this);
    m_UI.buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    connect(m_UI.levelNameInput, &QLineEdit::textChanged, this, &CreateLevelDialog::onTextChanged);
}

int CreateLevelDialog::levelWidth() const
{
    return m_UI.levelWidthInput->value();
}

int CreateLevelDialog::levelHeight() const
{
    return m_UI.levelHeightInput->value();
}

int CreateLevelDialog::tileSize() const
{
    return m_UI.tileSizeInput->value();
}

QString CreateLevelDialog::levelName() const
{
    return m_UI.levelNameInput->text();
}

void CreateLevelDialog::onTextChanged(const QString& text)
{
    QPushButton* okButton = m_UI.buttonBox->button(QDialogButtonBox::Ok);

    if (text.isEmpty())
    {
        okButton->setEnabled(false);
    }
    else
    {
        okButton->setEnabled(true);
    }
}