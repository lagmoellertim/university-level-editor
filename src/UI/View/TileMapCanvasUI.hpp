/********************************************************************************
** Form generated from reading UI file 'ui_level_editor_tilemapmEjNjY.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LEVEL_EDITOR_TILEMAPMEJNJY_H
#define UI_LEVEL_EDITOR_TILEMAPMEJNJY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TileMapCanvas
{
public:
    QGridLayout* gridLayout;

    void setupUi(QWidget* TileMapCanvas)
    {
        if (TileMapCanvas->objectName().isEmpty())
            TileMapCanvas->setObjectName(QString::fromUtf8("TileMapCanvas"));
        TileMapCanvas->resize(511, 406);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TileMapCanvas->sizePolicy().hasHeightForWidth());
        TileMapCanvas->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(TileMapCanvas);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

        retranslateUi(TileMapCanvas);

        QMetaObject::connectSlotsByName(TileMapCanvas);
    }  // setupUi

    void retranslateUi(QWidget* TileMapCanvas)
    {
        TileMapCanvas->setWindowTitle(QCoreApplication::translate("TileMapCanvas", "Form", nullptr));
    }  // retranslateUi
};

namespace Ui
{
    class TileMapCanvas : public Ui_TileMapCanvas
    {
    };
}  // namespace Ui

QT_END_NAMESPACE

#endif  // UI_LEVEL_EDITOR_TILEMAPMEJNJY_H
