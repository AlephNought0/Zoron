#include "playback.h"

#include <QScreen>
#include <QGraphicsVideoItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSimpleTextItem>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QLabel>
#include <QVBoxLayout>

#include <QCoreApplication>

#include <QTimer>

Playback::Playback(QWidget *parent)
    : QWidget{parent}
{
    player = new QMediaPlayer;
    audio = new QAudioOutput;
    graphics = new QGraphicsView;
    scene = new QGraphicsScene;
    video = new QGraphicsVideoItem;
    //subtitles = new QGraphicsSimpleTextItem("Meow");

    graphics -> setScene(scene); // Set graphic scene

    player -> setAudioOutput(audio);
    player -> setVideoOutput(video);

    //subtitles -> setPos(100, 100);
    //subtitles -> setZValue(1); // Set subtitles to be above video

    scene -> addItem(video);
    //scene -> addItem(subtitles);

    audio -> setVolume(0.2);

    QVBoxLayout *layout = new QVBoxLayout;
    layout -> addWidget(graphics);
    setLayout(layout);
}

void Playback::resizeEvent(QResizeEvent *event) // Resize event so the video has the viewport size
{
    QWidget::resizeEvent(event);

    graphics -> fitInView(scene -> sceneRect(), Qt::KeepAspectRatio);
}

void Playback::mediaPlayback(QStringList &files)
{
    player -> setSource(QUrl::fromLocalFile(files[0]));

    player -> play();

    QTimer::singleShot(100, this, [=]() { // Set graphics to fit the view right after the video starts playing
        graphics -> fitInView(scene -> sceneRect(), Qt::KeepAspectRatio);
    });
}
