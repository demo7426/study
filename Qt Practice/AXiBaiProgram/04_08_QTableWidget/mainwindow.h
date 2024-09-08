#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QDate>
#include <QPlainTextEdit>
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

private:
    enum class ItemType:qint32
    {
        HEADER = QTableWidgetItem::ItemType::UserType + 1,          //表头
        NAME,                                                       //姓名
        SEX,                                                        //性别
        DATEOFBIRTH,                                                //出生日期
        NATION,                                                     //民族
        SCORE,                                                      //分数
        ISPARTY,                                                    //是否为党员
    };

    //列号索引
    enum class TABLEWIDGETCOLUMNINDEX:quint32
    {
        NAME_INDEX = 0,                                             //姓名
        SEX_INDEX,                                                  //性别
        DATEOFBIRTH_INDEX,                                          //出生日期
        NATION_INDEX,                                               //民族
        SCORE_INDEX,                                                //分数
        ISPARTY_INDEX,                                              //是否为党员
    };

    //QTableWidget的一行数据信息
    typedef struct _TABLEWIDGETROW_INFO
    {
        QString Name;                                               //姓名
        QString Sex;                                                //性别
        QDate DateOfBirth;                                          //出生日期
        QString Nation;                                             //民族
        qint32 Score;                                               //分数
        bool IsParty;                                               //是否为党员
        quint32 ID;
    }TABLEWIDGETROW_INFO, *PTABLEWIDGETROW_INFO;

    qint32 m_nIDRole = 1000;

    QLabel* m_pcLabel_CurPos;                                         //当前坐标
    QLabel* m_pcLabel_Type;                                           //单元格类型
    QLabel* m_pcLabel_ID;                                             //身份ID

private:
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

private slots:

    /// <summary>
    /// 设置TableWidget的标题
    /// </summary>
    /// <param name="_pTableWidget"></param>
    /// <returns></returns>
    void SetTableWidgetHeader(QTableWidget* _pTableWidget) noexcept;


    /// <summary>
    /// 设置TableWidget的行数
    /// </summary>
    /// <param name="_pTableWidget"></param>
    /// <param name="_RowCount">_pTableWidget的行数</param>
    /// <returns></returns>
    void SetTableWidgetRowCount(QTableWidget* _pTableWidget, quint32 _RowCount) noexcept;

    /// <summary>
    /// 向 QTableWidget 对象中添加一行 TABLEWIDGETROW_INFO 数据
    /// </summary>
    /// <param name="_pTableWidget"></param>
    /// <param name="_RowNo">行号</param>
    /// <param name="_RowCount">_pTableWidget的行数</param>
    /// <returns></returns>
    void SetTableWidgetRowOfata(QTableWidget* _pTableWidget, const quint32& _RowNo, const TABLEWIDGETROW_INFO& _TableWidgetRow_Info) noexcept;

    /// <summary>
    /// 读取QTableWidgett的信息，显示到QPlainTextEdit中
    /// </summary>
    /// <param name="_pTableWidget"></param>
    /// <param name="_pPlainTextEdit"></param>
    /// <returns></returns>
    void ReadContentToPlainTextEdit(QTableWidget* _pTableWidget, QPlainTextEdit* _pPlainTextEdit);
};
#endif // MAINWINDOW_H
