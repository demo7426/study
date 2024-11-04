#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include <QAudioDeviceInfo>
#include <QAudioInput>

#include "qmydisplaydevice.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    const qint64  displayPointsCount=4000;

    QLineSeries *lineSeries;//曲线序列

    QList<QAudioDeviceInfo> deviceList;  //音频录入设备列表

    QAudioDeviceInfo curDevice;//当前输入设备

    QmyDisplayDevice    *displayDevice; //用于显示的IODevice

    QAudioInput         *audioInput;//音频输入设备

    Ui::MainWindow *ui;

private:
    QString SampleTypeString(QAudioFormat::SampleType sampleType);

    QString ByteOrderString(QAudioFormat::Endian endian);

private slots:
    //自定义槽函数
    void on_IODevice_UpdateBlockSize(qint64 blockSize);

    void on_comboDevices_currentIndexChanged(int index);

    void on_actStart_triggered();

    void on_actStop_triggered();

    void on_actDeviceTest_triggered();
};
#endif // MAINWINDOW_H
