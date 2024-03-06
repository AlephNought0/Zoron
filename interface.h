#ifndef INTERFACE_H
#define INTERFACE_H

#include "mediaplayer.h"
#include "customslider.h"

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
    void handleSliderClicked(int position);

private:
    Ui::Interface *ui;

    QTimer* timer;
    QMediaPlayer* m_mediaPlayer;
};

#endif // INTERFACE_H
