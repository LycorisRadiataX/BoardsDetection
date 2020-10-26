#include "mainwindow.h"
#include "component/MotorComponent.h"

#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
//    if (!MotorComponent::Motor::Init())
//    {
//        QMessageBox::information(nullptr, QString("Error"), QString("控制系统初始化失败"));
//        return 0;
//    }
    w.show();
    return a.exec();
}
