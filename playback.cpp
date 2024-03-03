#include "playback.h"

#include <QWidget>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QGraphicsVideoItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSimpleTextItem>
#include <QVBoxLayout>
#include <QMouseEvent>

Playback::Playback(QWidget *parent)
    : QWidget{parent}
{
    player = new QMediaPlayer;
    audio = new QAudioOutput;
    graphics = new QGraphicsView;
    scene = new QGraphicsScene;
    video = new QGraphicsVideoItem;
    //subtitles = new QGraphicsSimpleTextItem("Meow");
    //subtitles -> setPos(100, 100);
    //subtitles -> setZValue(1); // Set subtitles to be above video

    graphics -> setScene(scene); // Set graphic scene

    player -> setAudioOutput(audio);
    player -> setVideoOutput(video);

    scene -> addItem(video);
    //scene -> addItem(subtitles);

    audio -> setVolume(0.2);

    QVBoxLayout *layout = new QVBoxLayout;
    layout -> addWidget(graphics);
    layout -> setContentsMargins(0, 0, 0, 0);
    setLayout(layout);
}

void Playback::mousePressEvent(QMouseEvent *event)
{
    if (event -> button() == Qt::LeftButton) {

        if (player -> playbackState() == QMediaPlayer::PlayingState) {
            player -> pause();
        }

        else {
            player -> play();
        }
    }
}

void Playback::resizeEvent(QResizeEvent *event) // Resize event so the QGraphicsView fits into the viewport
{
    QWidget::resizeEvent(event);

    graphics -> fitInView(scene -> sceneRect(), Qt::KeepAspectRatio);
}

void Playback::mediaPlayback(QStringList &files)
{
    player -> setSource(QUrl::fromLocalFile(files[0]));

    player -> play();
}
