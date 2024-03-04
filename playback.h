#ifndef PLAYBACK_H
#define PLAYBACK_H

#include "customgraphicsview.h"

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
    void mediaPlayback(QStringList &files);
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void showEvent(QShowEvent* event);

private:
    QMediaPlayer* player;
    QAudioOutput* audio;
    CustomGraphicsView* graphics;
    QGraphicsScene* scene;
    QGraphicsVideoItem* video;
    QGraphicsSimpleTextItem* subtitles;

signals:

};

#endif // PLAYBACK_H
