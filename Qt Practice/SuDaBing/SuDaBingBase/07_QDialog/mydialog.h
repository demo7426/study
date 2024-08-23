#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>

namespace Ui {
class CMyDialog;
}

class CMyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CMyDialog(QWidget *parent = nullptr);
    ~CMyDialog();

private:
    void Connect();

private:
    Ui::CMyDialog *ui;
};

#endif // MYDIALOG_H
