#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "playback.h"

#include <QFileDialog>
#include <QMouseEvent>
#include <QTimer>
#include <QDebug>

#include <QGraphicsVideoItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSimpleTextItem>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QLabel>


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

    player = new QMediaPlayer;
    audio = new QAudioOutput;
    graphics = new QGraphicsView;
    scene = new QGraphicsScene;
    video = new QGraphicsVideoItem;
    subtitles = new QGraphicsSimpleTextItem("Meow");

    graphics -> setScene(scene);

    player -> setAudioOutput(audio);
    player -> setVideoOutput(video);

    const QSize screenGeometry = screen()->availableSize();
    video->setSize(QSizeF(screenGeometry.width() / 1.5, screenGeometry.height() / 1.25));

    scene -> addItem(video);

    subtitles -> setPos(100, 100);
    scene -> addItem(subtitles);
    subtitles -> setZValue(1);



    setCentralWidget(graphics);

    //connect(graphics, &QGraphicsView::resized, this, &MainWindow::resize);

    audio -> setVolume(0.2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::checkMousePosition() {
    QPoint currentPos = QCursor::pos();

    if (currentPos != lastMousePos) {
        qInfo() << currentPos;
        lastMousePos = currentPos;
    }
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

