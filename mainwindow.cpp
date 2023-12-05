#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , serial(new QSerialPort(this))
{
    ui->setupUi(this);

    serial->setPortName("/dev/tty.usbmodem101");
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if (!serial->open(QIODevice::ReadOnly)) {
        // Handle error
    }

    connect(serial, &QSerialPort::readyRead, this, &MainWindow::handleReadyRead);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleReadyRead()
{
    QByteArray data = serial->readAll();
    // Process data
    int value = data.toInt();
    qDebug() << value;
    if (value == 3) {
        qDebug() << "Luuk eet gras!";
    } else if (value == 4) {
        qDebug() << "Floris eet gras!";
    }
    ui->textBrowser->append(data);
}
