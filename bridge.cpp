#include "bridge.h"

Bridge::Bridge(Interface *interface, Playback *playback, QObject *parent)
    : QObject(parent), m_interface(interface), m_playback(playback)
{
    connect(m_interface, &Interface::nextMediaPressed , this, &Bridge::next);
    connect(m_interface, &Interface::previousMediaPressed , this, &Bridge::previous);
}

void Bridge::next()
{
    m_playback -> next();
}

void Bridge::previous()
{
    m_playback -> previous();
}
