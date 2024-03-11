#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui -> setupUi(this);

    check = false;

    setMouseTracking(true); // Enable mouse tracking for the widget

    // Set up a timer to check mouse position periodically
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::checkMousePosition);
    timer -> start(10);

    playback = new Playback(this);
    interface = new Interface(this);
    bridge = new Bridge(interface, playback, this);

    animation = new QPropertyAnimation(interface, "geometry");
    animation -> setDuration(50);

    setCentralWidget(playback);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event) // Resize event to adjust the interface to the bottom
{
    QWidget::resizeEvent(event);

    interface -> setGeometry(0, height() - interface -> height(), width(), interface -> height());
}

void MainWindow::checkMousePosition()
{
    static QTimer hideTimer;
    QPoint currentPos = QCursor::pos();

    if(currentPos != lastMousePos && check) {
        lastMousePos = currentPos;

        QApplication::setOverrideCursor(QCursor(Qt::ArrowCursor));

        animation -> setStartValue(QRect(0, height(), width(), interface -> height()));
        animation -> setEndValue(QRect(0, height() - interface -> height(), width(), interface -> height()));
        animation -> start();

        check = false;
    }

    else if(currentPos != lastMousePos) {
        lastMousePos = currentPos;

        hideTimer.start(2000);
    }

    connect(&hideTimer, &QTimer::timeout, interface, [this]() {
        animation -> setStartValue(interface -> geometry());
        animation -> setEndValue(QRect(0, height(), width(), interface -> height()));
        animation -> start();

        check = true;

        QApplication::setOverrideCursor(QCursor(Qt::BlankCursor));
    });
}

void MainWindow::on_actionOpen_triggered()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setNameFilter(tr("Video Files (*.mp4 *.mov *.mpv *.mkv)"));
    dialog.setViewMode(QFileDialog::Detail);

    QStringList m_files;

    if(dialog.exec()) {
        m_files = dialog.selectedFiles();
    }

    playback -> setFiles(m_files);
}
