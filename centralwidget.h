#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include <QMouseEvent>

class CentralWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CentralWidget(QWidget *parent = nullptr);

    void mouseMoveEvent(QMouseEvent* event);

signals:
    void Move();
};

#endif // CENTRALWIDGET_H
