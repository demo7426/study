#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class CLoginDialog;
}

class CLoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CLoginDialog(QWidget *parent = nullptr);
    ~CLoginDialog();

private:
    Ui::CLoginDialog *ui;
};

#endif // LOGINDIALOG_H
