/********************************************************************************
** Form generated from reading UI file 'tile_set_import_dialogGxmuNF.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef RESOURCE_IMPORT_DIALOGGXMUNF_H
#define RESOURCE_IMPORT_DIALOGGXMUNF_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ResourceImportDialog
{
public:
    QGridLayout* gridLayout_2;
    QGridLayout* gridLayout;
    QFormLayout* formLayout;
    QLabel* dialogSpecificLabel;
    QSpinBox* dialogSpecificInput;
    QLabel* paddingLabel;
    QSpinBox* paddingInput;
    QVBoxLayout* verticalLayout_2;
    QCheckBox* transparencyColorCheckbox;
    QPushButton* transparencyColorButton;
    QLabel* transparencyColorLabel;
    QVBoxLayout* verticalLayout;
    QLabel* previewLabel;
    QLabel* preview;
    QFormLayout* formLayout_2;
    QLabel* previewIdLabel;
    QSpinBox* previewIdInput;
    QDialogButtonBox* buttonBox;
    QFrame* line;

    void setupUi(QDialog* ResourceImportDialog)
    {
        if (ResourceImportDialog->objectName().isEmpty())
            ResourceImportDialog->setObjectName(QString::fromUtf8("ResourceImportDialog"));
        ResourceImportDialog->resize(328, 352);
        gridLayout_2 = new QGridLayout(ResourceImportDialog);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFormAlignment(Qt::AlignHCenter | Qt::AlignTop);
        dialogSpecificLabel = new QLabel(ResourceImportDialog);
        dialogSpecificLabel->setObjectName(QString::fromUtf8("dialogSpecificLabel"));
        dialogSpecificLabel->setMargin(5);

        formLayout->setWidget(0, QFormLayout::LabelRole, dialogSpecificLabel);

        dialogSpecificInput = new QSpinBox(ResourceImportDialog);
        dialogSpecificInput->setObjectName(QString::fromUtf8("dialogSpecificInput"));
        dialogSpecificInput->setMinimum(1);
        dialogSpecificInput->setMaximum(10000);

        formLayout->setWidget(0, QFormLayout::FieldRole, dialogSpecificInput);

        paddingLabel = new QLabel(ResourceImportDialog);
        paddingLabel->setObjectName(QString::fromUtf8("paddingLabel"));
        paddingLabel->setMargin(5);

        formLayout->setWidget(1, QFormLayout::LabelRole, paddingLabel);

        paddingInput = new QSpinBox(ResourceImportDialog);
        paddingInput->setObjectName(QString::fromUtf8("paddingInput"));
        paddingInput->setMaximum(10000);

        formLayout->setWidget(1, QFormLayout::FieldRole, paddingInput);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        transparencyColorCheckbox = new QCheckBox(ResourceImportDialog);
        transparencyColorCheckbox->setObjectName(QString::fromUtf8("transparencyColorCheckbox"));

        verticalLayout_2->addWidget(transparencyColorCheckbox);

        transparencyColorButton = new QPushButton(ResourceImportDialog);
        transparencyColorButton->setObjectName(QString::fromUtf8("transparencyColorButton"));

        verticalLayout_2->addWidget(transparencyColorButton);


        formLayout->setLayout(2, QFormLayout::FieldRole, verticalLayout_2);

        transparencyColorLabel = new QLabel(ResourceImportDialog);
        transparencyColorLabel->setObjectName(QString::fromUtf8("transparencyColorLabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, transparencyColorLabel);


        gridLayout->addLayout(formLayout, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        previewLabel = new QLabel(ResourceImportDialog);
        previewLabel->setObjectName(QString::fromUtf8("previewLabel"));
        previewLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(previewLabel);

        preview = new QLabel(ResourceImportDialog);
        preview->setObjectName(QString::fromUtf8("preview"));
        preview->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(preview);

        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setFormAlignment(Qt::AlignHCenter | Qt::AlignTop);
        previewIdLabel = new QLabel(ResourceImportDialog);
        previewIdLabel->setObjectName(QString::fromUtf8("previewIdLabel"));
        previewIdLabel->setMargin(5);

        formLayout_2->setWidget(0, QFormLayout::LabelRole, previewIdLabel);

        previewIdInput = new QSpinBox(ResourceImportDialog);
        previewIdInput->setObjectName(QString::fromUtf8("previewIdInput"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, previewIdInput);


        verticalLayout->addLayout(formLayout_2);


        gridLayout->addLayout(verticalLayout, 2, 0, 1, 1);

        buttonBox = new QDialogButtonBox(ResourceImportDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 3, 0, 1, 1);

        line = new QFrame(ResourceImportDialog);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 1, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(ResourceImportDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ResourceImportDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ResourceImportDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ResourceImportDialog);
    }  // setupUi

    void retranslateUi(QDialog* ResourceImportDialog)
    {
        ResourceImportDialog->setWindowTitle(QCoreApplication::translate("ResourceImportDialog", "Dialog", nullptr));
        dialogSpecificLabel->setText(QCoreApplication::translate("ResourceImportDialog", "REPLACE", nullptr));
        paddingLabel->setText(QCoreApplication::translate("ResourceImportDialog", "Tile-Padding:", nullptr));
        transparencyColorCheckbox->setText(QCoreApplication::translate("ResourceImportDialog", "Use Transparency Color", nullptr));
        transparencyColorButton->setText(QCoreApplication::translate("ResourceImportDialog", "Set Color", nullptr));
        transparencyColorLabel->setText(QCoreApplication::translate("ResourceImportDialog", "Transparency Color", nullptr));
        previewLabel->setText(QCoreApplication::translate("ResourceImportDialog", "Preview", nullptr));
        preview->setText(QString());
        previewIdLabel->setText(QCoreApplication::translate("ResourceImportDialog", "Preview ID:", nullptr));
    }  // retranslateUi
};

namespace Ui
{
    class ResourceImportDialog : public Ui_ResourceImportDialog
    {
    };
}  // namespace Ui

QT_END_NAMESPACE

#endif  // RESOURCE_IMPORT_DIALOGGXMUNF_H
