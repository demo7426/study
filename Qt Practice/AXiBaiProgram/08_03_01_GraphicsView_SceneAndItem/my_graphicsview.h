/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	my_graphicsview.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.10.01
描  述:	自定义 QGraphicsView 的实现
备  注:  Scene不会显示图形,item才会显示图形
修改记录:

  1.  日期: 2024.10.01
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#ifndef MY_GRAPHICSVIEW_H
#define MY_GRAPHICSVIEW_H

#include <QWidget>
#include <QGraphicsView>

class CMy_GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit CMy_GraphicsView(QWidget *parent = nullptr);

private:
    QGraphicsScene* m_pcGraphicsScene = nullptr;

signals:
    void SendMouseLeftClickSignal(QPoint _Point);                       //发出鼠标左键点击信号
    void SendMouseMoveSignal(QPoint _Point);                            //发出鼠标移动信号

private:
    /// <summary>
    /// 初始化ui界面
    /// </summary>
    void InitUi(void) noexcept;

    /// <summary>
    /// 初始化信号槽
    /// </summary>
    void InitSignalSlots(void) noexcept;

protected:
    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    bool eventFilter(QObject *obj, QEvent *event) override;

};

#endif // MY_GRAPHICSVIEW_H
