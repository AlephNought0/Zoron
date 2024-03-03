/*#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "playback.h"
#include "interface.h"

#include <QMainWindow>
#include <QMouseEvent>
#include <QTimer>


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
    void mediaFiles(QStringList &files);

private slots:
    void on_actionOpen_triggered();
    void checkMousePosition();

private:
    Ui::MainWindow *ui;

    Playback *playback;
    QPoint lastMousePos;
    QTimer* timer;
    Interface* interface;
};
#endif // MAINWINDOW_H
*/
