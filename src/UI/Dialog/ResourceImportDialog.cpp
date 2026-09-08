#include "ResourceImportDialog.hpp"
#include <QBitmap>
#include <QColorDialog>
#include <QSpinBox>

ResourceImportDialog::ResourceImportDialog(QPixmap& pixmap, QWidget* parent)
    : QDialog(parent), m_pixmap(pixmap)
{
    m_ui.setupUi(this);
    this->setModal(true);

    connect(m_ui.dialogSpecificInput, QOverload<int>::of(&QSpinBox::valueChanged), this, &ResourceImportDialog::onValueChanged);
    connect(m_ui.paddingInput, QOverload<int>::of(&QSpinBox::valueChanged), this, &ResourceImportDialog::onValueChanged);
    connect(m_ui.previewIdInput, QOverload<int>::of(&QSpinBox::valueChanged), this, &ResourceImportDialog::onValueChanged);

    connect(m_ui.transparencyColorCheckbox, &QCheckBox::clicked, this, &ResourceImportDialog::onButtonUpdate);
    connect(m_ui.transparencyColorCheckbox, &QCheckBox::clicked, this, &ResourceImportDialog::onElementClicked);
    connect(m_ui.transparencyColorButton, &QPushButton::released, this, &ResourceImportDialog::onColorPickerRequested);

    connect(this, &ResourceImportDialog::transparencyColorUpdated, this, &ResourceImportDialog::onTransparencyColorUpdated);
    connect(this, &ResourceImportDialog::transparencyColorUpdated, this, &ResourceImportDialog::onButtonUpdate);

    onButtonUpdate();
}

void ResourceImportDialog::onValueChanged(int value)
{
    renderPreview();
}

void ResourceImportDialog::onElementClicked()
{
    renderPreview();
}

void ResourceImportDialog::onTransparencyColorUpdated()
{
    renderPreview();
}

void ResourceImportDialog::onColorPickerRequested()
{
    m_color = QColorDialog::getColor();

    emit transparencyColorUpdated();
}

void ResourceImportDialog::onButtonUpdate()
{
    auto& button = m_ui.transparencyColorButton;

    bool isEnabled = isTransparencyMappingEnabled();
    button->setEnabled(isEnabled);

    QPalette pal = button->palette();
    pal.setColor(QPalette::Button, m_color);

    button->setAutoFillBackground(isEnabled);
    button->setPalette(pal);
    button->update();
}

void ResourceImportDialog::renderPreview()
{
    int padding = m_ui.paddingInput->value();
    int id = m_ui.previewIdInput->value();

    QPoint size = getItemSize();
    QPixmap previewPixmap;
    int width = size.x();
    int height = size.y();

    int maxXItems = 0;
    int maxYItems = 0;
    int x;
    int y;
    bool invalid = false;

    if (width > 0 && height > 0 && padding >= 0 && id >= 0)
    {
        maxXItems = (m_pixmap.width() + padding) / (width + padding);
        maxYItems = (m_pixmap.height() + padding) / (height + padding);

        if (maxXItems != 0 && maxYItems != 0)
        {
            x = (id % maxXItems) * (width + padding);
            y = (id / maxXItems) * (height + padding);
        }
        else
        {
            invalid = true;
        }
    }
    else
    {
        invalid = true;
    }

    int maxPreviewID = maxXItems * maxYItems - 1;
    if (maxPreviewID < 0)
    {
        maxPreviewID = 0;
        invalid = true;
    }

    if (width > m_pixmap.width())
    {
        width = m_pixmap.width();
        invalid = true;
    }

    if (height > m_pixmap.height())
    {
        height = m_pixmap.height();
        invalid = true;
    }

    if (invalid)
    {
        previewPixmap = QPixmap(1, 1);
        previewPixmap.fill(Qt::transparent);
    }
    else
    {
        previewPixmap = m_pixmap.copy(x, y, width, height);
    }

    m_ui.previewIdInput->setMaximum(maxPreviewID);

    if (m_scalePreview)
    {
        previewPixmap = previewPixmap.scaled(100, 100, Qt::KeepAspectRatio);
    }

    if (isTransparencyMappingEnabled())
    {
        previewPixmap.setMask(previewPixmap.createMaskFromColor(m_color));
    }

    m_ui.preview->setPixmap(previewPixmap);
    this->adjustSize();
}

std::vector<QPixmap>* ResourceImportDialog::generatePixmapVector()
{
    auto* pixmapCollection = new std::vector<QPixmap>;

    QPoint size = getItemSize();
    int width = size.x();
    int height = size.y();

    int padding = m_ui.paddingInput->value();

    if (isTransparencyMappingEnabled())
    {
        m_pixmap.setMask(m_pixmap.createMaskFromColor(m_color));
    }

    int maxXItems = 0;
    int maxYItems = 0;

    if (width > 0 && height > 0 && padding >= 0)
    {
        maxXItems = (m_pixmap.width() + padding) / (width + padding);
        maxYItems = (m_pixmap.height() + padding) / (height + padding);
    }

    for (int id = 0; id < maxXItems * maxYItems; ++id)
    {
        int x = (id % maxXItems) * (width + padding);
        int y = (id / maxXItems) * (height + padding);

        if (x + width > m_pixmap.width() || y + height > m_pixmap.height())
        {
            continue;
        }

        QPixmap tilePixmap = m_pixmap.copy(x, y, width, height);

        if (!isImageEmpty(tilePixmap.toImage()))
        {
            pixmapCollection->push_back(tilePixmap);
        }
    }

    if (pixmapCollection->empty())
    {
        delete pixmapCollection;
        return nullptr;
    }

    return pixmapCollection;
}

bool ResourceImportDialog::isTransparencyMappingEnabled() const
{
    return m_ui.transparencyColorCheckbox->isChecked();
}

bool ResourceImportDialog::isImageEmpty(const QImage& image)
{
    for (int y = 0; y < image.height(); ++y)
    {
        QRgb* row = (QRgb*) image.scanLine(y);
        for (int x = 0; x < image.width(); ++x)
        {
            // Check if the current pixel contains any non-transparent content
            if (((unsigned char*) &row[x])[3] != 0)
            {
                return false;
            }
        }
    }

    return true;
}
int ResourceImportDialog::getPadding() const
{
    return m_ui.paddingInput->value();
}
