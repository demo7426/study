#ifndef USERWIDGET_H
#define USERWIDGET_H

#include <QWidget>

namespace Ui {
class CUserWidget;
}

class CUserWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CUserWidget(QWidget *parent = nullptr);
    ~CUserWidget();

private:
    Ui::CUserWidget *ui;
};

#endif // USERWIDGET_H
