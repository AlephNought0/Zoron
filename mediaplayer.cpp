#include "mediaplayer.h"

MediaPlayer* MediaPlayer::instance()
{
    static MediaPlayer instance;
    return &instance;
}

MediaPlayer::MediaPlayer(QObject *parent) : QObject(parent)
{
    audio = new QAudioOutput;
    video = new QGraphicsVideoItem;

    m_mediaPlayer.setAudioOutput(audio);
    m_mediaPlayer.setVideoOutput(video);
}

QMediaPlayer* MediaPlayer::mediaPlayer()
{
    return &m_mediaPlayer;
}
