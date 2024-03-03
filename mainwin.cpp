#include "mainwin.h"
#include "ui_mainwin.h"
#include "interface.h"

#include <QFileDialog>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QTimer>
#include <QDebug>

Mainwin::Mainwin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Mainwin)
{
    ui->setupUi(this);

    setMouseTracking(true); // Enable mouse tracking for the widget

    // Set up a timer to check mouse position periodically
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Mainwin::checkMousePosition);
    timer -> start(10);

    playback = new Playback(this); // Create a playback instance
    interface = new Interface(this);

    QVBoxLayout *l1 = new QVBoxLayout(this);
    QVBoxLayout *l2 = new QVBoxLayout(this);

    l1 -> addWidget(playback);
    l2 -> addWidget(interface);

    interface -> raise();

    connect(this, &Mainwin::mediaFiles, playback, &Playback::mediaPlayback); // Send file location to the playback function
}

Mainwin::~Mainwin()
{
    delete ui;
}

void Mainwin::checkMousePosition()
{
    QPoint currentPos = QCursor::pos();

    if (currentPos != lastMousePos) {
        qInfo() << currentPos;
        lastMousePos = currentPos;
    }
}

void Mainwin::on_actionOpen_triggered()
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
