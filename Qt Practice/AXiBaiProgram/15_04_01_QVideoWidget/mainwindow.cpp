/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.05
描  述:	使用QVideoWidget实现视频的播放
备  注:	推荐使用Qt5进行编译
修改记录:

  1.  日期: 2024.11.05
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/
#include <QFileDialog>
#include <QUrl>

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

void MainWindow::InitUi() noexcept
{
    m_pcMediaPlayer = new QMediaPlayer(this);

    m_pcMediaPlayer->setVideoOutput(ui->videoWidget);

    ui->videoWidget->SetMediaPlayer(m_pcMediaPlayer);
}

void MainWindow::InitSignalSlots() noexcept
{
    connect(m_pcMediaPlayer, &QMediaPlayer::stateChanged, this, [this](QMediaPlayer::State _NewState){
       ui->btnPlay->setEnabled(_NewState != QMediaPlayer::State::PlayingState);
       ui->btnPause->setEnabled(_NewState == QMediaPlayer::State::PlayingState);
       ui->btnStop->setEnabled(_NewState == QMediaPlayer::State::PlayingState);
    });

    connect(m_pcMediaPlayer, &QMediaPlayer::positionChanged, this, [this](qint64 _Pos){
        m_llPosition = _Pos;

        ui->sliderPosition->setValue(_Pos);
        ui->LabRatio->setText(QString::asprintf("进度: %lld:%lld/%lld:%lld", m_llPosition / 1000 / 60,
                                                m_llPosition / 1000 % 60,m_llDuration / 1000 / 60,
                                                m_llDuration / 1000 % 60));
    });

    connect(m_pcMediaPlayer, &QMediaPlayer::durationChanged, this, [this](qint64 _Duration){
        m_llDuration = _Duration;

        ui->sliderPosition->setMaximum(_Duration);
        ui->LabRatio->setText(QString::asprintf("进度: %lld:%lld/%lld:%lld", m_llPosition / 1000 / 60,
                                                m_llPosition / 1000 % 60,m_llDuration / 1000 / 60,
                                                m_llDuration / 1000 % 60));
    });

    connect(m_pcMediaPlayer, &QMediaPlayer::stateChanged, this, [this](QMediaPlayer::State _NewState){
       ui->btnPlay->setEnabled(_NewState != QMediaPlayer::State::PlayingState);
       ui->btnPause->setEnabled(_NewState == QMediaPlayer::State::PlayingState);
       ui->btnStop->setEnabled(_NewState == QMediaPlayer::State::PlayingState);
    });

    connect(ui->btnAdd, &QPushButton::clicked, this, [this](){
       QString strFilter="wmv文件(*.wmv);;mp4文件(*.mp4);;所有文件(*.*)"; //文件过滤器
       QString strOpenFile = "";

       strOpenFile = QFileDialog::getOpenFileName(this, tr("选择单个文件"), QDir::currentPath(), strFilter);
       if(strOpenFile.isEmpty())
            return;

       m_pcMediaPlayer->setMedia(QUrl::fromLocalFile(strOpenFile));
    });

    connect(ui->btnPlay, &QPushButton::clicked, this, [this](){
       m_pcMediaPlayer->play();
    });

    connect(ui->btnPause, &QPushButton::clicked, this, [this](){
       m_pcMediaPlayer->pause();
    });

    connect(ui->btnStop, &QPushButton::clicked, this, [this](){
       m_pcMediaPlayer->stop();
    });
}


void MainWindow::on_sliderVolumn_valueChanged(int value)
{
    m_pcMediaPlayer->setVolume(value);
}

void MainWindow::on_btnSound_clicked()
{
    bool IsMute = m_pcMediaPlayer->isMuted();

    IsMute = !IsMute;
    if(IsMute)
        ui->btnSound->setIcon(QIcon(":/images/images/mute.bmp"));
    else
        ui->btnSound->setIcon(QIcon(":/images/images/volumn.bmp"));
}

void MainWindow::on_pushButton_clicked()
{
    ui->videoWidget->setFullScreen(true);
}

void MainWindow::on_sliderPosition_valueChanged(int value)
{
    if(ui->sliderPosition->isSliderDown())      //处理用户滑动进度的情况
        return;

    m_pcMediaPlayer->setPosition(value);


}
