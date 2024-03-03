#include "mainwindow.h"
#include "./ui_mainwindow.h"

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

    ui -> centralwidget -> setLayout(new QVBoxLayout);

    playback = new Playback(this); // Create a playback instance
    interface = new Interface(this);

    QVBoxLayout *l1 = new QVBoxLayout(this);
    QVBoxLayout *l2 = new QVBoxLayout(this);

    l1 -> addWidget(playback);
    l2 -> addWidget(interface);

    interface -> raise();

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
