#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QWidget>

namespace Ui {
class CTestWidget;
}

class CTestWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CTestWidget(QWidget *parent = nullptr);
    ~CTestWidget();

private:
    Ui::CTestWidget *ui;
};

#endif // TESTWIDGET_H
