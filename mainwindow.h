#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QSerialPort>


#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_Serach_clicked();

    void on_pushButton_Connect_clicked();

private:
    Ui::MainWindow *ui;
    void addToLogs(QString message);
    QSerialPort *device;
};
#endif // MAINWINDOW_H
