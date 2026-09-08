#include "SpriteImportDialog.hpp"
#include <QBitmap>
#include <QLabel>
#include <QLineEdit>

SpriteImportDialog::SpriteImportDialog(QPixmap& pixmap, Level* level, QWidget* parent)
    : ResourceImportDialog(pixmap, parent), m_level(level)
{
    setWindowTitle("Import Sprite");
    m_ui.dialogSpecificLabel->setText("Frame-Count");

    QLabel* label = new QLabel(this);
    label->setText("Sprite ID");
    label->setMargin(5);

    m_idInput = new QLineEdit(this);
    m_idInput->setMaximumSize(177, 100);

    m_ui.buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    connect(m_idInput, &QLineEdit::textChanged, this, &SpriteImportDialog::onTextChanged);

    m_ui.formLayout->setWidget(4, QFormLayout::LabelRole, label);
    m_ui.formLayout->setWidget(4, QFormLayout::FieldRole, m_idInput);

    m_scalePreview = false;
    renderPreview();
}

QPoint SpriteImportDialog::getItemSize() const
{
    int frameCount = m_ui.dialogSpecificInput->value();
    int width = (m_pixmap.width() - getPadding() * (frameCount - 1)) / frameCount;
    int height = m_pixmap.height();
    return {width, height};
}

std::string SpriteImportDialog::getSpriteID()
{
    return m_idInput->text().toStdString();
}

void SpriteImportDialog::onTextChanged(const QString& text)
{
    QPushButton* okButton = m_ui.buttonBox->button(QDialogButtonBox::Ok);

    if (text.isEmpty() || m_level->getSpriteByID(text.toStdString()))
    {
        okButton->setEnabled(false);
    }
    else
    {
        okButton->setEnabled(true);
    }
}