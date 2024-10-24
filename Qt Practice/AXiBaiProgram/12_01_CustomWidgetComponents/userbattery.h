/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	userbattery.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.10.24
描  述:	实现自定义电池绘制及接口
备  注:
修改记录:

  1.  日期: 2024.10.24
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#ifndef USERBATTERY_H
#define USERBATTERY_H

#include <QWidget>
#include <QColor>

namespace Ui {
class CUserBattery;
}

class CUserBattery : public QWidget
{
    Q_OBJECT

public:
    explicit CUserBattery(QWidget *parent = nullptr);
    ~CUserBattery();

    ///
    /// \brief SetPowerLevel--设置电池电量
    /// \param _PowerLevel--电量值
    ///
    inline void SetPowerLevel(qint16 _PowerLevel)
    {
        if(_PowerLevel >=0 && _PowerLevel <= 100)
            m_shPowerLevel = _PowerLevel;
        this->repaint();
    }

    ///
    /// \brief GetPowerLevel--获取电池电量
    ///
    inline qint16 GetPowerLevel(void)
    {
        return m_shPowerLevel;
    }

private:
    QColor m_cColoBorder = Qt::GlobalColor::black;          //边框颜色

    QColor m_cColoLowerPower = Qt::GlobalColor::red;        //低电量时候的颜色
    QColor m_cColoHighPower = Qt::GlobalColor::green;       //高电量时候的颜色

    qint16 m_shPowerLevel = 0;                              //电池电量
    static constexpr qint16 m_shElectricThreshold = 20;     //低电量阈值

    Ui::CUserBattery *ui;

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // USERBATTERY_H
