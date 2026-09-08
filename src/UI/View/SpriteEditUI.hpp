/********************************************************************************
** Form generated from reading UI file 'sprite_edit_dialogurkmsy.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef SPRITE_EDIT_DIALOGURKMSY_H
#define SPRITE_EDIT_DIALOGURKMSY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SpriteEditDialog
{
public:
    QVBoxLayout* verticalLayout;
    QScrollArea* scrollArea;
    QWidget* scrollAreaWidgetContents;
    QVBoxLayout* verticalLayout_2;
    QListWidget* modifierListView;
    QHBoxLayout* horizontalLayout;
    QLineEdit* modifierInput;
    QPushButton* addModifierButton;
    QSpacerItem* verticalSpacer;
    QHBoxLayout* horizontalLayout_2;
    QLabel* heightLabel;
    QSpinBox* heightInput;
    QHBoxLayout* horizontalLayout_3;
    QLabel* idLabel;
    QLineEdit* idInput;
    QSpacerItem* verticalSpacer_2;
    QCheckBox* isActorBox;
    QDialogButtonBox* buttonBox;

    void setupUi(QDialog* SpriteEditDialog)
    {
        if (SpriteEditDialog->objectName().isEmpty())
            SpriteEditDialog->setObjectName(QString::fromUtf8("SpriteEditDialog"));
        SpriteEditDialog->resize(470, 447);
        verticalLayout = new QVBoxLayout(SpriteEditDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        scrollArea = new QScrollArea(SpriteEditDialog);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 450, 195));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        modifierListView = new QListWidget(scrollAreaWidgetContents);
        modifierListView->setObjectName(QString::fromUtf8("modifierListView"));

        verticalLayout_2->addWidget(modifierListView);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        modifierInput = new QLineEdit(SpriteEditDialog);
        modifierInput->setObjectName(QString::fromUtf8("modifierInput"));

        horizontalLayout->addWidget(modifierInput);

        addModifierButton = new QPushButton(SpriteEditDialog);
        addModifierButton->setObjectName(QString::fromUtf8("addModifierButton"));

        horizontalLayout->addWidget(addModifierButton);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        heightLabel = new QLabel(SpriteEditDialog);
        heightLabel->setObjectName(QString::fromUtf8("heightLabel"));

        horizontalLayout_2->addWidget(heightLabel);

        heightInput = new QSpinBox(SpriteEditDialog);
        heightInput->setObjectName(QString::fromUtf8("heightInput"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(heightInput->sizePolicy().hasHeightForWidth());
        heightInput->setSizePolicy(sizePolicy);
        heightInput->setMinimum(1);
        heightInput->setMaximum(10000);

        horizontalLayout_2->addWidget(heightInput);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        idLabel = new QLabel(SpriteEditDialog);
        idLabel->setObjectName(QString::fromUtf8("idLabel"));

        horizontalLayout_3->addWidget(idLabel);

        idInput = new QLineEdit(SpriteEditDialog);
        idInput->setObjectName(QString::fromUtf8("idInput"));
        sizePolicy.setHeightForWidth(idInput->sizePolicy().hasHeightForWidth());
        idInput->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(idInput);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer_2 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer_2);

        isActorBox = new QCheckBox(SpriteEditDialog);
        isActorBox->setObjectName(QString::fromUtf8("isActorBox"));
        isActorBox->setContextMenuPolicy(Qt::DefaultContextMenu);

        verticalLayout->addWidget(isActorBox);

        buttonBox = new QDialogButtonBox(SpriteEditDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(SpriteEditDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SpriteEditDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SpriteEditDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SpriteEditDialog);
    }  // setupUi

    void retranslateUi(QDialog* SpriteEditDialog)
    {
        SpriteEditDialog->setWindowTitle(QApplication::translate("SpriteEditDialog", "Dialog", nullptr));
        addModifierButton->setText(QApplication::translate("SpriteEditDialog", "Add Modifier", nullptr));
        heightLabel->setText(QApplication::translate("SpriteEditDialog", "Sprite Height", nullptr));
        idLabel->setText(QApplication::translate("SpriteEditDialog", "Sprite ID", nullptr));
        isActorBox->setText(QApplication::translate("SpriteEditDialog", "Is Actor", nullptr));
    }  // retranslateUi
};

namespace Ui
{
    class SpriteEditDialog : public Ui_SpriteEditDialog
    {
    };
}  // namespace Ui

QT_END_NAMESPACE

#endif  // SPRITE_EDIT_DIALOGURKMSY_H
