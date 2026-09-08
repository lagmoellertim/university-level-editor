/********************************************************************************
** Form generated from reading UI file 'toolbarmxuICq.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef TOOLBARMXUICQ_H
#define TOOLBARMXUICQ_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Toolbar
{
public:
    QVBoxLayout* verticalLayout;
    QScrollArea* scrollArea_2;
    QWidget* scrollAreaWidgetContents_2;
    QVBoxLayout* verticalLayout_2;
    QListWidget* levelListView;
    QPushButton* newLevelButton;
    QScrollArea* scrollArea;
    QWidget* scrollAreaWidgetContents;
    QVBoxLayout* verticalLayout_3;
    QGraphicsView* itemSetView;
    QPushButton* eraserButton;
    QHBoxLayout* horizontalLayout;
    QPushButton* addItemSetButton;
    QPushButton* clearItemSetButton;

    void setupUi(QWidget* Toolbar)
    {
        if (Toolbar->objectName().isEmpty())
            Toolbar->setObjectName(QString::fromUtf8("Toolbar"));
        Toolbar->resize(332, 694);
        verticalLayout = new QVBoxLayout(Toolbar);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        scrollArea_2 = new QScrollArea(Toolbar);
        scrollArea_2->setObjectName(QString::fromUtf8("scrollArea_2"));
        scrollArea_2->setMaximumSize(QSize(16777215, 150));
        scrollArea_2->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 312, 148));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        levelListView = new QListWidget(scrollAreaWidgetContents_2);
        levelListView->setObjectName(QString::fromUtf8("levelListView"));

        verticalLayout_2->addWidget(levelListView);

        scrollArea_2->setWidget(scrollAreaWidgetContents_2);

        verticalLayout->addWidget(scrollArea_2);

        newLevelButton = new QPushButton(Toolbar);
        newLevelButton->setObjectName(QString::fromUtf8("newLevelButton"));

        verticalLayout->addWidget(newLevelButton);

        scrollArea = new QScrollArea(Toolbar);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 312, 423));
        verticalLayout_3 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        itemSetView = new QGraphicsView(scrollAreaWidgetContents);
        itemSetView->setObjectName(QString::fromUtf8("itemSetView"));

        verticalLayout_3->addWidget(itemSetView);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        eraserButton = new QPushButton(Toolbar);
        eraserButton->setObjectName(QString::fromUtf8("eraserButton"));

        verticalLayout->addWidget(eraserButton);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        addItemSetButton = new QPushButton(Toolbar);
        addItemSetButton->setObjectName(QString::fromUtf8("addItemSetButton"));

        horizontalLayout->addWidget(addItemSetButton);

        clearItemSetButton = new QPushButton(Toolbar);
        clearItemSetButton->setObjectName(QString::fromUtf8("clearItemSetButton"));

        horizontalLayout->addWidget(clearItemSetButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(Toolbar);

        QMetaObject::connectSlotsByName(Toolbar);
    }  // setupUi

    void retranslateUi(QWidget* Toolbar)
    {
        Toolbar->setWindowTitle(QApplication::translate("Toolbar", "Form", nullptr));
        newLevelButton->setText(QApplication::translate("Toolbar", "New Level", nullptr));
        eraserButton->setText(QApplication::translate("Toolbar", "Eraser", nullptr));
        addItemSetButton->setText(QApplication::translate("Toolbar", "Add TileSet", nullptr));
        clearItemSetButton->setText(QApplication::translate("Toolbar", "Clear TileSet", nullptr));
    }  // retranslateUi
};

namespace Ui
{
    class Toolbar : public Ui_Toolbar
    {
    };
}  // namespace Ui

QT_END_NAMESPACE

#endif  // TOOLBARMXUICQ_H
