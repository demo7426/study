/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.04
描  述:	使用QAudioRecoder实现音频的录制
备  注:	推荐使用Qt5进行编译
修改记录:

  1.  日期: 2024.11.04
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/
#include <QFileDialog>
#include <QMessageBox>
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
    m_pcAudioRecorder = new QAudioRecorder(this);
    m_pcAudioProbe = new QAudioProbe(this);

    m_pcAudioProbe->setSource(m_pcAudioRecorder);

    if (m_pcAudioRecorder->defaultAudioInput().isEmpty())
    {
        QMessageBox::critical(this, tr("警告窗口"), tr("无音频录入设备"));
        exit(0);         //无音频录入设备
    }

    foreach (auto device, m_pcAudioRecorder->audioInputs()) {
        ui->comboDevices->addItem(device);
    }

    foreach (auto codec, m_pcAudioRecorder->supportedAudioCodecs()) {
        ui->comboCodec->addItem(codec);
    }

    foreach (auto sampleRate, m_pcAudioRecorder->supportedAudioSampleRates()) {
        ui->comboSampleRate->addItem(QString::number(sampleRate));
    }

    ui->comboChannels->addItem("1");
    ui->comboChannels->addItem("2");
    ui->comboChannels->addItem("4");

    ui->sliderQuality->setRange(0, (int)QMultimedia::VeryHighQuality);
    ui->sliderQuality->setValue((int)QMultimedia::NormalQuality);

    ui->comboBitrate->addItem("32000");
    ui->comboBitrate->addItem("64000");
    ui->comboBitrate->addItem("96000");
    ui->comboBitrate->addItem("128000");
}

void MainWindow::InitSignalSlots() noexcept
{
    connect(m_pcAudioRecorder, &QAudioRecorder::stateChanged, this, &MainWindow::On_StateChanged);
    connect(m_pcAudioRecorder, &QAudioRecorder::durationChanged, this, &MainWindow::On_DurationChanged);
    connect(m_pcAudioProbe, &QAudioProbe::audioBufferProbed, this, &MainWindow::On_AudioBufferProbed);
}

void MainWindow::On_StateChanged(QMediaRecorder::State _State)
{
    ui->actRecord->setEnabled(_State != QMediaRecorder::RecordingState);
    ui->actPause->setEnabled(_State == QMediaRecorder::RecordingState);
    ui->actStop->setEnabled(_State == QMediaRecorder::RecordingState);

    ui->btnGetFile->setEnabled(_State != QMediaRecorder::RecordingState);
}

void MainWindow::On_DurationChanged(qint64 _Duration)
{
    _Duration = _Duration / 1000;

    ui->LabPassTime->setText(QString::asprintf("已录时间(min:sec): %lld:%lld", _Duration / 60, _Duration % 60));
}

void MainWindow::On_AudioBufferProbed(const QAudioBuffer &buffer)
{
    //处理探测到的缓冲区
    ui->spin_byteCount->setValue(buffer.byteCount());//缓冲区字节数
    ui->spin_duration->setValue(buffer.duration() / 1000);//缓冲区时长
    ui->spin_frameCount->setValue(buffer.frameCount());//缓冲区帧数
    ui->spin_sampleCount->setValue(buffer.sampleCount());//缓冲区采样数

    QAudioFormat audioFormat=buffer.format();//缓冲区格式
    ui->spin_channelCount->setValue(audioFormat.channelCount()); //通道数
    ui->spin_sampleSize->setValue(audioFormat.sampleSize());//采样大小
    ui->spin_sampleRate->setValue(audioFormat.sampleRate());//采样率
    ui->spin_bytesPerFrame->setValue(audioFormat.bytesPerFrame());//每帧字节数

    if (audioFormat.byteOrder()==QAudioFormat::LittleEndian)
        ui->edit_byteOrder->setText("LittleEndian");//字节序
    else
        ui->edit_byteOrder->setText("BigEndian");

    ui->edit_codec->setText(audioFormat.codec());//编码格式

    if (audioFormat.sampleType()==QAudioFormat::SignedInt)//采样点类型
        ui->edit_sampleType->setText("SignedInt");
    else if(audioFormat.sampleType()==QAudioFormat::UnSignedInt)
        ui->edit_sampleType->setText("UnSignedInt");
    else if(audioFormat.sampleType()==QAudioFormat::Float)
        ui->edit_sampleType->setText("Float");
    else
        ui->edit_sampleType->setText("Unknown");
}


void MainWindow::on_btnGetFile_clicked()
{
    QString strSaveFilePath = QFileDialog::getSaveFileName(this, tr("选择存放文件位置"), QDir::currentPath(), tr("WAV文件(*.WAV)"));

    if(strSaveFilePath.isEmpty())
        return;

    ui->editOutputFile->setText(strSaveFilePath);
}

void MainWindow::on_actRecord_triggered()
{
    if(m_pcAudioRecorder->state() == QMediaRecorder::StoppedState)
    {
        QString strSelectFilePath = ui->editOutputFile->text().trimmed();
        if(strSelectFilePath.isEmpty())
        {
            QMessageBox::warning(this, tr("警告窗口"), tr("请输入正确的文件保存路劲"));
            return;
        }

        if(QFile::exists(strSelectFilePath))
        {
            if(!QFile::remove(strSelectFilePath))
            {
                QMessageBox::warning(this, tr("警告窗口"), tr("文件已存在且无法删除"));
                return;
            }
        }

        m_pcAudioRecorder->setOutputLocation(QUrl::fromLocalFile(strSelectFilePath));
        m_pcAudioRecorder->setAudioInput(ui->comboDevices->currentText());

        QAudioEncoderSettings settings; //音频编码设置
        settings.setCodec(ui->comboCodec->currentText());//编码
        settings.setSampleRate(ui->comboSampleRate->currentText().toInt());//采样率
        settings.setBitRate(ui->comboBitrate->currentText().toInt());//比特率
        settings.setChannelCount(ui->comboChannels->currentText().toInt()); //通道数
        settings.setQuality(QMultimedia::EncodingQuality(ui->sliderQuality->value())); //品质
        if (ui->radioQuality->isChecked())//编码模式为固定品质,自动决定采样率，采样点大小
            settings.setEncodingMode(QMultimedia::ConstantQualityEncoding);
        else
            settings.setEncodingMode(QMultimedia::ConstantBitRateEncoding);//固定比特率

        m_pcAudioRecorder->setAudioSettings(settings); //音频设置
    }

    m_pcAudioRecorder->record();
}

void MainWindow::on_actPause_triggered()
{
    m_pcAudioRecorder->pause();
}

void MainWindow::on_actStop_triggered()
{
    m_pcAudioRecorder->stop();
}
