/********************************************************************************
** Form generated from reading UI file 'ui_item_previewQfyFSD.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ITEM_PREVIEWQFYFSD_H
#define UI_ITEM_PREVIEWQFYFSD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ItemPreview
{
public:
    QGridLayout* gridLayout;
    QGraphicsView* view;

    void setupUi(QWidget* ItemPreview)
    {
        if (ItemPreview->objectName().isEmpty())
            ItemPreview->setObjectName(QString::fromUtf8("ItemPreview"));
        ItemPreview->resize(332, 332);
        gridLayout = new QGridLayout(ItemPreview);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        view = new QGraphicsView(ItemPreview);
        view->setObjectName(QString::fromUtf8("view"));
        view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        gridLayout->addWidget(view, 0, 0, 1, 1);


        retranslateUi(ItemPreview);

        QMetaObject::connectSlotsByName(ItemPreview);
    }  // setupUi

    void retranslateUi(QWidget* ItemPreview)
    {
        ItemPreview->setWindowTitle(QApplication::translate("ItemPreview", "Form", nullptr));
    }  // retranslateUi
};

namespace Ui
{
    class ItemPreview : public Ui_ItemPreview
    {
    };
}  // namespace Ui

QT_END_NAMESPACE

#endif  // UI_ITEM_PREVIEWQFYFSD_H
