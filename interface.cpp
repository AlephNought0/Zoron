#include "interface.h"
#include "ui_interface.h"

Interface::Interface(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Interface)
{
    ui->setupUi(this);
}

Interface::~Interface()
{
    delete ui;
}
