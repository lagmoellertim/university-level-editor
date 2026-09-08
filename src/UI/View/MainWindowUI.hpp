/********************************************************************************
** Form generated from reading UI file 'ui_main_windowDTdCdz.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_WINDOWDTDCDZ_H
#define UI_MAIN_WINDOWDTDCDZ_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction* actionSave;
    QAction* actionOpen;
    QAction* actionImportSound;
    QAction* actionManageSounds;
    QAction* actionExtend;
    QWidget* centralwidget;
    QHBoxLayout* horizontalLayout;
    QHBoxLayout* mainContainer;
    QMenuBar* menubar;
    QMenu* menuFile;
    QMenu* menuSound;
    QStatusBar* statusbar;

    void setupUi(QMainWindow* MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(949, 475);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionImportSound = new QAction(MainWindow);
        actionImportSound->setObjectName(QString::fromUtf8("actionImportSound"));
        actionManageSounds = new QAction(MainWindow);
        actionManageSounds->setObjectName(QString::fromUtf8("actionManageSounds"));
        actionExtend = new QAction(MainWindow);
        actionExtend->setObjectName(QString::fromUtf8("actionExtend"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        mainContainer = new QHBoxLayout();
        mainContainer->setObjectName(QString::fromUtf8("mainContainer"));

        horizontalLayout->addLayout(mainContainer);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 949, 28));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuSound = new QMenu(menubar);
        menuSound->setObjectName(QString::fromUtf8("menuSound"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuSound->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionExtend);
        menuFile->addAction(actionSave);
        menuSound->addAction(actionImportSound);
        menuSound->addAction(actionManageSounds);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    }  // setupUi

    void retranslateUi(QMainWindow* MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
#if QT_CONFIG(shortcut)
        actionSave->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif  // QT_CONFIG(shortcut)
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
#if QT_CONFIG(shortcut)
        actionOpen->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif  // QT_CONFIG(shortcut)
        actionImportSound->setText(QCoreApplication::translate("MainWindow", "Import Sound", nullptr));
        actionManageSounds->setText(QCoreApplication::translate("MainWindow", "Manage Sounds", nullptr));
        actionExtend->setText(QCoreApplication::translate("MainWindow", "Extend", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuSound->setTitle(QCoreApplication::translate("MainWindow", "Sound", nullptr));
    }  // retranslateUi
};

namespace Ui
{
    class MainWindow : public Ui_MainWindow
    {
    };
}  // namespace Ui

QT_END_NAMESPACE

#endif  // UI_MAIN_WINDOWDTDCDZ_H
