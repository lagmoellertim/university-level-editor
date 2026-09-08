/********************************************************************************
** Form generated from reading UI file 'sound_edit_dialogPRfAZy.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef SOUND_EDIT_DIALOGPRFAZY_H
#define SOUND_EDIT_DIALOGPRFAZY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SoundEditDialog
{
public:
    QVBoxLayout* verticalLayout;
    QScrollArea* scrollArea;
    QWidget* scrollAreaWidgetContents;
    QVBoxLayout* verticalLayout_2;
    QListWidget* soundListView;
    QHBoxLayout* horizontalLayout_2;
    QPushButton* playButton;
    QPushButton* addSoundButton;
    QSpacerItem* verticalSpacer;
    QDialogButtonBox* buttonBox;

    void setupUi(QDialog* SoundEditDialog)
    {
        if (SoundEditDialog->objectName().isEmpty())
            SoundEditDialog->setObjectName(QString::fromUtf8("SoundEditDialog"));
        SoundEditDialog->resize(494, 406);
        verticalLayout = new QVBoxLayout(SoundEditDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        scrollArea = new QScrollArea(SoundEditDialog);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 474, 276));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        soundListView = new QListWidget(scrollAreaWidgetContents);
        soundListView->setObjectName(QString::fromUtf8("soundListView"));

        verticalLayout_2->addWidget(soundListView);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        playButton = new QPushButton(SoundEditDialog);
        playButton->setObjectName(QString::fromUtf8("playButton"));

        horizontalLayout_2->addWidget(playButton);

        addSoundButton = new QPushButton(SoundEditDialog);
        addSoundButton->setObjectName(QString::fromUtf8("addSoundButton"));

        horizontalLayout_2->addWidget(addSoundButton);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer);

        buttonBox = new QDialogButtonBox(SoundEditDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(SoundEditDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SoundEditDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SoundEditDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SoundEditDialog);
    }  // setupUi

    void retranslateUi(QDialog* SoundEditDialog)
    {
        SoundEditDialog->setWindowTitle(QApplication::translate("SoundEditDialog", "Dialog", nullptr));
        playButton->setText(QApplication::translate("SoundEditDialog", "Play", nullptr));
        addSoundButton->setText(QApplication::translate("SoundEditDialog", "Add Sound", nullptr));
    }  // retranslateUi
};

namespace Ui
{
    class SoundEditDialog : public Ui_SoundEditDialog
    {
    };
}  // namespace Ui

QT_END_NAMESPACE

#endif  // SOUND_EDIT_DIALOGPRFAZY_H