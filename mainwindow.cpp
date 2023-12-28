#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "centralwidget.h"

#include <QFileDialog>
#include <QAudioOutput>
#include <QAudioFormat>
#include <QMouseEvent>
#include <QLabel>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui -> setupUi(this);

    connect(ui -> centralwidget, SIGNAL(Move()), this, SLOT(Mouse_movement()));

    player = new QMediaPlayer;
    video = new QVideoWidget;
    audio = new QAudioOutput;

    //connect(audio, SIGNAL(stateChanged(QAudio::State)), this, SLOT(handleStateChanged(QAudio::State)));

    player -> setVideoOutput(video);
    player -> setAudioOutput(audio);

    audio -> setVolume(0.1);

    setCentralWidget(video);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setNameFilter(tr("Video Files (*.mp4 *.mov)"));
    dialog.setViewMode(QFileDialog::Detail);

    QStringList files;

    if(dialog.exec()) {
        files = dialog.selectedFiles();
    }

    player -> setSource(QUrl::fromLocalFile(files[0]));

    player -> play();
}

/*void MainWindow::mouseMoveEvent(QMouseEvent* event) {
    qDebug() << event -> pos();
}
