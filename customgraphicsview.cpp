#include "customgraphicsview.h"

CustomGraphicsView::CustomGraphicsView(QWidget *parent)
    : QGraphicsView(parent) {
}

void CustomGraphicsView::setViewportMargins(int left, int top, int right, int bottom) {
    QGraphicsView::setViewportMargins(left, top, right, bottom);
}
