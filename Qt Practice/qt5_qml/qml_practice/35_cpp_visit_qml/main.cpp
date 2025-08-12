#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QQmlProperty>
#include <QQmlContext>

#include "test.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    qmlRegisterType<CTest>("CTest", 1, 0, "CTest");

    engine.load(url);

    QVariant cRet;
    CTest *pcTest = new CTest(&app);

    // C++访问qml组件
    QObject* pcObj = engine.rootObjects().first();
    QObject* pcBtn = pcObj->findChild<QObject*>("g_btn_name");

    // 修改qml的属性
    QQmlProperty(pcObj, "title").write("hello window");
    QQmlProperty(pcObj, "width").write(800);
    QQmlProperty(pcObj, "height").write(600);

    QObject::connect(pcBtn, SIGNAL(sig()), pcTest, SLOT(Print()));

    QMetaObject::invokeMethod(pcBtn, "sig");
    QMetaObject::invokeMethod(pcBtn,
                              "test_arg",
                              Q_RETURN_ARG(QVariant, cRet),
                              Q_ARG(QVariant, "input parameter"));

    // 设置上下文属性值
    // engine.rootContext()->setContextProperty("g_btn_text", "确认");

    qDebug() << engine.rootObjects().size();

    return app.exec();
}
