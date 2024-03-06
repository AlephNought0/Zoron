#ifndef PLAYBACK_H
#define PLAYBACK_H

#include "customgraphicsview.h"
#include "interface.h"
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

    Interface* interface;

public slots:
    void mediaPlayback(QStringList &files);

private slots:
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void handleVideoNativeSizeChanged();

private:
    QMediaPlayer* player;
    CustomGraphicsView* graphics;
    QGraphicsScene* scene;
    QGraphicsSimpleTextItem* subtitles;
    QMediaPlayer* m_mediaPlayer;
    QAudioOutput* audio;
    QGraphicsVideoItem* video;

signals:
};

#endif // PLAYBACK_H
