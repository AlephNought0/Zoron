#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QGraphicsVideoItem>

class MediaPlayer : public QObject
{
    Q_OBJECT

public:
    static MediaPlayer* instance(); // Singleton instance getter

    QMediaPlayer* mediaPlayer(); // Getter for QMediaPlayer instance

private:
    explicit MediaPlayer(QObject *parent = nullptr);
    QMediaPlayer m_mediaPlayer;
    QAudioOutput* audio;
    QGraphicsVideoItem* video;

signals:

};

#endif // MEDIAPLAYER_H
