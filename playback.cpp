#include "playback.h"

Playback::Playback(QWidget *parent)
    : QWidget{parent}
{
    mediaPosition = 0;

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

void Playback::previous() {
    if(mediaPosition - 1 < 0) {
        return;
    }

    else {
        mediaPosition--;
        m_mediaPlayer -> setSource(QUrl::fromLocalFile(files[mediaPosition]));
        m_mediaPlayer -> play();
    }
}

void Playback::next() {
    if(mediaPosition + 1 > files.size() - 1) {
        return;
    }

    else {
        mediaPosition++;
        m_mediaPlayer -> setSource(QUrl::fromLocalFile(files[mediaPosition]));
        m_mediaPlayer -> play();
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

void Playback::setFiles(const QStringList &files)
{
    this -> files = files;

    if(files.isEmpty()) {
        return;
    }

    else {
        mediaPosition = 0;
        m_mediaPlayer -> setSource(QUrl::fromLocalFile(files[mediaPosition]));
        m_mediaPlayer -> play();
    }
}
