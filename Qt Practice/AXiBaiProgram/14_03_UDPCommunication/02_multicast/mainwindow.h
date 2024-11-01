#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actClear_triggered();

    void on_actStart_triggered();

    void on_actStop_triggered();

    void on_btnMulticast_clicked();

protected:
    void closeEvent(QCloseEvent *event);

private:
    QLabel *m_pcLabel_SocketStatus = nullptr;       //socket状态

    QUdpSocket m_cUdpSocket;

    Ui::MainWindow *ui;

private:
    /// <summary>
    /// 初始化ui界面
    /// </summary>
    void InitUi(void) noexcept;

    /// <summary>
    /// 初始化信号槽
    /// </summary>
    void InitSignalSlots(void) noexcept;

    ///
    /// \brief GetHostIPv4--获取本地主机IPv4的地址
    /// \return
    ///
    QString GetHostIPv4(void);
};
#endif // MAINWINDOW_H
