#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QDebug>
#include <QSerialPort>
#include <QList>
#include <QSerialPortInfo>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->device = new QSerialPort(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_Serach_clicked()
{
    ui->comboBox->clear();

    qDebug() << "Szukanie urzadzen";

    QList<QSerialPortInfo> devices;
    devices = QSerialPortInfo::availablePorts();

    for(int i = 0; i < devices.count(); i++){

        this->addToLogs("Znaleziono urzadzenie" + devices.at(i).portName() + " " + devices.at(i).description());
        qDebug() << devices.at(i).portName() << devices.at(i).description();
        ui->comboBox->addItem(devices.at(i).portName() + " " + devices.at(i).description());
    }


    //qDebug() << QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");

}


void MainWindow::addToLogs(QString message)
{
    QString currentDateTime = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
    ui->textConsole->append(currentDateTime + "\t" + message);
}

void MainWindow::on_pushButton_Connect_clicked()
{
    if(ui->comboBox->count()== 0) {
        this->addToLogs("Nie wykryto żadnych urządzeń!");
        return;
    }

    QString portName = ui->comboBox->currentText().split(" ").first();
    qDebug() << portName;

    this->device->setPortName(portName);
    //this->device->setPort('COM10');

    if(!device->isOpen()){


    // OTWÓRZ I SKONFIGURUJ PORT:
    if(device->open(QSerialPort::ReadWrite)) {
      this->device->setBaudRate(QSerialPort::Baud9600);
      this->device->setDataBits(QSerialPort::Data8);
      this->device->setParity(QSerialPort::NoParity);
      this->device->setStopBits(QSerialPort::OneStop);
      this->device->setFlowControl(QSerialPort::NoFlowControl);

      this->addToLogs("Otwarto port szeregowy.");
      } else {
      this->addToLogs("Otwarcie portu szeregowego się nie powiodło!");
        }
    } else {
        this->addToLogs("Port juz jest otwarty");
        return;
    }
}


void MainWindow::on_pushButton_Disconnect_clicked()
{
        if(this->device->isOpen()) {
          this->device->close();
          this->addToLogs("Zamknięto połączenie.");
        } else {
          this->addToLogs("Port nie jest otwarty!");
          return;
        }
}
