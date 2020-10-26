#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "about.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      _motor(nullptr),
      _axisChannel(1)
{
    ui->setupUi(this);
    this->InitUi();
    int axisNumber = MotorComponent::Motor::Axis();
    if (axisNumber)
    {
        _motor = new MotorComponent::Motor[axisNumber];
        for (int i = 0; i < axisNumber; ++i)
        {
            _motor[i].SetAxisChannel(i + 1);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete[] _motor;
}

void MainWindow::InitUi()
{
    int axisNumber = MotorComponent::Motor::Axis();
    for (int i = 1; i <= axisNumber; ++i)
    {
        this->ui->comboBox->addItem(QString::number(i));
    }
    if (!axisNumber)
    {
        this->ui->pushButton->setEnabled(false);
        this->ui->pushButton_2->setEnabled(false);
        this->ui->pushButton_3->setEnabled(false);
        this->ui->pushButton_4->setEnabled(false);
        this->ui->pushButton_5->setEnabled(false);
    }
    if (axisNumber)
    {
        this->ui->lineEdit_3->setText(QString::number(_motor[_axisChannel].MoveSpeed()));
        this->ui->lineEdit_4->setText(QString::number(_motor[_axisChannel].FastMoveSpeed().startingSpeed));
        this->ui->lineEdit_5->setText(QString::number(_motor[_axisChannel].FastMoveSpeed().targetSpeed));
        this->ui->lineEdit_6->setText(QString::number(_motor[_axisChannel].FastMoveSpeed().accelerationSpeed));

        this->ui->lineEdit_11->setText(QString::number(_motor[_axisChannel].InterpolationMoveSpeed()));

        this->ui->lineEdit_7->setText(QString::number(_motor[_axisChannel].InterpolationFastMoveSpeed().startingSpeed));
        this->ui->lineEdit_8->setText(QString::number(_motor[_axisChannel].InterpolationFastMoveSpeed().targetSpeed));
        this->ui->lineEdit_9->setText(QString::number(_motor[_axisChannel].InterpolationFastMoveSpeed().accelerationSpeed));

        this->ui->lineEdit_10->setText(QString::number(_motor[_axisChannel].MaxSpeed()));

        if (_motor[_axisChannel].MoveMode() == MotorComponent::MOVE_MODE::PULSE_AND_DIRECTION)
        {
            this->ui->comboBox_2->setCurrentIndex(0);
        }
        else
        {
            this->ui->comboBox_2->setCurrentIndex(1);
        }

        if (_motor[_axisChannel].OriginDetectionMode() == MotorComponent::ORIGIN_DETECTION_MODE::SWITCH_SIGNAL)
        {
            this->ui->comboBox_3->setCurrentIndex(0);
        }
        else
        {
            this->ui->comboBox_3->setCurrentIndex(1);
        }

        if (_motor[_axisChannel].OriginSignalIsValid() == MotorComponent::ORIGIN_SIGNAL_FLAG::SIGNAL_VALID)
        {
            this->ui->comboBox_4->setCurrentIndex(0);
        }
        else
        {
            this->ui->comboBox_4->setCurrentIndex(1);
        }

        if (_motor[_axisChannel].DecelerationSignalIsValid() == MotorComponent::DECELERATION_SIGNAL_FLAG::SIGNAL_VALID)
        {
            this->ui->comboBox_5->setCurrentIndex(0);
        }
        else
        {
            this->ui->comboBox_5->setCurrentIndex(1);
        }
    }
}

void MainWindow::on_actionguanyu_triggered()
{
    About about;
    about.exec();
}

void MainWindow::on_pushButton_clicked()
{
    bool ok;
    double value = this->ui->lineEdit_3->text().toDouble(&ok);
    if (ok)
    {
         _motor[_axisChannel].SetMoveSpeed(value);
         return;
    }
    QMessageBox::information(this, QString("Error"), QString("参数错误"));
}

void MainWindow::on_pushButton_2_clicked()
{
    bool ok, ok2, ok3;
    double value = this->ui->lineEdit_4->text().toDouble(&ok);
    double value2 = this->ui->lineEdit_5->text().toDouble(&ok2);
    double value3 = this->ui->lineEdit_6->text().toDouble(&ok3);
    if (ok && ok2 && ok3)
    {
        _motor[_axisChannel].SetFastMoveSpeed(value, value2, value3);
        return;
    }
    QMessageBox::information(this, QString("Error"), QString("参数错误"));
}

void MainWindow::on_pushButton_5_clicked()
{
    bool ok;
    double value = this->ui->lineEdit_11->text().toDouble(&ok);
    if (ok)
    {
        _motor[_axisChannel].SetInterpolationMoveSpeed(value);
        return;
    }
    QMessageBox::information(this, QString("Error"), QString("参数错误"));
}

void MainWindow::on_pushButton_3_clicked()
{
    bool ok, ok2, ok3;
    double value = this->ui->lineEdit_7->text().toDouble(&ok);
    double value2 = this->ui->lineEdit_8->text().toDouble(&ok2);
    double value3 = this->ui->lineEdit_9->text().toDouble(&ok3);
    if (ok && ok2 && ok3)
    {
        _motor[_axisChannel].SetInterpolationFastMoveSpeed(value, value2, value3);
        return;
    }
    QMessageBox::information(this, QString("Error"), QString("参数错误"));
}

void MainWindow::on_pushButton_4_clicked()
{
    bool ok;
    double value = this->ui->lineEdit_10->text().toDouble(&ok);
    if (ok)
    {
        _motor[_axisChannel].SetMaxSpeed(value);
        return;
    }
    QMessageBox::information(this, QString("Error"), QString("参数错误"));
}
