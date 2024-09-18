/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	dialog.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.09.15
描  述:	实现当前的dialog ui界面和后台数据的交互
备  注:
修改记录:

  1.  日期: 2024.09.15
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class Dialog;
}
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;

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
    /// 打开文件
    /// </summary>
    void OpenFile(void);

    /// <summary>
    /// 打开多个文件
    /// </summary>
    void OpenMultiFile(void);

    /// <summary>
    /// 选择目录
    /// </summary>
    void SelectDir(void);

    /// <summary>
    /// 保存文件
    /// </summary>
    void SaveFile(void);

    /// <summary>
    /// 选择文本颜色
    /// </summary>
    void SelectTextColor(void);

    /// <summary>
    /// 选择文本字体
    /// </summary>
    void SelectTextFont(void);

    /// <summary>
    /// 输入字符串
    /// </summary>
    void InputString(void);

    /// <summary>
    /// 输入整数
    /// </summary>
    void InputInt(void);

    /// <summary>
    /// 输入浮点数
    /// </summary>
    void InputFloat(void);

    /// <summary>
    /// 输入选择条目
    /// </summary>
    void InputSelectItem(void);
};
#endif // DIALOG_H
