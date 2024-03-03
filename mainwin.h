#ifndef MAINWIN_H
#define MAINWIN_H

#include "playback.h"
#include "interface.h"

#include <QWidget>
#include <QMouseEvent>
#include <QTimer>

namespace Ui {
class Mainwin;
}

class Mainwin : public QWidget
{
    Q_OBJECT

public:
    explicit Mainwin(QWidget *parent = nullptr);
    ~Mainwin();

signals:
    void mediaFiles(QStringList &files);

private slots:
    void on_actionOpen_triggered();
    void checkMousePosition();

private:
    Ui::Mainwin *ui;

    Playback *playback;
    QPoint lastMousePos;
    QTimer* timer;
    Interface* interface;
};

#endif // MAINWIN_H
