#include "customslider.h"

CustomSlider::CustomSlider(QWidget *parent)
    : QSlider(parent)
{}

void CustomSlider::mousePressEvent(QMouseEvent *event)
{
    if (event -> button() == Qt::LeftButton) {
        float position;

        if(orientation() == Qt::Horizontal) {
            position = QStyle::sliderValueFromPosition(minimum(), maximum(), event -> position().x(), width());
        }

        else {
            position = QStyle::sliderValueFromPosition(minimum(), maximum(), height() - event -> position().y(), height());
            updateStyleSheet(position);
        }

        emit sliderClicked(position);
    }

    QSlider::mousePressEvent(event);
}

void CustomSlider::mouseMoveEvent(QMouseEvent *event)
{
    if (event -> buttons() & Qt::LeftButton) {
        float position;

        if(orientation() == Qt::Horizontal) {
            position = QStyle::sliderValueFromPosition(minimum(), maximum(), event -> position().x(), width());
        }

        else {
            position = QStyle::sliderValueFromPosition(minimum(), maximum(), height() - event -> position().y(), height());
            updateStyleSheet(position);
        }

        emit sliderClicked(position);
    }

    QSlider::mouseMoveEvent(event);
}

void CustomSlider::updateStyleSheet(float position)
{
    // Calculate color based on value
    int red = 255 - (position * 255) / maximum();
    int green = (position * 255) / maximum();

    QString stylesheet = this -> styleSheet();
    QString backgroundColor = QString("rgb(%1, %2, 0)").arg(red).arg(green);

    stylesheet += QString("QSlider::groove {background: %1}").arg(backgroundColor);

    this -> setStyleSheet(stylesheet);
}


void CustomSlider::mouseReleaseEvent(QMouseEvent *event)
{
    QSlider::mouseReleaseEvent(event);
}
