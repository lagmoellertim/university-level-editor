#include "MainWindow.hpp"
#include "../Lib/AssetImport/AssetImport.hpp"
#include "../Lib/HDF5/Exceptions.hpp"
#include "Dialog/SoundEditDialog.hpp"
#include <boost/algorithm/string/predicate.hpp>


MainWindow::MainWindow(LevelManager& LevelManager)
    : m_levelManager(LevelManager)
{
    m_mainWindowUi.setupUi(this);
    resize(QDesktopWidget().availableGeometry(this).size() * 0.7);

    m_toolBar = new ToolBar(m_levelManager, this);
    m_tileMapCanvas = new CanvasWidget(m_levelManager, this);
    m_layersSettings = new LayersSettingsWidget(m_levelManager, this);
    m_itemPreview = new ItemPreviewWidget(m_levelManager, this);
    m_rightBar = new QSplitter(this);

    m_rightBar->setOrientation(Qt::Vertical);
    m_rightBar->addWidget(m_itemPreview);
    m_rightBar->addWidget(m_layersSettings);

    m_splitter.addWidget(m_toolBar);
    m_splitter.addWidget(m_tileMapCanvas);
    m_splitter.addWidget(m_rightBar);
    m_splitter.setSizes(QList<int>() << 100 << 500 << 100);

    m_mainWindowUi.mainContainer->addWidget(&m_splitter);

    connect(m_mainWindowUi.actionOpen, &QAction::triggered, this, &MainWindow::handleLoad);
    connect(m_mainWindowUi.actionExtend, &QAction::triggered, this, &MainWindow::handleLoadExtend);
    connect(m_mainWindowUi.actionSave, &QAction::triggered, this, &MainWindow::handleSave);

    connect(m_mainWindowUi.actionImportSound, &QAction::triggered, this, &MainWindow::handleImportSound);
    connect(m_mainWindowUi.actionManageSounds, &QAction::triggered, this, &MainWindow::handleManageSounds);

    connect(&m_levelManager, &LevelManager::selectedLevelMetadataChanged, this, &MainWindow::updateWindowTitle);
    connect(&m_levelManager, &LevelManager::levelSelectionChanged, this, &MainWindow::updateWindowTitle);

    updateWindowTitle();
}


MainWindow::~MainWindow()
{
    delete m_toolBar;
    delete m_tileMapCanvas;
    delete m_layersSettings;
    delete m_itemPreview;
    delete m_rightBar;
}

void MainWindow::handleImportSound()
{
    // Create List of all entries to parse in importSound Function
    std::vector<std::string> soundList;
    for (Sound* sound : m_levelManager.getSounds())
    {
        soundList.push_back(sound->getID());
    }

    Sound* sound = AssetImport::importSound(soundList, this);
    if (sound != nullptr)
    {
        m_levelManager.addSound(sound);
    }
}

void MainWindow::handleManageSounds()
{
    SoundEditDialog dialog(m_levelManager);
    dialog.setModal(true);
    dialog.show();

    if (dialog.exec())
    {
        m_levelManager.setSounds(dialog.getSounds());
    }
}

void MainWindow::handleSave()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                    "",
                                                    tr("Game-Resource-File (*.h5)"));

    if (fileName != "")
    {
        std::string newFileName = fileName.toStdString();

        if (!boost::algorithm::ends_with(newFileName, ".h5"))
        {
            newFileName += ".h5";
        }

        try
        {
            m_levelManager.save(newFileName);
        }
        catch (HDF5::FileException& e)
        {
            std::string message("An error has occurred while writing to the file.\n\nDescription:\n" + std::string(e.what()));
            QMessageBox::critical(this, "File Error", QString::fromStdString(message));
        }
        catch (HDF5::DataException& e)
        {
            std::string message("An error related to the data parsing has occurred.\n\nDescription:\n" + std::string(e.what()));
            QMessageBox::critical(this, "Data Error", QString::fromStdString(message));
        }
    }
}

void MainWindow::handleLoadExtend()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "",
                                                    tr("Game-Resource-File (*.h5)"));

    if (fileName != "")
    {
        try
        {
            m_levelManager.loadExtend(fileName.toStdString());
        }
        catch (HDF5::FileException& e)
        {
            std::string message("An error has occurred while reading from the file.\n\nDescription:\n" + std::string(e.what()));
            QMessageBox::critical(this, "Extend File Error", QString::fromStdString(message));
        }
        catch (HDF5::DataException& e)
        {
            std::string message("An error related to the data parsing has occurred.\n\nDescription:\n" + std::string(e.what()));
            QMessageBox::critical(this, "Extend Data Error", QString::fromStdString(message));
        }
    }
}

void MainWindow::handleLoad()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "",
                                                    tr("Game-Resource-File (*.h5)"));

    if (fileName != "")
    {
        try
        {
            m_levelManager.load(fileName.toStdString());
        }
        catch (HDF5::FileException& e)
        {
            std::string message("An error has occurred while reading from the file.\n\nDescription:\n" + std::string(e.what()));
            QMessageBox::critical(this, "Load File Error", QString::fromStdString(message));
        }
        catch (HDF5::DataException& e)
        {
            std::string message("An error related to the data parsing has occurred.\n\nDescription:\n" + std::string(e.what()));
            QMessageBox::critical(this, "Load Data Error", QString::fromStdString(message));
        }
    }
}

void MainWindow::updateWindowTitle()
{
    if (m_levelManager.getSelectedLevel())
    {
        setWindowTitle(QString::fromStdString("Level " + m_levelManager.getSelectedLevel()->getLevelName() + " - LevelEditor"));
    }
    else
    {
        setWindowTitle(QString::fromStdString("LevelEditor"));
    }
}
