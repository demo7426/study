#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>
#include <QSettings>

QString readSetting();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QString curLang=readSetting(); //读取语言设置

    w.m_pcTrans=new QTranslator;

    if (curLang=="EN")
        w.m_pcTrans->load("16_01_QtLinguist_en.qm");
    else
        w.m_pcTrans->load("16_01_QtLinguist_cn.qm");
    a.installTranslator(w.m_pcTrans);

    w.show();
    return a.exec();
}

QString readSetting()
{
    //从注册表读取上次设置的语言

    QString organization="WWB-Qt";                                  //用于注册表，
    QString appName="16_01_QtLinguist";                             //HKEY_CURRENT_USER/WWB-Qt/amp13_1
    QSettings  settings(organization,appName);                      //创建
    QString Language=settings.value("Language","EN").toString();    //读取 saved键的值
    return  Language;
}
