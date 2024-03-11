#ifndef BRIDGE_H
#define BRIDGE_H

#include "playback.h"
#include "interface.h"

class Bridge : public QObject
{
    Q_OBJECT
public:
    Bridge(Interface *interface, Playback *playback, QObject *parent = nullptr);
    void next();
    void previous();

private:
    Interface *m_interface;
    Playback *m_playback;
};

#endif // BRIDGE_H
