#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "playback.h"
#include "interface.h"
#include "bridge.h"

#include <QMainWindow>
#include <QMouseEvent>
#include <QTimer>
#include <QPropertyAnimation>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:

private slots:
    void on_actionOpen_triggered();
    void checkMousePosition();
    void resizeEvent(QResizeEvent *event);

private:
    bool check;

    Ui::MainWindow *ui;
    Playback *playback;
    Interface* interface;
    Bridge* bridge;
    QPoint lastMousePos;
    QTimer* timer;
    QPropertyAnimation* animation;
};
#endif // MAINWINDOW_H
