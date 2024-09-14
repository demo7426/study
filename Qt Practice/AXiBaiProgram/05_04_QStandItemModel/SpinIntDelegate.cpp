/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	SpinIntDelegate.cpp
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

#include <QSpinBox>

#include "SpinIntDelegate.h"

CSpinIntDelegate::CSpinIntDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{}

QWidget *CSpinIntDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)

    QSpinBox* pcSpinBox = new QSpinBox(parent);

    pcSpinBox->setMaximum(100);
    pcSpinBox->setMinimum(0);
    pcSpinBox->setSingleStep(1);

    return pcSpinBox;
}

void CSpinIntDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QSpinBox* pcSpinBox = static_cast<QSpinBox*>(editor);
    qint32 nValue = 0;

    nValue = index.model()->data(index, Qt::EditRole).toInt();                  //获取编辑框的数据

    pcSpinBox->setValue(nValue);
}

void CSpinIntDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QSpinBox* pcSpinBox = static_cast<QSpinBox*>(editor);

    pcSpinBox->interpretText();                                                 //强制立即解释输入
    model->setData(index, pcSpinBox->value(), Qt::EditRole);
}

void CSpinIntDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)

    editor->setGeometry(option.rect);
}
