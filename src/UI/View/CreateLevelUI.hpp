/********************************************************************************
** Form generated from reading UI file 'create_level_dialogHcDRHV.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef CREATE_LEVEL_DIALOGHCDRHV_H
#define CREATE_LEVEL_DIALOGHCDRHV_H

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

class Ui_CreateLevelDialog
{
public:
    QGridLayout* gridLayout_2;
    QDialogButtonBox* buttonBox;
    QFormLayout* formLayout;
    QLabel* levelWidthLabel;
    QLabel* levelHeightLabel;
    QLabel* tileSizeLabel;
    QSpinBox* levelWidthInput;
    QSpinBox* levelHeightInput;
    QSpinBox* tileSizeInput;
    QLabel* levelNameLabel;
    QLineEdit* levelNameInput;

    void setupUi(QDialog* CreateLevelDialog)
    {
        if (CreateLevelDialog->objectName().isEmpty())
            CreateLevelDialog->setObjectName(QString::fromUtf8("CreateLevelDialog"));
        CreateLevelDialog->resize(268, 204);
        gridLayout_2 = new QGridLayout(CreateLevelDialog);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        buttonBox = new QDialogButtonBox(CreateLevelDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);

        gridLayout_2->addWidget(buttonBox, 1, 0, 1, 1);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        levelWidthLabel = new QLabel(CreateLevelDialog);
        levelWidthLabel->setObjectName(QString::fromUtf8("levelWidthLabel"));
        levelWidthLabel->setMargin(6);

        formLayout->setWidget(0, QFormLayout::LabelRole, levelWidthLabel);

        levelHeightLabel = new QLabel(CreateLevelDialog);
        levelHeightLabel->setObjectName(QString::fromUtf8("levelHeightLabel"));
        levelHeightLabel->setMargin(6);

        formLayout->setWidget(1, QFormLayout::LabelRole, levelHeightLabel);

        tileSizeLabel = new QLabel(CreateLevelDialog);
        tileSizeLabel->setObjectName(QString::fromUtf8("tileSizeLabel"));
        tileSizeLabel->setMargin(6);

        formLayout->setWidget(2, QFormLayout::LabelRole, tileSizeLabel);

        levelWidthInput = new QSpinBox(CreateLevelDialog);
        levelWidthInput->setObjectName(QString::fromUtf8("levelWidthInput"));
        levelWidthInput->setMinimum(1);
        levelWidthInput->setMaximum(10000);

        formLayout->setWidget(0, QFormLayout::FieldRole, levelWidthInput);

        levelHeightInput = new QSpinBox(CreateLevelDialog);
        levelHeightInput->setObjectName(QString::fromUtf8("levelHeightInput"));
        levelHeightInput->setMinimum(1);
        levelHeightInput->setMaximum(10000);

        formLayout->setWidget(1, QFormLayout::FieldRole, levelHeightInput);

        tileSizeInput = new QSpinBox(CreateLevelDialog);
        tileSizeInput->setObjectName(QString::fromUtf8("tileSizeInput"));
        tileSizeInput->setMinimum(1);
        tileSizeInput->setMaximum(10000);

        formLayout->setWidget(2, QFormLayout::FieldRole, tileSizeInput);

        levelNameLabel = new QLabel(CreateLevelDialog);
        levelNameLabel->setObjectName(QString::fromUtf8("levelNameLabel"));
        levelNameLabel->setMargin(6);

        formLayout->setWidget(3, QFormLayout::LabelRole, levelNameLabel);

        levelNameInput = new QLineEdit(CreateLevelDialog);
        levelNameInput->setObjectName(QString::fromUtf8("levelNameInput"));

        formLayout->setWidget(3, QFormLayout::FieldRole, levelNameInput);


        gridLayout_2->addLayout(formLayout, 0, 0, 1, 1);


        retranslateUi(CreateLevelDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), CreateLevelDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), CreateLevelDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(CreateLevelDialog);
    }  // setupUi

    void retranslateUi(QDialog* CreateLevelDialog)
    {
        CreateLevelDialog->setWindowTitle(QApplication::translate("CreateLevelDialog", "Dialog", nullptr));
        levelWidthLabel->setText(QApplication::translate("CreateLevelDialog", "Initial Level-Width:", nullptr));
        levelHeightLabel->setText(QApplication::translate("CreateLevelDialog", "Level-Height", nullptr));
        tileSizeLabel->setText(QApplication::translate("CreateLevelDialog", "Tile-Size", nullptr));
        levelNameLabel->setText(QApplication::translate("CreateLevelDialog", "Level-Name", nullptr));
    }  // retranslateUi
};

namespace Ui
{
    class CreateLevelDialog : public Ui_CreateLevelDialog
    {
    };
}  // namespace Ui

QT_END_NAMESPACE

#endif  // CREATE_LEVEL_DIALOGHCDRHV_H
