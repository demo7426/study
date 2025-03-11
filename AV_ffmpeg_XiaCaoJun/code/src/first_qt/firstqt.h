#pragma once

#include <QtWidgets/QWidget>
#include "ui_firstqt.h"

class FirstQt : public QWidget
{
    Q_OBJECT

public:
    FirstQt(QWidget *parent = nullptr);
    ~FirstQt();

private:
    Ui::FirstQtClass ui;
};
