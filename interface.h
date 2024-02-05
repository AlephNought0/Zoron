#ifndef INTERFACE_H
#define INTERFACE_H

#include <QDialog>

namespace Ui {
class Interface;
}

class Interface : public QDialog
{
    Q_OBJECT

public:
    explicit Interface(QWidget *parent = nullptr);
    ~Interface();

private:
    Ui::Interface *ui;
};

#endif // INTERFACE_H
