/********************************************************************************
** Form generated from reading UI file 'designerHSPyTM.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef DESIGNERHSPYTM_H
#define DESIGNERHSPYTM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QGridLayout* gridLayout;
    QFormLayout* formLayout;
    QLabel* widthLabel;
    QLabel* heightLabel;
    QSpinBox* widthInput;
    QSpinBox* heightInput;
    QDialogButtonBox* buttonBox;

    void setupUi(QDialog* Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(288, 152);
        gridLayout = new QGridLayout(Dialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        widthLabel = new QLabel(Dialog);
        widthLabel->setObjectName(QString::fromUtf8("widthLabel"));
        widthLabel->setMargin(5);

        formLayout->setWidget(0, QFormLayout::LabelRole, widthLabel);

        heightLabel = new QLabel(Dialog);
        heightLabel->setObjectName(QString::fromUtf8("heightLabel"));
        heightLabel->setMargin(5);

        formLayout->setWidget(1, QFormLayout::LabelRole, heightLabel);

        widthInput = new QSpinBox(Dialog);
        widthInput->setObjectName(QString::fromUtf8("widthInput"));
        widthInput->setMinimum(1);
        widthInput->setMaximum(999999);

        formLayout->setWidget(0, QFormLayout::FieldRole, widthInput);

        heightInput = new QSpinBox(Dialog);
        heightInput->setObjectName(QString::fromUtf8("heightInput"));
        heightInput->setMinimum(1);
        heightInput->setMaximum(999999);

        formLayout->setWidget(1, QFormLayout::FieldRole, heightInput);


        gridLayout->addLayout(formLayout, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(Dialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(Dialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog);
    }  // setupUi

    void retranslateUi(QDialog* Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Change Level Size", nullptr));
        widthLabel->setText(QCoreApplication::translate("Dialog", "Level Width", nullptr));
        heightLabel->setText(QCoreApplication::translate("Dialog", "Level Height", nullptr));
    }  // retranslateUi
};

namespace Ui
{
    class Dialog : public Ui_Dialog
    {
    };
}  // namespace Ui

QT_END_NAMESPACE

#endif  // DESIGNERHSPYTM_H
