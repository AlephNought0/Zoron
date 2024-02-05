#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "interface.h"

#include <QFileDialog>
#include <QMouseEvent>
#include <QTimer>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui -> setupUi(this);

    setMouseTracking(true); // Enable mouse tracking for the widget

    // Set up a timer to check mouse position periodically
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::checkMousePosition);
    timer -> start(10);

    playback = new Playback; // Create a playback instance
    interface = new Interface;

    QVBoxLayout *stackedLayout = new QVBoxLayout;
    stackedLayout->addWidget(playback); // Add the Playback widget to the layout
    stackedLayout->addWidget(interface); // Add the InterfaceItem widget to the layout

    // Create a widget to hold the stacked layout
    QWidget *stackedWidget = new QWidget;
    stackedWidget->setLayout(stackedLayout);

    // Set the stacked widget as the central widget
    setCentralWidget(stackedWidget);

    // Initially, show the Playback widget
    interface->hide();

    //setCentralWidget(playback);

    connect(this, &MainWindow::mediaFiles, playback, &Playback::mediaPlayback); // Send file location to the playback function
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::checkMousePosition()
{
    QPoint currentPos = QCursor::pos();

    if (currentPos != lastMousePos) {
        qInfo() << currentPos;
        lastMousePos = currentPos;
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setNameFilter(tr("Video Files (*.mp4 *.mov)"));
    dialog.setViewMode(QFileDialog::Detail);

    QStringList files;

    if(dialog.exec()) {
        files = dialog.selectedFiles();
    }

    emit mediaFiles(files);
}
