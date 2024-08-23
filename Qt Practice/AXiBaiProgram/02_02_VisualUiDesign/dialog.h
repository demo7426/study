/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	dialog.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.08.22
描  述:	使用纯ui设计界面设计ui
备  注:
修改记录:

  1.  日期: 2024.08.22
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
    //连接信号槽
    int Connected(void) noexcept;

private slots:
    void on_checkBoxUnderline_clicked(bool checked);

    void on_checkBoxItalic_clicked(bool checked);

    void on_checkBoxBold_clicked(bool checked);

    void SetPlainTextEditColor(void);

private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H
