/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	dialogheaders.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.09.20
描  述:	用于设置QTableView的表头
备  注:
修改记录:

  1.  日期: 2024.09.20
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#ifndef DIALOGHEADERS_H
#define DIALOGHEADERS_H

#include <QDialog>
#include <QStringList>
#include <QStringListModel>

namespace Ui {
class CDialogHeaders;
}

class CDialogHeaders : public QDialog
{
    Q_OBJECT

public:
    explicit CDialogHeaders(QWidget *parent = nullptr);
    ~CDialogHeaders();

private:
    QStringListModel* m_pcStringListModel = nullptr;

private:
    Ui::CDialogHeaders *ui;

signals:
    //表头数据被修改
    void ListViewChanged(const QStringList _StrList);

public:
    //设置表头数据
    void SetListView(const QStringList _StrList);

private:
    /// <summary>
    /// 初始化ui界面
    /// </summary>
    void InitUi(void) noexcept;

    /// <summary>
    /// 初始化信号槽
    /// </summary>
    void InitSignalSlots(void) noexcept;
};

#endif // DIALOGHEADERS_H
