#ifndef PLAYBACK_H
#define PLAYBACK_H

#include "customgraphicsview.h"
#include "mediaplayer.h"

#include <QWidget>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QGraphicsVideoItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSimpleTextItem>
#include <QVBoxLayout>
#include <QMouseEvent>

class Playback : public QWidget
{
    Q_OBJECT
public:
    explicit Playback(QWidget *parent = nullptr);

public slots:
    void next();
    void previous();
    void setFiles(const QStringList &files);

private slots:
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void handleVideoNativeSizeChanged();

private:
    int mediaPosition;

    QMediaPlayer* player;
    CustomGraphicsView* graphics;
    QGraphicsScene* scene;
    QGraphicsSimpleTextItem* subtitles;
    QMediaPlayer* m_mediaPlayer;
    QAudioOutput* audio;
    QGraphicsVideoItem* video;
    QStringList files;

signals:
};

#endif // PLAYBACK_H
