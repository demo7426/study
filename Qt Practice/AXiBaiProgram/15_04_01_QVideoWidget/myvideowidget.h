#ifndef CMYVIDEOWIDGET_H
#define CMYVIDEOWIDGET_H

#include <QWidget>
#include <QVideoWidget>
#include <QMediaPlayer>

class CMyVideoWidget : public QVideoWidget
{
    Q_OBJECT
public:
    explicit CMyVideoWidget(QWidget *parent = nullptr);

    void SetMediaPlayer(QMediaPlayer *_pMediaPlayer);

protected:

    void keyPressEvent(QKeyEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

private:
    QMediaPlayer *m_pcMediaPlayer = nullptr;
signals:

};

#endif // CMYVIDEOWIDGET_H
