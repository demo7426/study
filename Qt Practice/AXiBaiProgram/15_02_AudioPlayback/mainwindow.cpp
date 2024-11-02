/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.02
描  述:	实现多个音频的播放
备  注:	必须使用Qt5进行编译、Qt6对音频播放方法进行了改版
修改记录:

  1.  日期: 2024.11.02
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/
#include <QFileDialog>
#include <QListWidget>
#include <QListWidgetItem>

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
    m_cMediaPlaylist.setPlaybackMode(QMediaPlaylist::Loop);
    m_cMediaPlayer.setPlaylist(&m_cMediaPlaylist);

    this->setWindowTitle(tr("音乐播放器"));
}

void MainWindow::InitSignalSlots() noexcept
{
    connect(&m_cMediaPlayer, &QMediaPlayer::stateChanged, this, & MainWindow::On_StateChanged);
    connect(&m_cMediaPlayer, &QMediaPlayer::positionChanged, this, & MainWindow::On_PositionChanged);
    connect(&m_cMediaPlayer, &QMediaPlayer::durationChanged, this, & MainWindow::On_DurationChanged);
    connect(&m_cMediaPlaylist, &QMediaPlaylist::currentIndexChanged, this, &MainWindow::On_CurrentIndexChanged);
}

void MainWindow::on_btnAdd_clicked()
{
    QString strFilter = tr("(音频文件(*.MP3 *WMA *WAV);;MP3文件(*.MP3);;WMA文件(*.WMA);;WAV文件(*.WAV))");
    QStringList strFilePathList;

    strFilePathList = QFileDialog::getOpenFileNames(this, tr("选择多个音频文件"), QDir::currentPath(), strFilter);

    foreach (auto filePath, strFilePathList)
    {
        ui->listWidget->addItem(QFileInfo(filePath).baseName());
        m_cMediaPlaylist.addMedia(QUrl::fromLocalFile(filePath));
    }

    if(m_cMediaPlayer.state() != QMediaPlayer::State::PlayingState)
    {
        m_cMediaPlaylist.setCurrentIndex(0);
        m_cMediaPlayer.play();
    }
}

void MainWindow::On_StateChanged(QMediaPlayer::State _NewState)
{
    ui->btnPlay->setEnabled(!(_NewState == QMediaPlayer::State::PlayingState));
    ui->btnPause->setEnabled(_NewState == QMediaPlayer::State::PlayingState);
    ui->btnStop->setEnabled(_NewState == QMediaPlayer::State::PlayingState);
}

void MainWindow::On_DurationChanged(qint64 duration)
{
    qint64 llSec = 0;
    qint64 llMin = 0;

    llSec = duration / 1000 % 60;
    llMin = duration / 1000 / 60;

    m_strDuration = QString::asprintf("%lldmin:%lldsec", llMin, llSec);

    ui->LabRatio->setText(m_strPosition + "/" + m_strDuration);

    m_llCurDuration = duration;
}

void MainWindow::On_PositionChanged(qint64 position)
{
    qint64 llSec = 0;
    qint64 llMin = 0;

    llSec = position / 1000 % 60;
    llMin = position / 1000 / 60;

    m_strPosition = QString::asprintf("%lldmin:%lldsec", llMin, llSec);
    ui->LabRatio->setText(m_strPosition + "/" + m_strDuration);

    if(m_llCurDuration != 0)
        ui->sliderPosition->setValue(position * 100 / m_llCurDuration);
}

void MainWindow::On_CurrentIndexChanged(int index)
{
    if(index >= 0 && index < ui->listWidget->count())
    {
        ui->listWidget->setCurrentRow(index);
        ui->LabCurMedia->setText(ui->listWidget->currentItem()->text());
    }
    else
    {
        ui->LabCurMedia->setText("");
    }
}

void MainWindow::on_btnRemove_clicked()
{
    m_cMediaPlaylist.removeMedia(ui->listWidget->currentRow());
    delete ui->listWidget->currentItem();
}

void MainWindow::on_btnClear_clicked()
{
    m_cMediaPlaylist.clear();
    ui->listWidget->clear();
}

void MainWindow::on_btnPlay_clicked()
{
    m_cMediaPlaylist.setCurrentIndex(ui->listWidget->currentRow());
    m_cMediaPlayer.play();
}

void MainWindow::on_btnPause_clicked()
{
    m_cMediaPlayer.pause();
}

void MainWindow::on_btnStop_clicked()
{
    m_cMediaPlayer.stop();
}

void MainWindow::on_btnPrevious_clicked()
{
    m_cMediaPlaylist.previous();
}

void MainWindow::on_btnNext_clicked()
{
    m_cMediaPlaylist.next();
}

void MainWindow::on_sliderVolumn_valueChanged(int value)
{
    m_cMediaPlayer.setVolume(value);
}

void MainWindow::on_listWidget_doubleClicked(const QModelIndex &index)
{
    m_cMediaPlaylist.setCurrentIndex(index.row());
}

void MainWindow::on_btnSound_clicked()
{
    m_cMediaPlayer.setMuted(!m_cMediaPlayer.isMuted());

    if(m_cMediaPlayer.isMuted())
        ui->btnSound->setIcon(QIcon(":/images/images/mute.bmp"));
    else
        ui->btnSound->setIcon(QIcon(":/images/images/volumn.bmp"));
}
