#ifndef PLAYBACK_H
#define PLAYBACK_H

#include <QWidget>

class Playback : public QWidget
{
    Q_OBJECT
public:
    explicit Playback(QWidget *parent = nullptr);

public slots:
    //void setMedia();
    //void addMedia();

signals:
    //void media(QStringList files);
};

#endif // PLAYBACK_H
