#pragma once
#include<iostream>
 
 //基类
 class QR_BaseClass
 {
 private:
    /* data */
 public:
    QR_BaseClass(/* args */);
    ~QR_BaseClass();

    int Func01();
    virtual int Func02();
    virtual int Func03() = 0;
 };

 