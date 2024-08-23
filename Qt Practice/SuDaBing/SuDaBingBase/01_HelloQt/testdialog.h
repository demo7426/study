#ifndef TESTDIALOG_H
#define TESTDIALOG_H

#include <QDialog>

namespace Ui {
class CTestDialog;
}

class CTestDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CTestDialog(QWidget *parent = nullptr);
    ~CTestDialog();

private:
    Ui::CTestDialog *ui;
};

#endif // TESTDIALOG_H
