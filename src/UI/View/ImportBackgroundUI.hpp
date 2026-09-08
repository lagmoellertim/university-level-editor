/********************************************************************************
** Form generated from reading UI file 'Import Background - untitled 2Znooli.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef IMPORT_20_BACKGROUND_20__2D__20_UNTITLED_20_2ZNOOLI_H
#define IMPORT_20_BACKGROUND_20__2D__20_UNTITLED_20_2ZNOOLI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_BackgroundImportDialog
{
public:
    QGridLayout* gridLayout;
    QFormLayout* formLayout;
    QLabel* parallaxLayerLabel;
    QLabel* backgroundIDInput_2;
    QLineEdit* backgroundIDInput;
    QSpinBox* parallaxLayerInput;
    QLabel* layerSpeedLabel;
    QSpinBox* layerSpeedInput;
    QDialogButtonBox* buttonBox;

    void setupUi(QDialog* BackgroundImportDialog)
    {
        if (BackgroundImportDialog->objectName().isEmpty())
            BackgroundImportDialog->setObjectName(QString::fromUtf8("BackgroundImportDialog"));
        BackgroundImportDialog->resize(274, 213);
        gridLayout = new QGridLayout(BackgroundImportDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        parallaxLayerLabel = new QLabel(BackgroundImportDialog);
        parallaxLayerLabel->setObjectName(QString::fromUtf8("parallaxLayerLabel"));
        parallaxLayerLabel->setMargin(5);

        formLayout->setWidget(0, QFormLayout::LabelRole, parallaxLayerLabel);

        backgroundIDInput_2 = new QLabel(BackgroundImportDialog);
        backgroundIDInput_2->setObjectName(QString::fromUtf8("backgroundIDInput_2"));
        backgroundIDInput_2->setMargin(5);

        formLayout->setWidget(2, QFormLayout::LabelRole, backgroundIDInput_2);

        backgroundIDInput = new QLineEdit(BackgroundImportDialog);
        backgroundIDInput->setObjectName(QString::fromUtf8("backgroundIDInput"));
        backgroundIDInput->setMinimumSize(QSize(10, 0));
        backgroundIDInput->setMaximumSize(QSize(150, 16777215));

        formLayout->setWidget(2, QFormLayout::FieldRole, backgroundIDInput);

        parallaxLayerInput = new QSpinBox(BackgroundImportDialog);
        parallaxLayerInput->setObjectName(QString::fromUtf8("parallaxLayerInput"));
        parallaxLayerInput->setMinimumSize(QSize(150, 0));
        parallaxLayerInput->setMaximum(999);

        formLayout->setWidget(0, QFormLayout::FieldRole, parallaxLayerInput);

        layerSpeedLabel = new QLabel(BackgroundImportDialog);
        layerSpeedLabel->setObjectName(QString::fromUtf8("layerSpeedLabel"));
        layerSpeedLabel->setMargin(5);

        formLayout->setWidget(1, QFormLayout::LabelRole, layerSpeedLabel);

        layerSpeedInput = new QSpinBox(BackgroundImportDialog);
        layerSpeedInput->setObjectName(QString::fromUtf8("layerSpeedInput"));
        layerSpeedInput->setMinimumSize(QSize(150, 0));
        layerSpeedInput->setMinimum(0);
        layerSpeedInput->setMaximum(999);

        formLayout->setWidget(1, QFormLayout::FieldRole, layerSpeedInput);


        gridLayout->addLayout(formLayout, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(BackgroundImportDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(BackgroundImportDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), BackgroundImportDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), BackgroundImportDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(BackgroundImportDialog);
    }  // setupUi

    void retranslateUi(QDialog* BackgroundImportDialog)
    {
        BackgroundImportDialog->setWindowTitle(QCoreApplication::translate("BackgroundImportDialog", "Import Background", nullptr));
        parallaxLayerLabel->setText(QCoreApplication::translate("BackgroundImportDialog", "Parallax Layer", nullptr));
        backgroundIDInput_2->setText(QCoreApplication::translate("BackgroundImportDialog", "Background ID", nullptr));
        layerSpeedLabel->setText(QCoreApplication::translate("BackgroundImportDialog", "Layer Speed", nullptr));
    }  // retranslateUi
};

namespace Ui
{
    class BackgroundImportDialog : public Ui_BackgroundImportDialog
    {
    };
}  // namespace Ui

QT_END_NAMESPACE

#endif  // IMPORT_20_BACKGROUND_20__2D__20_UNTITLED_20_2ZNOOLI_H
