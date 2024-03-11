#ifndef INTERFACE_H
#define INTERFACE_H

#include "mediaplayer.h"
#include "customslider.h"
#include "playback.h"

#include <QWidget>
#include <QMediaPlayer>

namespace Ui {
class Interface;
}

class Interface : public QWidget
{
    Q_OBJECT

public:
    explicit Interface(QWidget *parent = nullptr);
    ~Interface();

public slots:

private slots:
    void on_playButton_clicked();
    void positionText();
    void durationText();
    void iconOnStatusChange();
    void handleSliderClicked(float position);
    void handleAudioClicked(float position);

    void on_nextMedia_pressed();

    void on_previousMedia_pressed();

private:
    Ui::Interface *ui;

    QTimer* timer;
    QMediaPlayer* m_mediaPlayer;
    QAudioOutput* audio;

signals:
    void nextMediaPressed();
    void previousMediaPressed();
};

#endif // INTERFACE_H
