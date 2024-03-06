#include "playback.h"

Playback::Playback(QWidget *parent)
    : QWidget{parent}
{
    interface = new Interface;

    m_mediaPlayer = MediaPlayer::instance() -> mediaPlayer();

    graphics = new CustomGraphicsView;
    scene = new QGraphicsScene;
    //subtitles = new QGraphicsSimpleTextItem("Meow");
    //subtitles -> setPos(100, 100);
    //subtitles -> setZValue(1); // Set subtitles to be above video

    graphics -> setScene(scene); // Set graphic scene

    audio = m_mediaPlayer -> audioOutput();
    video = qobject_cast<QGraphicsVideoItem*>(m_mediaPlayer -> videoOutput());

    scene -> addItem(video);
    //scene -> addItem(subtitles);

    audio -> setVolume(0.1);

    QVBoxLayout *layout = new QVBoxLayout;
    layout -> addWidget(graphics);
    layout -> setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    graphics -> setViewportMargins(-2, -2, -2, -2); // QT please fix this. Explanation in customgraphicsview.h
    graphics -> setFrameStyle(QFrame::NoFrame);

    connect(video, &QGraphicsVideoItem::nativeSizeChanged, this, &Playback::handleVideoNativeSizeChanged);
}

void Playback::mousePressEvent(QMouseEvent *event)
{
    if (event -> button() == Qt::LeftButton) {

        if (m_mediaPlayer -> playbackState() == QMediaPlayer::PlayingState) {
            m_mediaPlayer -> pause();
        }

        else {
            m_mediaPlayer -> play();
        }
    }
}

void Playback::resizeEvent(QResizeEvent *event) // Resize event so the QGraphicsView fits into the viewport
{
    QWidget::resizeEvent(event);

    graphics -> fitInView(scene -> sceneRect(), Qt::KeepAspectRatio);
}

void Playback::handleVideoNativeSizeChanged()
{
    QResizeEvent event(size(), size());
    scene -> setSceneRect(scene -> itemsBoundingRect());
    resizeEvent(&event);
}

void Playback::mediaPlayback(QStringList &files)
{
    if(files.isEmpty()) {
        return;
    }

    else {
        m_mediaPlayer -> setSource(QUrl::fromLocalFile(files[0]));
        m_mediaPlayer -> play();
    }
}
