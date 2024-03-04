#include "interface.h"
#include "ui_interface.h"

#include <QSlider>
#include <QTimer>

Interface::Interface(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Interface)
{
    ui->setupUi(this);

    connect(ui -> durationSlider, &QSlider::valueChanged, [=](int value) {
        QString stylesheet = ui -> durationSlider->styleSheet();

        if(value > 0) {
            stylesheet += "QSlider::sub-page { background: cyan; }";
        }

        else {
            stylesheet += "QSlider::sub-page { background: transparent; }";
        }

        ui -> durationSlider -> setStyleSheet(stylesheet);
    });
}

Interface::~Interface()
{
    delete ui;
}
