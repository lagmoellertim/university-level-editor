/********************************************************************************
** Form generated from reading UI file 'designerMRFYSS.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef DESIGNERMRFYSS_H
#define DESIGNERMRFYSS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_ImportSoundDialog
{
public:
    QGridLayout* gridLayout;
    QFormLayout* formLayout;
    QLabel* soundIDLabel;
    QLineEdit* soundIDInput;
    QDialogButtonBox* buttonBox;

    void setupUi(QDialog* ImportSoundDialog)
    {
        if (ImportSoundDialog->objectName().isEmpty())
            ImportSoundDialog->setObjectName(QString::fromUtf8("ImportSoundDialog"));
        ImportSoundDialog->resize(206, 107);
        gridLayout = new QGridLayout(ImportSoundDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        soundIDLabel = new QLabel(ImportSoundDialog);
        soundIDLabel->setObjectName(QString::fromUtf8("soundIDLabel"));
        soundIDLabel->setMargin(5);

        formLayout->setWidget(0, QFormLayout::LabelRole, soundIDLabel);

        soundIDInput = new QLineEdit(ImportSoundDialog);
        soundIDInput->setObjectName(QString::fromUtf8("soundIDInput"));

        formLayout->setWidget(0, QFormLayout::FieldRole, soundIDInput);


        gridLayout->addLayout(formLayout, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(ImportSoundDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(ImportSoundDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ImportSoundDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ImportSoundDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ImportSoundDialog);
    }  // setupUi

    void retranslateUi(QDialog* ImportSoundDialog)
    {
        ImportSoundDialog->setWindowTitle(QCoreApplication::translate("ImportSoundDialog", "Import Sound", nullptr));
        soundIDLabel->setText(QCoreApplication::translate("ImportSoundDialog", "Sound ID", nullptr));
    }  // retranslateUi
};

namespace Ui
{
    class ImportSoundDialog : public Ui_ImportSoundDialog
    {
    };
}  // namespace Ui

QT_END_NAMESPACE

#endif  // DESIGNERMRFYSS_H
