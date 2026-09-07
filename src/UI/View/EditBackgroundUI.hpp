/********************************************************************************
** Form generated from reading UI file 'Import Background - untitled 2OiPhGC.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef IMPORT_20_BACKGROUND_20__2D__20_UNTITLED_20_2OIPHGC_H
#define IMPORT_20_BACKGROUND_20__2D__20_UNTITLED_20_2OIPHGC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_BackgroundAttributeChangeDialog
{
public:
    QGridLayout* gridLayout;
    QFormLayout* formLayout;
    QLabel* parallaxLayerLabel;
    QSpinBox* parallaxLayerInput;
    QLabel* layerSpeedLabel;
    QSpinBox* layerSpeedInput;
    QDialogButtonBox* buttonBox;

    void setupUi(QDialog* BackgroundAttributeChangeDialog)
    {
        if (BackgroundAttributeChangeDialog->objectName().isEmpty())
            BackgroundAttributeChangeDialog->setObjectName(QString::fromUtf8("BackgroundAttributeChangeDialog"));
        BackgroundAttributeChangeDialog->resize(274, 150);
        gridLayout = new QGridLayout(BackgroundAttributeChangeDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        parallaxLayerLabel = new QLabel(BackgroundAttributeChangeDialog);
        parallaxLayerLabel->setObjectName(QString::fromUtf8("parallaxLayerLabel"));
        parallaxLayerLabel->setMargin(5);

        formLayout->setWidget(0, QFormLayout::LabelRole, parallaxLayerLabel);

        parallaxLayerInput = new QSpinBox(BackgroundAttributeChangeDialog);
        parallaxLayerInput->setObjectName(QString::fromUtf8("parallaxLayerInput"));
        parallaxLayerInput->setMinimumSize(QSize(150, 0));
        parallaxLayerInput->setMaximum(999);

        formLayout->setWidget(0, QFormLayout::FieldRole, parallaxLayerInput);

        layerSpeedLabel = new QLabel(BackgroundAttributeChangeDialog);
        layerSpeedLabel->setObjectName(QString::fromUtf8("layerSpeedLabel"));
        layerSpeedLabel->setMargin(5);

        formLayout->setWidget(1, QFormLayout::LabelRole, layerSpeedLabel);

        layerSpeedInput = new QSpinBox(BackgroundAttributeChangeDialog);
        layerSpeedInput->setObjectName(QString::fromUtf8("layerSpeedInput"));
        layerSpeedInput->setMinimumSize(QSize(150, 0));
        layerSpeedInput->setMinimum(0);
        layerSpeedInput->setMaximum(999);

        formLayout->setWidget(1, QFormLayout::FieldRole, layerSpeedInput);


        gridLayout->addLayout(formLayout, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(BackgroundAttributeChangeDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(BackgroundAttributeChangeDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), BackgroundAttributeChangeDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), BackgroundAttributeChangeDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(BackgroundAttributeChangeDialog);
    }  // setupUi

    void retranslateUi(QDialog* BackgroundAttributeChangeDialog)
    {
        BackgroundAttributeChangeDialog->setWindowTitle(QCoreApplication::translate("BackgroundAttributeChangeDialog", "Edit Background", nullptr));
        parallaxLayerLabel->setText(QCoreApplication::translate("BackgroundAttributeChangeDialog", "Parallax Layer", nullptr));
        layerSpeedLabel->setText(QCoreApplication::translate("BackgroundAttributeChangeDialog", "Layer Speed", nullptr));
    }  // retranslateUi
};

namespace Ui
{
    class BackgroundAttributeChangeDialog : public Ui_BackgroundAttributeChangeDialog
    {
    };
}  // namespace Ui

QT_END_NAMESPACE

#endif  // IMPORT_20_BACKGROUND_20__2D__20_UNTITLED_20_2OIPHGC_H
