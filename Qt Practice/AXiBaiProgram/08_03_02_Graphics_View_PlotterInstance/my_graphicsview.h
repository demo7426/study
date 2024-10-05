#ifndef MY_GRAPHICSVIEW_H
#define MY_GRAPHICSVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>

class CMy_GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit CMy_GraphicsView(QWidget *parent = nullptr);
    ~CMy_GraphicsView();

    enum struct GRAPH_TYPE:char
    {
        Rect = 1,                   //矩形
        Ellipse,                    //椭圆
        Circle,                     //圆形
        Triangle,                   //三角形
        Trapezium,                  //梯形
        Line,                       //直线
        Text,                       //文字
    };

    enum struct GRAPH_KEY:char
    {
        Type = 1,                   //item类型
        Name,                       //item名称
    };

private:
    QGraphicsScene *m_pcGraphicsScene = nullptr;

public slots:
    ///
    /// \brief 新增并显示一个图形
    ///
    void NewAndShowGraph(const GRAPH_TYPE _Type) noexcept;

    ///
    /// \brief 放大item
    ///
    void ZoomInItems(void);

    ///
    /// \brief 缩小item
    ///
    void ZoomOutItems(void);

    ///
    /// \brief 恢复item
    ///
    void ZoomResetItems(void);

    ///
    /// \brief 左旋转item
    ///
    void RotateLeftItems(void);

    ///
    /// \brief 右旋转item
    ///
    void RotateRightItems(void);

    ///
    /// \brief 前置item
    ///
    void PreposItems(void);

    ///
    /// \brief 后置item
    ///
    void PostItems(void);

    ///
    /// \brief 组合图形
    ///
    void CompositeItems(void);

    ///
    /// \brief 打散图形
    ///
    void SplitItems(void);

    ///
    /// \brief 删除Items
    ///
    void DeleteItems(void);

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;
private:
    /// <summary>
    /// 初始化ui界面
    /// </summary>
    void InitUi(void) noexcept;

    /// <summary>
    /// 初始化信号槽
    /// </summary>
    void InitSignalSlots(void) noexcept;

signals:
    void SendMouseLeftClickSignal(QPointF _Point);                      //发出鼠标左键点击信号
    void SendItemMsg(QString _Msg);                                     //发出item的相关信息
    void SendMouseMoveSignal(QPoint _Point);                            //发出鼠标移动信号
};

#endif // MY_GRAPHICSVIEW_H
