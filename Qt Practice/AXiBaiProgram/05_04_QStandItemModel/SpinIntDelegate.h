/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	SpinIntDelegate.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.09.14
描  述:	实现SpinBox的代理
备  注:
修改记录:

  1.  日期: 2024.09.14
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#ifndef SPININTDELEGATE_H
#define SPININTDELEGATE_H

#include <QStyledItemDelegate>

class CSpinIntDelegate : public QStyledItemDelegate
{
public:
    explicit CSpinIntDelegate(QObject *parent = nullptr);

    // editing
    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;                         //创建编辑框

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;           //设置编辑框的数据
    void setModelData(QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const override;                             //设置modle的数据

    void updateEditorGeometry(QWidget *editor,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override;
};

#endif // SPININTDELEGATE_H
