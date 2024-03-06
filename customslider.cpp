#include "customslider.h"

CustomSlider::CustomSlider(QWidget *parent)
    : QSlider(parent)
{
}

void CustomSlider::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        int position = QStyle::sliderValueFromPosition(minimum(), maximum(), event -> position().x(), width());
        setValue(position);
        emit sliderClicked(position);
    }

    QSlider::mousePressEvent(event);
}

void CustomSlider::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        int position = QStyle::sliderValueFromPosition(minimum(), maximum(), event -> position().x(), width());
        setValue(position); // Update the slider's value as the mouse moves
        emit sliderClicked(position);
    }

    QSlider::mouseMoveEvent(event);
}

void CustomSlider::mouseReleaseEvent(QMouseEvent *event)
{
    QSlider::mouseReleaseEvent(event);
}
