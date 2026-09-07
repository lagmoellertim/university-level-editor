#include "UI/MainWindow.hpp"
#include <QApplication>

/// Level editor.
int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    LevelManager levelManager;

    MainWindow mainWindow(levelManager);

    mainWindow.show();

    return app.exec();
}