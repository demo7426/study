/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	customchartview.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.10.14
描  述:	自定义实现一个chartView,支持鼠标缩放，按键上下左右查看（暂只支持折线图）
备  注:
修改记录:

  1.  日期: 2024.10.14
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#ifndef CUSTOMCHARTVIEW_H
#define CUSTOMCHARTVIEW_H

#include <QWidget>
#include <QChartView>
#include <QPointF>
#include <QPair>

class CCustomChartView : public QChartView
{
    Q_OBJECT
public:
    explicit CCustomChartView(QWidget *parent = nullptr);

private:
    QPointF m_cPointF_StartPos;       //起始坐标
    QPointF m_cPointF_EndPos;         //结束坐标

    bool m_bResetStatus = true;                 //是否处于初始状态
    QList<QPair<qreal, qreal>> m_listPos;       //保存横纵坐标值

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;

    void wheelEvent(QWheelEvent *event) override;

signals:

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
    /// \brief ScrollAndZoomReset--恢复最初的显示状态
    ///
    void ScrollAndZoomReset(void);
};

#endif // CUSTOMCHARTVIEW_H
