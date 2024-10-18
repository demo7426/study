#include <QSplitter>
#include <QSurface3DSeries>
#include <QSurfaceDataArray>
#include <QSurfaceDataRow>
#include <QSurfaceDataItem>
#include <QHeightMapSurfaceDataProxy>

#include <QLinearGradient>
#include <QPainter>
#include <QColorDialog>
#include <QColor>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    InitUi();
    InitSignalSlots();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitUi(void) noexcept
{
    int nBtnGradWidth = ui->btnGrad1->width();

    Init3DData();

    //绘制按钮1的渐变色
    QLinearGradient cLinearGradient(0, 0, 100, 0);
    cLinearGradient.setColorAt(0, Qt::GlobalColor::red);
    cLinearGradient.setColorAt(0.5, Qt::GlobalColor::green);
    cLinearGradient.setColorAt(1, Qt::GlobalColor::blue);
    cLinearGradient.finalStop();

    QPixmap cPixmap(nBtnGradWidth, 20);
    QPainter cPainter(&cPixmap);

    cPainter.setBrush(QBrush(cLinearGradient));
    cPainter.drawRect(0, 0, nBtnGradWidth, 20);

    ui->btnGrad1->setIcon(QIcon(cPixmap));
    ui->btnGrad1->setIconSize(QSize(nBtnGradWidth, 20));

    //绘制按钮2的渐变色
    nBtnGradWidth = ui->btnGrad1->width();

    cLinearGradient.setColorAt(0, Qt::GlobalColor::blue);
    cLinearGradient.setColorAt(0.5, Qt::GlobalColor::green);
    cLinearGradient.setColorAt(1, Qt::GlobalColor::red);

    cPainter.eraseRect(0, 0, nBtnGradWidth, 20);                //擦除相应区域的画布
    cPainter.setBrush(QBrush(cLinearGradient));
    cPainter.drawRect(0, 0, nBtnGradWidth, 20);
    ui->btnGrad2->setIcon(QIcon(cPixmap));
    ui->btnGrad2->setIconSize(QSize(nBtnGradWidth, 20));
}

void MainWindow::InitSignalSlots(void) noexcept
{

}

void MainWindow::Init3DData()
{
    QSplitter *pcSplitter = new QSplitter(Qt::Horizontal);
    constexpr int nCount = 41;

    m_pc3DSurface = new Q3DSurface;

    pcSplitter->addWidget(ui->groupBox);
    pcSplitter->addWidget(createWindowContainer(m_pc3DSurface));
    this->setCentralWidget(pcSplitter);

    m_pc3DSurface->axisX()->setTitle(tr("东-西"));
    m_pc3DSurface->axisZ()->setTitle(tr("南-北"));
    m_pc3DSurface->axisY()->setTitle(tr("高度"));
    m_pc3DSurface->axisX()->setTitleVisible(true);
    m_pc3DSurface->axisZ()->setTitleVisible(true);
    m_pc3DSurface->axisY()->setTitleVisible(true);

    //添加数据

    QHeightMapSurfaceDataProxy *pcHeightMapSurfaceDataProxy = new QHeightMapSurfaceDataProxy(tr(":/map/map/sea.png"));
    QSurface3DSeries *pcSurface3DSeries = new QSurface3DSeries(pcHeightMapSurfaceDataProxy);

    pcSurface3DSeries->setBaseColor(Qt::GlobalColor::green);
    pcSurface3DSeries->setDrawMode(QSurface3DSeries::DrawSurface);

    m_pc3DSurface->addSeries(pcSurface3DSeries);
}

void MainWindow::on_btnBarColor_clicked()
{
    QSurface3DSeries *pcSurface3DSeries = m_pc3DSurface->seriesList()[0];
    QColor cColor = pcSurface3DSeries->baseColor();

    cColor = QColorDialog::getColor(cColor);
    if(cColor.isValid())
    {
        pcSurface3DSeries->setBaseColor(cColor);
        pcSurface3DSeries->setColorStyle(Q3DTheme::ColorStyleUniform);
    }
}

void MainWindow::on_btnGrad1_clicked()
{
    QSurface3DSeries *pcSurface3DSeries = m_pc3DSurface->seriesList()[0];
    QLinearGradient cLinearGradient(0, 0, 100, 0);

    cLinearGradient.setColorAt(0, Qt::GlobalColor::red);
    cLinearGradient.setColorAt(0.5, Qt::GlobalColor::green);
    cLinearGradient.setColorAt(1, Qt::GlobalColor::blue);
    cLinearGradient.finalStop();

    pcSurface3DSeries->setBaseGradient(cLinearGradient);
    pcSurface3DSeries->setColorStyle(Q3DTheme::ColorStyleRangeGradient);
}

void MainWindow::on_btnGrad2_clicked()
{
    QSurface3DSeries *pcSurface3DSeries = m_pc3DSurface->seriesList()[0];
    QLinearGradient cLinearGradient(0, 0, 100, 0);

    cLinearGradient.setColorAt(0, Qt::GlobalColor::blue);
    cLinearGradient.setColorAt(0.5, Qt::GlobalColor::green);
    cLinearGradient.setColorAt(1, Qt::GlobalColor::red);

    pcSurface3DSeries->setBaseGradient(cLinearGradient);
    pcSurface3DSeries->setColorStyle(Q3DTheme::ColorStyleObjectGradient);
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    m_pc3DSurface->scene()->activeCamera()->setCameraPreset(Q3DCamera::CameraPreset(index));
}

void MainWindow::on_sliderH_valueChanged(int value)
{
    Q_UNUSED(value)

    float horizontal = ui->sliderH->value();
    float vertical = ui->sliderV->value();
    float zoom = ui->sliderZoom->value();

    m_pc3DSurface->scene()->activeCamera()->setCameraPosition(horizontal, vertical, zoom);
}

void MainWindow::on_sliderV_valueChanged(int value)
{
    Q_UNUSED(value)
    on_sliderH_valueChanged(0);
}

void MainWindow::on_sliderZoom_valueChanged(int value)
{
    Q_UNUSED(value)
    on_sliderH_valueChanged(0);
}

void MainWindow::on_cBoxTheme_currentIndexChanged(int index)
{
    m_pc3DSurface->activeTheme()->setType(Q3DTheme::Theme(index));
}

void MainWindow::on_cBoxBarStyle_currentIndexChanged(int index)
{
    QSurface3DSeries *pcSurface3DSeries = m_pc3DSurface->seriesList()[0];
    pcSurface3DSeries->setMesh(QAbstract3DSeries::Mesh(index));
}

void MainWindow::on_cBoxSelectionMode_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        m_pc3DSurface->setSelectionMode(QAbstract3DGraph::SelectionFlag::SelectionNone);
        break;
    case 1:
        m_pc3DSurface->setSelectionMode(QAbstract3DGraph::SelectionFlag::SelectionItem);
        break;
    case 2:
        m_pc3DSurface->setSelectionMode(QAbstract3DGraph::SelectionFlag::SelectionRow);
        break;
    case 3:
        m_pc3DSurface->setSelectionMode(QAbstract3DGraph::SelectionFlag::SelectionColumn);
        break;
    default:
        break;
    }
}

void MainWindow::on_spinFontSize_valueChanged(int arg1)
{
    QFont cFont = m_pc3DSurface->activeTheme()->font();
    cFont.setPointSize(arg1);
    m_pc3DSurface->activeTheme()->setFont(cFont);
}

void MainWindow::on_comboDrawMode_currentIndexChanged(int index)
{
    QSurface3DSeries *pcSurface3DSeries = m_pc3DSurface->seriesList()[0];
    pcSurface3DSeries->setDrawMode(QSurface3DSeries::DrawFlags(index + 1));
}

void MainWindow::on_chkBoxBackground_stateChanged(int arg1)
{
    m_pc3DSurface->activeTheme()->setBackgroundEnabled(arg1);
}

void MainWindow::on_chkBoxGrid_stateChanged(int arg1)
{
    m_pc3DSurface->activeTheme()->setGridEnabled(arg1);
}

void MainWindow::on_chkBoxShadow_stateChanged(int arg1)
{
    if(arg1 == 0)
        m_pc3DSurface->setShadowQuality(QAbstract3DGraph::ShadowQualityNone);
    else
        m_pc3DSurface->setShadowQuality(QAbstract3DGraph::ShadowQualityMedium);
}

void MainWindow::on_chkBoxReflection_stateChanged(int arg1)
{
    m_pc3DSurface->setReflection(arg1);
}

void MainWindow::on_chkBoxSmooth_stateChanged(int arg1)
{
    QSurface3DSeries *pcSurface3DSeries = m_pc3DSurface->seriesList()[0];
    pcSurface3DSeries->setMeshSmooth(arg1);
}

void MainWindow::on_chkBoxReverse_stateChanged(int arg1)
{
    m_pc3DSurface->axisY()->setReversed(arg1);
}

void MainWindow::on_chkBoxItemLabel_stateChanged(int arg1)
{
    QSurface3DSeries *pcSurface3DSeries = m_pc3DSurface->seriesList()[0];
    pcSurface3DSeries->setItemLabelFormat("(@xLabel @yLabel @zLabel)");
    pcSurface3DSeries->setItemLabelVisible(arg1);
}

void MainWindow::on_chkBoxAxisTitle_stateChanged(int arg1)
{
    m_pc3DSurface->axisX()->setTitleVisible(arg1);
    m_pc3DSurface->axisZ()->setTitleVisible(arg1);
    m_pc3DSurface->axisY()->setTitleVisible(arg1);
}

void MainWindow::on_chkBoxAxisBackground_stateChanged(int arg1)
{
    m_pc3DSurface->activeTheme()->setLabelBackgroundEnabled(arg1);
}

