#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QGraphicsView>

class CustomGraphicsView : public QGraphicsView { // https://bugreports.qt.io/browse/QTBUG-11945 This bug is known for 14 years and yet nothing has been done about it.
public:                                           // It doesn't seem to have interest from QT devs or they have forgotten about it.
    CustomGraphicsView(QWidget *parent = nullptr);

    void setViewportMargins(int left, int top, int right, int bottom);
};

#endif // CUSTOMGRAPHICSVIEW_H
