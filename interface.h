#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>

namespace Ui {
class Interface;
}

class Interface : public QWidget
{
    Q_OBJECT

public:
    explicit Interface(QWidget *parent = nullptr);
    ~Interface();

private slots:

private:
    Ui::Interface *ui;

    QTimer* timer;
};

#endif // INTERFACE_H
