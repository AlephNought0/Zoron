#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QTimer>

#include <QGraphicsVideoItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSimpleTextItem>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QLabel>


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

private slots:
    void on_actionOpen_triggered();
    void checkMousePosition();

private:
    Ui::MainWindow *ui;

    QMediaPlayer* player;
    QAudioOutput* audio;
    QGraphicsView* graphics;
    QGraphicsScene* scene;
    QGraphicsVideoItem* video;
    QGraphicsSimpleTextItem* subtitles;

    QPoint lastMousePos;
    QTimer* timer;
};
#endif // MAINWINDOW_H
