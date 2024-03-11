#include "interface.h"
#include "ui_interface.h"

#include <QSlider>
#include <QTimer>

Interface::Interface(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Interface)
{
    ui -> setupUi(this);

    setMouseTracking(true);

    m_mediaPlayer = MediaPlayer::instance() -> mediaPlayer();
    audio = m_mediaPlayer -> audioOutput();

    audio -> setVolume(ui -> audioSlider -> value());
    handleAudioClicked(ui -> audioSlider -> value());

    connect(m_mediaPlayer, &QMediaPlayer::durationChanged, this, &Interface::durationText);
    connect(m_mediaPlayer, &QMediaPlayer::positionChanged, this, &Interface::positionText);
    connect(m_mediaPlayer, &QMediaPlayer::playbackStateChanged, this, &Interface::iconOnStatusChange);
    connect(ui -> positionSlider, &CustomSlider::sliderClicked, this, &Interface::handleSliderClicked);
    connect(ui -> audioSlider, &CustomSlider::sliderClicked, this, &Interface::handleAudioClicked);
}

Interface::~Interface()
{
    delete ui;
}

void Interface::iconOnStatusChange() {
    if(m_mediaPlayer -> playbackState() == QMediaPlayer::PlayingState) {
        ui -> playButton -> setIcon(QIcon(":/svg/Resources/Icons/pause.svg"));
    }

    else {
        ui -> playButton -> setIcon(QIcon(":/svg/Resources/Icons/play.svg"));
    }
}

void Interface::handleAudioClicked(float position)
{
    audio -> setVolume(position / 100);
    ui -> audioSlider -> setValue(position);
}

void Interface::handleSliderClicked(float position)
{
    m_mediaPlayer -> pause();
    m_mediaPlayer -> setPosition(position);
    ui -> positionSlider -> setValue(position);
    m_mediaPlayer -> play();
}

void Interface::durationText()
{
    QString hours = QString::number(m_mediaPlayer -> duration() / (1000 * 60 * 60));
    QString minutes = QString::number((m_mediaPlayer -> duration() % (1000 * 60 * 60)) / (1000 * 60));
    QString seconds = QString::number(((m_mediaPlayer -> duration() % (1000 * 60 * 60)) % (1000 * 60)) / 1000);

    ui -> positionSlider -> setMaximum(m_mediaPlayer -> duration());

    if(m_mediaPlayer -> mediaStatus() == QMediaPlayer::LoadedMedia || m_mediaPlayer -> mediaStatus() == QMediaPlayer::EndOfMedia ||
        m_mediaPlayer -> mediaStatus() == QMediaPlayer::BufferedMedia || m_mediaPlayer -> mediaStatus() == QMediaPlayer::BufferingMedia) {
        return;
    }

    if(m_mediaPlayer -> duration() > 0) {
        if(seconds.length() == 1) {
            seconds = '0' + seconds;
        }

        if(hours.toInt() > 0) {
            ui -> duration -> setText(hours + ":" + minutes + ":" + seconds);
        }

        else {
            ui -> duration -> setText(minutes + ":" + seconds);
        }
    }
}

void Interface::positionText()
{
    QString hours = QString::number(m_mediaPlayer -> position() / (1000 * 60 * 60));
    QString minutes = QString::number((m_mediaPlayer -> position() % (1000 * 60 * 60)) / (1000 * 60));
    QString seconds = QString::number(((m_mediaPlayer -> position() % (1000 * 60 * 60)) % (1000 * 60)) / 1000);

    ui -> positionSlider -> setValue(m_mediaPlayer -> position());

    if(m_mediaPlayer -> position() > 0) {
        if(seconds.length() == 1) {
            seconds = '0' + seconds;
        }

        if(hours.toInt() > 0) {
            ui -> currentPosition -> setText(hours + ":" + minutes + ":" + seconds);
        }

        else {
            ui -> currentPosition -> setText(minutes + ":" + seconds);
        }
    }
}

void Interface::on_playButton_clicked()
{
    if (m_mediaPlayer -> playbackState() == QMediaPlayer::PlayingState) {
        m_mediaPlayer -> pause();
    }

    else {
        m_mediaPlayer -> play();
    }
}

void Interface::on_nextMedia_pressed()
{
    emit nextMediaPressed();
}


void Interface::on_previousMedia_pressed()
{
    emit previousMediaPressed();
}

