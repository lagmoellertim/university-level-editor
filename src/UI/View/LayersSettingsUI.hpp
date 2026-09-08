/********************************************************************************
** Form generated from reading UI file 'ui_preview_and_layersbwacUI.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREVIEW_AND_LAYERSBWACUI_H
#define UI_PREVIEW_AND_LAYERSBWACUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LayersSettings
{
public:
    QVBoxLayout* verticalLayout_4;
    QScrollArea* scrollArea_3;
    QWidget* scrollAreaWidgetContents_3;
    QVBoxLayout* verticalLayout;
    QListWidget* layerList;
    QScrollArea* scrollArea_2;
    QWidget* scrollAreaWidgetContents_2;
    QVBoxLayout* verticalLayout_2;
    QListWidget* backgroundsList;
    QPushButton* pushButton;

    void setupUi(QWidget* LayersSettings)
    {
        if (LayersSettings->objectName().isEmpty())
            LayersSettings->setObjectName(QString::fromUtf8("LayersSettings"));
        LayersSettings->resize(332, 694);
        verticalLayout_4 = new QVBoxLayout(LayersSettings);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        scrollArea_3 = new QScrollArea(LayersSettings);
        scrollArea_3->setObjectName(QString::fromUtf8("scrollArea_3"));
        scrollArea_3->setMaximumSize(QSize(16777215, 120));
        scrollArea_3->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 312, 88));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents_3);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        layerList = new QListWidget(scrollAreaWidgetContents_3);
        layerList->setObjectName(QString::fromUtf8("layerList"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(layerList->sizePolicy().hasHeightForWidth());
        layerList->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(layerList);

        scrollArea_3->setWidget(scrollAreaWidgetContents_3);

        verticalLayout_4->addWidget(scrollArea_3);

        scrollArea_2 = new QScrollArea(LayersSettings);
        scrollArea_2->setObjectName(QString::fromUtf8("scrollArea_2"));
        scrollArea_2->setMaximumSize(QSize(16777215, 16777215));
        scrollArea_2->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 312, 547));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        backgroundsList = new QListWidget(scrollAreaWidgetContents_2);
        backgroundsList->setObjectName(QString::fromUtf8("backgroundsList"));

        verticalLayout_2->addWidget(backgroundsList);

        scrollArea_2->setWidget(scrollAreaWidgetContents_2);

        verticalLayout_4->addWidget(scrollArea_2);

        pushButton = new QPushButton(LayersSettings);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout_4->addWidget(pushButton);


        retranslateUi(LayersSettings);

        QMetaObject::connectSlotsByName(LayersSettings);
    }  // setupUi

    void retranslateUi(QWidget* LayersSettings)
    {
        LayersSettings->setWindowTitle(QCoreApplication::translate("LayersSettings", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("LayersSettings", "Add Background", nullptr));
    }  // retranslateUi
};

namespace Ui
{
    class LayersSettings : public Ui_LayersSettings
    {
    };
}  // namespace Ui

QT_END_NAMESPACE

#endif  // UI_PREVIEW_AND_LAYERSBWACUI_H
