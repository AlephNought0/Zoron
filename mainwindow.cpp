#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include <QMouseEvent>
#include <QTimer>
#include <QDebug>
#include <QFlags>

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

    playback = new Playback(this);
    interface = new Interface(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout -> addWidget(interface);

    setCentralWidget(playback);

    connect(this, &MainWindow::mediaFiles, playback, &Playback::mediaPlayback); // Send file location to the playback function
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event) // Resize event to adjust the interface to the bottom
{
    QWidget::resizeEvent(event);

    interface -> move(0, height() - interface -> height());
    interface -> setFixedWidth(width());

    qInfo() << "Window: " << playback -> width();
}

void MainWindow::checkMousePosition()
{
    QPoint currentPos = QCursor::pos();

    if (currentPos != lastMousePos) {
        //qInfo() << currentPos;
        lastMousePos = currentPos;
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setNameFilter(tr("Video Files (*.mp4 *.mov *.mpv)"));
    dialog.setViewMode(QFileDialog::Detail);

    QStringList files;

    if(dialog.exec()) {
        files = dialog.selectedFiles();
    }

    emit mediaFiles(files);
}
