#include "playback.h"
#include "customgraphicsview.h"

#include <QWidget>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QGraphicsVideoItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSimpleTextItem>

Playback::Playback(QWidget *parent)
    : QWidget{parent}
{
    player = new QMediaPlayer;
    audio = new QAudioOutput;
    graphics = new CustomGraphicsView;
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

    audio -> setVolume(0.1);

    QVBoxLayout *layout = new QVBoxLayout;
    layout -> addWidget(graphics);
    layout -> setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    graphics -> setViewportMargins(-2, -2, -2, -2); // QT please fix this. Explanation in customgraphicsview.h
    graphics -> setFrameStyle(QFrame::NoFrame);
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

    QRectF sceneRect = scene -> itemsBoundingRect();

    // Adjust the scene rectangle to maintain aspect ratio
    qreal aspectRatio = sceneRect.width() / sceneRect.height();
    qreal viewportAspectRatio = graphics -> viewport() -> width() / graphics -> viewport() -> height();

    if (aspectRatio > viewportAspectRatio) {
        // Scene is wider than viewport, adjust height
        qreal newHeight = sceneRect.width() / viewportAspectRatio;
        qreal heightDiff = newHeight - sceneRect.height();
        sceneRect.adjust(0, -heightDiff / 2, 0, heightDiff / 2);
    }

    else {
        // Scene is taller than viewport, adjust width
        qreal newWidth = sceneRect.height() * viewportAspectRatio;
        qreal widthDiff = newWidth - sceneRect.width();
        sceneRect.adjust(-widthDiff / 2, 0, widthDiff / 2, 0);
    }

    graphics -> fitInView(scene -> sceneRect(), Qt::KeepAspectRatio);
}

void Playback::showEvent(QShowEvent* event)
{
    if(!video)
        return;
   graphics -> fitInView(scene -> sceneRect(), Qt::KeepAspectRatio);
}

void Playback::mediaPlayback(QStringList &files)
{
    player -> setSource(QUrl::fromLocalFile(files[0]));

    player -> play();
}
