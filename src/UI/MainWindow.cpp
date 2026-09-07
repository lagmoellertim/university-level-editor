#include "MainWindow.hpp"
#include "../Lib/AssetImport/AssetImport.hpp"
#include "../Lib/HDF5/Exceptions.hpp"
#include "Dialog/ImportSoundDialog.hpp"
#include "Dialog/SoundEditDialog.hpp"
#include <QFile>
#include <QFileInfo>
#include <QScreen>


MainWindow::MainWindow(LevelManager& LevelManager)
    : m_levelManager(LevelManager)
{
    m_mainWindowUi.setupUi(this);
    if (auto* scr = screen())
    {
        resize(scr->availableGeometry().size() * 0.7);
    }
    else
    {
        resize(1024, 768);
    }

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
#ifdef __EMSCRIPTEN__
    QFileDialog::getOpenFileContent(tr("WAV (*.wav)"),
        [this](const QString &fileName, const QByteArray &fileContent) {
            if (fileName.isEmpty() || fileContent.isEmpty() || !fileName.endsWith(".wav", Qt::CaseInsensitive)) {
                return;
            }
            std::vector<std::string> soundList;
            for (Sound* sound : m_levelManager.getSounds())
            {
                soundList.push_back(sound->getID());
            }

            auto* dialog = new ImportSoundDialog(soundList, this);
            dialog->setAttribute(Qt::WA_DeleteOnClose);
            QString baseName = QFileInfo(fileName).completeBaseName();
            if (!baseName.isEmpty()) {
                dialog->setSuggestedID(baseName);
            }

            connect(dialog, &QDialog::accepted, this, [this, dialog, fileContent]() {
                Sound* sound = new Sound(dialog->getID(), fileContent);
                m_levelManager.addSound(sound);
            });
            dialog->open();
        });
#else
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
#endif
}

void MainWindow::handleManageSounds()
{
    SoundEditDialog dialog(m_levelManager, this);
    if (dialog.exec() == QDialog::Accepted)
    {
        m_levelManager.setSounds(dialog.getSounds());
    }
}


void MainWindow::handleSave()
{
#ifdef __EMSCRIPTEN__
    std::string tempFile = "/tmp/export.h5";
    try
    {
        m_levelManager.save(tempFile);
        QFile file(QString::fromStdString(tempFile));
        if (file.open(QIODevice::ReadOnly))
        {
            QByteArray data = file.readAll();
            file.close();
            QFileDialog::saveFileContent(data, "level.h5");
        }
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
#else
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                    "",
                                                    tr("Game-Resource-File (*.h5)"));

    if (fileName != "")
    {
        std::string newFileName = fileName.toStdString();

        if (!fileName.endsWith(".h5"))
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
#endif
}

void MainWindow::handleLoadExtend()
{
#ifdef __EMSCRIPTEN__
    QFileDialog::getOpenFileContent(tr("Game-Resource-File (*.h5);;All files (*)"),
        [this](const QString &fileName, const QByteArray &fileContent) {
            if (fileName.isEmpty() || fileContent.isEmpty()) {
                return;
            }
            std::string tempPath = "/tmp/import_extend.h5";
            QFile file(QString::fromStdString(tempPath));
            if (file.open(QIODevice::WriteOnly)) {
                file.write(fileContent);
                file.close();
                try {
                    m_levelManager.loadExtend(tempPath);
                }
                catch (HDF5::FileException& e) {
                    std::string message("An error has occurred while reading from the file.\n\nDescription:\n" + std::string(e.what()));
                    QMessageBox::critical(this, "Extend File Error", QString::fromStdString(message));
                }
                catch (HDF5::DataException& e) {
                    std::string message("An error related to the data parsing has occurred.\n\nDescription:\n" + std::string(e.what()));
                    QMessageBox::critical(this, "Extend Data Error", QString::fromStdString(message));
                }
            }
        });
#else
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
#endif
}

void MainWindow::handleLoad()
{
#ifdef __EMSCRIPTEN__
    QFileDialog::getOpenFileContent(tr("Game-Resource-File (*.h5);;All files (*)"),
        [this](const QString &fileName, const QByteArray &fileContent) {
            if (fileName.isEmpty() || fileContent.isEmpty()) {
                return;
            }
            std::string tempPath = "/tmp/import.h5";
            QFile file(QString::fromStdString(tempPath));
            if (file.open(QIODevice::WriteOnly)) {
                file.write(fileContent);
                file.close();
                try {
                    m_levelManager.load(tempPath);
                }
                catch (HDF5::FileException& e) {
                    std::string message("An error has occurred while reading from the file.\n\nDescription:\n" + std::string(e.what()));
                    QMessageBox::critical(this, "Load File Error", QString::fromStdString(message));
                }
                catch (HDF5::DataException& e) {
                    std::string message("An error related to the data parsing has occurred.\n\nDescription:\n" + std::string(e.what()));
                    QMessageBox::critical(this, "Load Data Error", QString::fromStdString(message));
                }
            }
        });
#else
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
#endif
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
