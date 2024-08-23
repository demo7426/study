#ifndef USERDIFINEDQTCONTROL_WIDGET_H
#define USERDIFINEDQTCONTROL_WIDGET_H

#include <QWidget>

namespace Ui {
class UserDifinedQtControl_Widget;
}

class UserDifinedQtControl_Widget : public QWidget
{
    Q_OBJECT

public:
    explicit UserDifinedQtControl_Widget(QWidget *parent = nullptr);
    ~UserDifinedQtControl_Widget();

    //设置值
    void SetData(int Value);

    //获取值
    int GetData();
private:
    Ui::UserDifinedQtControl_Widget *ui;
};

#endif // USERDIFINEDQTCONTROL_WIDGET_H
