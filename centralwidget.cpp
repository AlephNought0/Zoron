#include "centralwidget.h"

CentralWidget::CentralWidget(QWidget *parent)
    : QWidget{parent}
{}

void CentralWidget::mouseMoveEvent(QMouseEvent* event) {
    qDebug() << event -> pos();
    emit Move();
}
