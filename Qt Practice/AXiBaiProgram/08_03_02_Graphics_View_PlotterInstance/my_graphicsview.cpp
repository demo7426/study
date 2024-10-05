#include <QGraphicsView>
#include <QGraphicsItem>
#include <QTime>
#include <QInputDialog>
#include <QMouseEvent>
#include <QColorDialog>
#include <QFontDialog>

#include "my_graphicsview.h"

CMy_GraphicsView::CMy_GraphicsView(QWidget *parent)
    : QGraphicsView{parent}
{
    InitUi();
    InitSignalSlots();
}

CMy_GraphicsView::~CMy_GraphicsView()
{
    if(m_pcGraphicsScene != nullptr)
        delete m_pcGraphicsScene;
}

void CMy_GraphicsView::NewAndShowGraph(const GRAPH_TYPE _Type) noexcept
{
    switch (_Type)
    {
    case GRAPH_TYPE::Rect:                  //新增矩形
    {
        QRectF cRectF(rand() % 40, rand() % 30, 80, 60);
        QGraphicsRectItem* pcGraphicsRectItem = new QGraphicsRectItem(cRectF);

        pcGraphicsRectItem->setData((int)GRAPH_KEY::Type, (int)_Type);
        pcGraphicsRectItem->setData((int)GRAPH_KEY::Name, tr("矩形"));
        pcGraphicsRectItem->setPos(0, 0);
        pcGraphicsRectItem->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
        m_pcGraphicsScene->addItem(pcGraphicsRectItem);
    }
    break;
    case GRAPH_TYPE::Ellipse:               //新增椭圆
    {
        QRectF cRectF(rand() % 40, rand() % 30, 80, 60);
        QGraphicsEllipseItem* pcGraphicsEllipseItem = new QGraphicsEllipseItem(cRectF);

        pcGraphicsEllipseItem->setData((int)GRAPH_KEY::Type, (int)_Type);
        pcGraphicsEllipseItem->setData((int)GRAPH_KEY::Name, tr("椭圆"));
        pcGraphicsEllipseItem->setPos(0, 0);
        pcGraphicsEllipseItem->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
        m_pcGraphicsScene->addItem(pcGraphicsEllipseItem);
    }
    break;
    case GRAPH_TYPE::Circle:                //新增圆形
    {
        QRectF cRectF(rand() % 30, rand() % 30, 60, 60);
        QGraphicsEllipseItem* pcGraphicsEllipseItem = new QGraphicsEllipseItem(cRectF);

        pcGraphicsEllipseItem->setData((int)GRAPH_KEY::Type, (int)_Type);
        pcGraphicsEllipseItem->setData((int)GRAPH_KEY::Name, tr("圆形"));
        pcGraphicsEllipseItem->setPos(0, 0);
        pcGraphicsEllipseItem->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
        m_pcGraphicsScene->addItem(pcGraphicsEllipseItem);
    }
    break;
    case GRAPH_TYPE::Triangle:              //新增三角形
    {
        QPolygonF cPolygonF;

        cPolygonF.append(QPointF(30, 30));
        cPolygonF.append(QPointF(60, 30));
        cPolygonF.append(QPointF(45, 15));

        QGraphicsPolygonItem* pcGraphicsPolygonItem = new QGraphicsPolygonItem(cPolygonF);

        pcGraphicsPolygonItem->setData((int)GRAPH_KEY::Type, (int)_Type);
        pcGraphicsPolygonItem->setData((int)GRAPH_KEY::Name, tr("三角形"));
        pcGraphicsPolygonItem->setPos(0, 0);
        pcGraphicsPolygonItem->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
        m_pcGraphicsScene->addItem(pcGraphicsPolygonItem);
    }
    break;
    case GRAPH_TYPE::Trapezium:             //新增梯形
    {
        QPolygonF cPolygonF;

        cPolygonF.append(QPointF(0, 0));
        cPolygonF.append(QPointF(60, 0));
        cPolygonF.append(QPointF(45, -30));
        cPolygonF.append(QPointF(15, -30));

        QGraphicsPolygonItem* pcGraphicsPolygonItem = new QGraphicsPolygonItem(cPolygonF);

        pcGraphicsPolygonItem->setData((int)GRAPH_KEY::Type, (int)_Type);
        pcGraphicsPolygonItem->setData((int)GRAPH_KEY::Name, tr("梯形"));
        pcGraphicsPolygonItem->setPos(0, 0);
        pcGraphicsPolygonItem->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
        m_pcGraphicsScene->addItem(pcGraphicsPolygonItem);
    }
    break;
    case GRAPH_TYPE::Line:                  //新增直线
    {
        QPolygonF cPolygonF;

        cPolygonF.append(QPointF(30, 30));
        cPolygonF.append(QPointF(80, 30));

        QGraphicsPolygonItem* pcGraphicsPolygonItem = new QGraphicsPolygonItem(cPolygonF);

        pcGraphicsPolygonItem->setData((int)GRAPH_KEY::Type, (int)_Type);
        pcGraphicsPolygonItem->setData((int)GRAPH_KEY::Name, tr("直线"));
        pcGraphicsPolygonItem->setPos(0, 0);
        pcGraphicsPolygonItem->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
        m_pcGraphicsScene->addItem(pcGraphicsPolygonItem);
    }
    break;
    case GRAPH_TYPE::Text:                  //新增文字
    {
        QString strUserInputText = QInputDialog::getText(this, tr("单行文本输入框"), tr("输入一行文本"));

        QGraphicsTextItem* pcGraphicsTextItem = new QGraphicsTextItem(strUserInputText);

        pcGraphicsTextItem->setData((int)GRAPH_KEY::Type, (int)_Type);
        pcGraphicsTextItem->setData((int)GRAPH_KEY::Name, tr("文字"));
        pcGraphicsTextItem->setPos(0, 0);
        pcGraphicsTextItem->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
        m_pcGraphicsScene->addItem(pcGraphicsTextItem);
    }
    break;
    default:
        break;
    }
}

void CMy_GraphicsView::ZoomInItems()
{
    QGraphicsScene* pcGraphicsScene;
    QList<QGraphicsItem*> cList_SelectGraphicsItem;

    pcGraphicsScene = this->scene();
    cList_SelectGraphicsItem = pcGraphicsScene->selectedItems();

    foreach (auto item, cList_SelectGraphicsItem) {
        item->setScale(item->scale() + 0.1);
    }
}

void CMy_GraphicsView::ZoomOutItems()
{
    QGraphicsScene* pcGraphicsScene;
    QList<QGraphicsItem*> cList_SelectGraphicsItem;

    pcGraphicsScene = this->scene();
    cList_SelectGraphicsItem = pcGraphicsScene->selectedItems();

    foreach (auto item, cList_SelectGraphicsItem) {
        item->setScale(item->scale() - 0.1);
    }
}

void CMy_GraphicsView::ZoomResetItems()
{
    QGraphicsScene* pcGraphicsScene;
    QList<QGraphicsItem*> cList_SelectGraphicsItem;

    pcGraphicsScene = this->scene();
    cList_SelectGraphicsItem = pcGraphicsScene->selectedItems();

    foreach (auto item, cList_SelectGraphicsItem) {
        item->setScale(1);
    }
}

void CMy_GraphicsView::RotateLeftItems()
{
    QGraphicsScene* pcGraphicsScene;
    QList<QGraphicsItem*> cList_SelectGraphicsItem;

    pcGraphicsScene = this->scene();
    cList_SelectGraphicsItem = pcGraphicsScene->selectedItems();

    foreach (auto item, cList_SelectGraphicsItem) {
        item->setRotation(-45 + item->rotation());
    }
}

void CMy_GraphicsView::RotateRightItems()
{
    QGraphicsScene* pcGraphicsScene;
    QList<QGraphicsItem*> cList_SelectGraphicsItem;

    pcGraphicsScene = this->scene();
    cList_SelectGraphicsItem = pcGraphicsScene->selectedItems();

    foreach (auto item, cList_SelectGraphicsItem) {
        item->setRotation(45 + item->rotation());
    }
}

void CMy_GraphicsView::PreposItems()
{
    QGraphicsScene* pcGraphicsScene;
    QList<QGraphicsItem*> cList_SelectGraphicsItem;

    pcGraphicsScene = this->scene();
    cList_SelectGraphicsItem = pcGraphicsScene->selectedItems();

    foreach (auto item, cList_SelectGraphicsItem) {
        item->setZValue(item->zValue() + 1);
    }
}

void CMy_GraphicsView::PostItems()
{
    QGraphicsScene* pcGraphicsScene;
    QList<QGraphicsItem*> cList_SelectGraphicsItem;

    pcGraphicsScene = this->scene();
    cList_SelectGraphicsItem = pcGraphicsScene->selectedItems();

    foreach (auto item, cList_SelectGraphicsItem) {
        item->setZValue(item->zValue() - 1);
    }
}

void CMy_GraphicsView::CompositeItems()
{
    QGraphicsItemGroup* pcGraphicsItemGroup = new QGraphicsItemGroup();
    QGraphicsScene* pcGraphicsScene;
    QList<QGraphicsItem*> cList_SelectGraphicsItem;

    pcGraphicsScene = this->scene();
    cList_SelectGraphicsItem = pcGraphicsScene->selectedItems();

    foreach (auto item, cList_SelectGraphicsItem) {
        pcGraphicsScene->removeItem(item);

        pcGraphicsItemGroup->addToGroup(item);
    }

    pcGraphicsItemGroup->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
    pcGraphicsScene->addItem(pcGraphicsItemGroup);
}

void CMy_GraphicsView::SplitItems()
{
    QGraphicsItemGroup* pcGraphicsItemGroup = nullptr;
    QGraphicsScene* pcGraphicsScene;
    QList<QGraphicsItem*> cList_SelectGraphicsItem;

    pcGraphicsScene = this->scene();
    cList_SelectGraphicsItem = pcGraphicsScene->selectedItems();

    foreach (auto item, cList_SelectGraphicsItem) {
        if(item->type() != QGraphicsItemGroup::Type)
            continue;

        pcGraphicsItemGroup = dynamic_cast<QGraphicsItemGroup*>(item);
        pcGraphicsScene->destroyItemGroup(pcGraphicsItemGroup);
    }
}

void CMy_GraphicsView::DeleteItems()
{
    QGraphicsScene* pcGraphicsScene;
    QList<QGraphicsItem*> cList_SelectGraphicsItem;

    pcGraphicsScene = this->scene();
    cList_SelectGraphicsItem = pcGraphicsScene->selectedItems();

    foreach (auto item, cList_SelectGraphicsItem) {
        pcGraphicsScene->removeItem(item);

        delete item;
        item = nullptr;
    }
}

void CMy_GraphicsView::mouseDoubleClickEvent(QMouseEvent *event)
{
    QGraphicsScene* pcGraphicsScene;
    QGraphicsItem* pcGraphicsItem;

    pcGraphicsScene = this->scene();

    if(!pcGraphicsScene)
        return;

    pcGraphicsItem = pcGraphicsScene->itemAt(this->mapToScene(event->pos()), this->transform());

    if(!pcGraphicsItem)
        return;

    switch ((GRAPH_TYPE)(pcGraphicsItem->data((int)GRAPH_KEY::Type).toInt()))
    {
    case GRAPH_TYPE::Rect:                  //设置矩形
    {
        QColor cUserColor = QColorDialog::getColor();
        QGraphicsRectItem* pcGraphicsRectItem = dynamic_cast<QGraphicsRectItem*>(pcGraphicsItem);

        if(cUserColor.isValid())
            pcGraphicsRectItem->setBrush(QBrush(cUserColor));
    }
    break;
    case GRAPH_TYPE::Ellipse:               //设置椭圆
    case GRAPH_TYPE::Circle:                //设置圆形
    {
        QColor cUserColor = QColorDialog::getColor();
        QGraphicsEllipseItem* pcGraphicsEllipseItem = dynamic_cast<QGraphicsEllipseItem*>(pcGraphicsItem);

        if(cUserColor.isValid())
            pcGraphicsEllipseItem->setBrush(QBrush(cUserColor));
    }
    break;
    case GRAPH_TYPE::Triangle:              //设置三角形
    case GRAPH_TYPE::Trapezium:             //设置梯形
    {
        QColor cUserColor = QColorDialog::getColor();
        QGraphicsPolygonItem* pcGraphicsPolygonItem = dynamic_cast<QGraphicsPolygonItem*>(pcGraphicsItem);

        if(cUserColor.isValid())
            pcGraphicsPolygonItem->setBrush(QBrush(cUserColor));
    }
    break;
    case GRAPH_TYPE::Line:                  //设置直线
    {
        QColor cUserColor = QColorDialog::getColor();
        QGraphicsPolygonItem* pcGraphicsPolygonItem = dynamic_cast<QGraphicsPolygonItem*>(pcGraphicsItem);

        if(cUserColor.isValid())
            pcGraphicsPolygonItem->setPen(QPen(cUserColor));
    }
    break;
    case GRAPH_TYPE::Text:                  //设置文字
    {
        bool bIsOK = false;

        QGraphicsTextItem* pcGraphicsTextItem = dynamic_cast<QGraphicsTextItem*>(pcGraphicsItem);

        QFont cUserFont = QFontDialog::getFont(&bIsOK);
        if(bIsOK)
            pcGraphicsTextItem->setFont(cUserFont);

    }
    break;
    default:
        break;
    }

    QGraphicsView::mouseDoubleClickEvent(event);
}

void CMy_GraphicsView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsScene* pcGraphicsScene;
    QGraphicsItem* pcGraphicsItem;
    QPointF cPointF_CurScene = this->mapToScene(event->pos());

    pcGraphicsScene = this->scene();

    if(!pcGraphicsScene)
        return;

    pcGraphicsItem = pcGraphicsScene->itemAt(cPointF_CurScene, this->transform());

    if(!pcGraphicsItem)
        return;

    emit SendMouseLeftClickSignal(pcGraphicsItem->mapFromScene(cPointF_CurScene));
    emit SendItemMsg(QString("类别:%1, 类型:%2").arg(pcGraphicsItem->data((int)GRAPH_KEY::Type).toInt()).
                     arg(pcGraphicsItem->data((int)GRAPH_KEY::Name).toString()));

    QGraphicsView::mousePressEvent(event);
}

void CMy_GraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    emit SendMouseMoveSignal(event->pos());

    QGraphicsView::mouseMoveEvent(event);
}

void CMy_GraphicsView::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Delete)
        DeleteItems();


    if(event->key() == Qt::Key_Up)
    {
        QGraphicsScene* pcGraphicsScene;
        QList<QGraphicsItem*> cList_SelectGraphicsItem;

        pcGraphicsScene = this->scene();
        cList_SelectGraphicsItem = pcGraphicsScene->selectedItems();

        foreach (auto item, cList_SelectGraphicsItem) {
            item->setY(item->y() - 1);
        }
    }


    if(event->key() == Qt::Key_Down)
    {
        QGraphicsScene* pcGraphicsScene;
        QList<QGraphicsItem*> cList_SelectGraphicsItem;

        pcGraphicsScene = this->scene();
        cList_SelectGraphicsItem = pcGraphicsScene->selectedItems();

        foreach (auto item, cList_SelectGraphicsItem) {
            item->setY(item->y() + 1);
        }
    }


    if(event->key() == Qt::Key_Left)
    {
        QGraphicsScene* pcGraphicsScene;
        QList<QGraphicsItem*> cList_SelectGraphicsItem;

        pcGraphicsScene = this->scene();
        cList_SelectGraphicsItem = pcGraphicsScene->selectedItems();

        foreach (auto item, cList_SelectGraphicsItem) {
            item->setX(item->x() - 1);
        }
    }


    if(event->key() == Qt::Key_Right)
    {
        QGraphicsScene* pcGraphicsScene;
        QList<QGraphicsItem*> cList_SelectGraphicsItem;

        pcGraphicsScene = this->scene();
        cList_SelectGraphicsItem = pcGraphicsScene->selectedItems();

        foreach (auto item, cList_SelectGraphicsItem) {
            item->setX(item->x() + 1);
        }
    }
}

void CMy_GraphicsView::InitUi(void) noexcept
{
    qint32 nRenderHint = QPainter::Antialiasing | QPainter::TextAntialiasing;

    m_pcGraphicsScene = new QGraphicsScene(-300, -200, 600, 400);

    this->setScene(m_pcGraphicsScene);

    this->setMouseTracking(true);
    this->setRenderHint((QPainter::RenderHint)nRenderHint);

    srand(QTime::currentTime().second());
}

void CMy_GraphicsView::InitSignalSlots(void) noexcept
{

}


